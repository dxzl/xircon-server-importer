//---------------------------------------------------------------------------
// Copyright 2008 Scott Swift - This program is distributed under the
// terms of the GNU General Public License.
//---------------------------------------------------------------------------
// DESCRIPTION:
// This program converts a servers.ini file for the mIRC IRC chat-client
// into a server-list the XiRCON IRC chat-client can use and saves them
// in your registry. The next time you start XiRCON, the new servers will
// be appended to your old servers-list. The program also weeds-out
// redundant servers.
//
// Download the mIRC servers list:
//   http://mIRC.co.uk/servers.ini
//
// For instructions, run ServerImporter.exe and click the Help button.
//---------------------------------------------------------------------------
#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
//#include <Vcl.OleCtrls.hpp>
//#include <Vcl.DdeMan.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Mask.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Menus.hpp>
#include <System.Classes.hpp>
#include <Registry.hpp>
//---------------------------------------------------------------------------
// Registry path to XiRCON's Info
#define DEFAULT_KEY "\\software\\XiRCON\\1.0\\Default\\Connection\\ServerTree"
// Web-link for mIRC servers.ini file
#define MIRC_LINK L"http://www.mirc.co.uk/servers.ini"
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:  // IDE-managed Components
  TPanel *Panel1;
  TButton *ButtonReadMirc;
  TButton *ButtonReadXirc;
  TButton *ButtonMergeServers;
  TButton *ButtonEraseXirc;
  TOpenDialog *OpenDialog1;
  TMemo *Memo1;
  TButton *ButtonProcess;
  TButton *ButtonHelp;
  TButton *ButtonSaveAs;
  TSaveDialog *SaveDialog1;
  TCheckBox *CheckBoxForcePorts;
  TMaskEdit *MaskEdit1;
  TEdit *Edit1;
  TButton *ButtonDefRegKey;
  TLabel *Label3;
  TGroupBox *GroupBox1;
  TLabel *LinkLabel;
  TCheckBox *CheckBoxElimDups;
  TPopupMenu *PopupMenu1;
  TMenuItem *c1;
  TMenuItem *SelectALL1;
  TMenuItem *Copy1;
  TMenuItem *Paste1;
  TMenuItem *Cut1;
  TMenuItem *N1;
  TMenuItem *N2;
  void __fastcall ButtonReadMircClick(TObject *Sender);
  void __fastcall ButtonReadXircClick(TObject *Sender);
  bool __fastcall ReadXircServers( TStringList *pSl );
  void __fastcall ButtonMergeServersClick(TObject *Sender);
  void __fastcall ButtonEraseXircClick(TObject *Sender);
  void __fastcall EraseXircServers( void );
  void __fastcall ButtonProcessClick(TObject *Sender);
  void __fastcall ButtonDefRegKeyClick(TObject *Sender);
  void __fastcall ButtonHelpClick(TObject *Sender);
  void __fastcall Edit1Change(TObject *Sender);
  void __fastcall ButtonSaveAsClick(TObject *Sender);
  void __fastcall CheckBoxForcePortsClick(TObject *Sender);
  void __fastcall LinkLabelClick(TObject *Sender);
  void __fastcall Clear1Click(TObject *Sender);
  void __fastcall Cut1Click(TObject *Sender);
  void __fastcall Copy1Click(TObject *Sender);
  void __fastcall Paste1Click(TObject *Sender);
  void __fastcall SelectALL1Click(TObject *Sender);
private:  // User declarations
  bool bServersProcessed;
public:    // User declarations
  __fastcall TFormMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
