
// MD2 View

// Written by William Chin
// Developed in MSDEV C++ v6.0 using the DirectX 7.0a SDK
// Date : 16th May 2000
// File : info.hpp

// Website: http://members.aol.com/billybop7
// Email:  billybop7@aol.com 


#ifndef __INFO_HPP
#define __INFO_HPP

#include <windows.h>

void DisplayCredits(HWND hwnd);
void DisplayMemoryStats(HWND hwnd);		
void DisplayModelStats(HWND hwnd);				
void DisplayControls(HWND hwnd);

BOOL CALLBACK AppAbout(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);



typedef struct Rgb_bits_typ
{
	BYTE r;
	BYTE g;
	BYTE b;
	
} RGB_BITS, *Rgb_bits_ptr;

#endif // __INFO_HPP