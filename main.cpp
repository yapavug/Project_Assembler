#include <iostream>
#include <array>
#include <string>
#include <map>
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

const int NONE_OPCODE = 255;


void labelsFind(const string& filename, map<string, int>& labels, string& result) {
	// ��������� ���� ��� ������
	ifstream file(filename);

	// ���������, ������� �� ������� ����
	if (!file.is_open()) {
		cerr << "������: �� ������� ������� ���� " << filename << endl;
		return;
	}

	int lineNumber = 0; // ������� �����

	// ������ ���� ��������� � ������� ��� ����������
	string line;
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
			string label = line.substr(0, line.size() - 1); // ������� ':'
			labels[label] = lineNumber; // ���������� ����� � ����� ������
			--lineNumber;
		}

		result.append(line);
		result.append("\n");
	}

	// ��������� ����
	file.close();

	// ������� ���������� � ������
	cout << "\n����� � �� ������:\n";
	for (const auto& pair : labels) {
		cout << "�����: " << pair.first << ", ������: " << pair.second << endl;
	}
}


// ������� ��� ��������������� �������
vector<int> assembleInstruction(const vector<string>& instruction, const map<string, int>& OPCODES, const map<string, int>& REGISTERS, const map<string, int>& SPECIAL_VALUES, const map<string, int>& label_addresses) {
	// ������ ������ ��� ������� hlt
	if (instruction[0] == "hlt") {
		return { OPCODES.at("hlt"), NONE_OPCODE, NONE_OPCODE, NONE_OPCODE };
	}

	// ���� ��� ����� (������ �� ������ ��������)
	if (instruction.size() == 1) {
		return {}; // ���������� ������ ������
	}

	// �������� opcode
	auto opcode_it = OPCODES.find(instruction[0]);
	if (opcode_it == OPCODES.end()) {
		throw runtime_error("����������� �������: " + instruction[0]);
	}
	int opcode = opcode_it->second;

	// ������������ ��������
	vector<int> operands;
	for (size_t i = 1; i < instruction.size(); ++i) {
		const string& operand = instruction[i];

		// ���� ������� � �������
		auto reg_it = REGISTERS.find(operand);
		if (reg_it != REGISTERS.end()) {
			operands.push_back(reg_it->second);
		}
		// ���� ������� � ��������� ��������� (��������, [r1])
		else if (operand.front() == '[' && operand.back() == ']') {
			string reg = operand.substr(1, operand.size() - 2);
			auto reg_indirect_it = REGISTERS.find(reg);
			if (reg_indirect_it != REGISTERS.end()) {
				operands.push_back(reg_indirect_it->second + 100); // ��������� �������� ��� ��������� ���������
			}
			else {
				throw runtime_error("����������� �������: " + reg);
			}
		}
		// ���� ������� � �����
		else if (all_of(operand.begin(), operand.end(), ::isdigit)) {
			int value = stoi(operand);
			if (value < 0 || value > 85) {
				throw runtime_error("���������������� �������� " + operand + " ������� �� ������� ��������� (0�85)");
			}
			if (value == 0) {
				operands.push_back(value + NONE_OPCODE); // ��������� �������� ��� ������, ����� ������� == 0
			}
			else
			{
				operands.push_back(value + 170); // ��������� ��������
			}
			
		}
		// ���� ������� � ����������� ��������
		else if (SPECIAL_VALUES.find(operand) != SPECIAL_VALUES.end()) {
			operands.push_back(SPECIAL_VALUES.at(operand));
		}
		// ���� ������� � �����
		else if (label_addresses.find(operand) != label_addresses.end()) {
			operands.push_back(label_addresses.at(operand));
		}
		// ���� ������� � 0 (NONE_OPCODE)
		else if (operand == "0") {
			operands.push_back(NONE_OPCODE);
		}
		// ����������� �������
		else {
			throw runtime_error("����������� �������: " + operand);
		}
	}

	// ��������� �������� �� 3 ����
	while (operands.size() < 3) {
		operands.push_back(NONE_OPCODE);
	}

	// ��������� �������� ����������
	vector<int> machineCode = { opcode };
	machineCode.insert(machineCode.end(), operands.begin(), operands.end());

	return machineCode;
}



int main()
{

	setlocale(LC_ALL, "ru");

	array<int, 2048> data_mem = { 0 };
	
	int initial_data[] = {10, 15, 21, 28, 29, 33, 88, 45, 47, 97, 99};

	for (int i = 0; i <= initial_data[0]; ++i)
	{
		data_mem[i] = initial_data[i];
	}

	//for (auto elem : data_memory)
	//{
	//	cout << elem << endl;
	//}

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

	map<string, int> SPECIAL_VALUES = { {"data_memory", 0} };

	string filePath = "NIns.txt";

	//��� �������� "����������" ����������� �����
	string result;

	// ��� �������� ����� � �� �����
	map<string, int> labels;

	labelsFind(filePath, labels, result);

	cout << endl << "RESULT:\n" << result << endl;

	// ������ ��� �������� �����
	vector<string> lines;

	// ��������� ������ �� ���������
	size_t start = 0;
	size_t end = result.find('\n');
	while (end != string::npos) {
		lines.push_back(result.substr(start, end - start)); // ��������� ������ � ������
		start = end + 1; // ��������� � ��������� ������
		end = result.find('\n', start); // ���� ��������� ������ '\n'
	}

	// ��������� ��������� ������ (���� ����� �� ������������� �� '\n')
	if (start < result.size()) {
		lines.push_back(result.substr(start));
	}


	// ������ ��� �������� ��������� ����
	vector<vector<int>> program;

	// ������������ ������ ������
	for (size_t i = 0; i < lines.size(); ++i) {
		string line = lines[i];
		line.erase(0, line.find_first_not_of(' ')); // ������� ������� �������

		if (line.empty() || line[0] == '#') {
			continue; // ���������� ������ ������ � �����������
		}

		// ��������� ������ �� ������� � ��������
		istringstream iss(line);
		vector<string> instruction;
		string token;
		while (iss >> token) {
			instruction.push_back(token);
		}

		try {
			// ������������ �������
			vector<int> machineCode = assembleInstruction(instruction, OPCODES, REGISTERS, SPECIAL_VALUES, labels);
			program.push_back(machineCode); // ��������� �������� ���
			cout << "�������� ��� ��� ������ " << i + 1 << ": ";
			for (int byte : machineCode) {
				cout << byte << " ";
			}
			cout << endl;
		}
		catch (const exception& e) {
			cerr << "������ � ������ " << i + 1 << ": " << e.what() << endl;
		}
	}






	return 0;
}
