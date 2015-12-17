/*---------------------------------------------------------------------------*\
 |                                                                           |
 | Name: CCKLib.h		[V0.1298b]		Programmed by Tobias Lensing         |
 | Date: 03/07/1999		Status: ALPHA	Started in February 1999             |
 |                                                                           |
 | Copyright (C) 1998-1999 Code Creators Komitee - All rights reserved       |
 |                                                                           |
 | Desc: This module contains classes and variables to handle the memory     |
 |       that is needed by the different CYCLON3D structures.                |
 |																		     |
 |---------------------------------------------------------------------------|
 |																			 |
 | This is a free version of the CCK-Library which is also used for the      |
 | CYCLON3D game engine. This version is free of charge. Permission to use,  |
 | copy, modify and distribute for free is hereby granted as long as the     |
 | above copyright note is included to the product.                          |
 |                                                                           |
 | The CCKLib contains routines for timing, random number generator          |
 | management, etc. This library was made for Win32, but should be           |
 | compatible with any C++ based code.                                       |
 |                                                                           |
 | Please note that this is an alpha-version of the CCKLib, so it might      |
 | contain several bugs. It does it's work in the CYCLON3D engine perfectly, |
 | but there might be circumstances in which it won't work correctly.        |
 |                                                                           |
\*---------------------------------------------------------------------------*/

#ifndef CCKLIB_H
#define CCKLIB_H

#include <time.h>
#include <math.h>


template <class T>
class Array
{
  protected:
    int nSize;
    T*  ptArray;

  public:
    Array(int nArraySize)
    {
        nSize = nArraySize;
        ptArray = new T[nSize];
    }
	
	~Array()
	{
		nSize = NULL;
		delete[] ptArray;
	}

    int size() { return nSize; }
	T* GetPointer() { return ptArray; }

    T& operator[](int nIndex)
    {
        if (nIndex < 0 || nIndex >= nSize)
        {
            throw "Value exceeds array limits";
        }
	    return ptArray[nIndex];
    }
};


class Timer
{
public:
	Timer()
	{
		m_fCurrentTime = timeGetTime();
		m_fLastTime = 0;
		m_fWait = 0;
	}

	Timer( float waitTime )
	{
		m_fCurrentTime = timeGetTime();
		m_fLastTime = timeGetTime();
		m_fWait = waitTime;
	}

	BOOL GetEvent()
	{
		m_fCurrentTime = timeGetTime();
		if( m_fCurrentTime - m_fLastTime >= m_fWait )
		{
			m_fLastTime = m_fCurrentTime;
			return TRUE;
		}
		else return FALSE;
	}

	void SetWaitTime( float waitTime )
	{
		m_fWait = waitTime;
	}

	float GetWaitTime()
	{
		return m_fWait;
	}

	float GetCurrentTime()
	{
		m_fCurrentTime = (float)timeGetTime();
		return m_fCurrentTime;
	}

	float GetLastTime()
	{
		return m_fLastTime;
	}

protected:
	float m_fCurrentTime, m_fLastTime;
	float m_fWait;
};


class Randomizer
{
public:
	////////////////////////////
	// Constructor & Destructor
	Randomizer() { }
	~Randomizer() { }

	/////////////////////
	// Element Functions
	void SeedRand()
	{
		srand(time(0));
	}

	float GetRandNum( float rand_max )
	{ 
		return float(rand()) / RAND_MAX * rand_max;
	}

	float GetSignedRandNum( float rand_max )
	{
		float plusminus;
		float signrand = GetRandNum(1);
		if( signrand < 0.5 ) plusminus = -1;
			else plusminus = 1;
		return float(rand()) / RAND_MAX * rand_max * plusminus;
	}
};

#endif