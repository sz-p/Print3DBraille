#pragma once
#include "fstream"
#include "iostream"
#include "string"

using namespace concurrency;
using namespace Platform;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace Windows::Storage::Provider;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Navigation;
using namespace std;
class SavaSTL
{
public:
	SavaSTL();
	~SavaSTL();
	string SaveFileName;
	
	
	float StepX;
	float StepY;

	void GetSaveFileName(string Name);
	void GeiFileBuffer(string  & buffer);
	void SaveZero(string  & buffer, int x, int y);
	void SaveOne(string & buffer, int x, int y);

	void OpenFile();
	void Save();
	float ComputeRealX(float Value, int x);
	float ComputeRealY(float Value, int y);
	string float_to_string(float src);
	void ReleaseCache();
};

