#include "pch.h"
#include "stdafx.h"
#include "SavaSTL.h"
#include "STRUCT.h"
#include "vector"
#include "sstream"


SavaSTL::SavaSTL()
{
}


SavaSTL::~SavaSTL()
{
}



void SavaSTL::GetSaveFileName(string Name)
{
	SaveFileName = Name;
}
void SavaSTL::OpenFile()
{
	Platform::String^ stops(std::string s);
	FileSavePicker^ savePicker = ref new FileSavePicker();
	savePicker->SuggestedStartLocation = PickerLocationId::DocumentsLibrary;

	auto plainTextExtensions = ref new Platform::Collections::Vector<String^>();
	plainTextExtensions->Append(".stl");
	savePicker->FileTypeChoices->Insert("Plain Text", plainTextExtensions);
	savePicker->SuggestedFileName = "3DPrintTask";

	create_task(savePicker->PickSaveFileAsync()).then([this](StorageFile^ file)
	{
		if (file != nullptr)
		{
			string buffer;
			
			GeiFileBuffer(buffer);

			FileIO::WriteTextAsync(file, stops(buffer));
			buffer = "";
			ReleaseCache();
			extern	int SaveFileProgress;
			SaveFileProgress = 100;
		}
		else
		{
			//OutputTextBlock->Text = "Operation cancelled.";
		}

	});
}


void SavaSTL::GeiFileBuffer(string  & buffer1)
{
	extern vector<PrintData> V_PrintData;

	buffer1.append("solid braille");
	buffer1.append("\r\n");

	for (int i = 0;i < V_PrintData.size();i++)
	{
		extern int GreateFileProgress;
		GreateFileProgress = (i + 1) * 100 / V_PrintData.size();
		for (int j = 0;j < 6;j++)
		{
			if (V_PrintData[i].WordData[j])
			{
				SaveOne(buffer1, V_PrintData[i].PageX * 2 + j / 3, V_PrintData[i].PageY * 4 + j % 3);
			}
			else
			{
				SaveZero(buffer1, V_PrintData[i].PageX * 2 + j / 3, V_PrintData[i].PageY * 4 + j % 3);
			}
		}
		SaveZero(buffer1, V_PrintData[i].PageX * 2 + 0, V_PrintData[i].PageY * 4 + 3);
		SaveZero(buffer1, V_PrintData[i].PageX * 2 + 1, V_PrintData[i].PageY * 4 + 3);
	}
	
	buffer1.append("endsolid braille");
	buffer1.append("\r\n");

}


void SavaSTL::SaveZero(string  & buffer1,int x,int y)
{
	StepX = 2.0;
	StepY = 2.0;
	extern vector <TriangularFacet> m_V_ZeroLump;
	for (int i = 0;i < m_V_ZeroLump.size();i++)
	{
		buffer1.append("facet normal " + float_to_string(m_V_ZeroLump[i].facetX) + " " + float_to_string(m_V_ZeroLump[i].facetY) + " " + float_to_string(m_V_ZeroLump[i].facetZ));
		buffer1.append("\r\n");
		buffer1.append("outer loop");
		buffer1.append("\r\n");
		
		buffer1.append("vertex " + float_to_string(m_V_ZeroLump[i].vertexX1 + x * StepX) + " " + float_to_string(m_V_ZeroLump[i].vertexY1 - y * StepY) + " " + float_to_string(m_V_ZeroLump[i].vertexZ1));
		buffer1.append("\r\n");
		buffer1.append("vertex " + float_to_string(m_V_ZeroLump[i].vertexX2 + x * StepX) + " " + float_to_string(m_V_ZeroLump[i].vertexY2 - y * StepY) + " " + float_to_string(m_V_ZeroLump[i].vertexZ2));		
		buffer1.append("\r\n");
		buffer1.append("vertex " + float_to_string(m_V_ZeroLump[i].vertexX3 + x * StepX) + " " + float_to_string(m_V_ZeroLump[i].vertexY3 - y * StepY) + " " + float_to_string(m_V_ZeroLump[i].vertexZ3));		
		buffer1.append("\r\n");

		buffer1.append("endloop");
		buffer1.append("\r\n");
		buffer1.append("endfacet");
		buffer1.append("\r\n");
	}
}


void SavaSTL::SaveOne(string  & buffer1, int x, int y)
{
	StepX = 2.0;
	StepY = 2.0;
	extern vector <TriangularFacet> m_V_OneLump;
	for (int i = 0;i < m_V_OneLump.size();i++)
	{
		buffer1.append("facet normal " + float_to_string(m_V_OneLump[i].facetX) + " " + float_to_string(m_V_OneLump[i].facetY) + " " + float_to_string(m_V_OneLump[i].facetZ));
		buffer1.append("\r\n");
		buffer1.append("outer loop");
		buffer1.append("\r\n");

		buffer1.append("vertex " + float_to_string(m_V_OneLump[i].vertexX1 + x * StepX) + " " + float_to_string(m_V_OneLump[i].vertexY1 - y * StepY) + " " + float_to_string(m_V_OneLump[i].vertexZ1));
		buffer1.append("\r\n");
		buffer1.append("vertex " + float_to_string(m_V_OneLump[i].vertexX2 + x * StepX) + " " + float_to_string(m_V_OneLump[i].vertexY2 - y * StepY) + " " + float_to_string(m_V_OneLump[i].vertexZ2));
		buffer1.append("\r\n");
		buffer1.append("vertex " + float_to_string(m_V_OneLump[i].vertexX3 + x * StepX) + " " + float_to_string(m_V_OneLump[i].vertexY3 - y * StepY) + " " + float_to_string(m_V_OneLump[i].vertexZ3));
		buffer1.append("\r\n");

		buffer1.append("endloop");
		buffer1.append("\r\n");
		buffer1.append("endfacet");
		buffer1.append("\r\n");
	}
}


void SavaSTL::Save()
{
	OpenFile();
}


float SavaSTL::ComputeRealX(float Value,int x)
{
	return Value + x*StepX;
}


float SavaSTL::ComputeRealY(float Value, int y)
{
	return Value + y*StepX;
}


string SavaSTL::float_to_string(float src)
{
	stringstream ss;
	ss << src;
	return ss.str();
}


void SavaSTL::ReleaseCache()
{
	extern vector<PrintData> V_PrintData;
	vector<PrintData>().swap(V_PrintData);

}
