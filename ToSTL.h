#pragma once
#include "vector"
using namespace std;
class ToSTL
{
public:
	ToSTL();
	~ToSTL();

	


	int StepX = 10;
	int StepY = 10;
	int MaxX = 25;
	int MaxY = 19;





	void GetData(bool BraiMatrix[]);

	void AddWordToPage(bool BraiMatrix[], int WordNumber);
};

