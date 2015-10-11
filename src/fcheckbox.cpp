// File: fcheckbox.cpp
// Provides: class FCheckBox

#include "fcheckbox.h"


//----------------------------------------------------------------------
// class FCheckBox
//----------------------------------------------------------------------

// constructor and destructor
//----------------------------------------------------------------------
FCheckBox::FCheckBox(FWidget* parent)
  : FToggleButton(parent)
{
  init();
}

//----------------------------------------------------------------------
FCheckBox::FCheckBox (const FString& txt, FWidget* parent)
  : FToggleButton(txt, parent)
{
  init();
}

//----------------------------------------------------------------------
FCheckBox::~FCheckBox()  // destructor
{ }


// private methods of FCheckBox
//----------------------------------------------------------------------
void FCheckBox::init()
{
  label_offset_pos = 4;
  button_width = 4;
  setVisibleCursor();
}

//----------------------------------------------------------------------
void FCheckBox::draw()
{
  setUpdateVTerm(false);
  drawCheckButton();
  drawLabel();
  setUpdateVTerm(true);

  FToggleButton::draw();
}

//----------------------------------------------------------------------
void FCheckBox::drawCheckButton()
{
  if ( ! isVisible() )
    return;
  gotoxy (xpos+xmin-1, ypos+ymin-1);
  setColor (foregroundColor, backgroundColor);
  if ( isMonochron() )
  {
    if ( hasFocus() )
      setReverse(false);
    else
      setReverse(true);
  }
  if ( checked )
  {
    if ( isNewFont() )
      print (CHECKBOX_ON);
    else
    {
      print ('[');
      print ('x');
      print (']');
    }
  }
  else
  {
    if ( isNewFont() )
      print (CHECKBOX);
    else
    {
      print ('[');
      print (' ');
      print (']');
    }
  }
  if ( isMonochron() )
    setReverse(false);
}
