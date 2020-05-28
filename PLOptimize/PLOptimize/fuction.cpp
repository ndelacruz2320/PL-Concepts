#include "function.h"

int op(vector<unsigned int> * theVec)
{
	//you may only modify the code in this fuction; you may not inline assembly instructions as they are most likely not cross compatible. 
	//what i have placed here is a copy of the unoptimzied function

	int size = theVec->size(); //Minimize the vector function call
	int amountToRemove = 0;
	unsigned int i = 0; //removed call stacks by removing new creation of unsigned ints
	unsigned int * vecPoint = theVec->data(); //again minimizing fucntion calls by using the  [ ] operator
	int result = 0;

	for (i = 0; i < size -2; i+= 2)
	{
			result += (vecPoint[i] << 1) - (((vecPoint[i] << 1) >> 12) << 12) + 4 + ((vecPoint[i + 1] << 1) + 1 + (vecPoint[i] << 1) - (((vecPoint[i] << 1) >> 12) << 12) + 1) - ((((vecPoint[i + 1] << 1) >> 12)) << 12);
	}

	//manually accessing last two indexes where we did not calculate

	result += ((vecPoint[size - 1] << 1) - (((vecPoint[size - 1] << 1) >> 12) << 12) + 4) + (vecPoint[size - 2] << 1) - (((vecPoint[size - 2] << 1) >> 12) << 12);

	return result;

}