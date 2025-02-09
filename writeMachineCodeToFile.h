#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

// Функция для записи машинного кода в файл
void writeMachineCodeToFile(const std::vector<std::vector<int>>& program, const std::string& filename);