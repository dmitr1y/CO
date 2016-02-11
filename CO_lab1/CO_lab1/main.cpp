#include <iostream>

using namespace std;

template <typename T>
void PrintBinNumberf(T arg);
void convert(const int, int);

int main()
{
	int a;
	char b;
	float c;
	double d = 1.2;
	long e;
	cout << "input: ";
	cin >> a;
	PrintBinNumberf(a);
	system("pause");
	return 0;
}

template<typename T>
void PrintBinNumberf(T arg)
{
	char *pointer = (char*)&arg;

	for (int i = 0; i < sizeof(T); i++, pointer++)
	{
		convert(*pointer, 2);
	}
};

void convert(const int number, int scile)
{
	if (number)
	{
		convert(number / scile, scile);
		cout << number%scile;
	}
}
