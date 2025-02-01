#include <iostream>
#include <array>
#include <string>
#include <map>
#include <fstream>
#include <algorithm>
using namespace std;

const int NPNE_OPCODE = 255;

string readFile(const string& filePath) {
	ifstream file(filePath);  // Открываем файл для чтения
	string content;

	if (file.is_open()) {
		// Читаем содержимое файла в строку
		string line;
		while (getline(file, line)) {
			// Удаляем двоеточия из строки
			//line.erase(remove(line.begin(), line.end(), ':'), line.end());

			// Пропускаем пустые строки
			if (!line.empty()) {
				content += line + "\n";  // Добавляем строку в content
			}
		}
		file.close();  // Закрываем файл
	}
	else {
		cerr << "Не удалось открыть файл: " << filePath << endl;
	}
	return content;
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

	for (auto elem : data_memory)
	{
		cout << elem << endl;
	}

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

	std::string filePath = "NIns.txt";
	std::string fileContent = readFile(filePath);

	std::cout << "Содержимое файла:\n" << fileContent << std::endl;



	return 0;
}
