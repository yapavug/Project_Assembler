#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

// ������� ��� ������ ��������� ���� � ����
void writeMachineCodeToFile(const std::vector<std::vector<int>>& program, const std::string& filename);