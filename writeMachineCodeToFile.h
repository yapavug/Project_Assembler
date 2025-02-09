#pragma once
#ifndef _WRITEMACHINECODETOFILE_H_
#define _WRITEMACHINECODETOFILE_H_

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

// Функция для записи машинного кода в файл
void writeMachineCodeToFile(const std::vector<std::vector<int>>& program, const std::string& filename);

#endif // !_WRITEMACHINECODETOFILE_H_
