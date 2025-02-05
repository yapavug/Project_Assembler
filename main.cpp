#include <iostream>
#include <array>
#include <string>
#include <map>
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

const int NONE_OPCODE = 255;


void labelsFind(const string& filename, map<string, int>& labels, string& result) {
	// Открываем файл для чтения
	ifstream file(filename);

	// Проверяем, удалось ли открыть файл
	if (!file.is_open()) {
		cerr << "Ошибка: не удалось открыть файл " << filename << endl;
		return;
	}

	int lineNumber = 0; // Счётчик строк

	// Читаем файл построчно и выводим его содержимое
	string line;
	while (getline(file, line)) {

		// Удаляем ведущие пробелы
		line.erase(0, line.find_first_not_of(' '));

		// Пропускаем пустые строки и строки, начинающиеся с #
		if (line.empty() || line[0] == '#') {
			continue;
		}

		lineNumber++; // Увеличиваем счётчик строк

		// Проверяем, является ли строка меткой
		if (line.back() == ':') { // Метка заканчивается на ':'
			string label = line.substr(0, line.size() - 1); // Убираем ':'
			labels[label] = lineNumber; // Запоминаем метку и номер строки
			--lineNumber;
		}

		result.append(line);
		result.append("\n");
	}

	// Закрываем файл
	file.close();

	// Выводим информацию о метках
	cout << "\nМетки и их строки:\n";
	for (const auto& pair : labels) {
		cout << "Метка: " << pair.first << ", Строка: " << pair.second << endl;
	}
}


// Функция для ассемблирования команды
vector<int> assembleInstruction(const vector<string>& instruction, const map<string, int>& OPCODES, const map<string, int>& REGISTERS, const map<string, int>& SPECIAL_VALUES, const map<string, int>& label_addresses) {
	// Особый случай для команды hlt
	if (instruction[0] == "hlt") {
		return { OPCODES.at("hlt"), NONE_OPCODE, NONE_OPCODE, NONE_OPCODE };
	}

	// Если это метка (строка из одного элемента)
	if (instruction.size() == 1) {
		return {}; // Возвращаем пустой вектор
	}

	// Получаем opcode
	auto opcode_it = OPCODES.find(instruction[0]);
	if (opcode_it == OPCODES.end()) {
		throw runtime_error("Неизвестная команда: " + instruction[0]);
	}
	int opcode = opcode_it->second;

	// Обрабатываем операнды
	vector<int> operands;
	for (size_t i = 1; i < instruction.size(); ++i) {
		const string& operand = instruction[i];

		// Если операнд — регистр
		auto reg_it = REGISTERS.find(operand);
		if (reg_it != REGISTERS.end()) {
			operands.push_back(reg_it->second);
		}
		// Если операнд — косвенная адресация (например, [r1])
		else if (operand.front() == '[' && operand.back() == ']') {
			string reg = operand.substr(1, operand.size() - 2);
			auto reg_indirect_it = REGISTERS.find(reg);
			if (reg_indirect_it != REGISTERS.end()) {
				operands.push_back(reg_indirect_it->second + 100); // Добавляем смещение для косвенной адресации
			}
			else {
				throw runtime_error("Неизвестный регистр: " + reg);
			}
		}
		// Если операнд — число
		else if (all_of(operand.begin(), operand.end(), ::isdigit)) {
			int value = stoi(operand);
			if (value < 0 || value > 85) {
				throw runtime_error("Непосредственное значение " + operand + " выходит за пределы диапазона (0–85)");
			}
			if (value == 0) {
				operands.push_back(value + NONE_OPCODE); // Добавляем смещение при случае, когда операнд == 0
			}
			else
			{
				operands.push_back(value + 170); // Добавляем смещение
			}
			
		}
		// Если операнд — специальное значение
		else if (SPECIAL_VALUES.find(operand) != SPECIAL_VALUES.end()) {
			operands.push_back(SPECIAL_VALUES.at(operand));
		}
		// Если операнд — метка
		else if (label_addresses.find(operand) != label_addresses.end()) {
			operands.push_back(label_addresses.at(operand));
		}
		// Если операнд — 0 (NONE_OPCODE)
		else if (operand == "0") {
			operands.push_back(NONE_OPCODE);
		}
		// Неизвестный операнд
		else {
			throw runtime_error("Неизвестный операнд: " + operand);
		}
	}

	// Дополняем операнды до 3 байт
	while (operands.size() < 3) {
		operands.push_back(NONE_OPCODE);
	}

	// Формируем машинную инструкцию
	vector<int> machineCode = { opcode };
	machineCode.insert(machineCode.end(), operands.begin(), operands.end());

	return machineCode;
}



int main()
{

	setlocale(LC_ALL, "ru");

	array<int, 2048> data_mem = { 0 };
	
	int initial_data[] = {10, 15, 21, 28, 29, 33, 88, 45, 47, 97, 99};

	for (int i = 0; i <= initial_data[0]; ++i)
	{
		data_mem[i] = initial_data[i];
	}

	//for (auto elem : data_memory)
	//{
	//	cout << elem << endl;
	//}

	map<string, int> OPCODES;
	OPCODES["mov"] = 1;
	OPCODES["add"] = 2;
	OPCODES["sub"] = 3;
	OPCODES["cmp"] = 4;
	OPCODES["je"] = 5;
	OPCODES["jle"] = 6;
	OPCODES["jmp"] = 7;
	OPCODES["dec"] = 8;
	OPCODES["hlt"] = 9;
	OPCODES["load"] = 10;



	map<string, int> REGISTERS;
	REGISTERS["r0"] = 7;
	REGISTERS["r1"] = 8;
	REGISTERS["r2"] = 9;
	REGISTERS["r3"] = 10;
	REGISTERS["r4"] = 11;
	REGISTERS["r5"] = 12;
	REGISTERS["rax"] = 13;
	REGISTERS["rbx"] = 14;
	REGISTERS["rcx"] = 15;
	REGISTERS["rdi"] = 16;

	map<string, int> SPECIAL_VALUES = { {"data_memory", 0} };

	string filePath = "NIns.txt";

	//Для хранения "очищенного" содержимого файла
	string result;

	// Для хранения меток и их строк
	map<string, int> labels;

	labelsFind(filePath, labels, result);

	cout << endl << "RESULT:\n" << result << endl;

	// вектор для хранения строк
	vector<string> lines;

	// разбиваем строку на подстроки
	size_t start = 0;
	size_t end = result.find('\n');
	while (end != string::npos) {
		lines.push_back(result.substr(start, end - start)); // добавляем строку в вектор
		start = end + 1; // переходим к следующей строке
		end = result.find('\n', start); // ищем следующий символ '\n'
	}

	// добавляем последнюю строку (если текст не заканчивается на '\n')
	if (start < result.size()) {
		lines.push_back(result.substr(start));
	}


	// Вектор для хранения машинного кода
	vector<vector<int>> program;

	// Обрабатываем каждую строку
	for (size_t i = 0; i < lines.size(); ++i) {
		string line = lines[i];
		line.erase(0, line.find_first_not_of(' ')); // Удаляем ведущие пробелы

		if (line.empty() || line[0] == '#') {
			continue; // Пропускаем пустые строки и комментарии
		}

		// Разбиваем строку на команду и операнды
		istringstream iss(line);
		vector<string> instruction;
		string token;
		while (iss >> token) {
			instruction.push_back(token);
		}

		try {
			// Ассемблируем команду
			vector<int> machineCode = assembleInstruction(instruction, OPCODES, REGISTERS, SPECIAL_VALUES, labels);
			program.push_back(machineCode); // Сохраняем машинный код
			cout << "Машинный код для строки " << i + 1 << ": ";
			for (int byte : machineCode) {
				cout << byte << " ";
			}
			cout << endl;
		}
		catch (const exception& e) {
			cerr << "Ошибка в строке " << i + 1 << ": " << e.what() << endl;
		}
	}






	return 0;
}
