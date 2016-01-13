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
#include <Buttons.hpp>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <OleCtrls.hpp>
#include <StdCtrls.hpp>
#include <vcspell3.hpp>
#include <DdeMan.hpp>
#include <Registry.hpp>
#include <Mask.hpp>
//---------------------------------------------------------------------------
// Registry path to XiRCON's Info
#define DEFAULT_KEY "\\software\\XiRCON\\1.0\\Default\\Connection\\ServerTree"
// Web-link for mIRC servers.ini file
#define MIRC_LINK "http://www.mirc.co.uk/servers.ini"
//---------------------------------------------------------------------------
class TXirconForm : public TForm
{
__published:	// IDE-managed Components
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
  TButton *Button6;
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
  bool __fastcall EraseXircServers( void );
  void __fastcall ButtonProcessClick(TObject *Sender);
  void __fastcall Button6Click(TObject *Sender);
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
private:	// User declarations
  bool bServersProcessed;
public:		// User declarations
  __fastcall TXirconForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TXirconForm *XirconForm;
//---------------------------------------------------------------------------
#endif
