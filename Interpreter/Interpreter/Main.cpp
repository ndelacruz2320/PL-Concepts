#include <fstream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

unsigned int globalCounter = 0; //using global variable to keep track of where I am in the language, used mainly with commands vector

int Input(vector<string> c)
{
	int num;
	globalCounter++;
	cout << "Enter a integer to place into register " << c[globalCounter] << ":\n";
	cin >> num;
	return num;
}

int Add(vector<int> r, vector<string> c)
{
	int num;
	globalCounter++;
	num = r[stoi(c[globalCounter]) - 1] + r[stoi(c[globalCounter + 1]) - 1];
	globalCounter++;
	return num;	
}

bool ifLess(vector<int> r, vector<string> c)
{
	if (r[stoi(c[globalCounter]) - 1] < r[stoi(c[globalCounter + 1]) - 1])
	{
		globalCounter++;
		return true;
	}
	else
	{
		globalCounter++;
		return false;
	}
}

int main()
{
	string next, theFile;
	vector<string> commands;
	vector<int> registers;

	ifstream inFile;
	cout << "Enter the file name you desire to read from: ";
	cin >> theFile;
	inFile.open(theFile);

	if (!inFile) 
	{
		cerr << "Unable to open file datafile.txt";
		exit(1);
	}

	while (inFile >> next) //All commands in a vector
	{
		commands.push_back(next);
	}

	for (int i = 0; i < 100; i++) //Load registers
	{
		registers.push_back(i);
	}

	while (globalCounter < commands.size() - 1)
	{
		string action = commands[globalCounter];//Every read input here should be a keyword command

		if (action == "INP")
		{
			int toAssign = Input(commands);
			int loc = stoi(commands[globalCounter]); //converts the string to an int
			registers[loc - 1] = toAssign;
			globalCounter++;
		}
		if (action == "ADD")
		{
			globalCounter++;
			int loc = stoi(commands[globalCounter]);
			registers[loc - 1] = Add(registers, commands);
			globalCounter++;
		}
		if (action == "PRT")
		{
			globalCounter++;
			cout << registers[stoi(commands[globalCounter]) - 1] << "\n";
			globalCounter++;
		}
		if (action == "SET")
		{
			globalCounter++;
			int loc = stoi(commands[globalCounter]) - 1;
			globalCounter++;
			int toAssign = stoi(commands[globalCounter]);
			registers.at(loc) = toAssign;
			globalCounter++;
		}
		if (action == "IFL")
		{
			globalCounter++;
			bool jump = ifLess(registers,commands);
			globalCounter++;

			string label = commands[globalCounter];

				if (jump)
				{
					for (int i = 0; i < commands.size(); i++)
					{
						if (commands[i] == "LBL" && commands[i + 1] == label)
						{
							globalCounter = i;
						}
					}
					globalCounter = globalCounter + 2;
				}
				else
				{
					globalCounter++;
				}
			
		}
		if (action == "JMP") //unconditional jump
		{
			globalCounter++;
			string label = commands[globalCounter];
			
				for (int i = 0; i < commands.size(); i++)
				{
					if (commands[i] == "LBL" && commands[i + 1] == label)
					{
						globalCounter = i;
					}
				}
				globalCounter = globalCounter + 2;		
		}
		if (action == "LBL")
		{
			globalCounter = globalCounter + 2;
		}
	}

	int holdopen;
	cin >> holdopen;
}