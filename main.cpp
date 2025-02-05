#include <iostream>
#include <array>
#include <string>
#include <map>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

const int NPNE_OPCODE = 255;



void printAsmFile(const string& filename) {
	// Открываем файл для чтения
	ifstream file(filename);

	// Проверяем, удалось ли открыть файл
	if (!file.is_open()) {
		cerr << "Ошибка: не удалось открыть файл " << filename << endl;
		return;
	}

	// Для хранения меток и их строк
	map<string, int> labels;
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

		cout << line << endl;
	}

	// Закрываем файл
	file.close();

	// Выводим информацию о метках
	cout << "\nМетки и их строки:\n";
	for (const auto& pair : labels) {
		cout << "Метка: " << pair.first << ", Строка: " << pair.second << endl;
	}
}



int main()
{

	setlocale(LC_ALL, "ru");

	array<int, 2048> data_memory = { 0 };
	
	int initial_data[] = {10, 15, 21, 28, 29, 33, 88, 45, 47, 97, 99};

	for (int i = 0; i <= initial_data[0]; ++i)
	{
		data_memory[i] = initial_data[i];
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

	string filePath = "NIns.txt";
	printAsmFile(filePath);





	return 0;
}
