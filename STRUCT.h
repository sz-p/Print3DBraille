#pragma once
#include "string"
using namespace std;
struct TriangularFacet
{
	float facetX;
	float facetY;
	float facetZ;

	float vertexX1;
	float vertexY1;
	float vertexZ1;

	float vertexX2;
	float vertexY2;
	float vertexZ2;

	float vertexX3;
	float vertexY3;
	float vertexZ3;
};

struct PrintData
{
	int Page;
	int PageX;
	int PageY;
	bool WordData[6];
};

struct DataBase
{
	char Ch[2];
	bool Value[6];
};

struct ChineseToCodeData
{
	int ChineseCode;
	int value;
};
struct PYData
{
	string ShengMuYunMU;
	string ShengMuYunMUData;
};