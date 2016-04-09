//
// MainPage.xaml.cpp
// MainPage 类的实现。
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "SavaSTL.h"
#include "LoadFileData.h"
#include "STRUCT.h"
#include "ShowResult.h"
#include "RecognizeLanguage.h"
#include "WordCount.h"

#define NoText 1
#define NoTranslate 2

using namespace Print3DBraille;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI;
using namespace Windows::UI::Popups;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Xaml::Shapes;

//“空白页”项模板在 http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409 上有介绍


std::wstring stows(std::string s)
{
	std::wstring ws;
	ws.assign(s.begin(), s.end());
	return ws;
}

Platform::String^ stops(std::string s)
{
	return ref new Platform::String(stows(s).c_str());
}

std::string wstos(std::wstring ws)
{
	std::string s;
	s.assign(ws.begin(), ws.end());
	return s;
}

std::string pstos(Platform::String^ ps)
{
	return wstos(std::wstring(ps->Data()));
}

bool UnicodeToAscii(const wchar_t * szUnicode, char * szAscii)
{
	int len, i;
	if ((szUnicode == NULL) || (szAscii == NULL))
		return false;
	len = wcslen(szUnicode);
	for (i = 0;i<len + 1;i++)
		*szAscii++ = static_cast<char>(*szUnicode++);
	return true;
}


MainPage::MainPage()
{
	InitializeComponent();
}

void Print3DBraille::MainPage::DrawPoint(int x, int y,bool type)
{
	Ellipse  ^e = ref new Ellipse();
	e->Width = 15;
	e->Height = 15;
	e->StrokeThickness = 1;

	e->SetValue(View->LeftProperty, y);
	e->SetValue(View->TopProperty, x);

	Color  c0;

	c0.A = 255;
	c0.B = 255;
	c0.R = 255;
	c0.G = 255;

	Color  c1;

	c1.A = 255;
	c1.B = 0;
	c1.R = 0;
	c1.G = 0;
	
	SolidColorBrush ^ gBrush;
	
	gBrush = ref new SolidColorBrush(c1);
	e->Stroke = gBrush;

	if (type)
	{
		gBrush = ref new SolidColorBrush(c1);
	}
	else
	{
		gBrush = ref new SolidColorBrush(c0);
	}

	e->Fill = gBrush;
	View->Children->Append(e);
}
void Print3DBraille::MainPage::Draw1(int x, int y)
{
	DrawPoint(x*15, y*15, 1);
}
void Print3DBraille::MainPage::Draw0(int x, int y)
{
	DrawPoint(x*15, y*15, 0);
}

void Print3DBraille::MainPage::OnClick_Translation(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	State->Text = "正在翻译";
	
	extern vector<PrintData> V_PrintData;
	vector<PrintData>().swap(V_PrintData);
	
	LoadFileData load;

	load.GetLine(textBox->Text);
	
	if (V_PrintData.size() == 0)
	{
		Error(NoText);
	}
	else
	{
		int a = 10;
		
		View->Children->Clear();
		FuncShowResult();
		

		//Progress->SetBinding(a);
		
		//Progress->DataContext = a;
		a = 100;
		WordCount::Number = 0;	
	}
}


void Print3DBraille::MainPage::OnClick_Save(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	extern vector<PrintData> V_PrintData;
	if (V_PrintData.size() == 0)
	{
		Error(NoTranslate);
	}
	else
	{
		Save();
		WordCount::Number = 0;
	}
}
void Print3DBraille::MainPage::FuncShowResult()
{
	ShowResult Show;
	extern int  TranslateProgress;

	//Progress->Value = TranslateProgress;

	State->Text = "翻译完成";
	TranslateProgress = 0;

	int buffer[100][60];
	for (int i = 0;i < 100;i++)
	{
		for (int j = 0;j< 60;j++)
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
			buffer[y + j][x] = V_PrintData[i].WordData[j];
		}
		for (int j = 3;j < 6;j++)
		{
			buffer[y + j - 3][x + 1] = V_PrintData[i].WordData[j];
		}
	}

	for (int i = 0;i < 100;i++)
	{
		for (int j = 0;j < 50;j++)
		{
			if (buffer[i][j]==-1)
			{
				break;
			}
			else if (buffer[i][j] == 1)
			{
				Draw1(i,j);
			}
			else if(buffer[i][j] == 0)
			{
				Draw0(i,j);
			}
		}
	}
}
void Print3DBraille::MainPage::Save()
{
	State->Text = "正在创建文件";

	SavaSTL save;

	save.Save();

	extern int  GreateFileProgress;

	Progress->Value = GreateFileProgress;

	if (GreateFileProgress == 100)
	{
		State->Text = "正在保存文件请勿关闭程序";
		extern int  SaveFileProgress;
		if (SaveFileProgress == 100)
		{
			State->Text = "保存成功";
		}

	}
}
void Print3DBraille::MainPage::Error(int ErrorCode)
{
	switch (ErrorCode)
	{
	case 1:
	{
		MessageDialog^ msg = ref new MessageDialog("Please input text.", "Warring");

		// Set the command that will be invoked by default
		msg->DefaultCommandIndex = 0;

		// Set the command to be invoked when escape is pressed
		msg->CancelCommandIndex = 1;

		// Show the message dialog
		msg->ShowAsync();

		break;
	}
	case 2:
	{
		MessageDialog^ msg = ref new MessageDialog("Please input text and tick Translation.", "Warring");

		// Set the command that will be invoked by default
		msg->DefaultCommandIndex = 0;

		// Set the command to be invoked when escape is pressed
		msg->CancelCommandIndex = 1;

		// Show the message dialog
		msg->ShowAsync();

		break;
	}

	default:
		break;
	}

}
