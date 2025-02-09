#include "writeMachineCodeToFile.h"

// Функция для записи машинного кода в файл
void writeMachineCodeToFile(const std::vector<std::vector<int>>& program, const std::string& filename) {
	std::ofstream file(filename); // Открываем файл для записи

	if (!file.is_open()) {
		std::cerr << "Ошибка: не удалось открыть файл " << filename << " для записи." << std::endl;
		return;
	}

	// Проходим по всем машинным инструкциям
	for (const auto& instruction : program) {
		// Пропускаем пустые инструкции (например, метки)
		if (instruction.empty()) {
			continue;
		}

		// Записываем каждый байт инструкции в файл
		for (size_t i = 0; i < instruction.size(); ++i) {
			file << instruction[i];
			if (i < instruction.size() - 1) {
				file << " "; // Добавляем пробел между байтами
			}
		}
		file << std::endl; // Переходим на новую строку для следующей инструкции
	}

	file.close(); // Закрываем файл
	std::cout << "Машинный код успешно записан в файл " << filename << std::endl;
}
