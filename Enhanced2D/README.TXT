
Enhanced2D Sample Readme
========================

First thank you for using my software. This sample demonstrates the use of
Direct3D Immediate Mode to implement advanced 2D features. It combines
DirectDraw and D3D IM to attain fast alphablending and lit 2D surfaces.


COPYRIGHT AND LICENSE
=====================

Enhanced2D V1.1 (03/08/1999)
Copyright (C) 1999 by Tobias M. Lensing - All rights reserved

LICENSE
~~~~~~~
This software may be used under the terms of the GNU Library General 
Public License which is included to this product.

This is an open-source freeware. Permission to use, copy, modify
or redistribute without fee is hereby granted for any purpose as long
as the above copyright note is included to the product. Please note
that reselling this freeware is strictly forbidden and will not be
tolerated. If you got this software not free of charge please contact
me so that I get to know the distributor.

Important License Notes:
~~~~~~~~~~~~~~~~~~~~~~~~
1. It is forbidden to resell the whole or parts of the source code or
   the binaries of this product. This product is FREEWARE, so please
   treat it as is.
2. This software is distributed as is and there's NO WARRENTY that it
   works correctly or does not damage hardware or software (refer to
   GNU Library General Public License for details)!
3. This software may be treated under the terms of the GNU Library 
   General Public License which is included to this product.


REQUIREMENTS
============

* 486DX or better supported by Windows(R) 95 / 98 / 2000
* Minimum requirements of hardware by DirectX 6.0 / 6.1
* Microsoft(R) Windows(R) 95, 98, 2000 or better
* DirectX 6.0 (or higher) installed on the system
* Graphic accelerator card supporting alphablending and alphatesting

* Pentium II with RivaTNT or Voodoo 2/3 graphic accelerator board recommended

This sample runs with all DirectX compatible graphic boards. 3D acceleration
is not needed, but prefered to speed up effects like alphablending and
gouraud shading (Direct3D).

Note: Games using the Enhanced2D system will be accelerated very strong by
3D graphic accelerators. Without graphic acceleration the software might
not reach high performance, because of the use of software renderer drivers.


HOW THIS SAMPLE WORKS
=====================

This sample consists of the main application and a special module containing
the Sprite3D class which is responsible for Direct3D Immediate Mode
rendering in 2D. The sample first blits a surface using DirectDraw and then
renders a sample sprite over the surface. It is now possible to use the
fast Direct3D Immediate Mode alphablending and vertex lighting.

Note: The sample project was created with Visual C++ 5.0. It does not use
MFC but is based on the Direct3D Framework helper library for Immediate Mode.
The d3dframe.lib file is linked in the LIB directory of this project. For
further details please refer to the source code notes in the modules.


NOTES & COMMENTS
================

General notes for using the Sprite3D class
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
1. Always render the Sprite3D stuff at last in your game (2D and 3D). If
   your whole engine is built on the system of Sprite3D look at the next
   section...
   
2. If you are using Sprite3D with alphablending please note that you have
   to render the sprite at last which is most in front of you, otherwise
   alphablending will not be correct on most graphic boards.

3. If you want to use the interpolated lighting effect that Direct3D
   performs when you light the vertices with different color values, please
   activate Gouraud Shading in Direct3D IM (see Shading Modes in the D3DIM
   docs), otherwise interpolated lighting will not be attained.

Using Sprite3D class in Direct3D games
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
You can generally use Sprite3D in your Direct3D games, but you have to know
some things that Sprite3D does and that you should do, so that Sprite3D can
create correct outputs.

1. Sprite3D is designed to use the advanced effects of Direct3D to speed
   up 2D (3D is also possible) rendering. If your game uses these effects
   you'll have to manage the settings that your game and Sprite3D need.
   This means that you have to deactivate Fog before rendering a sprite
   using Sprite3D and you have to set the right alphablending modes for
   correct rendering.

2. You should always render the sprites at the end of your 2D rendering.
   First render the 3D stuff (if there is some) and then the 2D stuff.
   And when you are finished with your 2D stuff (if there is some) then
   render the Sprite3D stuff.

3. Advanced 2D effects like lense flares can be attained by using the
   Sprite3D class. Please refer to the Direct3D documentation and to the
   general notes for Sprite3D for correct rendering.

Modifying and Extending the Sprite3D class
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
If you achieve enhancements of the Sprite3D class, please send it to me
and I will publish it on my web site. This project is build upon the
open-source principle which means that if you use it for free and enhance
it you should publish your enhancements to give the whole thing a sense.
Thank you!


CONTACT
=======

If you have questions, suggestions or found bugs please don't hesitate to
e-mail me. I will answer all e-mails, but please be a little patient.

Tobias Lensing
e-mail: tobias.lensing@okay.net
ICQ:22102329

(My website will soon be available, there I will publish this via WWW as well)
