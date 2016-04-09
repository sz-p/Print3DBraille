//
// App.xaml.cpp
// App 类的实现。
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "STRUCT.h"
#include "vector"
#include "string"
#include "fstream"
#include "iostream"
#include "InitDatabase.h"

using namespace Print3DBraille;

using namespace std;
using namespace Platform;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

using namespace concurrency;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace Windows::Storage::Provider;

vector <DataBase> m_NumLib;

vector <DataBase> m_EnglishLib;

vector <DataBase> m_SymbolLib;

vector <PYData> m_PinYinLib;

vector <ChineseToCodeData> m_Chinese2CodeLib;

vector <string> m_Code2PYLib;

vector <TriangularFacet> m_V_ZeroLump;

vector <TriangularFacet> m_V_OneLump;

vector <PrintData> V_PrintData;

int TranslateProgress;

int GreateFileProgress;

int SaveFileProgress;

float GetVertex(string buffer, char type, char key)
{

	int length = 0;


	int start;
	int end;


	string buffer2;


	switch (key)
	{
	case 'x': start = 1;end = 2; break;
	case 'y': start = 2;end = 3; break;
	case 'z': start = 3;end = 4; break;
	default:
		break;
	}

	if (type == 'f')
	{
		if (key == 'x')
		{
			start = 2;end = 3;
		}
		if (key == 'y')
		{
			start = 3;end = 4;
		}
		if (key == 'z')
		{
			start = 4;end = 5;
		}
	}
	if (type == 'v')
	{
		if (key == 'x')
		{
			start = 1;end = 2;
		}
		if (key == 'y')
		{
			start = 2;end = 3;
		}
		if (key == 'z')
		{
			start = 3;end = 4;
		}
	}


	int n = 0;
	for (int i = 0; i < buffer.length();i++)
	{
		if (buffer[i] == ' ')
		{
			n = n + 1;
		}
		if (n == start)
		{
			buffer2.push_back(buffer[i + 1]);
			length++;
		}
		if (n == end || i == buffer.length() - 1)
		{
			buffer2.erase(buffer2.length() - 1, 1);
			float number = strtod(buffer2.c_str(), NULL);
			return number;
		}
	}
}

void GetZeorLump()
{
	float ZeroFacetX[] = { 0,0,0,0,-0,0,1,1,-0,0,-1,-1};
	float ZeroFacetY[] = { -0,0,0,0,-1,-1,0,0,1,1,0,0, };
	float ZeroFacetZ[] = { -1,-1,1,1,0,0,0,0,0,0,0,0, };

	float ZerovertexX1[] = { -1,1,-1,1,-1,1,1,1,1,-1,-1,-1, };
	float ZerovertexY1[] = { -1,1,-1,1,-1,-1,-1,1,1,1,1,-1, };
	float ZerovertexZ1[] = { 0,0,2,2,0,2,0,2,0,2,0,2, };

	float ZerovertexX2[] = { -1,1,1,-1,1,-1,1,1,-1,1,-1,-1, };
	float ZerovertexY2[] = { 1,-1,-1,1,-1,-1,1,-1,1,1,-1,1, };
	float ZerovertexZ2[] = { 0,0,2,2,0,2,0,2,0,2,0,2, };

	float ZerovertexX3[] = { 1,-1,1,-1,1,-1,1,1,-1,1,-1,-1, };
	float ZerovertexY3[] = { 1,-1,1,-1,-1,-1,1,-1,1,1,-1,1, };
	float ZerovertexZ3[] = { 0,0,2,2,2,0,2,0,2,0,2,0, };

	for (int i = 0;i < 12;i++)
	{
		TriangularFacet tf;

		tf.facetX = ZeroFacetX[i];
		tf.facetY = ZeroFacetY[i];
		tf.facetZ = ZeroFacetZ[i];

		tf.vertexX1 = ZerovertexX1[i];
		tf.vertexY1 = ZerovertexY1[i];
		tf.vertexZ1 = ZerovertexZ1[i];

		tf.vertexX2 = ZerovertexX2[i];
		tf.vertexY2 = ZerovertexY2[i];
		tf.vertexZ2 = ZerovertexZ2[i];

		tf.vertexX3 = ZerovertexX3[i];
		tf.vertexY3 = ZerovertexY3[i];
		tf.vertexZ3 = ZerovertexZ3[i];

		m_V_ZeroLump.push_back(tf);
	}
}

void GetOneLump()
{
	float OneFacetX[] = { 0,0,0,0,-0,0,1,1,-0,0,-1,-1,0.184824,0.533382,0.057175,-0.0243925,0.807302,0.517682,0.353779,-0.041802,-0.196368,0.948576,0.864707,0.678413,0.457923,0.248316,-0.116665,-0.25417,-0.369648,-0.50899,-0.11435,-0.50899,-0.610933,-0.47588,-0.707559,-0.47588,-0.610933,-0.694406,-0.748042,-0.92673,-0.915847,-0.92673,-0.748042,-0.694406,0.184824,-0.0243925,0.057175,0.533382,-0.196368,-0.041802,0.353779,0.517682,0.807302,-0.25417,-0.116665,0.248316,0.457923,0.678413,0.864707,0.948576,0,0,0,-0,-0,-0,0,0,0,0,0,0, };
	float OneFacetY[] = { -0,0,0,0,-1,-1,0,0,1,1,0,0,0.320124,0.279782,0.09903,0.601814,0.239349,0.250615,0.612764,0.573633,0.818818,0.25417,0.364525,0.678413,0.793147,0.92673,0.931121,0.948576,0,0.322031,0,-0.322031,0.579469,0.323018,0,-0.323018,-0.579469,0.694406,0.566595,0.248316,0,-0.248316,-0.566595,-0.694406,-0.320124,-0.601814,-0.09903,-0.279782,-0.818818,-0.573634,-0.612764,-0.250615,-0.239349,-0.948576,-0.931121,-0.92673,-0.793147,-0.678413,-0.364525,-0.25417,0,0,0,0,0,0,-0,-0,0,0,0,0, };
	float OneFacetZ[] = { -1,-1,1,1,0,0,0,0,0,0,0,0,0.929172,0.798264,0.993441,0.798264,0.539422,0.818045,0.706655,0.818045,0.539422,0.188683,0.345549,0.281977,0.401528,0.281977,0.345549,0.188683,0.929172,0.798264,0.993441,0.798264,0.539422,0.818045,0.706655,0.818045,0.539422,0.188683,0.345549,0.281977,0.401528,0.281977,0.345549,0.188683,0.929172,0.798264,0.993441,0.798264,0.539422,0.818045,0.706655,0.818045,0.539422,0.188683,0.345549,0.281977,0.401528,0.281977,0.345549,0.188683,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, };
	
	float OnevertexX1[] = { -1,1,-1,1,-1,1,1,1,1,-1,-1,-1,0,0.306147,0.306147,-0.153073,0.565686,0.565686,0.178885,0.178885,-0.282843,0.739104,0.739104,0.504221,0.504221,0.0826332,0.0826332,-0.369552,0,-0.153073,-0.153073,-0.153073,-0.282843,-0.282843,-0.357771,-0.357771,-0.282843,-0.369552,-0.369552,-0.586854,-0.586854,-0.586854,-0.586854,-0.369552,0,-0.153073,-0.153073,0.306147,-0.282843,-0.282843,0.178885,0.178885,0.565686,-0.369552,-0.369552,0.0826332,0.0826332,0.504221,0.504221,0.739104,0.69282,0.4,0,-0.4,-0.69282,-0.8,-0.69282,-0.4,0,0.4,0.69282,0.8, };
	float OnevertexY1[] = { -1,1,-1,1,-1,-1,-1,1,1,1,1,-1,0,0,0,0.265131,0,0,0.309839,0.309839,0.489898,0,0,0.386529,0.386529,0.629932,0.629932,0.640082,0,0.265131,0.265131,-0.265131,0.489898,0.489898,0,0,-0.489898,0.640082,0.640082,0.243404,0.243404,-0.243404,-0.243404,-0.640082,0,-0.265131,-0.265131,0,-0.489898,-0.489898,-0.309839,-0.309839,0,-0.640082,-0.640082,-0.629932,-0.629932,-0.386529,-0.386529,0,0.4,0.69282,0.8,0.69282,0.4,0,-0.4,-0.69282,-0.8,-0.69282,-0.4,0, };
	float OnevertexZ1[] = { 0,0,2,2,0,2,0,2,0,2,0,2,2.8,2.7391,2.7391,2.7391,2.56569,2.56569,2.71554,2.71554,2.56569,2.30615,2.30615,2.48617,2.48617,2.48617,2.48617,2.30615,2.8,2.7391,2.7391,2.7391,2.56569,2.56569,2.71554,2.71554,2.56569,2.30615,2.30615,2.48617,2.48617,2.48617,2.48617,2.30615,2.8,2.7391,2.7391,2.7391,2.56569,2.56569,2.71554,2.71554,2.56569,2.30615,2.30615,2.48617,2.48617,2.48617,2.48617,2.30615,2,2,2,2,2,2,2,2,2,2,2,2, };

	float OnevertexX2[] = { -1,1,1,-1,1,-1,1,1,-1,1,-1,-1,0.306147,0.565686,0.178885,0.178885,0.739104,0.504221,0.504221,0.0826332,0.0826332,0.8,0.69282,0.69282,0.4,0.4,0,0,-0.153073,-0.282843,-0.357771,-0.357771,-0.369552,-0.586854,-0.586854,-0.586854,-0.586854,-0.4,-0.69282,-0.69282,-0.8,-0.8,-0.69282,-0.69282,-0.153073,-0.282843,0.178885,0.178885,-0.369552,0.0826332,0.0826332,0.504221,0.504221,-0.4,0,0,0.4,0.4,0.69282,0.69282,0.8,0.69282,0.4,0,-0.4,-0.69282,-0.8,-0.69282,-0.4,0,0.4,0.69282, };
	float OnevertexY2[] = { 1,-1,-1,1,-1,-1,1,-1,1,1,-1,1,0,0,0.309839,0.309839,0,0.386529,0.386529,0.629932,0.629932,0,0.4,0.4,0.69282,0.69282,0.8,0.8,0.265131,0.489898,0,0,0.640082,0.243404,0.243404,-0.243404,-0.243404,0.69282,0.4,0.4,0,0,-0.4,-0.4,-0.265131,-0.489898,-0.309839,-0.309839,-0.640082,-0.629932,-0.629932,-0.386529,-0.386529,-0.69282,-0.8,-0.8,-0.69282,-0.69282,-0.4,-0.4,0,0.4,0.69282,0.8,0.69282,0.4,0,-0.4,-0.69282,-0.8,-0.69282,-0.4, };
	float OnevertexZ2[] = { 0,0,2,2,0,2,0,2,0,2,0,2,2.7391,2.56569,2.71554,2.71554,2.30615,2.48617,2.48617,2.48617,2.48617,2,2,2,2,2,2,2,2.7391,2.56569,2.71554,2.71554,2.30615,2.48617,2.48617,2.48617,2.48617,2,2,2,2,2,2,2,2.7391,2.56569,2.71554,2.71554,2.30615,2.48617,2.48617,2.48617,2.48617,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, };

	float OnevertexX3[] = { 1,-1,1,-1,1,-1,1,1,-1,1,-1,-1,-0.153073,0.178885,-0.153073,-0.282843,0.504221,0.178885,0.0826332,-0.282843,-0.369552,0.69282,0.504221,0.4,0.0826332,0,-0.369552,-0.4,-0.153073,-0.357771,-0.153073,-0.282843,-0.586854,-0.357771,-0.586854,-0.282843,-0.369552,-0.69282,-0.586854,-0.8,-0.586854,-0.69282,-0.369552,-0.4,0.306147,0.178885,0.306147,0.565686,0.0826332,0.178885,0.504221,0.565686,0.739104,0,0.0826332,0.4,0.504221,0.69282,0.739104,0.8,0,0,0,0,0,0,0,0,0,0,0,0, };
	float OnevertexY3[] = { 1,-1,1,-1,-1,-1,1,-1,1,1,-1,1,0.265131,0.309839,0.265131,0.489898,0.386529,0.309839,0.629932,0.489898,0.640082,0.4,0.386529,0.69282,0.629932,0.8,0.640082,0.69282,-0.265131,0,-0.265131,-0.489898,0.243404,0,-0.243404,-0.489898,-0.640082,0.4,0.243404,0,-0.243404,-0.4,-0.640082,-0.69282,0,-0.309839,0,0,-0.629932,-0.309839,-0.386529,0,0,-0.8,-0.629932,-0.69282,-0.386529,-0.4,0,0,0,0,0,0,0,0,0,0,0,0,0,0, };
	float OnevertexZ3[] = { 0,0,2,2,2,0,2,0,2,0,2,0,2.7391,2.71554,2.7391,2.56569,2.48617,2.71554,2.48617,2.56569,2.30615,2,2.48617,2,2.48617,2,2.30615,2,2.7391,2.71554,2.7391,2.56569,2.48617,2.71554,2.48617,2.56569,2.30615,2,2.48617,2,2.48617,2,2.30615,2,2.7391,2.71554,2.7391,2.56569,2.48617,2.71554,2.48617,2.56569,2.30615,2,2.48617,2,2.48617,2,2.30615,2,2,2,2,2,2,2,2,2,2,2,2,2, };

	for (int i = 0;i < 72;i++)
	{
		TriangularFacet tf;

		tf.facetX = OneFacetX[i];
		tf.facetY = OneFacetY[i];
		tf.facetZ = OneFacetZ[i];

		tf.vertexX1 = OnevertexX1[i];
		tf.vertexY1 = OnevertexY1[i];
		tf.vertexZ1 = OnevertexZ1[i];

		tf.vertexX2 = OnevertexX2[i];
		tf.vertexY2 = OnevertexY2[i];
		tf.vertexZ2 = OnevertexZ2[i];

		tf.vertexX3 = OnevertexX3[i];
		tf.vertexY3 = OnevertexY3[i];
		tf.vertexZ3 = OnevertexZ3[i];

		m_V_OneLump.push_back(tf);
	}

}

void InitSTLVertex()
{
	InitDatabase init;
	init.Init();
	GetZeorLump();
	GetOneLump();
}


/// <summary>
/// 初始化单一实例应用程序对象。这是执行的创作代码的第一行，
/// 已执行，逻辑上等同于 main() 或 WinMain()。
/// </summary>
App::App()
{
	InitSTLVertex();
	InitializeComponent();
	Suspending += ref new SuspendingEventHandler(this, &App::OnSuspending);
}

/// <summary>
/// 在最终用户正常启动应用程序时调用。	将在启动应用程序
/// 将在启动应用程序以打开特定文件等情况下使用。
/// </summary>
/// <param name="e">有关启动请求和过程的详细信息。</param>
void App::OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ e)
{

#if _DEBUG
		// 调试时显示图形分析信息。
		if (IsDebuggerPresent())
		{
			// 显示当前帧速率计数器
			 DebugSettings->EnableFrameRateCounter = true;
		}
#endif

	auto rootFrame = dynamic_cast<Frame^>(Window::Current->Content);

	// 不要在窗口已包含内容时重复应用程序初始化，
	// 只需确保窗口处于活动状态
	if (rootFrame == nullptr)
	{
		// 创建一个 Frame 以用作导航上下文并将其与
		// SuspensionManager 键关联
		rootFrame = ref new Frame();

		rootFrame->NavigationFailed += ref new Windows::UI::Xaml::Navigation::NavigationFailedEventHandler(this, &App::OnNavigationFailed);

		if (e->PreviousExecutionState == ApplicationExecutionState::Terminated)
		{
			// TODO: 仅当适用时还原保存的会话状态，并安排
			// 还原完成后的最终启动步骤

		}

		if (rootFrame->Content == nullptr)
		{
			// 当导航堆栈尚未还原时，导航到第一页，
			// 并通过将所需信息作为导航参数传入来配置
			// 参数
			rootFrame->Navigate(TypeName(MainPage::typeid), e->Arguments);
		}
		// 将框架放在当前窗口中
		Window::Current->Content = rootFrame;
		// 确保当前窗口处于活动状态
		Window::Current->Activate();
	}
	else
	{
		if (rootFrame->Content == nullptr)
		{
			// 当导航堆栈尚未还原时，导航到第一页，
			// 并通过将所需信息作为导航参数传入来配置
			// 参数
			rootFrame->Navigate(TypeName(MainPage::typeid), e->Arguments);
		}
		// 确保当前窗口处于活动状态
		Window::Current->Activate();
	}
}

/// <summary>
/// 在挂起应用程序执行时调用。	保存应用程序状态
/// 无需知道应用程序会被终止还是会恢复，
/// 并让内存内容保持不变。
/// </summary>
/// <param name="sender">挂起的请求的源。</param>
/// <param name="e">有关挂起请求的详细信息。</param>
void App::OnSuspending(Object^ sender, SuspendingEventArgs^ e)
{
	(void) sender;	// 未使用的参数
	(void) e;	// 未使用的参数

	//TODO: 保存应用程序状态并停止任何后台活动
}

/// <summary>
/// 导航到特定页失败时调用
/// </summary>
///<param name="sender">导航失败的框架</param>
///<param name="e">有关导航失败的详细信息</param>
void App::OnNavigationFailed(Platform::Object ^sender, Windows::UI::Xaml::Navigation::NavigationFailedEventArgs ^e)
{
	throw ref new FailureException("Failed to load Page " + e->SourcePageType.Name);
}