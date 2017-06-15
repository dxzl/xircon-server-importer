//---------------------------------------------------------------------------
// Software by Scott Swift - This program is distributed under the
// terms of the GNU General Public License. Use and distribute freely.
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "MainForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

// By Scott M. Swift www.yahcolorize.com,
// dxzl@live.com June. 15, 2017

TFormMain *FormMain;

String FileName;
String RegKey;

//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
  : TForm(Owner)
{
  RegKey = DEFAULT_KEY;
  Edit1->Text = RegKey;
	FileName = "save1.txt";

  ButtonReadXirc->Hint = "Load your present XiRcon servers\n"
                    "from the Windows registry into\n"
                    "the edit window";

  ButtonMergeServers->Hint =
                    "Merges and sorts servers shown in the edit\n"
                    "window with your current XiRCON servers";

  ButtonProcess->Hint = "Convert the mIRC servers into XiRCON format.";

  ButtonEraseXirc->Hint = "Caution: Deletes your present XiRCON\n"
                          "server list from the Windows registry!";

  LinkLabel->Caption = "Click For Servers: " + String(MIRC_LINK);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonReadMircClick(TObject *Sender)
{
  try
  {
    OpenDialog1->Title = "Open File";
    OpenDialog1->DefaultExt = "ini";
    OpenDialog1->Filter = "Ini files (*.ini)|*.ini|"
                  "Text files (*.txt)|*.txt|"
             "All files (*.*)|*.*";
    OpenDialog1->FilterIndex = 1; // start the dialog showing ini files
    OpenDialog1->Options.Clear();
    OpenDialog1->Options << ofHideReadOnly
    << ofPathMustExist << ofFileMustExist << ofEnableSizing;

    if ( !OpenDialog1->Execute() )
    {
      Memo1->SetFocus();
      return; // Cancel
    }

    Memo1->Clear();

		FileName = OpenDialog1->FileName;

    // Load ini file
    Memo1->Lines->LoadFromFile( FileName );
  }
  catch(...)
  {
    ShowMessage("Can't load file: \"" + OpenDialog1->FileName + "\"" );
  }
  
  Memo1->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonProcessClick(TObject *Sender)
{
  String TempStr, TempLower, ServerStr;
  String GroupStr, KeyStr, PortStr;

  int ServerPosition, GroupPosition, PortPosition, Count;

  bool HaveServers = false;

  Count = Memo1->Lines->Count;

  for( int ii = 0 ; ii < Count ; ii++ )
  {
    TempStr = Memo1->Lines->Strings[0].Trim();
    Memo1->Lines->Delete(0); // Delete this line
    TempLower = TempStr.LowerCase();

    if ( !HaveServers )
    {
      if ( TempLower.Pos( "[servers]" ) != 0 )
        HaveServers = true;
    }
    else
    {
      ServerPosition = TempLower.Pos( "server:" );
      GroupPosition = TempLower.Pos( "group:" );

      if ( ServerPosition && GroupPosition )
      {
        // Get server string with ports and ":"
        ServerStr = TempStr.SubString( ServerPosition+7,
             (GroupPosition-ServerPosition)-7);

        // Find start of ports, if any
        PortPosition = ServerStr.Pos( ":" );

        if ( CheckBoxForcePorts->Checked && MaskEdit1->Text.Length() != 0 )
          PortStr = MaskEdit1->Text; // force single port
        else if ( PortPosition )
        {
          PortStr = ServerStr.SubString( PortPosition+1,
             ((ServerStr.Length()+1)-PortPosition)-1);
        }
        else // no port, no ":"
          PortStr = "";

          // Get server string without ports or ":"
        if ( PortPosition )
          ServerStr = ServerStr.SubString( 1, PortPosition );

        GroupStr = TempStr.SubString( GroupPosition+6,
           ((TempStr.Length()+1)-GroupPosition)-6);

        KeyStr = GroupStr.Trim() + "/" + ServerStr.Trim() + PortStr.Trim();
        Memo1->Lines->Add( KeyStr );
      }
    }
  }

  if ( !HaveServers || Memo1->Lines->Count == 0 )
    ShowMessage("The processed data had an invalid mIRC servers.ini format");

  Memo1->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Edit1Change(TObject *Sender)
{
  RegKey = Edit1->Text;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonEraseXircClick(TObject *Sender)
{
  if ( EraseXircServers() )
    ShowMessage("List deleted");
  else
    ShowMessage("List could not be deleted");

  Memo1->SetFocus();
}
//---------------------------------------------------------------------------
bool __fastcall TFormMain::EraseXircServers( void )
// Delete XiRCON Server list
{
  TRegistry * MyRegistry = new TRegistry();

  try
  {
    MyRegistry->RootKey = HKEY_CURRENT_USER;

    try
    {
      MyRegistry->DeleteKey(RegKey);
    }
    catch(ERegistryException &E)
    {
      return false;
    }
  }
  __finally
  {
    if ( MyRegistry )
      delete MyRegistry;
  }

  return true;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonHelpClick(TObject *Sender)
{
  Memo1->Lines->Text =
 "To delete this text, right click, choose \"Clear\".\n"
 "\n"
 "Follow these steps, in order, to merge new servers with your existing XiRCON server-list:\n"
 "1) Click \"Read mIRC Servers\" to import an existing mIRC \"servers.ini\" file.\n"
 "2) Click \"Convert mIRC to XiRCON\" to convert the mIRC format into XiRCON registry keys.\n"
 "3) Click \"Merge, Sort, Write XiRCON Servers\" to write the new, merged XiRCON server-list.\n"
 "\n"
 "Optionally:\n"
 "**CAUTION** Click \"Erase XiRCON Servers\" to erase the old XiRCON server-list.\n"
 "Click \"Read XiRCON Servers\" to check the new XiRCON server list.\n"
 "Click \"Save As\" to write whatever is in the edit window to a file.\n"
 "\n"
 "Notes: You will need administrator privileges to run this program.\n"
 "This program was written and tested using Windows XP.\n"
 "\n"
 "Freeware Chat utility by Scott M. Swift,\n"
 "Original Release 2002. Updated 2013. Post to GitHub 2015.";

  Memo1->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonReadXircClick(TObject *Sender)
{
  TStringList* pSl = new TStringList();

  try
  {
    if ( ReadXircServers( pSl ) )
      Memo1->Lines->Assign(pSl);
  }
  __finally
  {
    if ( pSl )
      delete pSl;
  }

  Memo1->SetFocus();
}
//---------------------------------------------------------------------------
bool __fastcall TFormMain::ReadXircServers( TStringList *pSl )
{
  TRegistry * MyRegistry = new TRegistry();

  try
  {
    MyRegistry->RootKey = HKEY_CURRENT_USER;

    if ( !MyRegistry->OpenKey(RegKey, false) )
    {
      ShowMessage("Registry key specified does not exist: ReadXircServers()");
      return false; // if no key, quit
    }

    // Get Info structure
    TRegKeyInfo rki;
    if ( !MyRegistry->GetKeyInfo( rki ) )
    {
      ShowMessage("Unable to read registry key info: ReadXircServers()");
      return false;
    }

    // We handle 001 to 999 (000 is Default)
    if ( rki.NumValues > 999 )
    {
      ShowMessage("XiRCON Server list is full: ReadXircServers()");
      return false;
    }

    String StrIdx;
    int RegIndex = 1;

    for ( int ii = 0; ii < rki.NumValues && RegIndex < 1000 ; ii++ )
    {
      try
      {
        StrIdx = String( RegIndex );

        if ( RegIndex < 100 )
          StrIdx.Insert( "0", 1 );
        if ( RegIndex < 10 )
          StrIdx.Insert( "0", 1 );

        RegIndex++; // Do this prior to possibly throwing an exception!

        if ( MyRegistry->ValueExists( StrIdx ) )
          pSl->Add( MyRegistry->ReadString(StrIdx) );

      } catch(...) {
      }
    }
  }
  __finally
  {
    try {
      if ( MyRegistry )
        MyRegistry->CloseKey();
    } catch(...) {
    }
    try {
      if ( MyRegistry )
        delete MyRegistry;
    } catch(...) {
    }
  }

  if ( pSl->Count )
    return true;

  return false;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonMergeServersClick(TObject *Sender)
{
  if ( Memo1->Lines->Count == 0 )
  {
    ShowMessage("No keys to write... first import from mIRC.ini");
    return;
  }

  String StrIdx, TempStr;

  TStringList* pSlNew = new TStringList();
  TStringList* pSlOld = new TStringList();
  TRegistry * MyRegistry = new TRegistry();

  try
  {
    if ( !pSlNew || !pSlOld  )
    {
      ShowMessage("Unable to create string-list!");
      return;
    }

    // Purge duplicates from new mIRC Memo1 servers...
    if ( CheckBoxElimDups->Checked )
    {
      pSlNew->Sorted = true;
	  pSlNew->Duplicates = System::Types::dupIgnore;
	  pSlOld->Sorted = true;
	  pSlOld->Duplicates = System::Types::dupIgnore;
	}
	else
	{
	  pSlNew->Sorted = false;
	  pSlNew->Duplicates = System::Types::dupAccept;
	  pSlOld->Sorted = false;
      pSlOld->Duplicates = System::Types::dupAccept;
    }

    // Fill StringList from new servers in Memo1, possibly sorting
    // and purging duplicates.
    pSlNew->AddStrings(Memo1->Lines);

    // Read existing server-list
    bool bHaveExisting = ReadXircServers( pSlOld );

    if ( bHaveExisting )
    {
      if ( !EraseXircServers() )
      {
        ShowMessage("Unable to erase old server-list!");
        return;
      }
    }

    MyRegistry->RootKey = HKEY_CURRENT_USER;

    if ( !MyRegistry->OpenKey(RegKey, true) )
    {
      ShowMessage("Unable to create registry key!");
      return;
    }

    // Merge the old list into the new...
    pSlNew->AddStrings(pSlOld);

    int RegIndex = 1;
    int NewIndex = 0;
    String TempStr;

    // Start writing merged server-list, up to 999 max
    for ( ; NewIndex < pSlNew->Count && RegIndex < 1000; NewIndex++ )
    {
      try
      {
        StrIdx = String( RegIndex );

        if ( RegIndex < 100 )
          StrIdx.Insert( "0", 1 );

        if ( RegIndex < 10 )
          StrIdx.Insert( "0", 1 );

        TempStr = pSlNew->Strings[NewIndex];

        if ( TempStr.Length() )
          MyRegistry->WriteString( StrIdx, TempStr );

        RegIndex++;
      }
      catch(...)
      {
        ShowMessage("Registry-write error during list merge!\n" + TempStr);
        return;
      }
    }

    ShowMessage("Wrote " + String(RegIndex-1) + " total servers!" );
    if ( pSlNew->Count > 999 )
      ShowMessage("Warning, " + String(pSlNew->Count-999) + " server(s)\n"
          "were not written because list is full..." );
  }
  __finally
  {
    try {
      if ( pSlNew != NULL )
        delete pSlNew;
      if ( pSlOld != NULL )
        delete pSlOld;
    } catch(...) {
    }
    try {
      if ( MyRegistry != NULL ) MyRegistry->CloseKey();
    } catch(...) {
    }
    try {
      if ( MyRegistry != NULL )
        delete MyRegistry;
    } catch(...) {
    }
  }

  Memo1->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Button6Click(TObject *Sender)
{
  RegKey = DEFAULT_KEY;
  Edit1->Text = RegKey;
  Edit1->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonSaveAsClick(TObject *Sender)
{
  try
  {
    SaveDialog1->Title = "Save File";
    SaveDialog1->DefaultExt = "txt";
    SaveDialog1->Filter = "Text files (*.txt)|*.txt|"
             "All files (*.*)|*.*";
    SaveDialog1->FilterIndex = 2; // start the dialog showing all files
    SaveDialog1->Options.Clear();
    SaveDialog1->Options << ofHideReadOnly
     << ofPathMustExist << ofOverwritePrompt << ofEnableSizing
        << ofNoReadOnlyReturn;
    SaveDialog1->FileName = FileName;

  	if (SaveDialog1->Execute())
    {
      FileName = SaveDialog1->FileName;
      Memo1->Lines->SaveToFile( FileName );
    }
  }
  catch(...)
  {
    ShowMessage("Can't save file: \"" + SaveDialog1->FileName + "\"" );
  }

  Memo1->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::CheckBoxForcePortsClick(TObject *Sender)
{
  if ( CheckBoxForcePorts->Checked )
    MaskEdit1->Visible = true;
  else
    MaskEdit1->Visible = false;

  Memo1->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::LinkLabelClick(TObject *Sender)
{
  // launch default web-browser
  //ShellExecute(Handle, "open", "iexplore.exe",
  //                 Iftf->Strings[INFO_WEB_SITE].c_str(), NULL, SW_SHOW);
  ShellExecute(NULL, L"open", MIRC_LINK, NULL, NULL, SW_SHOWNORMAL);
  Memo1->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Clear1Click(TObject *Sender)
{
  Memo1->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Cut1Click(TObject *Sender)
{
  Memo1->CutToClipboard();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Copy1Click(TObject *Sender)
{
  Memo1->CopyToClipboard();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Paste1Click(TObject *Sender)
{
  Memo1->PasteFromClipboard();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::SelectALL1Click(TObject *Sender)
{
  Memo1->SelectAll();
}
//---------------------------------------------------------------------------

