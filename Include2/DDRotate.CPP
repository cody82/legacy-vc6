/**************************************************************************************************

Title:  DDRAW RotoZoomer Code
From :  Dallas Nutsch ynb53@ttu.edu
Desc :
 
	This code is the first in a series of functions designed to expand the functionality of DirectDraw.
	The scan line conversion is based largely on Michael Abrash code from a book called Zen of Graphics.


	Another Quality ARROWHEAD release. Visit our web sight at www.door.net/arrowhead and see this 
	code in action.


Notes:

Revisions:

	6-1-98 First Release

Limitations:

	-No Perspective Correction
	-No 24- or 32- bit support yet (it just needs new scanout functions similar to  ScanOutLine16)
	-Accuracy isn't too good. 

Disclaimer:

	THIS SOFTWARE IS NOT SUPPORTED. THE AUTHOR IS NOT RESPONSIBLE OR LIABLE FOR ANY USE OF THIS CODE.
	THE AUTHOR IS NOT LIABLE FOR ANY DAMAGE, MISUSE, OR BAD STUFF THAT HAPPENS WHEN YOU USE THIS 
	CODE.

*************************************************************************************************/

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <math.h>
#include <ddutil.h>
#include "DDRAW.H"
#include "DDROTATE.H"

//Some very basic fixed point stuff

FXFixed FXmul (FXFixed a, FXFixed b)
{
	__asm {
		mov		eax,a		; Access directly without stack frame
		imul	b
		add		eax,8000h		; Round by adding 2^-17
		adc		edx,0			; Whole part of result is in DX
		shrd	eax,edx,16		; EAX := a * b
	}
}

FXFixed FXdiv (FXFixed a, FXFixed b)
{
	__asm {

		mov		edx,a		; Access directly without stack frame
		xor		eax,eax
		shrd	eax,edx,16		; position so that result ends up
		sar		edx,16			; in EAX
		idiv	dword ptr [b]
	}
}


//Structure for polygon traverse

typedef struct {
   int Direction;    /* through edge list; 1 for a right edge (forward
                        through vertex list), -1 for a left edge (backward
                        through vertex list) */
   int RemainingScans;  /* height left to scan out in dest */
   int CurrentEnd;      /* vertex # of end of current edge */

   real SourceX;     /* current X location in source for this edge */
   real SourceY;     /* current Y location in source for this edge */
   real SourceZ;     /* current Y location in source for this edge */
   real ASourceX;     /* current X location in source for this edge */
   real ASourceY;     /* current Y location in source for this edge */

   real SourceStepX; /* X step in source for X step in dest of 1 */
   real SourceStepY; /* Y step in source for X step in dest of 1 */
   real SourceStepZ;     /* current Y location in source for this edge */

                        /* variables used for all-integer Bresenham's-type
                           Y stepping through the dest, needed for precise
                           pixel placement to avoid gaps */
   int DestX;           /* current Y location in dest for this edge */
   int DestXIntStep;    /* whole part of dest x step per column Y step */
   int DestXDirection;  /* -1 or 1 to indicate which way Y steps
                           (left/right) */
   int DestXErrTerm;    /* current error term for dest Y stepping */
   int DestXAdjUp;      /* amount to add to error term per column move */
   int DestXAdjDown;    /* amount to subtract from error term when the
                           error term turns over */
} EdgeScan;

//Vertex structure - Used to define points on screen and texture points they map to 


typedef struct {
	FXFixed x;              //X coordinate
	FXFixed y;              //Y coordinate
	FXFixed z;              //Z coordinate
	FXFixed reserved;       //This space reserved in case you want to do some transformations
} vertex_t;



/***********************************************************************************

	Globals:

		These variables hold all the texture mapping info as globals so it doesn't 
		have to be passed to function calls

************************************************************************************/


//Globals for texture mapping

int SetUpEdgeFast(EdgeScan * Edge, int StartVert);
int StepEdgeFast(EdgeScan * Edge);
void ScanOutLine16 (void);
void ScanOutLine(void);




EdgeScan LeftEdge;				//Position of left edge 
EdgeScan RightEdge;             //Position of right edge
int NumVerts;                   //Number of vertices in polygon to texture map
int MaxVert;                    //Max vertex (bottom vertex)
int DestY;                      //Scan line to draw on
int DestX;                      //First X pixel to start drawing on
real SourceWidth;               //Fixed point 16.16 width of source image
real SourceHeight;              //Fixed point 16.16 height of source image
LPDIRECTDRAWSURFACE TexSrc;   //Source DDRAW object
LPDIRECTDRAWSURFACE TexDest;  //Dest DDRAW object
DDSURFACEDESC SrcInfo;          //Source Info
DDSURFACEDESC DestInfo;         //Dest Info

//These are the coordinates - note there are four for a square or rectange

vertex_t PolyCoords [4];        //Screen coordinates for polygon
vertex_t TextureCoords[4];     //Texture coordinates corresponding to the respective screen coords

RECT DestRect;                   //Screen Rectangle to clip to 

/************************************************************************
Function: SetUpEdgeFast
Description: Sets up an edge (either left or right) when a new vertex has
             been reached

************************************************************************/

int SetUpEdgeFast(EdgeScan * Edge, int StartVert)
{
   int NextVert, DestXWidth;
   real DestYHeight;
  for (;;)
   {
      // If this edge starts at the very bottom vertex return zero

      if (StartVert == MaxVert) return 0;
   
      
      NextVert = StartVert + Edge->Direction;				  //go to the next vertex
      if (NextVert >= NumVerts)   NextVert = 0;               //wrap around vertex array
      else if (NextVert < 0) NextVert = NumVerts - 1;         // "      "     "       "

      // If the height of this polygon side isn't zero calculate the variables 
	  // This uses a technique called forward referencing which is a fancy way of saying
	  // that the x values are interpolated at each scan line


	  //Set the number of scan lines this polygon side crosses to the difference in the
	  //two y components of the starting and ending coords and shift right 16 bits to 
	  // convert a 16.16 fixed point to a 16.0 integer
	  //If the number of scan lines this poly side crosses isn't zero continue
      if ((Edge->RemainingScans = (PolyCoords[NextVert].y - PolyCoords[StartVert].y)>>16 ) != 0) 
	  {
      
		  //Set the variable DestYHeight to the number of scans in 16.16 rounded to the integer
		  //this really could be removed and you could use (Edge->RemainingScans)<<16 in its place

		  DestYHeight = FXintToReal(Edge->RemainingScans);  


		Edge->CurrentEnd = NextVert;				//Set up the ending vertex
		Edge->SourceX = TextureCoords[StartVert].x;   //Set up the source pointers		 
		Edge->SourceY = TextureCoords[StartVert].y;   // "  "  "      "      "

		//Now calculate how much to add to the x and y source position per scanline in 16.16

		Edge->SourceStepY = FXdiv(TextureCoords[NextVert].y - Edge->SourceY, DestYHeight);
		Edge->SourceStepX = FXdiv(TextureCoords[NextVert].x - Edge->SourceX, DestYHeight);

		//These lines were added so that textures will wrap in y
		//No support for texture wrapping in x has been made yet

		if (Edge->SourceY > SourceHeight) Edge->SourceY -= SourceHeight;
		if (Edge->SourceY < 0) Edge->SourceY += SourceHeight;

         // Set up integer math stuff for the destination position stepping
		 // Basically all the stuff above here was for finding the position of the source 
		 // bitmap.  all the stuff below here is for finding the pixel on the screen that 
		 // the edge of the polygon goes through

		 // "If the x width of the polygon side is negative"
         if ((DestXWidth = FXrealToInt(PolyCoords[NextVert].x - PolyCoords[StartVert].x)) < 0) 
		 { 
			 
            Edge->DestXDirection = -1;                   //set the direction to -1
            DestXWidth = -DestXWidth;                    //Negate the width to make it positive 

			//Edge->DestXIntStep is the whole part to add for each scan line
			//Edge->DestX is the starting screen coord
            Edge->DestXIntStep = -(DestXWidth / Edge->RemainingScans);
            Edge->DestX = FXrealToInt(PolyCoords[StartVert].x);
         } 
		 else
		 {
            Edge->DestXDirection = 1;                   //Direction is positive
			//Edge->DestXIntStep is the whole part to add for each scan line
			//Edge->DestX is the starting screen coord
            Edge->DestXIntStep = DestXWidth / Edge->RemainingScans;
            Edge->DestX =  FXrealToInt(PolyCoords[StartVert].x) + 1;
         }

		 //This stuff is for the integer math
		 //To find out what it does look up the breshenham line algorithm 

         Edge->DestXErrTerm = 1 - Edge->RemainingScans;
         Edge->DestXAdjUp = DestXWidth % Edge->RemainingScans;
         Edge->DestXAdjDown = Edge->RemainingScans;
         return 1; //Done setting up this edge
      }
      StartVert = NextVert;  //Skip to next vertex if this edge was zero height
   }
}


/************************************************************************
Function: StepEdgeFast
Description:  

  Called once per scanline for the left and right edges
  when the side gets to the very bottom vertex this function returns zero
  thus ending the texture mapping routine


************************************************************************/
int StepEdgeFast(EdgeScan * Edge)
{
   // "If there are no more scan lines left on this side"
   if (--Edge->RemainingScans == 0)
   {
	  // Call the function to get a new vertex or if its done exit
      if (SetUpEdgeFast(Edge, Edge->CurrentEnd) == 0) 
	  {
         return 0; //Polygon is done so return zero the end polygon drawing
      }
      return 1 ;  //New edge was set up
   }

   //Otherwise do all the math for this side


	Edge->SourceX += Edge->SourceStepX;                    //Increment the source x
	Edge->SourceY += Edge->SourceStepY;                    //Increment the source y

	//These two lines are so that textures will wrap around in y
	//For instance if your texture is 10 pixels high and you specify a source rectangle
	//That is 100 pixels heigh, the texture will wrap 10 times

	if (Edge->SourceY > SourceHeight) Edge->SourceY -= SourceHeight;
	if (Edge->SourceY < 0) Edge->SourceY += SourceHeight;

	//Add the whole number amount to the destination (screen) coord

   Edge->DestX += Edge->DestXIntStep;

   //Now add up the fractional part and see if it is >= one pixel

   if ((Edge->DestXErrTerm += Edge->DestXAdjUp) > 0)
   {
	  //The fractional part has built up enough that an extra pixel has to be added
      Edge->DestX += Edge->DestXDirection;
      Edge->DestXErrTerm -= Edge->DestXAdjDown;
   }
   return 1; //success
}








/***************************************************************************************
//Scanoutline 16 bit

  Simple scan out procedure for 16-bit graphics. This function assumes that both the source
  and destination are both 16-bit bitmaps  

**************************************************************************************/
void ScanOutLine16 (void) 
{

   real SourceX = LeftEdge.SourceX;
   real SourceY = LeftEdge.SourceY;
   int DestX = LeftEdge.DestX;
   int DestXMax = RightEdge.DestX;
   real DestWidth;
   real SourceXStep, SourceYStep;

   // Return if this span is < the left of the screen or > the right side of the screen

   if (DestXMax <= DestRect . left || DestX >= DestRect . right)  return;

   // Return if this span is zero width

   if ((DestXMax - DestX) <= 0) return;

   //Find the FXFixed 16.16 value of x and y source stepping

   DestWidth = FXintToReal(DestXMax - DestX);
   SourceXStep = FXdiv(RightEdge.SourceX - SourceX, DestWidth);
   SourceYStep = FXdiv(RightEdge.SourceY - SourceY, DestWidth);

   //If the span crosses the right side of the clip rectangle just subtract the number of pixels
   if (DestXMax > DestRect . right) DestXMax = DestRect . right;

   //If the span crosses the left side of the clip rectangle we have to calculate a new starting
   //point on the source image

   if (DestX < DestRect . left) {
      SourceX += SourceXStep * (DestRect . left - DestX);
      SourceY += SourceYStep * (DestRect . left - DestX);
      DestX = DestRect . left;
   }


   //Even though we're dealing with 16-bit surfaces, we have to keep byte pointers to the data
   //Because a surface might have an odd pith, for instance a surface with a pitch of 37 is
   // 18 1/2 words wide
    
	BYTE * Bitmap_Source = (BYTE*)  SrcInfo.lpSurface;
	BYTE * Bitmap_Dest = (BYTE*) DestInfo.lpSurface;
	WORD CPixel;

	Bitmap_Dest += DestX*2+DestY * DestInfo.lPitch;
	for (; DestX<DestXMax; DestX++)
	{
		   //Load up a pixel
		   CPixel = *((WORD*) (Bitmap_Source +FXrealToInt(SourceX)*2+FXrealToInt(SourceY) * SrcInfo.lPitch));
		   if (CPixel) //if color is not black - RGB(0,0,0)
		   *((WORD*) (Bitmap_Dest)) = CPixel;
		   //Increment the source position
		   //the destination pixel is incremented by the loop statement
		  SourceX += SourceXStep;
		  SourceY += SourceYStep;
		   //Increment the destination pointer by 2 bytes
		  Bitmap_Dest += 2;
	   }
}



/***************************************************************************************
//SCANOUTLINE 8-BIT

  Notes:
        Color index zero is transparent. All this mess below here serves a single purpose.
		fast TRANSPARENT texture mapping.  What no one tells you about DirectX and video 
		memory is that you have to write to it DWORD aligned and in DWORD or even DWORDLONG
		sizes to make it fast. Because of this:
		 
		On my P-133 with a 128-bit video card and 33 mhz bus this is how long it takes to 
		fill an 8-bit screen.

		time      method
		--------------------------------------------------------
		30 ms     Drawing each pixel one byte at a time
		3 ms      Drawing 8 pixels at a time by writing two DWORDS in a row


		So you can see that the key is in caching pixels together.  For 60 Frames per second
		your WHOLE FRAME can't take longer than 16.666 ms and each screen fill the slow way
		takes 30. Trust me this is way better.

  So what do we do about this.  Well, a couple things.  First I broke the scan out into three parts
  1 - do a few pixels to align to DWORD boundary
  2 - Do each remaining groups of 4 pixels
  3 - do the last 0 to 3 pixels to finish out the scan lines

  Section - 1 & 3
    We do these simple - read a pixel, see if its zero, and output it if it isn't

  Section - 2
    Read four source pixels and see if they are all nonzero, all zero, or mixed

  -All nonzero = write out a DWORD
  -All zero = skip four spaces
  -Mixed = do each one individually
		

**************************************************************************************/

void ScanOutLine(void)
{
   real SourceX = LeftEdge.SourceX;            //Source location for current pioxel
   real SourceY = LeftEdge.SourceY;            // 
   int DestX = LeftEdge.DestX;                 //Starting pixel
   int DestXMax = RightEdge.DestX-1;           //Ending pixel
   real DestWidth;                             //16.16 width of scan
   real SourceXStep, SourceYStep;              //16.16 amounts to add

   // Return if x < left clip or > right clip
   if (DestXMax <= DestRect . left || DestX >= DestRect . right) return;
   //Return on zero width scans
   if (DestX >= DestXMax) return ;           

   //Set up variables

   DestWidth = (DestXMax - DestX)<<16;
   SourceXStep = FXdiv(RightEdge.SourceX - SourceX, DestWidth);
   SourceYStep = FXdiv(RightEdge.SourceY - SourceY, DestWidth);

   //Right clip

   if (DestXMax > DestRect . right)   DestXMax = DestRect . right;

   //Left clip
   
   if (DestX < DestRect . left) {
	  //Calculate a new starting point for the scan
      SourceX += SourceXStep * (DestRect . left - DestX);
      SourceY += SourceYStep * (DestRect . left - DestX);
      DestX = DestRect . left;
   }

   //Step into the source a half a pixel so it rounds right

   SourceX += FXdiv (SourceXStep,FXintToReal (2));
   SourceY += FXdiv (SourceYStep,FXintToReal (2));

   

   int YAdd , XIntAdd;

   //This section fixes a special characteristic of 16.16 math
   //If the whole step is 0xffff and the fractional part is zero 
   //It means that for each screen pixel left to right the source should be
   //Moved up or left (-1) one pixel.  BUT, something screwy happens and if there
   //isn't a special case both the whole amount and fractional amount end up being
   //zero which means that no addition happens across the scanline.
   //
   //Furthermore if the step is negative, the whole part has to be incremented by one
   // because 0xffffffff = -1 / 65536 in FXFixed.  But look at the number, both
   // the high word and low word are -1 which would appear to be -1 1/65536
   // So because we split up the whole part and fraction here we have to fix this

  if ((DWORD)SourceYStep == 0xffff0000) YAdd = -1;  //Fix special one off error
   else
   {
	   YAdd =  (int) FXrealToInt(SourceYStep);
	   if (YAdd < 0) YAdd++;                        //If its negative increase the whole part by one
   }
   
   if ((DWORD)SourceXStep == 0xffff0000)  XIntAdd = -1;  //Fix special one off error
   else
   {
	   XIntAdd =  (int) FXrealToInt(SourceXStep);   
	   if (XIntAdd < 0) XIntAdd++;                   //If its negative increase the whole part by one
   }
   
   //Now we change the whole parts of y and x source steps into one variable called TAdd for now

   YAdd *=(int)SrcInfo.lPitch;
   int TAdd = XIntAdd + YAdd;
   
   //Here I use the same variables to hold the amount to add when it is necessary to bump the source
   //One pixel in the x or y.  This is because the algorithm doesn't know which way to bump the source
   // it only knows when the source needs bumped

   if (SourceYStep < 0)   
	YAdd =(int)-SrcInfo.lPitch;
   else if (SourceYStep > 0) 
	YAdd = (int)SrcInfo.lPitch;

   //Figure out which way to go for x

   if (SourceXStep < 0)   
	XIntAdd =-1;
   else if (SourceXStep > 0) 
	XIntAdd =1;

	//Set up a couple of BYTE pointes 

	BYTE * Bitmap_In = (BYTE*) SrcInfo.lpSurface;
	BYTE * Bitmap_Out = (BYTE*) DestInfo.lpSurface;

	//Now calculate the starting pointers
  
	   Bitmap_Out += DestX+DestY * DestInfo.lPitch;
	   Bitmap_In += (int) FXrealToInt(SourceX)+(int) FXrealToInt(SourceY) * (int)SrcInfo.lPitch;

    // This section does some more special case stuff for separating the whole and fraction parts
	// of the 16.16 number.  This time its for the fractional parts

   	   if (SourceXStep <0)                              //If we are stepping left
	   {
		   if ((DWORD) SourceXStep == 0xffff0000)       //If we are stepping left by exactly -1.0 
		   {     
				//Fix special one off error
			   SourceXStep = 0;                         //Set the fractional x to zero because
			                                            //We've already set the whole x  to -1
		   }
		   else
		   {
			   //At this point the source position is already known in the pointer Bitmap_In so the value of sourcex 
			   //isn't really the source x position, but we still use the fractional part below
			   //to initialize our fixed point routine
			   //Since the initial stepping is negative and we want to always step positive
			   // (remembering that XIntAdd keeps track of which way we are going)
			   // We negate the stepping direction, but we also have to take
			   // 1 - the fractional part so that the positive steppiong starts at the right place
			   
			   //Whew that's a mouthful.  This took a lot of trial and error to fix

			   SourceX &= 0xffff;                        //Keep only fraction part
			   SourceX = 0x10000 - SourceX;              //Find 1 - fraction
			   SourceXStep=-SourceXStep;                 //Make sure we always step positive
		   }

	   }
	   if (SourceYStep <0)
	   {	
		  if ((DWORD) SourceYStep == 0xffff0000)
		   {
				//Fix special one off error - see above
			   SourceYStep = 0;
		   }
		   else
		   {
			   // see above 

			   SourceY &= 0xffff;
			   SourceY = 0xffff - SourceY;
			   SourceYStep=-SourceYStep;
		   }
	   }

	   int pixcount;  //This is the outer loop variable because
	                  //I didn't have enough registers


	   /*
	   And now the good stuff
	   Note: this code probably only assembles with VC 5++ because Borland (now named ?) 
	         doesn't support 32-bit inline assembly much less MMX or any other stuff
	         I don't know about watcom or GCC though

		Register Usage:
		   esi = source pointer
		   edi = destination pointer
		   eax = 

		*/

	   __asm {
		   push edi                                  //Save register for c++ compiler
		   push esi                                  //Save register for c++ compiler

												     //Set up some stuff

		   mov dx, word ptr [SourceX]                //DX  = Source X Fraction
		   shl edx, 16                               //EDX = Source X Fraction in high byte
		   mov dx, word ptr [SourceY]                //DX  = Source Y Fraction in low byte
		   shr dx, 1						         //DX  = Source Y Fraction 
		                  
		   //NOTE: We only use 7-bits for the y fraction and 8 for the x fraction which is stored in

		   mov bx, word ptr [SourceXStep]			 //BX = Source X Fraction Step
		   shl ebx, 16                               //EBX = Source X Fraction Step in High Byte
		   mov bx, word ptr [SourceYStep]            //BX == Source Y Fraction Step
		   shr bx, 1						         //Make Y Fraction Step 7 bits instead of 8

		   //NOTE: We only use 7-bits for the y stepping too

		   mov esi, Bitmap_In;                       //ESI = pointer to source
		   mov edi, Bitmap_Out;                      //EDI = pointer to destination
			
		   //Phase 1 - do a couple pixels to align to DWORD boundary

		   mov eax, DestXMax                         //EAX = Max pixel
		   mov ecx, DestX;                           //EDX = Start Pixel
		   sub eax, ecx                              //EAX = number of pixels to do 

		   and ecx, 0000000000000011b				 //ECX = start pixel mod 4;

		   //ECX = number of bytes to do to align to dword boundary
		                                          
		   cmp ecx, eax								 //if we have more alignment pixels than actual 
		                                             //pixels to draw then adjust the number 
		   jle Phase1Adjust
		   mov pixcount , eax					     //pixcount = phase one pixels
		   jmp Phase1Adjust2
		   
Phase1Adjust:
		   mov pixcount, ecx                         //pixcount = DestX % 4 still
Phase1Adjust2:


		   mov ecx, 0                                //Clear out ecx 

Phase1:
		   cmp pixcount, 0                           //If we are already dword aligned skip section 1
		   je Phase1Done                           
		   dec pixcount                              //decrease the loop counter
  
		   mov cl, [esi]                             //Load a pixel
		   add edx, ebx                              //Add the fractional steppings to the fractional positions
		   jnc short Phase1NoXAdd                    //If there wasn't a carry no x pixel needs to be added
		   add esi, XIntAdd;                         //Otherwise move the source pointer in the 
                                                     //appropriate direction. Remember xintadd is 
		                                             //either -1 or 1
		   Phase1NoXAdd:

		   add esi, TAdd                             //Add the whole x and y to the source pointer
		   or ecx,ecx                                //see if the pixel is index zero (transparent)
		   jz Phase1SkipPixel                        //if so skip this pixel
		   mov [edi], cl                             //Write the pixel to the screen or destination

Phase1SkipPixel:

		   test dh, 80h                              //See if we need to bump the y pixel by
		   jz short Phase1NoAdd                      //checking bit 15 of the source (edx)
		   add esi, YAdd;                            //if needed, add a pixel (by adding bytes = surface pitch
		   and dh, not 80h                           //turn off bit 15
Phase1NoAdd:  
		   inc edi                                   //increment the destination pointer by 1 pixel
		   inc DestX                                 //increment the destination x
		   jmp short Phase1                          //Loop back to top of phase 1

Phase1Done:

//**************************************************************

//		   Phase 2 - do four byte writes

//**************************************************************

           mov ecx, DestXMax                        //ecx = max pixel
		   sub ecx, DestX                           //eax = start pixel modified by phase 1
		   shr ecx, 2                               //ecx = DestXMax-DestX)>>3; //Number of DWORDS left
		   mov pixcount, ecx                        //pixcount = ecx
		   shl ecx, 2                               //ecx = number of pixels we're fixing to do
		   add DestX, ecx		                    //DestX += number of pixels in phase 2

Phase2:

		   cmp pixcount,0                           //See if we're done with phase 2
		   je Phase2Done                            //if so jump
		   dec pixcount                             //decrement the counter

//First load four bytes unrolled version


//********* 1111111111111111111111
		   mov cl, [esi]
		   add esi, TAdd   		     //Add whole part of source pointer
		   ror ecx, 8
		   add edx, ebx		   	     //Add fraction 
		   jnc short Phase2NoXAdd    //See if X needs updating
		   add esi, XIntAdd;         //Yes, add the x component
Phase2NoXAdd:
		   test dh, 80h				 //See if Y needs updating
		   jz short Phase2NoAdd      
		   add esi, YAdd;            //Yes, add the component
		   and dh, not 80h			 //reset the flag
Phase2NoAdd:  

//******** 22222222222222222222222
		   mov cl, [esi]			//Load byte int cl
		   add esi, TAdd			//Add whole part of source pointer
		   ror ecx, 8               //Adjust ecx
		   add edx, ebx		   	    //Add fraction 
		   jnc short Phase2NoXAdd2  //See if X needs updating
		   add esi, XIntAdd;        //if yes, add the x component
Phase2NoXAdd2:
		   test dh, 80h				//See if Y needs updating
		   jz short Phase2NoAdd2      
		   add esi, YAdd;           //if yes, add the component
		   and dh, not 80h			//reset the flag
Phase2NoAdd2: 
//******** 33333333333333333333333
		   mov cl, [esi]
		   ror ecx, 8
		   add esi, TAdd			 //Add whole part of source pointer
		   add edx, ebx		   	     //Add fraction 
		   jnc short Phase2NoXAdd3   //See if X needs updating
		   add esi, XIntAdd;         //Yes, add the x component
Phase2NoXAdd3:
		   test dh, 80h				 //See if Y needs updating
		   jz short Phase2NoAdd3     
		   add esi, YAdd;            //Yes, add the component
		   and dh, not 80h			 //reset the flag
Phase2NoAdd3:  
//******** 44444444444444444444444
		   mov cl, [esi]
		   add esi, TAdd			 //Add whole part of source pointer
		   ror ecx, 8
		   add edx, ebx		   	     //Add fraction 
		   jnc short Phase2NoXAdd4   //See if X needs updating
		   add esi, XIntAdd;         //Yes, add the x component
Phase2NoXAdd4:
		   test dh, 80h				 //See if Y needs updating
		   jz short Phase2NoAdd4      
		   add esi, YAdd;            //Yes, add the component
		   and dh, not 80h			 //reset the flag
Phase2NoAdd4: 
		   
//This is a rather complex test to see if any byte in ecx is zero 
		   push ecx								//save pixel for a second
			mov eax, 7efefeffh                  
			add eax, ecx
			xor ecx,-1
			xor ecx, eax
			mov eax, ecx
		   pop ecx                              //restore pixels
		   test eax,81010100h                   
		   je short SkipTransAll                //If eax = 81010100h none are zero
		   shr eax, 24                          //eax >>24
		   cmp eax, 0x20                        //If bit 6 is set none are zero
		   je short SkipTransAll      
		   and ecx, ecx						    //Just skip all of them if all were zero
		   jz SkipTransDone

		                                        //Draw each individual pixel here

		   and cl,cl                            //See if byte is zero
		   jz  short SS1                        //skip if it is
		   mov [edi],cl                         //otherwise store it
SS1:
		   ror ecx, 8                           //CL = next pixel

		   and cl,cl
		   jz  short SS2
		   mov [edi+1],cl
SS2:
		   ror ecx, 8

		   and cl,cl
		   jz  short SS3
		   mov [edi+2],cl
SS3:
		   ror ecx, 8

		   and cl,cl
		   jz  short SS4
		   mov [edi+3],cl
SS4:

		   jmp short SkipTransDone              //All done

SkipTransAll:
		   mov [edi], ecx                       //Write all four pixels at once
SkipTransDone:
		   add edi, 4                           //increment destination
		   jmp Phase2                           //Loop phase 2
Phase2Done:
		   
/*************************************************************

  PHASE 3 - Finish off pixels - SAME AS PHASE 1

*************************************************************/
		   
		   mov ecx, DestXMax
		   sub ecx, DestX;
		   mov pixcount, ecx          
		   mov ecx, 0
Phase3:
		   cmp pixcount, 0 
		   je Phase3Done
		   dec pixcount

		   mov cl, [esi]
		   add edx, ebx
		   jnc short Phase3NoXAdd
		   add esi, XIntAdd;

		   Phase3NoXAdd:

		   add esi, TAdd
		   or ecx,ecx
		   jz Phase3SkipPixel
		   mov [edi], cl

Phase3SkipPixel:


		   test dh, 80h
		   jz short Phase3NoAdd
		   add esi, YAdd;
		   and dh, not 80h
Phase3NoAdd:  
		   inc edi
		   jmp Phase3

Phase3Done:

		   //ALL DONE
  
		   pop esi                     //Restore c++ register
		   pop edi                     //  "

	   }

// Thus ends this massive texture mapping scan line function.  Its big, but a lot faster than
// Doing it one pixel at a time

}











/************************************************************************
Function: DrawRotatedZoomed
Description:


	This is the function to draw the rotated and zoomed rectangle

	NOTE: you can change this function to draw a trapezoid, triangle, whatever by
	changing the number of vertices and moving them. However, this code doesn't 
	perspective correct transformed polygons

    To incorporate this into existing code, just remove the corresponding argument and 
	rename it in this function

************************************************************************/
void DrawRotatedZoomed( LPDIRECTDRAWSURFACE src, LPDIRECTDRAWSURFACE dest,
					   RECT & SrcRect, RECT & destclip,
					    int X, int Y, float Angle, float xzoom, float yzoom,
						bool ReCenter)

{
	HRESULT ret;
	//Copy the destination clip rectangle (i.e. normally 0,0,640,480 for 640x480)
    memcpy (&DestRect,&destclip,sizeof (RECT));


	int PixelWidth = SrcRect . right - SrcRect . left;
	int PixelHeight = SrcRect . bottom - SrcRect . top;

	if (ReCenter == true)
	{
		X -= (PixelWidth>>1)*xzoom;
		Y -= (PixelHeight>>1)*yzoom;
	}


	//Get Surface info

   ZeroMemory (&SrcInfo, sizeof (DDSURFACEDESC));
   ZeroMemory (&DestInfo, sizeof (DDSURFACEDESC));

   SrcInfo . dwSize = sizeof (DDSURFACEDESC);
   DestInfo . dwSize = sizeof (DDSURFACEDESC);

	ret = src ->GetSurfaceDesc (&SrcInfo );
	if (ret != DD_OK)
	{
//		GlobalError ("Couldn't get surface desc for source\n");
//		DDError (ret,NULL);
	}
	dest->GetSurfaceDesc (&DestInfo);
	if (ret != DD_OK)
	{
//		GlobalError ("Couldn't get surface desc for dest\n");
//		DDError (ret,NULL);
	}
	

	//First rotate the four corners by theta using a basic 2d rotation


	SourceWidth = FXintToReal (SrcInfo.dwWidth);
	SourceHeight = FXintToReal (SrcInfo.dwHeight);

	int xpos;
	int ypos;

	//Since we are rotating a rectangle, vertices 1 and 3 are the same points reflected across y=x
	// vertices 0 and 2 are the same points reflected across y=-x

	real SinTheta =FXdblToReal (sin(Angle*3.14159/180));
	real CosTheta =FXdblToReal (cos(Angle*3.14159/180));

	xpos = -(PixelWidth>>1)*xzoom;
	ypos = -(PixelHeight>>1)*yzoom;

	PolyCoords [0] . x = FXmul (FXintToReal(xpos), CosTheta) - FXmul (FXintToReal(ypos), SinTheta);
	PolyCoords [0] . y = FXmul (FXintToReal(xpos), SinTheta) + FXmul (FXintToReal(ypos), CosTheta);

	PolyCoords [2] . x = -PolyCoords [0] . x + FXintToReal(X);
	PolyCoords [2] . y = -PolyCoords [0] . y + FXintToReal(Y);

	PolyCoords [0] . x += FXintToReal(X);
	PolyCoords [0] . y += FXintToReal(Y);

	xpos = (PixelWidth>>1)*xzoom;
	ypos = -(PixelHeight>>1)*yzoom;

	PolyCoords [1] . x = FXmul (FXintToReal(xpos), CosTheta) - FXmul (FXintToReal(ypos), SinTheta);
	PolyCoords [1] . y = FXmul (FXintToReal(xpos), SinTheta) + FXmul (FXintToReal(ypos), CosTheta);
	PolyCoords [1] . z = 0x10000;	

	PolyCoords [3] . x = -PolyCoords [1] . x +FXintToReal(X);
	PolyCoords [3] . y = -PolyCoords [1] . y +FXintToReal(Y);
	PolyCoords [3] . z = 0x10000;	

	PolyCoords [1] . x += FXintToReal(X);
	PolyCoords [1] . y += FXintToReal(Y);

	TextureCoords [0] . x = FXintToReal (SrcRect . left);
	TextureCoords [0] . y = FXintToReal (SrcRect . top);
	TextureCoords [1] . x = FXintToReal (SrcRect . right-1);
	TextureCoords [1] . y = FXintToReal (SrcRect . top);
	TextureCoords [2] . x = FXintToReal (SrcRect . right-1);
	TextureCoords [2] . y = FXintToReal (SrcRect . bottom-1);
	TextureCoords [3] . x = FXintToReal (SrcRect . left);
	TextureCoords [3] . y = FXintToReal (SrcRect . bottom-1);


  //Now Find the miniumum and maximum vertices

  int MinY, MaxY, MinVert,MaxV, i;

   MinY = FXintToReal(32000);
   MaxY = FXintToReal(-32000);
   for (i=0; i<4; i++) {
      if (PolyCoords[i].y < MinY) {
         MinY = PolyCoords[i].y;
         MinVert = i;
      }
      if (PolyCoords[i].y > MaxY) {
         MaxY = PolyCoords[i].y;
         MaxV = i;
      }
   }


   NumVerts = 4;
   MaxVert = MaxV;
   DestY = FXrealToInt(MinY);

   //Skip zero height polygons, this happens when zooming by small values

   if (MinY >= MaxY) return;

   //Initial set up of edges

   LeftEdge.Direction = -1;     
   SetUpEdgeFast(&LeftEdge, MinVert);
   RightEdge.Direction = 1; 
   SetUpEdgeFast(&RightEdge, MinVert);

   //Set up surface pointers and information

   TexSrc = src;
   TexDest = dest;

   //Lock surfaces

   ZeroMemory (&SrcInfo, sizeof (DDSURFACEDESC));
   ZeroMemory (&DestInfo, sizeof (DDSURFACEDESC));

   SrcInfo . dwSize = sizeof (DDSURFACEDESC);
   DestInfo . dwSize = sizeof (DDSURFACEDESC);

	ret = src -> Lock(NULL,&SrcInfo, DDLOCK_WAIT,NULL);
	if (ret != DD_OK)
	{
//		GlobalError ("Couldn't lock source\n");
//		DDError (ret,NULL);
	}

	ret = dest -> Lock(NULL,&DestInfo, DDLOCK_WAIT,NULL);
	if (ret != DD_OK)
	{
//		GlobalError ("Couldn't lock dest\n");
//		DDError (ret,NULL);
	}

	   if (DestInfo.ddpfPixelFormat.dwRGBBitCount==16)
	   {
		   for (;;) 
		   {
				  if (DestY >= DestRect . bottom) break;
				  if (DestY >= DestRect . top) ScanOutLine16();
				  if (!StepEdgeFast(&LeftEdge))	break;
				  if (!StepEdgeFast(&RightEdge)) break;
				  DestY++;
		   }
	   }
	   else
	   {
		   for (;;) 
		   {
				  if (DestY >= DestRect . bottom) break;
				  if (DestY >= DestRect . top) ScanOutLine();
				  if (!StepEdgeFast(&LeftEdge)) break;
				  if (!StepEdgeFast(&RightEdge)) break;
				  DestY++;
		   }
	   }

   //Unlock Surfaces

	src -> Unlock(NULL);
	dest -> Unlock(NULL);

}

/*
DirectDraw is a trademark of Microsoft Corp.
*/