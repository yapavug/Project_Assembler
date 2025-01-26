#include <iostream>
#include <array>
using namespace std;

int main()
{

	array<int, 1000> data_memory = { 0 };
	
	array<int> initial_data;


	for (int i = 0; i <= initial_data[0]; ++i)
	{
		data_memory[i] = initial_data[i];
	}

	for (auto elem : data_memory)
	{
		cout << elem << endl;
	}

	return 0;
}
