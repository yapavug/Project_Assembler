#include "labelsFind.h"

void labelsFind(const std::string& filename, std::map<std::string, int>& labels, std::string& result) {
	// ��������� ���� ��� ������
	std::ifstream file(filename);

	// ���������, ������� �� ������� ����
	if (!file.is_open()) {
		std::cerr << "������: �� ������� ������� ���� " << filename << std::endl;
		return;
	}

	int lineNumber = 0; // ������� �����

	// ������ ���� ��������� � ������� ��� ����������
	std::string line;
	while (getline(file, line)) {

		// ������� ������� �������
		line.erase(0, line.find_first_not_of(' '));

		// ���������� ������ ������ � ������, ������������ � #
		if (line.empty() || line[0] == '#') {
			continue;
		}

		lineNumber++; // ����������� ������� �����

		// ���������, �������� �� ������ ������
		if (line.back() == ':') { // ����� ������������� �� ':'
			std::string label = line.substr(0, line.size() - 1); // ������� ':'
			labels[label] = lineNumber; // ���������� ����� � ����� ������
			--lineNumber;
		}

		result.append(line);
		result.append("\n");
	}

	// ��������� ����
	file.close();

	// ������� ���������� � ������
	std::cout << "\n����� � �� ������:\n";
	for (const auto& pair : labels) {
		std::cout << "�����: " << pair.first << ", ������: " << pair.second << std::endl;
	}
}
