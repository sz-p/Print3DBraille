//
// MainPage.xaml.h
// MainPage 类的声明。
//

#pragma once

#include "MainPage.g.h"

namespace Print3DBraille
{
	/// <summary>
	/// 可用于自身或导航至 Frame 内部的空白页。
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

	private:
		void OnClick_Translation(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnClick_Save(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	public:
		void Error(int ErrorCode);
		void DrawPoint(int x, int y,bool type);
		void Draw1(int x,int y);
		void Draw0(int x,int y);
		void Save();
		void FuncShowResult();
	};
}
