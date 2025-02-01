#include <iostream>
#include <array>
#include <string>
#include <map>
#include <fstream>
#include <algorithm>
#include <vector>
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


// Функция для разбиения строки на массив строк
vector<string> splitIntoLines(const string& content) {
	vector<string> lines;
	size_t start = 0;  // Начальная позиция для поиска подстроки
	size_t end = content.find('\n');  // Ищем первый символ новой строки

	while (end != string::npos) {
		// Извлекаем подстроку от start до end
		string line = content.substr(start, end - start);
		if (!line.empty()) {  // Пропускаем пустые строки
			lines.push_back(line);
		}
		start = end + 1;  // Перемещаем start на позицию после '\n'
		end = content.find('\n', start);  // Ищем следующий символ новой строки
	}

	// Добавляем последнюю строку, если она есть
	if (start < content.length()) {
		string line = content.substr(start);
		if (!line.empty()) {
			lines.push_back(line);
		}
	}

	return lines;
}



map<string, int> findLabels(const string& fileContent) {
	


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

	//// Находим метки в файле
	//map<string, int> labels = findLabels(fileContent);

	//// Выводим найденные метки и их позиции
	//for (const auto& label : labels) {
	//	cout << "Метка: " << label.first << ", Строка: " << label.second << endl;
	//}

	return 0;
}
