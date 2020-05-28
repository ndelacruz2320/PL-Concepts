#include <iostream>
#include <chrono>
#include <vector>

#include "function.h"

using namespace std;

int  original(vector<unsigned int> * theVec)
{

	for (unsigned int i = 0; i < theVec->size(); i++)
	{
		theVec->at(i) = theVec->at(i) * 2;
	}

	for (unsigned int i = 0; i < theVec->size(); i++)
	{

		if (theVec->at(i) > 4095)
		{
			int amountToRemove = theVec->at(i) / 4096;
			amountToRemove = amountToRemove * 4096;
			theVec->at(i) = theVec->at(i) - amountToRemove;
		}
	}

	for (unsigned int i = 0; i < theVec->size(); i++)
	{
		theVec->at(i) = theVec->at(i) + 1;
	}

	for (unsigned int i = 1; i < theVec->size() - 2; i += 2)
	{
		theVec->at(i) = theVec->at(i) + theVec->at(i - 1);
	}
	for (unsigned int i = 0; i < theVec->size(); i++)
	{
		if (theVec->at(i) % 2 == 0)
			theVec->at(i) = theVec->at(i) + 1;
	}
	for (unsigned int i = 0; i < theVec->size(); i++)
	{
		theVec->at(i) = theVec->at(i) + 1;
	}

	int result = 0;
	for (unsigned int i = 0; i < theVec->size(); i++)
	{
		result += theVec->at(i);
	}
	return result;
}








int main(int argc, char ** argv)
{
	int a, b;

	srand(clock());

	long long originaltime = 0, optime = 0;

	for (int z = 0; z < 5; z++)
	{

		int amountOfData = 10000 + rand() % 10000;
		if (amountOfData % 2 == 1)
		{
			amountOfData++;
		}

		vector<unsigned int> data;
		for (int i = 0; i < amountOfData; i++)
		{
			data.push_back(rand());
		}

		vector<unsigned int> data2 = data;



		//time counting from https://www.techiedelight.com/measure-elapsed-time-program-chrono-library/
		auto start = chrono::steady_clock::now();

		a = original(&data);

		auto end = chrono::steady_clock::now();
		//cout << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " ns" << endl;
		originaltime += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
		start = chrono::steady_clock::now();


		b = op(&data2);

		end = chrono::steady_clock::now();


		optime += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
		//cout << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " ns" << endl;

		if (a != b)
		{
			cout << "answers do not match\n";
		}
	}


	cout << originaltime << endl;
	cout << optime << endl;
	cout << optime / (originaltime*1.0) << "\n";

	std::cin.ignore();
}