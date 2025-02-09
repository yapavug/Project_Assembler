#include "labelsFind.h"

void labelsFind(const std::string& filename, std::map<std::string, int>& labels, std::string& result) {
	// Открываем файл для чтения
	std::ifstream file(filename);

	// Проверяем, удалось ли открыть файл
	if (!file.is_open()) {
		std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
		return;
	}

	int lineNumber = 0; // Счётчик строк

	// Читаем файл построчно и выводим его содержимое
	std::string line;
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
			std::string label = line.substr(0, line.size() - 1); // Убираем ':'
			labels[label] = lineNumber; // Запоминаем метку и номер строки
			--lineNumber;
		}

		result.append(line);
		result.append("\n");
	}

	// Закрываем файл
	file.close();

	// Выводим информацию о метках
	std::cout << "\nМетки и их строки:\n";
	for (const auto& pair : labels) {
		std::cout << "Метка: " << pair.first << ", Строка: " << pair.second << std::endl;
	}
}
