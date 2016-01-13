//---------------------------------------------------------------------------
// Copyright 2015 Scott Swift - This program is distributed under the
// terms of the GNU General Public License.
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("ServerImporter.res");
USEFORM("MainForm.cpp", XirconForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  try
  {
     Application->Initialize();
     Application->Title = "Server-Importer";
     Application->CreateForm(__classid(TXirconForm), &XirconForm);
     Application->Run();
  }
  catch (Exception &exception)
  {
     Application->ShowException(&exception);
  }
  return 0;
}
//---------------------------------------------------------------------------
