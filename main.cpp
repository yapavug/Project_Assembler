#include <iostream>
#include <array>
#include <sstream>

#include "labelsFind.h"
#include "assembleInstruction.h"
#include "writeMachineCodeToFile.h"


int main()
{

	setlocale(LC_ALL, "ru");

	std::array<int, 2048> data_mem = { 0 };
	
	int initial_data[] = {10, 15, 21, 28, 29, 33, 88, 45, 47, 97, 99};

	for (int i = 0; i <= initial_data[0]; ++i)
	{
		data_mem[i] = initial_data[i];
	}

	//for (auto elem : data_mem)
	//{
	//	cout << elem << endl;
	//}

	std::map<std::string, int> OPCODES;
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



	std::map<std::string, int> REGISTERS;
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

	std::map<std::string, int> SPECIAL_VALUES = { {"data_memory", 0} };

	std::string filePath = "NIns.txt";

	//Для хранения "очищенного" содержимого файла
	std::string result;

	// Для хранения меток и их строк
	std::map<std::string, int> labels;

	labelsFind(filePath, labels, result);

	std::cout << std::endl << "RESULT:\n" << result << std::endl;

	// вектор для хранения строк
	std::vector<std::string> lines;

	// разбиваем строку на подстроки
	size_t start = 0;
	size_t end = result.find('\n');
	while (end != std::string::npos) {
		lines.push_back(result.substr(start, end - start)); // добавляем строку в вектор
		start = end + 1; // переходим к следующей строке
		end = result.find('\n', start); // ищем следующий символ '\n'
	}

	// добавляем последнюю строку (если текст не заканчивается на '\n')
	if (start < result.size()) {
		lines.push_back(result.substr(start));
	}


	// Вектор для хранения машинного кода
	std::vector<std::vector<int>> program;

	// Обрабатываем каждую строку
	for (size_t i = 0; i < lines.size(); ++i) {
		std::string line = lines[i];
		line.erase(0, line.find_first_not_of(' ')); // Удаляем ведущие пробелы

		if (line.empty() || line[0] == '#') {
			continue; // Пропускаем пустые строки и комментарии
		}

		// Разбиваем строку на команду и операнды
		std::istringstream iss(line);
		std::vector<std::string> instruction;
		std::string token;
		while (iss >> token) {
			instruction.push_back(token);
		}

		try {
			// Ассемблируем команду
			std::vector<int> machineCode = assembleInstruction(instruction, OPCODES, REGISTERS, SPECIAL_VALUES, labels);
			program.push_back(machineCode); // Сохраняем машинный код
			std::cout << "Машинный код для строки " << i + 1 << ": ";
			for (int byte : machineCode) {
				std::cout << byte << " ";
			}
			std::cout << std::endl;
		}
		catch (const std::exception& e) {
			std::cerr << "Ошибка в строке " << i + 1 << ": " << e.what() << std::endl;
		}
	}

	writeMachineCodeToFile(program, "machine_code.txt");

	return 0;
}
