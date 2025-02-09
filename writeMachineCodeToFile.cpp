#include "writeMachineCodeToFile.h"

// ������� ��� ������ ��������� ���� � ����
void writeMachineCodeToFile(const std::vector<std::vector<int>>& program, const std::string& filename) {
	std::ofstream file(filename); // ��������� ���� ��� ������

	if (!file.is_open()) {
		std::cerr << "������: �� ������� ������� ���� " << filename << " ��� ������." << std::endl;
		return;
	}

	// �������� �� ���� �������� �����������
	for (const auto& instruction : program) {
		// ���������� ������ ���������� (��������, �����)
		if (instruction.empty()) {
			continue;
		}

		// ���������� ������ ���� ���������� � ����
		for (size_t i = 0; i < instruction.size(); ++i) {
			file << instruction[i];
			if (i < instruction.size() - 1) {
				file << " "; // ��������� ������ ����� �������
			}
		}
		file << std::endl; // ��������� �� ����� ������ ��� ��������� ����������
	}

	file.close(); // ��������� ����
	std::cout << "�������� ��� ������� ������� � ���� " << filename << std::endl;
}
