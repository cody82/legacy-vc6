#if !defined(AFX_GENERATOR_H__01CDD1EC_0377_49E4_AECC_1F4C8CC1DA54__INCLUDED_)
#define AFX_GENERATOR_H__01CDD1EC_0377_49E4_AECC_1F4C8CC1DA54__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <math.h>

class CGenerator : public CObject  
{
public:
	CGenerator();
	virtual ~CGenerator();

	virtual float Function(float x);
	virtual float GetValue();
	virtual VOID Update(float dTime);
	
	float fTime;
};

class CWaveGenerator : public CGenerator  
{
public:
	CWaveGenerator();
	virtual ~CWaveGenerator();

	virtual float Function(float x);

	float fAmp;
	float fFrequence;
};

#endif // !defined(AFX_GENERATOR_H__01CDD1EC_0377_49E4_AECC_1F4C8CC1DA54__INCLUDED_)
