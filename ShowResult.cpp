#include "pch.h"
#include "ShowResult.h"
#include "STRUCT.h"
#include "MainPage.xaml.h"

using namespace Windows::UI::Popups;
using namespace Windows::UI::Xaml::Shapes;

ShowResult::ShowResult()
	: MaxLineSize(0)
	, MaxLineNumber(0)
{
}

void ShowResult::ShowBuffer(int **buffer)
{
	
	buffer = new int*[100];
	for (int i = 0;i < 100;i++)
	{
		buffer[i] = new int[60];
		for (int j = 0;j < 50;j++)
		{
			buffer[i][j] = -1;
		}
	}
	extern vector<PrintData> V_PrintData;
	for (int i = 0;i < V_PrintData.size();i++)
	{
		int x = V_PrintData[i].PageX * 2;
		int y = V_PrintData[i].PageY * 4;
		for (int j = 0;j < 3;j++)
		{
			buffer[y+j][x] = V_PrintData[i].WordData[j];
		}
		for (int j = 3;j < 6;j++)
		{
			buffer[y+j-3][x + 1] = V_PrintData[i].WordData[j];
		}
	}
}


void ShowResult::WriteBuffer()
{

}
