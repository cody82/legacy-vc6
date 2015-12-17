
                              SkinSys Ver 1.0


     A picture based skin system For MFC. Based on FriendSoft's(www.yeah.net/FriendSoft)
SkinForm.

     CopyRight 2000 Cüneyt ELÝBOL

          www.celibol.freeservers.com
          celibol@hotmail.com

Includes:
   CSkinsys codes
   Simple Skin Editor
   A Beatiful MPEG 1,2,3 decoder (Copyright www.eldos.org < Based On MAPlay Decoder >)
   MPEGPlayer project (not ended. It is only a sample)

Directories
   Decoder: MPEG Decoder codes
   Editor : Skineditor Files
   Sample : Sample Skin Files
   SkinSys: CSkinsys Codes
   Root   : MPEGPlayer Project

Requirement
  This system only required "OleLoadPicture" Function. (Please see LoadPictureFile function in Skindialog.cpp)

How To Use:
   Please Read This notes and see Sample Directory and MPEGPlayer project

   1: Draw mask bitmap
   2: Draw main Bitmap
   3: If you need or want
      a: Draw mouse over bitmap
      b: Draw mouse down bitmap
      c: Draw disable bitmap
   4: Run Skineditor
   5: Select "Screens" Tab
   6: Fill All Pictures
   7: If you want select "Preview" Button
   8: Save and exit
   9: Run Visual Studio
  10: Create a Dialog based new Project (for example Dialog Name = CBaseDialog)
  11: Include "SkinDialog.h" (for example in "StdAfx.h")
  12: Change to CBaseDialog : public CDialog To
                CBaseDialog : public CSkinDialog
  13: Go to CBaseDialog::OnInitDialog
  14: Add these lines
        char m_skin[512];

    	sprintf(m_skin, "<Your Skin Name>");
// If you want a menu < Activate to Right click > add this line
    	SetMenuID(IDR_MAINMENU);
// If you Want Caption 
    	SetWindowText("MPEG Player");
// Set To My SkinFile
     	SetSkinFile(m_skin);
      CSkinDialog::OnInitDialog();
  15: Compile and Run;

Controlling Buttons Click, Trackbar, ProgressBar, Text and etc...

  If you want these events in the Base Class (CSkinDialog)

	1: void ProgresChanged(CString m_Name); // If progress changes
	2: void MouseMoved(CString m_ButtonName, int x, int y); // if Mouse Moved
	3: void TrackChange(CString m_ButtonName, UINT nSBCode, UINT nPos); // if Trackbar change
	4: void ButtonPressed(CString m_ButtonName); // if Button Pressed

  you are added these functions your CBaseDialog class.

Changing the tooltip
    use Set<xxx>ToolTip function. Where <xxx> is Button, Text...
	(for example SetButtonToolTip("BUTTON_USEEQ", "Equalizer is On");

Getting Value
    use Get<xxx> Function 
          (for example: BOOL useEQ = GetButtonCheck("BUTTON_USEEQ"); // if BUTTON_USEEQ checked)

Setting Value
    use Set<xxx> Function 
          (for example: SetButtonCheck("BUTTON_USEEQ", useEQ); 
     // if useEQ = True BUTTON_USEEQ is checked)

Notes:
  Thanks for enterested to CSkinsys. But this is first release. It may have any bug and error.
Please report any bug and error or any question to me.

