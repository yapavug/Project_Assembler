#pragma once

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>

const int NONE_OPCODE = 255;

// Функция для ассемблирования команды
std::vector<int> assembleInstruction(const std::vector<std::string>& instruction, const std::map<std::string, int>& OPCODES, const std::map<std::string, int>& REGISTERS
	, const std::map<std::string, int>& SPECIAL_VALUES, const std::map<std::string, int>& label_addresses);
