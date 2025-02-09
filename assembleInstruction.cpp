#include "assembleInstruction.h"


// Функция для ассемблирования команды
std::vector<int> assembleInstruction(const std::vector<std::string>& instruction, const std::map<std::string, int>& OPCODES, const std::map<std::string, int>& REGISTERS
	, const std::map<std::string, int>& SPECIAL_VALUES, const std::map<std::string, int>& label_addresses) {
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
		throw std::runtime_error("Неизвестная команда: " + instruction[0]);
	}
	int opcode = opcode_it->second;

	// Обрабатываем операнды
	std::vector<int> operands;
	for (size_t i = 1; i < instruction.size(); ++i) {
		const std::string& operand = instruction[i];

		// Если операнд — регистр
		auto reg_it = REGISTERS.find(operand);
		if (reg_it != REGISTERS.end()) {
			operands.push_back(reg_it->second);
		}
		// Если операнд — косвенная адресация (например, [r1])
		else if (operand.front() == '[' && operand.back() == ']') {
			std::string reg = operand.substr(1, operand.size() - 2);
			auto reg_indirect_it = REGISTERS.find(reg);
			if (reg_indirect_it != REGISTERS.end()) {
				operands.push_back(reg_indirect_it->second + 100); // Добавляем смещение для косвенной адресации
			}
			else {
				throw std::runtime_error("Неизвестный регистр: " + reg);
			}
		}
		// Если операнд — число
		else if (all_of(operand.begin(), operand.end(), ::isdigit)) {
			int value = stoi(operand);
			if (value < 0 || value > 85) {
				throw std::runtime_error("Непосредственное значение " + operand + " выходит за пределы диапазона (0–85)");
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
			throw std::runtime_error("Неизвестный операнд: " + operand);
		}
	}

	// Дополняем операнды до 3 байт
	while (operands.size() < 3) {
		operands.push_back(NONE_OPCODE);
	}

	// Формируем машинную инструкцию
	std::vector<int> machineCode = { opcode };
	machineCode.insert(machineCode.end(), operands.begin(), operands.end());

	return machineCode;
}