// Generator.cpp: Implementierung der Klasse CGenerator.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Generator.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CGenerator::CGenerator()
{
	fTime=0;
}

CGenerator::~CGenerator()
{
}

VOID CGenerator::Update(float dTime)
{
	fTime+=dTime;
}

float CGenerator::GetValue()
{
	return Function(fTime);
}

float CGenerator::Function(float x)
{
	return 0;
}

CWaveGenerator::CWaveGenerator() : CGenerator()
{
	fAmp=100;
	fFrequence=1;
}

CWaveGenerator::~CWaveGenerator()
{
}

float CWaveGenerator::Function(float x)
{
	return (float) sin(x*2*3.14*fFrequence)*fAmp;
}
