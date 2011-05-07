// ************************************************************************ //
// WARNING                                                                    
// -------                                                                    
// The types declared in this file were generated from data read from a       
// Type Library. If this type library is explicitly or indirectly (via        
// another type library referring to this type library) re-imported, or the   
// 'Refresh' command of the Type Library Editor activated while editing the   
// Type Library, the contents of this file will be regenerated and all        
// manual modifications will be lost.                                         
// ************************************************************************ //

// $Rev: 18756 $
// File generated on 06.12.2010 18:48:32 from Type Library described below.

// ************************************************************************  //
// Type Lib: C:\WINDOWS\system32\wmp.dll (1)
// LIBID: {6BF52A50-394A-11D3-B153-00C04F79FAA6}
// LCID: 0
// Helpfile: 
// HelpString: Windows Media Player
// DepndLst: 
//   (1) v2.0 stdole, (C:\WINDOWS\system32\stdole2.tlb)
// Errors:
//   Hint: Symbol 'Click' renamed to '_Click'
//   Hint: Symbol 'Click' renamed to '_Click'
//   Hint: Symbol 'Click' renamed to '_Click'
//   Hint: Symbol 'Click' renamed to '_Click'
// ************************************************************************ //

#include <vcl.h>
#pragma hdrstop

#include <olectrls.hpp>
#include <oleserver.hpp>
#if defined(USING_ATL)
#include <atl\atlvcl.h>
#endif

#include "WMPLib_OCX.h"

#if !defined(__PRAGMA_PACKAGE_SMART_INIT)
#define      __PRAGMA_PACKAGE_SMART_INIT
#pragma package(smart_init)
#endif

namespace Wmplib_tlb
{



// *********************************************************************//
// OCX PROXY CLASS IMPLEMENTATION
// (The following variables/methods implement the class TWindowsMediaPlayer which
// allows "Windows Media Player ActiveX Control" to be hosted in CBuilder IDE/apps).
// *********************************************************************//
int   TWindowsMediaPlayer::EventDispIDs[62] = {
    0x00001389, 0x000013ED, 0x000013EE, 0x0000138A, 0x000014B5, 0x0000151B,
    0x00001519, 0x0000151A, 0x0000157D, 0x000015E1, 0x00001451, 0x00001452,
    0x00001453, 0x00001454, 0x00001645, 0x000016A9, 0x000016AC, 0x000016AD,
    0x000016AA, 0x000016AB, 0x000016AE, 0x000016AF, 0x000016B0, 0x000016B1,
    0x000016BC, 0x000016B2, 0x000016B3, 0x000016B4, 0x000016BA, 0x000016BB,
    0x000016BD, 0x000016BF, 0x000016BE, 0x00001965, 0x00001966, 0x00001967,
    0x00001968, 0x00001969, 0x0000196A, 0x0000196B, 0x0000196C, 0x0000196D,
    0x0000196E, 0x0000196F, 0x00001970, 0x00001971, 0x00001972, 0x00001973,
    0x00001974, 0x00001975, 0x00001976, 0x00001977, 0x00001978, 0x00001979,
    0x0000197A, 0x0000197B, 0x0000197C, 0x0000197D, 0x0000197E, 0x000016C0,
    0x000016C1, 0x000016C2};

TControlData2 TWindowsMediaPlayer::CControlData =
{
  // GUID of CoClass and Event Interface of Control
  {0x6BF52A52, 0x394A, 0x11D3,{ 0xB1, 0x53, 0x00,0xC0, 0x4F, 0x79,0xFA, 0xA6} }, // CoClass
  {0x6BF52A51, 0x394A, 0x11D3,{ 0xB1, 0x53, 0x00,0xC0, 0x4F, 0x79,0xFA, 0xA6} }, // Events

  // Count of Events and array of their DISPIDs
  62, &EventDispIDs,

  // Pointer to Runtime License string
  NULL,  // HRESULT(0x80004002)

  // Flags for OnChanged PropertyNotification
  0x00000000,
  401,// (IDE Version)

  // Count of Font Prop and array of their DISPIDs
  0, Activex::PDispIDList(NULL),

  // Count of Pict Prop and array of their DISPIDs
  0, Activex::PDispIDList(NULL),
  0, // Reserved
  0, // Instance count (used internally)
  0, // List of Enum descriptions (internal)
};

GUID     TWindowsMediaPlayer::DEF_CTL_INTF = {0x6C497D62, 0x8919, 0x413C,{ 0x82, 0xDB, 0xE9,0x35, 0xFB, 0x3E,0xC5, 0x84} };
TNoParam TWindowsMediaPlayer::OptParam;

static inline void ValidCtrCheck(TWindowsMediaPlayer *)
{
   delete new TWindowsMediaPlayer((TComponent*)(0));
};

void __fastcall TWindowsMediaPlayer::InitControlData()
{
  ControlData = (TControlData*)&CControlData;
  CControlData.FirstEventOfs = System::PByte(&FOnOpenStateChange) - System::PByte(this);
};

void __fastcall TWindowsMediaPlayer::CreateControl()
{
  if (!m_OCXIntf)
  {
    _ASSERTE(DefaultDispatch);
    DefaultDispatch->QueryInterface(DEF_CTL_INTF, (LPVOID*)&m_OCXIntf);
  }
};

IWMPPlayer4Disp __fastcall TWindowsMediaPlayer::GetDefaultInterface()
{
  CreateControl();
  return m_OCXIntf;
};

void __fastcall TWindowsMediaPlayer::close(void)
{
  GetDefaultInterface()->close();
}

void __fastcall TWindowsMediaPlayer::launchURL(BSTR bstrURL/*[in]*/)
{
  GetDefaultInterface()->launchURL(bstrURL/*[in]*/);
}

Wmplib_tlb::IWMPPlaylist* __fastcall TWindowsMediaPlayer::newPlaylist(BSTR bstrName/*[in]*/, 
                                                                      BSTR bstrURL/*[in]*/)
{
  Wmplib_tlb::IWMPPlaylist* ppPlaylist = 0;
  OLECHECK(GetDefaultInterface()->newPlaylist(bstrName, bstrURL, (Wmplib_tlb::IWMPPlaylist**)&ppPlaylist));
  return ppPlaylist;
}

Wmplib_tlb::IWMPMedia* __fastcall TWindowsMediaPlayer::newMedia(BSTR bstrURL/*[in]*/)
{
  Wmplib_tlb::IWMPMedia* ppMedia = 0;
  OLECHECK(GetDefaultInterface()->newMedia(bstrURL, (Wmplib_tlb::IWMPMedia**)&ppMedia));
  return ppMedia;
}

void __fastcall TWindowsMediaPlayer::openPlayer(BSTR bstrURL/*[in]*/)
{
  GetDefaultInterface()->openPlayer(bstrURL/*[in]*/);
}

Wmplib_tlb::IWMPControlsPtr __fastcall TWindowsMediaPlayer::get_controls(void)
{
  Wmplib_tlb::IWMPControlsPtr ppControl;
  OLECHECK(GetDefaultInterface()->get_controls(&ppControl));
  return ppControl;
}

Wmplib_tlb::IWMPSettingsPtr __fastcall TWindowsMediaPlayer::get_settings(void)
{
  Wmplib_tlb::IWMPSettingsPtr ppSettings;
  OLECHECK(GetDefaultInterface()->get_settings(&ppSettings));
  return ppSettings;
}

Wmplib_tlb::IWMPMediaPtr __fastcall TWindowsMediaPlayer::get_currentMedia(void)
{
  Wmplib_tlb::IWMPMediaPtr ppMedia;
  OLECHECK(GetDefaultInterface()->get_currentMedia(&ppMedia));
  return ppMedia;
}

void __fastcall TWindowsMediaPlayer::set_currentMedia(Wmplib_tlb::IWMPMediaPtr ppMedia/*[in]*/)
{
  GetDefaultInterface()->set_currentMedia(ppMedia/*[in]*/);
}

Wmplib_tlb::IWMPMediaCollectionPtr __fastcall TWindowsMediaPlayer::get_mediaCollection(void)
{
  Wmplib_tlb::IWMPMediaCollectionPtr ppMediaCollection;
  OLECHECK(GetDefaultInterface()->get_mediaCollection(&ppMediaCollection));
  return ppMediaCollection;
}

Wmplib_tlb::IWMPPlaylistCollectionPtr __fastcall TWindowsMediaPlayer::get_playlistCollection(void)
{
  Wmplib_tlb::IWMPPlaylistCollectionPtr ppPlaylistCollection;
  OLECHECK(GetDefaultInterface()->get_playlistCollection(&ppPlaylistCollection));
  return ppPlaylistCollection;
}

Wmplib_tlb::IWMPNetworkPtr __fastcall TWindowsMediaPlayer::get_network(void)
{
  Wmplib_tlb::IWMPNetworkPtr ppQNI;
  OLECHECK(GetDefaultInterface()->get_network(&ppQNI));
  return ppQNI;
}

Wmplib_tlb::IWMPPlaylistPtr __fastcall TWindowsMediaPlayer::get_currentPlaylist(void)
{
  Wmplib_tlb::IWMPPlaylistPtr ppPL;
  OLECHECK(GetDefaultInterface()->get_currentPlaylist(&ppPL));
  return ppPL;
}

void __fastcall TWindowsMediaPlayer::set_currentPlaylist(Wmplib_tlb::IWMPPlaylistPtr ppPL/*[in]*/)
{
  GetDefaultInterface()->set_currentPlaylist(ppPL/*[in]*/);
}

Wmplib_tlb::IWMPCdromCollectionPtr __fastcall TWindowsMediaPlayer::get_cdromCollection(void)
{
  Wmplib_tlb::IWMPCdromCollectionPtr ppCdromCollection;
  OLECHECK(GetDefaultInterface()->get_cdromCollection(&ppCdromCollection));
  return ppCdromCollection;
}

Wmplib_tlb::IWMPClosedCaptionPtr __fastcall TWindowsMediaPlayer::get_closedCaption(void)
{
  Wmplib_tlb::IWMPClosedCaptionPtr ppClosedCaption;
  OLECHECK(GetDefaultInterface()->get_closedCaption(&ppClosedCaption));
  return ppClosedCaption;
}

Wmplib_tlb::IWMPErrorPtr __fastcall TWindowsMediaPlayer::get_Error(void)
{
  Wmplib_tlb::IWMPErrorPtr ppError;
  OLECHECK(GetDefaultInterface()->get_Error(&ppError));
  return ppError;
}

Wmplib_tlb::IWMPDVDPtr __fastcall TWindowsMediaPlayer::get_dvd(void)
{
  Wmplib_tlb::IWMPDVDPtr ppDVD;
  OLECHECK(GetDefaultInterface()->get_dvd(&ppDVD));
  return ppDVD;
}

Wmplib_tlb::IWMPPlayerApplicationPtr __fastcall TWindowsMediaPlayer::get_playerApplication(void)
{
  Wmplib_tlb::IWMPPlayerApplicationPtr ppIWMPPlayerApplication;
  OLECHECK(GetDefaultInterface()->get_playerApplication(&ppIWMPPlayerApplication));
  return ppIWMPPlayerApplication;
}

IWMPButtonCtrlPtr& TWMPButtonCtrl::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TWMPButtonCtrl::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TWMPButtonCtrl::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TWMPButtonCtrl::Disconnect()
{
  if (m_DefaultIntf) {

    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TWMPButtonCtrl::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TWMPButtonCtrl::ConnectTo(IWMPButtonCtrlPtr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TWMPButtonCtrl::InitServerData()
{
  static Oleserver::TServerData sd;
  sd.ClassID = CLSID_WMPButtonCtrl;
  sd.IntfIID = __uuidof(IWMPButtonCtrl);
  sd.EventIID= __uuidof(IWMPButtonCtrlEvents);
  ServerData = &sd;
}

void __fastcall TWMPButtonCtrl::InvokeEvent(int id, Oleserver::TVariantArray& params)
{
  switch(id)
  {
    case 5120: {
      if (Ononclick) {
        (Ononclick)(this);
      }
      break;
      }
    default:
      break;
  }
}

BSTR __fastcall TWMPButtonCtrl::get_image(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_image((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPButtonCtrl::set_image(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_image(pVal/*[in]*/);
}

BSTR __fastcall TWMPButtonCtrl::get_hoverImage(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_hoverImage((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPButtonCtrl::set_hoverImage(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_hoverImage(pVal/*[in]*/);
}

BSTR __fastcall TWMPButtonCtrl::get_downImage(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_downImage((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPButtonCtrl::set_downImage(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_downImage(pVal/*[in]*/);
}

BSTR __fastcall TWMPButtonCtrl::get_disabledImage(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_disabledImage((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPButtonCtrl::set_disabledImage(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_disabledImage(pVal/*[in]*/);
}

BSTR __fastcall TWMPButtonCtrl::get_hoverDownImage(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_hoverDownImage((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPButtonCtrl::set_hoverDownImage(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_hoverDownImage(pVal/*[in]*/);
}

VARIANT_BOOL __fastcall TWMPButtonCtrl::get_tiled(void)
{
  VARIANT_BOOL pVal;
  OLECHECK(GetDefaultInterface()->get_tiled((VARIANT_BOOL*)&pVal));
  return pVal;
}

void __fastcall TWMPButtonCtrl::set_tiled(VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_tiled(pVal/*[in]*/);
}

BSTR __fastcall TWMPButtonCtrl::get_transparencyColor(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_transparencyColor((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPButtonCtrl::set_transparencyColor(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_transparencyColor(pVal/*[in]*/);
}

VARIANT_BOOL __fastcall TWMPButtonCtrl::get_down(void)
{
  VARIANT_BOOL pVal;
  OLECHECK(GetDefaultInterface()->get_down((VARIANT_BOOL*)&pVal));
  return pVal;
}

void __fastcall TWMPButtonCtrl::set_down(VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_down(pVal/*[in]*/);
}

VARIANT_BOOL __fastcall TWMPButtonCtrl::get_sticky(void)
{
  VARIANT_BOOL pVal;
  OLECHECK(GetDefaultInterface()->get_sticky((VARIANT_BOOL*)&pVal));
  return pVal;
}

void __fastcall TWMPButtonCtrl::set_sticky(VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_sticky(pVal/*[in]*/);
}

BSTR __fastcall TWMPButtonCtrl::get_upToolTip(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_upToolTip((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPButtonCtrl::set_upToolTip(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_upToolTip(pVal/*[in]*/);
}

BSTR __fastcall TWMPButtonCtrl::get_downToolTip(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_downToolTip((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPButtonCtrl::set_downToolTip(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_downToolTip(pVal/*[in]*/);
}

BSTR __fastcall TWMPButtonCtrl::get_cursor(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_cursor((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPButtonCtrl::set_cursor(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_cursor(pVal/*[in]*/);
}

IWMPListBoxCtrlPtr& TWMPListBoxCtrl::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TWMPListBoxCtrl::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TWMPListBoxCtrl::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TWMPListBoxCtrl::Disconnect()
{
  if (m_DefaultIntf) {

    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TWMPListBoxCtrl::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TWMPListBoxCtrl::ConnectTo(IWMPListBoxCtrlPtr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TWMPListBoxCtrl::InitServerData()
{
  static Oleserver::TServerData sd;
  sd.ClassID = CLSID_WMPListBoxCtrl;
  sd.IntfIID = __uuidof(IWMPListBoxCtrl);
  sd.EventIID= GUID_NULL;
  ServerData = &sd;
}

BSTR __fastcall TWMPListBoxCtrl::getItem(long nPos/*[in]*/)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->getItem(nPos, (BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPListBoxCtrl::insertItem(long nPos/*[in]*/, BSTR newVal/*[in]*/)
{
  GetDefaultInterface()->insertItem(nPos/*[in]*/, newVal/*[in]*/);
}

void __fastcall TWMPListBoxCtrl::appendItem(BSTR newVal/*[in]*/)
{
  GetDefaultInterface()->appendItem(newVal/*[in]*/);
}

void __fastcall TWMPListBoxCtrl::replaceItem(long nPos/*[in]*/, BSTR newVal/*[in]*/)
{
  GetDefaultInterface()->replaceItem(nPos/*[in]*/, newVal/*[in]*/);
}

void __fastcall TWMPListBoxCtrl::deleteItem(long nPos/*[in]*/)
{
  GetDefaultInterface()->deleteItem(nPos/*[in]*/);
}

void __fastcall TWMPListBoxCtrl::deleteAll(void)
{
  GetDefaultInterface()->deleteAll();
}

long __fastcall TWMPListBoxCtrl::findItem(long nStartIndex/*[in]*/, BSTR newVal/*[in]*/)
{
  long pnPos;
  OLECHECK(GetDefaultInterface()->findItem(nStartIndex, newVal, (long*)&pnPos));
  return pnPos;
}

long __fastcall TWMPListBoxCtrl::getNextSelectedItem(long nStartIndex/*[in]*/)
{
  long pnSelected;
  OLECHECK(GetDefaultInterface()->getNextSelectedItem(nStartIndex, (long*)&pnSelected));
  return pnSelected;
}

void __fastcall TWMPListBoxCtrl::setSelectedState(long nPos/*[in]*/, VARIANT_BOOL vbSelected/*[in]*/)
{
  GetDefaultInterface()->setSelectedState(nPos/*[in]*/, vbSelected/*[in]*/);
}

void __fastcall TWMPListBoxCtrl::show(void)
{
  GetDefaultInterface()->show();
}

void __fastcall TWMPListBoxCtrl::dismiss(void)
{
  GetDefaultInterface()->dismiss();
}

long __fastcall TWMPListBoxCtrl::get_selectedItem(void)
{
  long pnPos;
  OLECHECK(GetDefaultInterface()->get_selectedItem((long*)&pnPos));
  return pnPos;
}

void __fastcall TWMPListBoxCtrl::set_selectedItem(long pnPos/*[in]*/)
{
  GetDefaultInterface()->set_selectedItem(pnPos/*[in]*/);
}

VARIANT_BOOL __fastcall TWMPListBoxCtrl::get_sorted(void)
{
  VARIANT_BOOL pVal;
  OLECHECK(GetDefaultInterface()->get_sorted((VARIANT_BOOL*)&pVal));
  return pVal;
}

void __fastcall TWMPListBoxCtrl::set_sorted(VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_sorted(pVal/*[in]*/);
}

VARIANT_BOOL __fastcall TWMPListBoxCtrl::get_multiselect(void)
{
  VARIANT_BOOL pVal;
  OLECHECK(GetDefaultInterface()->get_multiselect((VARIANT_BOOL*)&pVal));
  return pVal;
}

void __fastcall TWMPListBoxCtrl::set_multiselect(VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_multiselect(pVal/*[in]*/);
}

VARIANT_BOOL __fastcall TWMPListBoxCtrl::get_readOnly(void)
{
  VARIANT_BOOL pVal;
  OLECHECK(GetDefaultInterface()->get_readOnly((VARIANT_BOOL*)&pVal));
  return pVal;
}

void __fastcall TWMPListBoxCtrl::set_readOnly(VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_readOnly(pVal/*[in]*/);
}

BSTR __fastcall TWMPListBoxCtrl::get_foregroundColor(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_foregroundColor((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPListBoxCtrl::set_foregroundColor(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_foregroundColor(pVal/*[in]*/);
}

BSTR __fastcall TWMPListBoxCtrl::get_backgroundColor(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_backgroundColor((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPListBoxCtrl::set_backgroundColor(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_backgroundColor(pVal/*[in]*/);
}

long __fastcall TWMPListBoxCtrl::get_fontSize(void)
{
  long pVal;
  OLECHECK(GetDefaultInterface()->get_fontSize((long*)&pVal));
  return pVal;
}

void __fastcall TWMPListBoxCtrl::set_fontSize(long pVal/*[in]*/)
{
  GetDefaultInterface()->set_fontSize(pVal/*[in]*/);
}

BSTR __fastcall TWMPListBoxCtrl::get_fontStyle(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_fontStyle((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPListBoxCtrl::set_fontStyle(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_fontStyle(pVal/*[in]*/);
}

BSTR __fastcall TWMPListBoxCtrl::get_fontFace(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_fontFace((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPListBoxCtrl::set_fontFace(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_fontFace(pVal/*[in]*/);
}

long __fastcall TWMPListBoxCtrl::get_itemCount(void)
{
  long pVal;
  OLECHECK(GetDefaultInterface()->get_itemCount((long*)&pVal));
  return pVal;
}

long __fastcall TWMPListBoxCtrl::get_firstVisibleItem(void)
{
  long pVal;
  OLECHECK(GetDefaultInterface()->get_firstVisibleItem((long*)&pVal));
  return pVal;
}

void __fastcall TWMPListBoxCtrl::set_firstVisibleItem(long pVal/*[in]*/)
{
  GetDefaultInterface()->set_firstVisibleItem(pVal/*[in]*/);
}

void __fastcall TWMPListBoxCtrl::set_popUp(VARIANT_BOOL Param1/*[in]*/)
{
  GetDefaultInterface()->set_popUp(Param1/*[in]*/);
}

long __fastcall TWMPListBoxCtrl::get_focusItem(void)
{
  long pVal;
  OLECHECK(GetDefaultInterface()->get_focusItem((long*)&pVal));
  return pVal;
}

void __fastcall TWMPListBoxCtrl::set_focusItem(long pVal/*[in]*/)
{
  GetDefaultInterface()->set_focusItem(pVal/*[in]*/);
}

VARIANT_BOOL __fastcall TWMPListBoxCtrl::get_border(void)
{
  VARIANT_BOOL pVal;
  OLECHECK(GetDefaultInterface()->get_border((VARIANT_BOOL*)&pVal));
  return pVal;
}

void __fastcall TWMPListBoxCtrl::set_border(VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_border(pVal/*[in]*/);
}

IWMPSliderCtrlPtr& TWMPSliderCtrl::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TWMPSliderCtrl::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TWMPSliderCtrl::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TWMPSliderCtrl::Disconnect()
{
  if (m_DefaultIntf) {

    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TWMPSliderCtrl::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TWMPSliderCtrl::ConnectTo(IWMPSliderCtrlPtr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TWMPSliderCtrl::InitServerData()
{
  static Oleserver::TServerData sd;
  sd.ClassID = CLSID_WMPSliderCtrl;
  sd.IntfIID = __uuidof(IWMPSliderCtrl);
  sd.EventIID= __uuidof(IWMPSliderCtrlEvents);
  ServerData = &sd;
}

void __fastcall TWMPSliderCtrl::InvokeEvent(int id, Oleserver::TVariantArray& params)
{
  switch(id)
  {
    case 5430: {
      if (Onondragbegin) {
        (Onondragbegin)(this);
      }
      break;
      }
    case 5431: {
      if (Onondragend) {
        (Onondragend)(this);
      }
      break;
      }
    case 5432: {
      if (Ononpositionchange) {
        (Ononpositionchange)(this);
      }
      break;
      }
    default:
      break;
  }
}

BSTR __fastcall TWMPSliderCtrl::get_direction(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_direction((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPSliderCtrl::set_direction(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_direction(pVal/*[in]*/);
}

VARIANT_BOOL __fastcall TWMPSliderCtrl::get_slide(void)
{
  VARIANT_BOOL pVal;
  OLECHECK(GetDefaultInterface()->get_slide((VARIANT_BOOL*)&pVal));
  return pVal;
}

void __fastcall TWMPSliderCtrl::set_slide(VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_slide(pVal/*[in]*/);
}

VARIANT_BOOL __fastcall TWMPSliderCtrl::get_tiled(void)
{
  VARIANT_BOOL pVal;
  OLECHECK(GetDefaultInterface()->get_tiled((VARIANT_BOOL*)&pVal));
  return pVal;
}

void __fastcall TWMPSliderCtrl::set_tiled(VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_tiled(pVal/*[in]*/);
}

BSTR __fastcall TWMPSliderCtrl::get_foregroundColor(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_foregroundColor((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPSliderCtrl::set_foregroundColor(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_foregroundColor(pVal/*[in]*/);
}

BSTR __fastcall TWMPSliderCtrl::get_foregroundEndColor(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_foregroundEndColor((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPSliderCtrl::set_foregroundEndColor(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_foregroundEndColor(pVal/*[in]*/);
}

BSTR __fastcall TWMPSliderCtrl::get_backgroundColor(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_backgroundColor((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPSliderCtrl::set_backgroundColor(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_backgroundColor(pVal/*[in]*/);
}

BSTR __fastcall TWMPSliderCtrl::get_backgroundEndColor(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_backgroundEndColor((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPSliderCtrl::set_backgroundEndColor(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_backgroundEndColor(pVal/*[in]*/);
}

BSTR __fastcall TWMPSliderCtrl::get_disabledColor(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_disabledColor((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPSliderCtrl::set_disabledColor(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_disabledColor(pVal/*[in]*/);
}

BSTR __fastcall TWMPSliderCtrl::get_transparencyColor(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_transparencyColor((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPSliderCtrl::set_transparencyColor(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_transparencyColor(pVal/*[in]*/);
}

BSTR __fastcall TWMPSliderCtrl::get_foregroundImage(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_foregroundImage((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPSliderCtrl::set_foregroundImage(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_foregroundImage(pVal/*[in]*/);
}

BSTR __fastcall TWMPSliderCtrl::get_backgroundImage(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_backgroundImage((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPSliderCtrl::set_backgroundImage(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_backgroundImage(pVal/*[in]*/);
}

BSTR __fastcall TWMPSliderCtrl::get_backgroundHoverImage(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_backgroundHoverImage((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPSliderCtrl::set_backgroundHoverImage(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_backgroundHoverImage(pVal/*[in]*/);
}

BSTR __fastcall TWMPSliderCtrl::get_disabledImage(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_disabledImage((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPSliderCtrl::set_disabledImage(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_disabledImage(pVal/*[in]*/);
}

BSTR __fastcall TWMPSliderCtrl::get_thumbImage(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_thumbImage((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPSliderCtrl::set_thumbImage(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_thumbImage(pVal/*[in]*/);
}

BSTR __fastcall TWMPSliderCtrl::get_thumbHoverImage(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_thumbHoverImage((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPSliderCtrl::set_thumbHoverImage(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_thumbHoverImage(pVal/*[in]*/);
}

BSTR __fastcall TWMPSliderCtrl::get_thumbDownImage(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_thumbDownImage((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPSliderCtrl::set_thumbDownImage(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_thumbDownImage(pVal/*[in]*/);
}

BSTR __fastcall TWMPSliderCtrl::get_thumbDisabledImage(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_thumbDisabledImage((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPSliderCtrl::set_thumbDisabledImage(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_thumbDisabledImage(pVal/*[in]*/);
}

float __fastcall TWMPSliderCtrl::get_min(void)
{
  float pVal;
  OLECHECK(GetDefaultInterface()->get_min((float*)&pVal));
  return pVal;
}

void __fastcall TWMPSliderCtrl::set_min(float pVal/*[in]*/)
{
  GetDefaultInterface()->set_min(pVal/*[in]*/);
}

float __fastcall TWMPSliderCtrl::get_max(void)
{
  float pVal;
  OLECHECK(GetDefaultInterface()->get_max((float*)&pVal));
  return pVal;
}

void __fastcall TWMPSliderCtrl::set_max(float pVal/*[in]*/)
{
  GetDefaultInterface()->set_max(pVal/*[in]*/);
}

float __fastcall TWMPSliderCtrl::get_value(void)
{
  float pVal;
  OLECHECK(GetDefaultInterface()->get_value((float*)&pVal));
  return pVal;
}

void __fastcall TWMPSliderCtrl::set_value(float pVal/*[in]*/)
{
  GetDefaultInterface()->set_value(pVal/*[in]*/);
}

BSTR __fastcall TWMPSliderCtrl::get_toolTip(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_toolTip((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPSliderCtrl::set_toolTip(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_toolTip(pVal/*[in]*/);
}

BSTR __fastcall TWMPSliderCtrl::get_cursor(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_cursor((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPSliderCtrl::set_cursor(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_cursor(pVal/*[in]*/);
}

int __fastcall TWMPSliderCtrl::get_borderSize(void)
{
  int pVal;
  OLECHECK(GetDefaultInterface()->get_borderSize((int*)&pVal));
  return pVal;
}

void __fastcall TWMPSliderCtrl::set_borderSize(int pVal/*[in]*/)
{
  GetDefaultInterface()->set_borderSize(pVal/*[in]*/);
}

BSTR __fastcall TWMPSliderCtrl::get_foregroundHoverImage(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_foregroundHoverImage((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPSliderCtrl::set_foregroundHoverImage(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_foregroundHoverImage(pVal/*[in]*/);
}

float __fastcall TWMPSliderCtrl::get_foregroundProgress(void)
{
  float pVal;
  OLECHECK(GetDefaultInterface()->get_foregroundProgress((float*)&pVal));
  return pVal;
}

void __fastcall TWMPSliderCtrl::set_foregroundProgress(float pVal/*[in]*/)
{
  GetDefaultInterface()->set_foregroundProgress(pVal/*[in]*/);
}

VARIANT_BOOL __fastcall TWMPSliderCtrl::get_useForegroundProgress(void)
{
  VARIANT_BOOL pVal;
  OLECHECK(GetDefaultInterface()->get_useForegroundProgress((VARIANT_BOOL*)&pVal));
  return pVal;
}

void __fastcall TWMPSliderCtrl::set_useForegroundProgress(VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_useForegroundProgress(pVal/*[in]*/);
}

IWMPVideoCtrlPtr& TWMPVideoCtrl::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TWMPVideoCtrl::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TWMPVideoCtrl::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TWMPVideoCtrl::Disconnect()
{
  if (m_DefaultIntf) {

    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TWMPVideoCtrl::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TWMPVideoCtrl::ConnectTo(IWMPVideoCtrlPtr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TWMPVideoCtrl::InitServerData()
{
  static Oleserver::TServerData sd;
  sd.ClassID = CLSID_WMPVideoCtrl;
  sd.IntfIID = __uuidof(IWMPVideoCtrl);
  sd.EventIID= __uuidof(IWMPVideoCtrlEvents);
  ServerData = &sd;
}

void __fastcall TWMPVideoCtrl::InvokeEvent(int id, Oleserver::TVariantArray& params)
{
  switch(id)
  {
    case 5720: {
      if (Ononvideostart) {
        (Ononvideostart)(this);
      }
      break;
      }
    case 5721: {
      if (Ononvideoend) {
        (Ononvideoend)(this);
      }
      break;
      }
    default:
      break;
  }
}

void __fastcall TWMPVideoCtrl::set_windowless(VARIANT_BOOL pbClipped/*[in]*/)
{
  GetDefaultInterface()->set_windowless(pbClipped/*[in]*/);
}

VARIANT_BOOL __fastcall TWMPVideoCtrl::get_windowless(void)
{
  VARIANT_BOOL pbClipped;
  OLECHECK(GetDefaultInterface()->get_windowless((VARIANT_BOOL*)&pbClipped));
  return pbClipped;
}

void __fastcall TWMPVideoCtrl::set_cursor(BSTR pbstrCursor/*[in]*/)
{
  GetDefaultInterface()->set_cursor(pbstrCursor/*[in]*/);
}

BSTR __fastcall TWMPVideoCtrl::get_cursor(void)
{
  BSTR pbstrCursor = 0;
  OLECHECK(GetDefaultInterface()->get_cursor((BSTR*)&pbstrCursor));
  return pbstrCursor;
}

void __fastcall TWMPVideoCtrl::set_backgroundColor(BSTR pbstrColor/*[in]*/)
{
  GetDefaultInterface()->set_backgroundColor(pbstrColor/*[in]*/);
}

BSTR __fastcall TWMPVideoCtrl::get_backgroundColor(void)
{
  BSTR pbstrColor = 0;
  OLECHECK(GetDefaultInterface()->get_backgroundColor((BSTR*)&pbstrColor));
  return pbstrColor;
}

void __fastcall TWMPVideoCtrl::set_maintainAspectRatio(VARIANT_BOOL pbMaintainAspectRatio/*[in]*/)
{
  GetDefaultInterface()->set_maintainAspectRatio(pbMaintainAspectRatio/*[in]*/);
}

VARIANT_BOOL __fastcall TWMPVideoCtrl::get_maintainAspectRatio(void)
{
  VARIANT_BOOL pbMaintainAspectRatio;
  OLECHECK(GetDefaultInterface()->get_maintainAspectRatio((VARIANT_BOOL*)&pbMaintainAspectRatio));
  return pbMaintainAspectRatio;
}

void __fastcall TWMPVideoCtrl::set_toolTip(BSTR bstrToolTip/*[in]*/)
{
  GetDefaultInterface()->set_toolTip(bstrToolTip/*[in]*/);
}

BSTR __fastcall TWMPVideoCtrl::get_toolTip(void)
{
  BSTR bstrToolTip = 0;
  OLECHECK(GetDefaultInterface()->get_toolTip((BSTR*)&bstrToolTip));
  return bstrToolTip;
}

VARIANT_BOOL __fastcall TWMPVideoCtrl::get_fullScreen(void)
{
  VARIANT_BOOL pbFullScreen;
  OLECHECK(GetDefaultInterface()->get_fullScreen((VARIANT_BOOL*)&pbFullScreen));
  return pbFullScreen;
}

void __fastcall TWMPVideoCtrl::set_fullScreen(VARIANT_BOOL pbFullScreen/*[in]*/)
{
  GetDefaultInterface()->set_fullScreen(pbFullScreen/*[in]*/);
}

void __fastcall TWMPVideoCtrl::set_shrinkToFit(VARIANT_BOOL pbShrinkToFit/*[in]*/)
{
  GetDefaultInterface()->set_shrinkToFit(pbShrinkToFit/*[in]*/);
}

VARIANT_BOOL __fastcall TWMPVideoCtrl::get_shrinkToFit(void)
{
  VARIANT_BOOL pbShrinkToFit;
  OLECHECK(GetDefaultInterface()->get_shrinkToFit((VARIANT_BOOL*)&pbShrinkToFit));
  return pbShrinkToFit;
}

void __fastcall TWMPVideoCtrl::set_stretchToFit(VARIANT_BOOL pbStretchToFit/*[in]*/)
{
  GetDefaultInterface()->set_stretchToFit(pbStretchToFit/*[in]*/);
}

VARIANT_BOOL __fastcall TWMPVideoCtrl::get_stretchToFit(void)
{
  VARIANT_BOOL pbStretchToFit;
  OLECHECK(GetDefaultInterface()->get_stretchToFit((VARIANT_BOOL*)&pbStretchToFit));
  return pbStretchToFit;
}

void __fastcall TWMPVideoCtrl::set_zoom(long pzoom/*[in]*/)
{
  GetDefaultInterface()->set_zoom(pzoom/*[in]*/);
}

long __fastcall TWMPVideoCtrl::get_zoom(void)
{
  long pzoom;
  OLECHECK(GetDefaultInterface()->get_zoom((long*)&pzoom));
  return pzoom;
}

IWMPEffectsCtrlPtr& TWMPEffects::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TWMPEffects::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TWMPEffects::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TWMPEffects::Disconnect()
{
  if (m_DefaultIntf) {

    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TWMPEffects::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TWMPEffects::ConnectTo(IWMPEffectsCtrlPtr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TWMPEffects::InitServerData()
{
  static Oleserver::TServerData sd;
  sd.ClassID = CLSID_WMPEffects;
  sd.IntfIID = __uuidof(IWMPEffectsCtrl);
  sd.EventIID= GUID_NULL;
  ServerData = &sd;
}

void __fastcall TWMPEffects::next(void)
{
  GetDefaultInterface()->next();
}

void __fastcall TWMPEffects::previous(void)
{
  GetDefaultInterface()->previous();
}

void __fastcall TWMPEffects::settings(void)
{
  GetDefaultInterface()->settings();
}

void __fastcall TWMPEffects::nextEffect(void)
{
  GetDefaultInterface()->nextEffect();
}

void __fastcall TWMPEffects::previousEffect(void)
{
  GetDefaultInterface()->previousEffect();
}

void __fastcall TWMPEffects::nextPreset(void)
{
  GetDefaultInterface()->nextPreset();
}

void __fastcall TWMPEffects::previousPreset(void)
{
  GetDefaultInterface()->previousPreset();
}

VARIANT_BOOL __fastcall TWMPEffects::get_windowed(void)
{
  VARIANT_BOOL pVal;
  OLECHECK(GetDefaultInterface()->get_windowed((VARIANT_BOOL*)&pVal));
  return pVal;
}

void __fastcall TWMPEffects::set_windowed(VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_windowed(pVal/*[in]*/);
}

VARIANT_BOOL __fastcall TWMPEffects::get_allowAll(void)
{
  VARIANT_BOOL pVal;
  OLECHECK(GetDefaultInterface()->get_allowAll((VARIANT_BOOL*)&pVal));
  return pVal;
}

void __fastcall TWMPEffects::set_allowAll(VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_allowAll(pVal/*[in]*/);
}

void __fastcall TWMPEffects::set_currentEffectType(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_currentEffectType(pVal/*[in]*/);
}

BSTR __fastcall TWMPEffects::get_currentEffectType(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_currentEffectType((BSTR*)&pVal));
  return pVal;
}

BSTR __fastcall TWMPEffects::get_currentEffectTitle(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_currentEffectTitle((BSTR*)&pVal));
  return pVal;
}

LPDISPATCH __fastcall TWMPEffects::get_currentEffect(void)
{
  LPDISPATCH p;
  OLECHECK(GetDefaultInterface()->get_currentEffect((LPDISPATCH*)&p));
  return p;
}

void __fastcall TWMPEffects::set_currentEffect(LPDISPATCH p/*[in]*/)
{
  GetDefaultInterface()->set_currentEffect(p/*[in]*/);
}

long __fastcall TWMPEffects::get_currentPreset(void)
{
  long pVal;
  OLECHECK(GetDefaultInterface()->get_currentPreset((long*)&pVal));
  return pVal;
}

void __fastcall TWMPEffects::set_currentPreset(long pVal/*[in]*/)
{
  GetDefaultInterface()->set_currentPreset(pVal/*[in]*/);
}

BSTR __fastcall TWMPEffects::get_currentPresetTitle(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_currentPresetTitle((BSTR*)&pVal));
  return pVal;
}

long __fastcall TWMPEffects::get_currentEffectPresetCount(void)
{
  long pVal;
  OLECHECK(GetDefaultInterface()->get_currentEffectPresetCount((long*)&pVal));
  return pVal;
}

VARIANT_BOOL __fastcall TWMPEffects::get_fullScreen(void)
{
  VARIANT_BOOL pbFullScreen;
  OLECHECK(GetDefaultInterface()->get_fullScreen((VARIANT_BOOL*)&pbFullScreen));
  return pbFullScreen;
}

void __fastcall TWMPEffects::set_fullScreen(VARIANT_BOOL pbFullScreen/*[in]*/)
{
  GetDefaultInterface()->set_fullScreen(pbFullScreen/*[in]*/);
}

VARIANT_BOOL __fastcall TWMPEffects::get_effectCanGoFullScreen(void)
{
  VARIANT_BOOL pbFullScreen;
  OLECHECK(GetDefaultInterface()->get_effectCanGoFullScreen((VARIANT_BOOL*)&pbFullScreen));
  return pbFullScreen;
}

VARIANT_BOOL __fastcall TWMPEffects::get_effectHasPropertyPage(void)
{
  VARIANT_BOOL pbPropertyPage;
  OLECHECK(GetDefaultInterface()->get_effectHasPropertyPage((VARIANT_BOOL*)&pbPropertyPage));
  return pbPropertyPage;
}

long __fastcall TWMPEffects::get_effectCount(void)
{
  long pVal;
  OLECHECK(GetDefaultInterface()->get_effectCount((long*)&pVal));
  return pVal;
}

BSTR __fastcall TWMPEffects::get_effectTitle(long index/*[in]*/)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_effectTitle(index, (BSTR*)&pVal));
  return pVal;
}

BSTR __fastcall TWMPEffects::get_effectType(long index/*[in]*/)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_effectType(index, (BSTR*)&pVal));
  return pVal;
}

IWMPEqualizerSettingsCtrlPtr& TWMPEqualizerSettingsCtrl::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TWMPEqualizerSettingsCtrl::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TWMPEqualizerSettingsCtrl::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TWMPEqualizerSettingsCtrl::Disconnect()
{
  if (m_DefaultIntf) {

    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TWMPEqualizerSettingsCtrl::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TWMPEqualizerSettingsCtrl::ConnectTo(IWMPEqualizerSettingsCtrlPtr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TWMPEqualizerSettingsCtrl::InitServerData()
{
  static Oleserver::TServerData sd;
  sd.ClassID = CLSID_WMPEqualizerSettingsCtrl;
  sd.IntfIID = __uuidof(IWMPEqualizerSettingsCtrl);
  sd.EventIID= GUID_NULL;
  ServerData = &sd;
}

void __fastcall TWMPEqualizerSettingsCtrl::reset(void)
{
  GetDefaultInterface()->reset();
}

void __fastcall TWMPEqualizerSettingsCtrl::nextPreset(void)
{
  GetDefaultInterface()->nextPreset();
}

void __fastcall TWMPEqualizerSettingsCtrl::previousPreset(void)
{
  GetDefaultInterface()->previousPreset();
}

VARIANT_BOOL __fastcall TWMPEqualizerSettingsCtrl::get_bypass(void)
{
  VARIANT_BOOL pVal;
  OLECHECK(GetDefaultInterface()->get_bypass((VARIANT_BOOL*)&pVal));
  return pVal;
}

void __fastcall TWMPEqualizerSettingsCtrl::set_bypass(VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_bypass(pVal/*[in]*/);
}

float __fastcall TWMPEqualizerSettingsCtrl::get_gainLevel1(void)
{
  float pflLevel;
  OLECHECK(GetDefaultInterface()->get_gainLevel1((float*)&pflLevel));
  return pflLevel;
}

void __fastcall TWMPEqualizerSettingsCtrl::set_gainLevel1(float pflLevel/*[in]*/)
{
  GetDefaultInterface()->set_gainLevel1(pflLevel/*[in]*/);
}

float __fastcall TWMPEqualizerSettingsCtrl::get_gainLevel2(void)
{
  float pflLevel;
  OLECHECK(GetDefaultInterface()->get_gainLevel2((float*)&pflLevel));
  return pflLevel;
}

void __fastcall TWMPEqualizerSettingsCtrl::set_gainLevel2(float pflLevel/*[in]*/)
{
  GetDefaultInterface()->set_gainLevel2(pflLevel/*[in]*/);
}

float __fastcall TWMPEqualizerSettingsCtrl::get_gainLevel3(void)
{
  float pflLevel;
  OLECHECK(GetDefaultInterface()->get_gainLevel3((float*)&pflLevel));
  return pflLevel;
}

void __fastcall TWMPEqualizerSettingsCtrl::set_gainLevel3(float pflLevel/*[in]*/)
{
  GetDefaultInterface()->set_gainLevel3(pflLevel/*[in]*/);
}

float __fastcall TWMPEqualizerSettingsCtrl::get_gainLevel4(void)
{
  float pflLevel;
  OLECHECK(GetDefaultInterface()->get_gainLevel4((float*)&pflLevel));
  return pflLevel;
}

void __fastcall TWMPEqualizerSettingsCtrl::set_gainLevel4(float pflLevel/*[in]*/)
{
  GetDefaultInterface()->set_gainLevel4(pflLevel/*[in]*/);
}

float __fastcall TWMPEqualizerSettingsCtrl::get_gainLevel5(void)
{
  float pflLevel;
  OLECHECK(GetDefaultInterface()->get_gainLevel5((float*)&pflLevel));
  return pflLevel;
}

void __fastcall TWMPEqualizerSettingsCtrl::set_gainLevel5(float pflLevel/*[in]*/)
{
  GetDefaultInterface()->set_gainLevel5(pflLevel/*[in]*/);
}

float __fastcall TWMPEqualizerSettingsCtrl::get_gainLevel6(void)
{
  float pflLevel;
  OLECHECK(GetDefaultInterface()->get_gainLevel6((float*)&pflLevel));
  return pflLevel;
}

void __fastcall TWMPEqualizerSettingsCtrl::set_gainLevel6(float pflLevel/*[in]*/)
{
  GetDefaultInterface()->set_gainLevel6(pflLevel/*[in]*/);
}

float __fastcall TWMPEqualizerSettingsCtrl::get_gainLevel7(void)
{
  float pflLevel;
  OLECHECK(GetDefaultInterface()->get_gainLevel7((float*)&pflLevel));
  return pflLevel;
}

void __fastcall TWMPEqualizerSettingsCtrl::set_gainLevel7(float pflLevel/*[in]*/)
{
  GetDefaultInterface()->set_gainLevel7(pflLevel/*[in]*/);
}

float __fastcall TWMPEqualizerSettingsCtrl::get_gainLevel8(void)
{
  float pflLevel;
  OLECHECK(GetDefaultInterface()->get_gainLevel8((float*)&pflLevel));
  return pflLevel;
}

void __fastcall TWMPEqualizerSettingsCtrl::set_gainLevel8(float pflLevel/*[in]*/)
{
  GetDefaultInterface()->set_gainLevel8(pflLevel/*[in]*/);
}

float __fastcall TWMPEqualizerSettingsCtrl::get_gainLevel9(void)
{
  float pflLevel;
  OLECHECK(GetDefaultInterface()->get_gainLevel9((float*)&pflLevel));
  return pflLevel;
}

void __fastcall TWMPEqualizerSettingsCtrl::set_gainLevel9(float pflLevel/*[in]*/)
{
  GetDefaultInterface()->set_gainLevel9(pflLevel/*[in]*/);
}

float __fastcall TWMPEqualizerSettingsCtrl::get_gainLevel10(void)
{
  float pflLevel;
  OLECHECK(GetDefaultInterface()->get_gainLevel10((float*)&pflLevel));
  return pflLevel;
}

void __fastcall TWMPEqualizerSettingsCtrl::set_gainLevel10(float pflLevel/*[in]*/)
{
  GetDefaultInterface()->set_gainLevel10(pflLevel/*[in]*/);
}

float __fastcall TWMPEqualizerSettingsCtrl::get_gainLevels(long iIndex/*[in]*/)
{
  float pflLevel;
  OLECHECK(GetDefaultInterface()->get_gainLevels(iIndex, (float*)&pflLevel));
  return pflLevel;
}

void __fastcall TWMPEqualizerSettingsCtrl::set_gainLevels(long iIndex/*[in]*/, 
                                                          float pflLevel/*[in]*/)
{
  GetDefaultInterface()->set_gainLevels(iIndex/*[in]*/, pflLevel/*[in]*/);
}

long __fastcall TWMPEqualizerSettingsCtrl::get_bands(void)
{
  long pbands;
  OLECHECK(GetDefaultInterface()->get_bands((long*)&pbands));
  return pbands;
}

long __fastcall TWMPEqualizerSettingsCtrl::get_currentPreset(void)
{
  long pVal;
  OLECHECK(GetDefaultInterface()->get_currentPreset((long*)&pVal));
  return pVal;
}

void __fastcall TWMPEqualizerSettingsCtrl::set_currentPreset(long pVal/*[in]*/)
{
  GetDefaultInterface()->set_currentPreset(pVal/*[in]*/);
}

BSTR __fastcall TWMPEqualizerSettingsCtrl::get_currentPresetTitle(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_currentPresetTitle((BSTR*)&pVal));
  return pVal;
}

long __fastcall TWMPEqualizerSettingsCtrl::get_presetCount(void)
{
  long pVal;
  OLECHECK(GetDefaultInterface()->get_presetCount((long*)&pVal));
  return pVal;
}

VARIANT_BOOL __fastcall TWMPEqualizerSettingsCtrl::get_enhancedAudio(void)
{
  VARIANT_BOOL pfVal;
  OLECHECK(GetDefaultInterface()->get_enhancedAudio((VARIANT_BOOL*)&pfVal));
  return pfVal;
}

void __fastcall TWMPEqualizerSettingsCtrl::set_enhancedAudio(VARIANT_BOOL pfVal/*[in]*/)
{
  GetDefaultInterface()->set_enhancedAudio(pfVal/*[in]*/);
}

long __fastcall TWMPEqualizerSettingsCtrl::get_speakerSize(void)
{
  long plVal;
  OLECHECK(GetDefaultInterface()->get_speakerSize((long*)&plVal));
  return plVal;
}

void __fastcall TWMPEqualizerSettingsCtrl::set_speakerSize(long plVal/*[in]*/)
{
  GetDefaultInterface()->set_speakerSize(plVal/*[in]*/);
}

BSTR __fastcall TWMPEqualizerSettingsCtrl::get_currentSpeakerName(void)
{
  BSTR pbstrName = 0;
  OLECHECK(GetDefaultInterface()->get_currentSpeakerName((BSTR*)&pbstrName));
  return pbstrName;
}

long __fastcall TWMPEqualizerSettingsCtrl::get_truBassLevel(void)
{
  long plTruBassLevel;
  OLECHECK(GetDefaultInterface()->get_truBassLevel((long*)&plTruBassLevel));
  return plTruBassLevel;
}

void __fastcall TWMPEqualizerSettingsCtrl::set_truBassLevel(long plTruBassLevel/*[in]*/)
{
  GetDefaultInterface()->set_truBassLevel(plTruBassLevel/*[in]*/);
}

long __fastcall TWMPEqualizerSettingsCtrl::get_wowLevel(void)
{
  long plWowLevel;
  OLECHECK(GetDefaultInterface()->get_wowLevel((long*)&plWowLevel));
  return plWowLevel;
}

void __fastcall TWMPEqualizerSettingsCtrl::set_wowLevel(long plWowLevel/*[in]*/)
{
  GetDefaultInterface()->set_wowLevel(plWowLevel/*[in]*/);
}

float __fastcall TWMPEqualizerSettingsCtrl::get_splineTension(void)
{
  float pflSplineTension;
  OLECHECK(GetDefaultInterface()->get_splineTension((float*)&pflSplineTension));
  return pflSplineTension;
}

void __fastcall TWMPEqualizerSettingsCtrl::set_splineTension(float pflSplineTension/*[in]*/)
{
  GetDefaultInterface()->set_splineTension(pflSplineTension/*[in]*/);
}

VARIANT_BOOL __fastcall TWMPEqualizerSettingsCtrl::get_enableSplineTension(void)
{
  VARIANT_BOOL pfEnableSplineTension;
  OLECHECK(GetDefaultInterface()->get_enableSplineTension((VARIANT_BOOL*)&pfEnableSplineTension));
  return pfEnableSplineTension;
}

void __fastcall TWMPEqualizerSettingsCtrl::set_enableSplineTension(VARIANT_BOOL pfEnableSplineTension/*[in]*/)
{
  GetDefaultInterface()->set_enableSplineTension(pfEnableSplineTension/*[in]*/);
}

BSTR __fastcall TWMPEqualizerSettingsCtrl::get_presetTitle(long iIndex/*[in]*/)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_presetTitle(iIndex, (BSTR*)&pVal));
  return pVal;
}

VARIANT_BOOL __fastcall TWMPEqualizerSettingsCtrl::get_normalization(void)
{
  VARIANT_BOOL pfVal;
  OLECHECK(GetDefaultInterface()->get_normalization((VARIANT_BOOL*)&pfVal));
  return pfVal;
}

void __fastcall TWMPEqualizerSettingsCtrl::set_normalization(VARIANT_BOOL pfVal/*[in]*/)
{
  GetDefaultInterface()->set_normalization(pfVal/*[in]*/);
}

float __fastcall TWMPEqualizerSettingsCtrl::get_normalizationAverage(void)
{
  float pflAverage;
  OLECHECK(GetDefaultInterface()->get_normalizationAverage((float*)&pflAverage));
  return pflAverage;
}

float __fastcall TWMPEqualizerSettingsCtrl::get_normalizationPeak(void)
{
  float pflPeak;
  OLECHECK(GetDefaultInterface()->get_normalizationPeak((float*)&pflPeak));
  return pflPeak;
}

VARIANT_BOOL __fastcall TWMPEqualizerSettingsCtrl::get_crossFade(void)
{
  VARIANT_BOOL pfVal;
  OLECHECK(GetDefaultInterface()->get_crossFade((VARIANT_BOOL*)&pfVal));
  return pfVal;
}

void __fastcall TWMPEqualizerSettingsCtrl::set_crossFade(VARIANT_BOOL pfVal/*[in]*/)
{
  GetDefaultInterface()->set_crossFade(pfVal/*[in]*/);
}

long __fastcall TWMPEqualizerSettingsCtrl::get_crossFadeWindow(void)
{
  long plWindow;
  OLECHECK(GetDefaultInterface()->get_crossFadeWindow((long*)&plWindow));
  return plWindow;
}

void __fastcall TWMPEqualizerSettingsCtrl::set_crossFadeWindow(long plWindow/*[in]*/)
{
  GetDefaultInterface()->set_crossFadeWindow(plWindow/*[in]*/);
}

IWMPVideoSettingsCtrlPtr& TWMPVideoSettingsCtrl::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TWMPVideoSettingsCtrl::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TWMPVideoSettingsCtrl::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TWMPVideoSettingsCtrl::Disconnect()
{
  if (m_DefaultIntf) {

    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TWMPVideoSettingsCtrl::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TWMPVideoSettingsCtrl::ConnectTo(IWMPVideoSettingsCtrlPtr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TWMPVideoSettingsCtrl::InitServerData()
{
  static Oleserver::TServerData sd;
  sd.ClassID = CLSID_WMPVideoSettingsCtrl;
  sd.IntfIID = __uuidof(IWMPVideoSettingsCtrl);
  sd.EventIID= GUID_NULL;
  ServerData = &sd;
}

void __fastcall TWMPVideoSettingsCtrl::reset(void)
{
  GetDefaultInterface()->reset();
}

long __fastcall TWMPVideoSettingsCtrl::get_brightness(void)
{
  long pVal;
  OLECHECK(GetDefaultInterface()->get_brightness((long*)&pVal));
  return pVal;
}

void __fastcall TWMPVideoSettingsCtrl::set_brightness(long pVal/*[in]*/)
{
  GetDefaultInterface()->set_brightness(pVal/*[in]*/);
}

long __fastcall TWMPVideoSettingsCtrl::get_contrast(void)
{
  long pVal;
  OLECHECK(GetDefaultInterface()->get_contrast((long*)&pVal));
  return pVal;
}

void __fastcall TWMPVideoSettingsCtrl::set_contrast(long pVal/*[in]*/)
{
  GetDefaultInterface()->set_contrast(pVal/*[in]*/);
}

long __fastcall TWMPVideoSettingsCtrl::get_hue(void)
{
  long pVal;
  OLECHECK(GetDefaultInterface()->get_hue((long*)&pVal));
  return pVal;
}

void __fastcall TWMPVideoSettingsCtrl::set_hue(long pVal/*[in]*/)
{
  GetDefaultInterface()->set_hue(pVal/*[in]*/);
}

long __fastcall TWMPVideoSettingsCtrl::get_saturation(void)
{
  long pVal;
  OLECHECK(GetDefaultInterface()->get_saturation((long*)&pVal));
  return pVal;
}

void __fastcall TWMPVideoSettingsCtrl::set_saturation(long pVal/*[in]*/)
{
  GetDefaultInterface()->set_saturation(pVal/*[in]*/);
}

IWMPLibraryTreeCtrlPtr& TWMPLibraryTreeCtrl::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TWMPLibraryTreeCtrl::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TWMPLibraryTreeCtrl::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TWMPLibraryTreeCtrl::Disconnect()
{
  if (m_DefaultIntf) {

    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TWMPLibraryTreeCtrl::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TWMPLibraryTreeCtrl::ConnectTo(IWMPLibraryTreeCtrlPtr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TWMPLibraryTreeCtrl::InitServerData()
{
  static Oleserver::TServerData sd;
  sd.ClassID = CLSID_WMPLibraryTreeCtrl;
  sd.IntfIID = __uuidof(IWMPLibraryTreeCtrl);
  sd.EventIID= GUID_NULL;
  ServerData = &sd;
}

VARIANT_BOOL __fastcall TWMPLibraryTreeCtrl::get_dropDownVisible(void)
{
  VARIANT_BOOL pVal;
  OLECHECK(GetDefaultInterface()->get_dropDownVisible((VARIANT_BOOL*)&pVal));
  return pVal;
}

void __fastcall TWMPLibraryTreeCtrl::set_dropDownVisible(VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_dropDownVisible(pVal/*[in]*/);
}

BSTR __fastcall TWMPLibraryTreeCtrl::get_foregroundColor(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_foregroundColor((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPLibraryTreeCtrl::set_foregroundColor(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_foregroundColor(pVal/*[in]*/);
}

BSTR __fastcall TWMPLibraryTreeCtrl::get_backgroundColor(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_backgroundColor((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPLibraryTreeCtrl::set_backgroundColor(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_backgroundColor(pVal/*[in]*/);
}

long __fastcall TWMPLibraryTreeCtrl::get_fontSize(void)
{
  long pVal;
  OLECHECK(GetDefaultInterface()->get_fontSize((long*)&pVal));
  return pVal;
}

void __fastcall TWMPLibraryTreeCtrl::set_fontSize(long pVal/*[in]*/)
{
  GetDefaultInterface()->set_fontSize(pVal/*[in]*/);
}

BSTR __fastcall TWMPLibraryTreeCtrl::get_fontStyle(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_fontStyle((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPLibraryTreeCtrl::set_fontStyle(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_fontStyle(pVal/*[in]*/);
}

BSTR __fastcall TWMPLibraryTreeCtrl::get_fontFace(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_fontFace((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPLibraryTreeCtrl::set_fontFace(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_fontFace(pVal/*[in]*/);
}

BSTR __fastcall TWMPLibraryTreeCtrl::get_filter(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_filter((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPLibraryTreeCtrl::set_filter(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_filter(pVal/*[in]*/);
}

BSTR __fastcall TWMPLibraryTreeCtrl::get_expandState(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_expandState((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPLibraryTreeCtrl::set_expandState(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_expandState(pVal/*[in]*/);
}

Wmplib_tlb::IWMPPlaylistPtr __fastcall TWMPLibraryTreeCtrl::get_Playlist(void)
{
  Wmplib_tlb::IWMPPlaylistPtr ppPlaylist;
  OLECHECK(GetDefaultInterface()->get_Playlist(&ppPlaylist));
  return ppPlaylist;
}

void __fastcall TWMPLibraryTreeCtrl::set_Playlist(Wmplib_tlb::IWMPPlaylistPtr ppPlaylist/*[in]*/)
{
  GetDefaultInterface()->set_Playlist(ppPlaylist/*[in]*/);
}

Wmplib_tlb::IWMPPlaylistPtr __fastcall TWMPLibraryTreeCtrl::get_selectedPlaylist(void)
{
  Wmplib_tlb::IWMPPlaylistPtr ppPlaylist;
  OLECHECK(GetDefaultInterface()->get_selectedPlaylist(&ppPlaylist));
  return ppPlaylist;
}

Wmplib_tlb::IWMPMediaPtr __fastcall TWMPLibraryTreeCtrl::get_selectedMedia(void)
{
  Wmplib_tlb::IWMPMediaPtr ppMedia;
  OLECHECK(GetDefaultInterface()->get_selectedMedia(&ppMedia));
  return ppMedia;
}

IWMPEditCtrlPtr& TWMPEditCtrl::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TWMPEditCtrl::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TWMPEditCtrl::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TWMPEditCtrl::Disconnect()
{
  if (m_DefaultIntf) {

    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TWMPEditCtrl::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TWMPEditCtrl::ConnectTo(IWMPEditCtrlPtr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TWMPEditCtrl::InitServerData()
{
  static Oleserver::TServerData sd;
  sd.ClassID = CLSID_WMPEditCtrl;
  sd.IntfIID = __uuidof(IWMPEditCtrl);
  sd.EventIID= GUID_NULL;
  ServerData = &sd;
}

BSTR __fastcall TWMPEditCtrl::getLine(long nIndex/*[in]*/)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->getLine(nIndex, (BSTR*)&pVal));
  return pVal;
}

long __fastcall TWMPEditCtrl::getSelectionStart(void)
{
  long pnStart;
  OLECHECK(GetDefaultInterface()->getSelectionStart((long*)&pnStart));
  return pnStart;
}

long __fastcall TWMPEditCtrl::getSelectionEnd(void)
{
  long pnEnd;
  OLECHECK(GetDefaultInterface()->getSelectionEnd((long*)&pnEnd));
  return pnEnd;
}

void __fastcall TWMPEditCtrl::setSelection(long nStart/*[in]*/, long nEnd/*[in]*/)
{
  GetDefaultInterface()->setSelection(nStart/*[in]*/, nEnd/*[in]*/);
}

void __fastcall TWMPEditCtrl::replaceSelection(BSTR newVal/*[in]*/)
{
  GetDefaultInterface()->replaceSelection(newVal/*[in]*/);
}

long __fastcall TWMPEditCtrl::getLineIndex(long nIndex/*[in]*/)
{
  long pnPosition;
  OLECHECK(GetDefaultInterface()->getLineIndex(nIndex, (long*)&pnPosition));
  return pnPosition;
}

long __fastcall TWMPEditCtrl::getLineFromChar(long nPosition/*[in]*/)
{
  long pnLine;
  OLECHECK(GetDefaultInterface()->getLineFromChar(nPosition, (long*)&pnLine));
  return pnLine;
}

BSTR __fastcall TWMPEditCtrl::get_value(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_value((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPEditCtrl::set_value(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_value(pVal/*[in]*/);
}

VARIANT_BOOL __fastcall TWMPEditCtrl::get_border(void)
{
  VARIANT_BOOL pVal;
  OLECHECK(GetDefaultInterface()->get_border((VARIANT_BOOL*)&pVal));
  return pVal;
}

void __fastcall TWMPEditCtrl::set_border(VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_border(pVal/*[in]*/);
}

BSTR __fastcall TWMPEditCtrl::get_justification(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_justification((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPEditCtrl::set_justification(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_justification(pVal/*[in]*/);
}

BSTR __fastcall TWMPEditCtrl::get_editStyle(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_editStyle((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPEditCtrl::set_editStyle(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_editStyle(pVal/*[in]*/);
}

VARIANT_BOOL __fastcall TWMPEditCtrl::get_wordWrap(void)
{
  VARIANT_BOOL pVal;
  OLECHECK(GetDefaultInterface()->get_wordWrap((VARIANT_BOOL*)&pVal));
  return pVal;
}

void __fastcall TWMPEditCtrl::set_wordWrap(VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_wordWrap(pVal/*[in]*/);
}

VARIANT_BOOL __fastcall TWMPEditCtrl::get_readOnly(void)
{
  VARIANT_BOOL pVal;
  OLECHECK(GetDefaultInterface()->get_readOnly((VARIANT_BOOL*)&pVal));
  return pVal;
}

void __fastcall TWMPEditCtrl::set_readOnly(VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_readOnly(pVal/*[in]*/);
}

BSTR __fastcall TWMPEditCtrl::get_foregroundColor(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_foregroundColor((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPEditCtrl::set_foregroundColor(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_foregroundColor(pVal/*[in]*/);
}

BSTR __fastcall TWMPEditCtrl::get_backgroundColor(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_backgroundColor((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPEditCtrl::set_backgroundColor(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_backgroundColor(pVal/*[in]*/);
}

long __fastcall TWMPEditCtrl::get_fontSize(void)
{
  long pVal;
  OLECHECK(GetDefaultInterface()->get_fontSize((long*)&pVal));
  return pVal;
}

void __fastcall TWMPEditCtrl::set_fontSize(long pVal/*[in]*/)
{
  GetDefaultInterface()->set_fontSize(pVal/*[in]*/);
}

BSTR __fastcall TWMPEditCtrl::get_fontStyle(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_fontStyle((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPEditCtrl::set_fontStyle(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_fontStyle(pVal/*[in]*/);
}

BSTR __fastcall TWMPEditCtrl::get_fontFace(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_fontFace((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPEditCtrl::set_fontFace(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_fontFace(pVal/*[in]*/);
}

long __fastcall TWMPEditCtrl::get_textLimit(void)
{
  long pVal;
  OLECHECK(GetDefaultInterface()->get_textLimit((long*)&pVal));
  return pVal;
}

void __fastcall TWMPEditCtrl::set_textLimit(long pVal/*[in]*/)
{
  GetDefaultInterface()->set_textLimit(pVal/*[in]*/);
}

long __fastcall TWMPEditCtrl::get_lineCount(void)
{
  long pVal;
  OLECHECK(GetDefaultInterface()->get_lineCount((long*)&pVal));
  return pVal;
}

IWMPMenuCtrlPtr& TWMPMenuCtrl::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TWMPMenuCtrl::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TWMPMenuCtrl::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TWMPMenuCtrl::Disconnect()
{
  if (m_DefaultIntf) {

    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TWMPMenuCtrl::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TWMPMenuCtrl::ConnectTo(IWMPMenuCtrlPtr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TWMPMenuCtrl::InitServerData()
{
  static Oleserver::TServerData sd;
  sd.ClassID = CLSID_WMPMenuCtrl;
  sd.IntfIID = __uuidof(IWMPMenuCtrl);
  sd.EventIID= GUID_NULL;
  ServerData = &sd;
}

void __fastcall TWMPMenuCtrl::deleteAllItems(void)
{
  GetDefaultInterface()->deleteAllItems();
}

void __fastcall TWMPMenuCtrl::appendItem(long nID/*[in]*/, BSTR bstrItem/*[in]*/)
{
  GetDefaultInterface()->appendItem(nID/*[in]*/, bstrItem/*[in]*/);
}

void __fastcall TWMPMenuCtrl::appendSeparator(void)
{
  GetDefaultInterface()->appendSeparator();
}

void __fastcall TWMPMenuCtrl::enableItem(long nID/*[in]*/, VARIANT_BOOL newVal/*[in]*/)
{
  GetDefaultInterface()->enableItem(nID/*[in]*/, newVal/*[in]*/);
}

void __fastcall TWMPMenuCtrl::checkItem(long nID/*[in]*/, VARIANT_BOOL newVal/*[in]*/)
{
  GetDefaultInterface()->checkItem(nID/*[in]*/, newVal/*[in]*/);
}

void __fastcall TWMPMenuCtrl::checkRadioItem(long nID/*[in]*/, VARIANT_BOOL newVal/*[in]*/)
{
  GetDefaultInterface()->checkRadioItem(nID/*[in]*/, newVal/*[in]*/);
}

long __fastcall TWMPMenuCtrl::show(void)
{
  long pnID;
  OLECHECK(GetDefaultInterface()->show((long*)&pnID));
  return pnID;
}

void __fastcall TWMPMenuCtrl::showEx(long nID/*[in]*/)
{
  GetDefaultInterface()->showEx(nID/*[in]*/);
}

long __fastcall TWMPMenuCtrl::get_showFlags(void)
{
  long pVal;
  OLECHECK(GetDefaultInterface()->get_showFlags((long*)&pVal));
  return pVal;
}

void __fastcall TWMPMenuCtrl::set_showFlags(long pVal/*[in]*/)
{
  GetDefaultInterface()->set_showFlags(pVal/*[in]*/);
}

IWMPAutoMenuCtrlPtr& TWMPAutoMenuCtrl::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TWMPAutoMenuCtrl::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TWMPAutoMenuCtrl::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TWMPAutoMenuCtrl::Disconnect()
{
  if (m_DefaultIntf) {

    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TWMPAutoMenuCtrl::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TWMPAutoMenuCtrl::ConnectTo(IWMPAutoMenuCtrlPtr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TWMPAutoMenuCtrl::InitServerData()
{
  static Oleserver::TServerData sd;
  sd.ClassID = CLSID_WMPAutoMenuCtrl;
  sd.IntfIID = __uuidof(IWMPAutoMenuCtrl);
  sd.EventIID= GUID_NULL;
  ServerData = &sd;
}

void __fastcall TWMPAutoMenuCtrl::show(BSTR newVal/*[in]*/)
{
  GetDefaultInterface()->show(newVal/*[in]*/);
}

IWMPRegionalButtonCtrlPtr& TWMPRegionalButtonCtrl::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TWMPRegionalButtonCtrl::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TWMPRegionalButtonCtrl::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TWMPRegionalButtonCtrl::Disconnect()
{
  if (m_DefaultIntf) {

    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TWMPRegionalButtonCtrl::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TWMPRegionalButtonCtrl::ConnectTo(IWMPRegionalButtonCtrlPtr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TWMPRegionalButtonCtrl::InitServerData()
{
  static Oleserver::TServerData sd;
  sd.ClassID = CLSID_WMPRegionalButtonCtrl;
  sd.IntfIID = __uuidof(IWMPRegionalButtonCtrl);
  sd.EventIID= GUID_NULL;
  ServerData = &sd;
}

LPDISPATCH __fastcall TWMPRegionalButtonCtrl::createButton(void)
{
  LPDISPATCH pButton;
  OLECHECK(GetDefaultInterface()->createButton((LPDISPATCH*)&pButton));
  return pButton;
}

LPDISPATCH __fastcall TWMPRegionalButtonCtrl::getButton(long nButton/*[in]*/)
{
  LPDISPATCH pButton;
  OLECHECK(GetDefaultInterface()->getButton(nButton, (LPDISPATCH*)&pButton));
  return pButton;
}

void __fastcall TWMPRegionalButtonCtrl::_Click(long nButton/*[in]*/)
{
  GetDefaultInterface()->_Click(nButton/*[in]*/);
}

BSTR __fastcall TWMPRegionalButtonCtrl::get_image(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_image((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPRegionalButtonCtrl::set_image(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_image(pVal/*[in]*/);
}

BSTR __fastcall TWMPRegionalButtonCtrl::get_hoverImage(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_hoverImage((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPRegionalButtonCtrl::set_hoverImage(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_hoverImage(pVal/*[in]*/);
}

BSTR __fastcall TWMPRegionalButtonCtrl::get_downImage(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_downImage((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPRegionalButtonCtrl::set_downImage(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_downImage(pVal/*[in]*/);
}

BSTR __fastcall TWMPRegionalButtonCtrl::get_hoverDownImage(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_hoverDownImage((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPRegionalButtonCtrl::set_hoverDownImage(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_hoverDownImage(pVal/*[in]*/);
}

BSTR __fastcall TWMPRegionalButtonCtrl::get_hoverHoverImage(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_hoverHoverImage((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPRegionalButtonCtrl::set_hoverHoverImage(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_hoverHoverImage(pVal/*[in]*/);
}

BSTR __fastcall TWMPRegionalButtonCtrl::get_disabledImage(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_disabledImage((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPRegionalButtonCtrl::set_disabledImage(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_disabledImage(pVal/*[in]*/);
}

BSTR __fastcall TWMPRegionalButtonCtrl::get_mappingImage(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_mappingImage((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPRegionalButtonCtrl::set_mappingImage(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_mappingImage(pVal/*[in]*/);
}

BSTR __fastcall TWMPRegionalButtonCtrl::get_transparencyColor(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_transparencyColor((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPRegionalButtonCtrl::set_transparencyColor(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_transparencyColor(pVal/*[in]*/);
}

BSTR __fastcall TWMPRegionalButtonCtrl::get_cursor(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_cursor((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPRegionalButtonCtrl::set_cursor(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_cursor(pVal/*[in]*/);
}

VARIANT_BOOL __fastcall TWMPRegionalButtonCtrl::get_showBackground(void)
{
  VARIANT_BOOL pVal;
  OLECHECK(GetDefaultInterface()->get_showBackground((VARIANT_BOOL*)&pVal));
  return pVal;
}

void __fastcall TWMPRegionalButtonCtrl::set_showBackground(VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_showBackground(pVal/*[in]*/);
}

VARIANT_BOOL __fastcall TWMPRegionalButtonCtrl::get_radio(void)
{
  VARIANT_BOOL pVal;
  OLECHECK(GetDefaultInterface()->get_radio((VARIANT_BOOL*)&pVal));
  return pVal;
}

void __fastcall TWMPRegionalButtonCtrl::set_radio(VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_radio(pVal/*[in]*/);
}

long __fastcall TWMPRegionalButtonCtrl::get_buttonCount(void)
{
  long nButtons;
  OLECHECK(GetDefaultInterface()->get_buttonCount((long*)&nButtons));
  return nButtons;
}

float __fastcall TWMPRegionalButtonCtrl::get_hueShift(void)
{
  float pVal;
  OLECHECK(GetDefaultInterface()->get_hueShift((float*)&pVal));
  return pVal;
}

void __fastcall TWMPRegionalButtonCtrl::set_hueShift(float pVal/*[in]*/)
{
  GetDefaultInterface()->set_hueShift(pVal/*[in]*/);
}

float __fastcall TWMPRegionalButtonCtrl::get_saturation(void)
{
  float pVal;
  OLECHECK(GetDefaultInterface()->get_saturation((float*)&pVal));
  return pVal;
}

void __fastcall TWMPRegionalButtonCtrl::set_saturation(float pVal/*[in]*/)
{
  GetDefaultInterface()->set_saturation(pVal/*[in]*/);
}

IWMPRegionalButtonPtr& TWMPRegionalButton::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TWMPRegionalButton::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TWMPRegionalButton::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TWMPRegionalButton::Disconnect()
{
  if (m_DefaultIntf) {

    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TWMPRegionalButton::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TWMPRegionalButton::ConnectTo(IWMPRegionalButtonPtr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TWMPRegionalButton::InitServerData()
{
  static Oleserver::TServerData sd;
  sd.ClassID = CLSID_WMPRegionalButton;
  sd.IntfIID = __uuidof(IWMPRegionalButton);
  sd.EventIID= __uuidof(IWMPRegionalButtonEvents);
  ServerData = &sd;
}

void __fastcall TWMPRegionalButton::InvokeEvent(int id, Oleserver::TVariantArray& params)
{
  switch(id)
  {
    case 5360: {
      if (Ononblur) {
        (Ononblur)(this);
      }
      break;
      }
    case 5361: {
      if (Ononfocus) {
        (Ononfocus)(this);
      }
      break;
      }
    case 5362: {
      if (Ononclick) {
        (Ononclick)(this);
      }
      break;
      }
    case 5363: {
      if (Onondblclick) {
        (Onondblclick)(this);
      }
      break;
      }
    case 5364: {
      if (Ononmousedown) {
        (Ononmousedown)(this);
      }
      break;
      }
    case 5365: {
      if (Ononmouseup) {
        (Ononmouseup)(this);
      }
      break;
      }
    case 5366: {
      if (Ononmousemove) {
        (Ononmousemove)(this);
      }
      break;
      }
    case 5367: {
      if (Ononmouseover) {
        (Ononmouseover)(this);
      }
      break;
      }
    case 5368: {
      if (Ononmouseout) {
        (Ononmouseout)(this);
      }
      break;
      }
    case 5369: {
      if (Ononkeypress) {
        (Ononkeypress)(this);
      }
      break;
      }
    case 5370: {
      if (Ononkeydown) {
        (Ononkeydown)(this);
      }
      break;
      }
    case 5371: {
      if (Ononkeyup) {
        (Ononkeyup)(this);
      }
      break;
      }
    default:
      break;
  }
}

void __fastcall TWMPRegionalButton::_Click(void)
{
  GetDefaultInterface()->_Click();
}

BSTR __fastcall TWMPRegionalButton::get_upToolTip(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_upToolTip((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPRegionalButton::set_upToolTip(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_upToolTip(pVal/*[in]*/);
}

BSTR __fastcall TWMPRegionalButton::get_downToolTip(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_downToolTip((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPRegionalButton::set_downToolTip(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_downToolTip(pVal/*[in]*/);
}

BSTR __fastcall TWMPRegionalButton::get_mappingColor(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_mappingColor((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPRegionalButton::set_mappingColor(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_mappingColor(pVal/*[in]*/);
}

VARIANT_BOOL __fastcall TWMPRegionalButton::get_enabled(void)
{
  VARIANT_BOOL pVal;
  OLECHECK(GetDefaultInterface()->get_enabled((VARIANT_BOOL*)&pVal));
  return pVal;
}

void __fastcall TWMPRegionalButton::set_enabled(VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_enabled(pVal/*[in]*/);
}

VARIANT_BOOL __fastcall TWMPRegionalButton::get_sticky(void)
{
  VARIANT_BOOL pVal;
  OLECHECK(GetDefaultInterface()->get_sticky((VARIANT_BOOL*)&pVal));
  return pVal;
}

void __fastcall TWMPRegionalButton::set_sticky(VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_sticky(pVal/*[in]*/);
}

VARIANT_BOOL __fastcall TWMPRegionalButton::get_down(void)
{
  VARIANT_BOOL pVal;
  OLECHECK(GetDefaultInterface()->get_down((VARIANT_BOOL*)&pVal));
  return pVal;
}

void __fastcall TWMPRegionalButton::set_down(VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_down(pVal/*[in]*/);
}

long __fastcall TWMPRegionalButton::get_index(void)
{
  long pVal;
  OLECHECK(GetDefaultInterface()->get_index((long*)&pVal));
  return pVal;
}

VARIANT_BOOL __fastcall TWMPRegionalButton::get_tabStop(void)
{
  VARIANT_BOOL pVal;
  OLECHECK(GetDefaultInterface()->get_tabStop((VARIANT_BOOL*)&pVal));
  return pVal;
}

void __fastcall TWMPRegionalButton::set_tabStop(VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_tabStop(pVal/*[in]*/);
}

BSTR __fastcall TWMPRegionalButton::get_cursor(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_cursor((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPRegionalButton::set_cursor(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_cursor(pVal/*[in]*/);
}

BSTR __fastcall TWMPRegionalButton::get_accName(void)
{
  BSTR pszName = 0;
  OLECHECK(GetDefaultInterface()->get_accName((BSTR*)&pszName));
  return pszName;
}

void __fastcall TWMPRegionalButton::set_accName(BSTR pszName/*[in]*/)
{
  GetDefaultInterface()->set_accName(pszName/*[in]*/);
}

BSTR __fastcall TWMPRegionalButton::get_accDescription(void)
{
  BSTR pszDescription = 0;
  OLECHECK(GetDefaultInterface()->get_accDescription((BSTR*)&pszDescription));
  return pszDescription;
}

void __fastcall TWMPRegionalButton::set_accDescription(BSTR pszDescription/*[in]*/)
{
  GetDefaultInterface()->set_accDescription(pszDescription/*[in]*/);
}

BSTR __fastcall TWMPRegionalButton::get_accKeyboardShortcut(void)
{
  BSTR pszShortcut = 0;
  OLECHECK(GetDefaultInterface()->get_accKeyboardShortcut((BSTR*)&pszShortcut));
  return pszShortcut;
}

void __fastcall TWMPRegionalButton::set_accKeyboardShortcut(BSTR pszShortcut/*[in]*/)
{
  GetDefaultInterface()->set_accKeyboardShortcut(pszShortcut/*[in]*/);
}

IWMPCustomSliderPtr& TWMPCustomSliderCtrl::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TWMPCustomSliderCtrl::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TWMPCustomSliderCtrl::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TWMPCustomSliderCtrl::Disconnect()
{
  if (m_DefaultIntf) {

    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TWMPCustomSliderCtrl::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TWMPCustomSliderCtrl::ConnectTo(IWMPCustomSliderPtr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TWMPCustomSliderCtrl::InitServerData()
{
  static Oleserver::TServerData sd;
  sd.ClassID = CLSID_WMPCustomSliderCtrl;
  sd.IntfIID = __uuidof(IWMPCustomSlider);
  sd.EventIID= __uuidof(IWMPCustomSliderCtrlEvents);
  ServerData = &sd;
}

void __fastcall TWMPCustomSliderCtrl::InvokeEvent(int id, Oleserver::TVariantArray& params)
{
  switch(id)
  {
    case 5020: {
      if (Onondragbegin) {
        (Onondragbegin)(this);
      }
      break;
      }
    case 5021: {
      if (Onondragend) {
        (Onondragend)(this);
      }
      break;
      }
    case 5022: {
      if (Ononpositionchange) {
        (Ononpositionchange)(this);
      }
      break;
      }
    default:
      break;
  }
}

BSTR __fastcall TWMPCustomSliderCtrl::get_cursor(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_cursor((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPCustomSliderCtrl::set_cursor(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_cursor(pVal/*[in]*/);
}

float __fastcall TWMPCustomSliderCtrl::get_min(void)
{
  float pVal;
  OLECHECK(GetDefaultInterface()->get_min((float*)&pVal));
  return pVal;
}

void __fastcall TWMPCustomSliderCtrl::set_min(float pVal/*[in]*/)
{
  GetDefaultInterface()->set_min(pVal/*[in]*/);
}

float __fastcall TWMPCustomSliderCtrl::get_max(void)
{
  float pVal;
  OLECHECK(GetDefaultInterface()->get_max((float*)&pVal));
  return pVal;
}

void __fastcall TWMPCustomSliderCtrl::set_max(float pVal/*[in]*/)
{
  GetDefaultInterface()->set_max(pVal/*[in]*/);
}

float __fastcall TWMPCustomSliderCtrl::get_value(void)
{
  float pVal;
  OLECHECK(GetDefaultInterface()->get_value((float*)&pVal));
  return pVal;
}

void __fastcall TWMPCustomSliderCtrl::set_value(float pVal/*[in]*/)
{
  GetDefaultInterface()->set_value(pVal/*[in]*/);
}

BSTR __fastcall TWMPCustomSliderCtrl::get_toolTip(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_toolTip((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPCustomSliderCtrl::set_toolTip(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_toolTip(pVal/*[in]*/);
}

BSTR __fastcall TWMPCustomSliderCtrl::get_positionImage(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_positionImage((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPCustomSliderCtrl::set_positionImage(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_positionImage(pVal/*[in]*/);
}

BSTR __fastcall TWMPCustomSliderCtrl::get_image(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_image((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPCustomSliderCtrl::set_image(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_image(pVal/*[in]*/);
}

BSTR __fastcall TWMPCustomSliderCtrl::get_hoverImage(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_hoverImage((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPCustomSliderCtrl::set_hoverImage(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_hoverImage(pVal/*[in]*/);
}

BSTR __fastcall TWMPCustomSliderCtrl::get_disabledImage(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_disabledImage((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPCustomSliderCtrl::set_disabledImage(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_disabledImage(pVal/*[in]*/);
}

BSTR __fastcall TWMPCustomSliderCtrl::get_downImage(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_downImage((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPCustomSliderCtrl::set_downImage(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_downImage(pVal/*[in]*/);
}

BSTR __fastcall TWMPCustomSliderCtrl::get_transparencyColor(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_transparencyColor((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPCustomSliderCtrl::set_transparencyColor(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_transparencyColor(pVal/*[in]*/);
}

IWMPTextCtrlPtr& TWMPTextCtrl::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TWMPTextCtrl::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TWMPTextCtrl::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TWMPTextCtrl::Disconnect()
{
  if (m_DefaultIntf) {

    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TWMPTextCtrl::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TWMPTextCtrl::ConnectTo(IWMPTextCtrlPtr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TWMPTextCtrl::InitServerData()
{
  static Oleserver::TServerData sd;
  sd.ClassID = CLSID_WMPTextCtrl;
  sd.IntfIID = __uuidof(IWMPTextCtrl);
  sd.EventIID= GUID_NULL;
  ServerData = &sd;
}

BSTR __fastcall TWMPTextCtrl::get_backgroundColor(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_backgroundColor((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPTextCtrl::set_backgroundColor(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_backgroundColor(pVal/*[in]*/);
}

BSTR __fastcall TWMPTextCtrl::get_fontFace(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_fontFace((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPTextCtrl::set_fontFace(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_fontFace(pVal/*[in]*/);
}

BSTR __fastcall TWMPTextCtrl::get_fontStyle(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_fontStyle((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPTextCtrl::set_fontStyle(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_fontStyle(pVal/*[in]*/);
}

long __fastcall TWMPTextCtrl::get_fontSize(void)
{
  long pVal;
  OLECHECK(GetDefaultInterface()->get_fontSize((long*)&pVal));
  return pVal;
}

void __fastcall TWMPTextCtrl::set_fontSize(long pVal/*[in]*/)
{
  GetDefaultInterface()->set_fontSize(pVal/*[in]*/);
}

BSTR __fastcall TWMPTextCtrl::get_foregroundColor(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_foregroundColor((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPTextCtrl::set_foregroundColor(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_foregroundColor(pVal/*[in]*/);
}

BSTR __fastcall TWMPTextCtrl::get_hoverBackgroundColor(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_hoverBackgroundColor((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPTextCtrl::set_hoverBackgroundColor(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_hoverBackgroundColor(pVal/*[in]*/);
}

BSTR __fastcall TWMPTextCtrl::get_hoverForegroundColor(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_hoverForegroundColor((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPTextCtrl::set_hoverForegroundColor(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_hoverForegroundColor(pVal/*[in]*/);
}

BSTR __fastcall TWMPTextCtrl::get_hoverFontStyle(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_hoverFontStyle((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPTextCtrl::set_hoverFontStyle(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_hoverFontStyle(pVal/*[in]*/);
}

BSTR __fastcall TWMPTextCtrl::get_value(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_value((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPTextCtrl::set_value(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_value(pVal/*[in]*/);
}

BSTR __fastcall TWMPTextCtrl::get_toolTip(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_toolTip((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPTextCtrl::set_toolTip(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_toolTip(pVal/*[in]*/);
}

BSTR __fastcall TWMPTextCtrl::get_disabledFontStyle(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_disabledFontStyle((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPTextCtrl::set_disabledFontStyle(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_disabledFontStyle(pVal/*[in]*/);
}

BSTR __fastcall TWMPTextCtrl::get_disabledForegroundColor(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_disabledForegroundColor((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPTextCtrl::set_disabledForegroundColor(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_disabledForegroundColor(pVal/*[in]*/);
}

BSTR __fastcall TWMPTextCtrl::get_disabledBackgroundColor(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_disabledBackgroundColor((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPTextCtrl::set_disabledBackgroundColor(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_disabledBackgroundColor(pVal/*[in]*/);
}

VARIANT_BOOL __fastcall TWMPTextCtrl::get_fontSmoothing(void)
{
  VARIANT_BOOL pVal;
  OLECHECK(GetDefaultInterface()->get_fontSmoothing((VARIANT_BOOL*)&pVal));
  return pVal;
}

void __fastcall TWMPTextCtrl::set_fontSmoothing(VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_fontSmoothing(pVal/*[in]*/);
}

BSTR __fastcall TWMPTextCtrl::get_justification(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_justification((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPTextCtrl::set_justification(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_justification(pVal/*[in]*/);
}

VARIANT_BOOL __fastcall TWMPTextCtrl::get_wordWrap(void)
{
  VARIANT_BOOL pVal;
  OLECHECK(GetDefaultInterface()->get_wordWrap((VARIANT_BOOL*)&pVal));
  return pVal;
}

void __fastcall TWMPTextCtrl::set_wordWrap(VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_wordWrap(pVal/*[in]*/);
}

BSTR __fastcall TWMPTextCtrl::get_cursor(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_cursor((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPTextCtrl::set_cursor(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_cursor(pVal/*[in]*/);
}

VARIANT_BOOL __fastcall TWMPTextCtrl::get_scrolling(void)
{
  VARIANT_BOOL pVal;
  OLECHECK(GetDefaultInterface()->get_scrolling((VARIANT_BOOL*)&pVal));
  return pVal;
}

void __fastcall TWMPTextCtrl::set_scrolling(VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_scrolling(pVal/*[in]*/);
}

BSTR __fastcall TWMPTextCtrl::get_scrollingDirection(void)
{
  BSTR pVal = 0;
  OLECHECK(GetDefaultInterface()->get_scrollingDirection((BSTR*)&pVal));
  return pVal;
}

void __fastcall TWMPTextCtrl::set_scrollingDirection(BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_scrollingDirection(pVal/*[in]*/);
}

int __fastcall TWMPTextCtrl::get_scrollingDelay(void)
{
  int pVal;
  OLECHECK(GetDefaultInterface()->get_scrollingDelay((int*)&pVal));
  return pVal;
}

void __fastcall TWMPTextCtrl::set_scrollingDelay(int pVal/*[in]*/)
{
  GetDefaultInterface()->set_scrollingDelay(pVal/*[in]*/);
}

int __fastcall TWMPTextCtrl::get_scrollingAmount(void)
{
  int pVal;
  OLECHECK(GetDefaultInterface()->get_scrollingAmount((int*)&pVal));
  return pVal;
}

void __fastcall TWMPTextCtrl::set_scrollingAmount(int pVal/*[in]*/)
{
  GetDefaultInterface()->set_scrollingAmount(pVal/*[in]*/);
}

int __fastcall TWMPTextCtrl::get_textWidth(void)
{
  int pVal;
  OLECHECK(GetDefaultInterface()->get_textWidth((int*)&pVal));
  return pVal;
}

VARIANT_BOOL __fastcall TWMPTextCtrl::get_onGlass(void)
{
  VARIANT_BOOL pVal;
  OLECHECK(GetDefaultInterface()->get_onGlass((VARIANT_BOOL*)&pVal));
  return pVal;
}

void __fastcall TWMPTextCtrl::set_onGlass(VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_onGlass(pVal/*[in]*/);
}

IWMPPlaylistCtrlPtr& TWMPPlaylistCtrl::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TWMPPlaylistCtrl::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TWMPPlaylistCtrl::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TWMPPlaylistCtrl::Disconnect()
{
  if (m_DefaultIntf) {

    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TWMPPlaylistCtrl::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TWMPPlaylistCtrl::ConnectTo(IWMPPlaylistCtrlPtr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TWMPPlaylistCtrl::InitServerData()
{
  static Oleserver::TServerData sd;
  sd.ClassID = CLSID_WMPPlaylistCtrl;
  sd.IntfIID = __uuidof(IWMPPlaylistCtrl);
  sd.EventIID= GUID_NULL;
  ServerData = &sd;
}

void __fastcall TWMPPlaylistCtrl::copy(void)
{
  GetDefaultInterface()->copy();
}

void __fastcall TWMPPlaylistCtrl::abortCopy(void)
{
  GetDefaultInterface()->abortCopy();
}

void __fastcall TWMPPlaylistCtrl::deleteSelected(void)
{
  GetDefaultInterface()->deleteSelected();
}

void __fastcall TWMPPlaylistCtrl::deleteSelectedFromLibrary(void)
{
  GetDefaultInterface()->deleteSelectedFromLibrary();
}

void __fastcall TWMPPlaylistCtrl::moveSelectedUp(void)
{
  GetDefaultInterface()->moveSelectedUp();
}

void __fastcall TWMPPlaylistCtrl::moveSelectedDown(void)
{
  GetDefaultInterface()->moveSelectedDown();
}

void __fastcall TWMPPlaylistCtrl::addSelectedToPlaylist(Wmplib_tlb::IWMPPlaylist* pdispPlaylist/*[in]*/)
{
  GetDefaultInterface()->addSelectedToPlaylist(pdispPlaylist/*[in]*/);
}

long __fastcall TWMPPlaylistCtrl::getNextSelectedItem(long nStartIndex/*[in]*/)
{
  long pnSelected;
  OLECHECK(GetDefaultInterface()->getNextSelectedItem(nStartIndex, (long*)&pnSelected));
  return pnSelected;
}

long __fastcall TWMPPlaylistCtrl::getNextCheckedItem(long nStartIndex/*[in]*/)
{
  long pnChecked;
  OLECHECK(GetDefaultInterface()->getNextCheckedItem(nStartIndex, (long*)&pnChecked));
  return pnChecked;
}

void __fastcall TWMPPlaylistCtrl::setSelectedState(long nIndex/*[in]*/, 
                                                   VARIANT_BOOL vbSelected/*[in]*/)
{
  GetDefaultInterface()->setSelectedState(nIndex/*[in]*/, vbSelected/*[in]*/);
}

void __fastcall TWMPPlaylistCtrl::setCheckedState(long nIndex/*[in]*/, 
                                                  VARIANT_BOOL vbChecked/*[in]*/)
{
  GetDefaultInterface()->setCheckedState(nIndex/*[in]*/, vbChecked/*[in]*/);
}

void __fastcall TWMPPlaylistCtrl::sortColumn(long nIndex/*[in]*/)
{
  GetDefaultInterface()->sortColumn(nIndex/*[in]*/);
}

void __fastcall TWMPPlaylistCtrl::setColumnResizeMode(long nIndex/*[in]*/, BSTR newMode/*[in]*/)
{
  GetDefaultInterface()->setColumnResizeMode(nIndex/*[in]*/, newMode/*[in]*/);
}

void __fastcall TWMPPlaylistCtrl::setColumnWidth(long nIndex/*[in]*/, long nWidth/*[in]*/)
{
  GetDefaultInterface()->setColumnWidth(nIndex/*[in]*/, nWidth/*[in]*/);
}

long __fastcall TWMPPlaylistCtrl::getNextSelectedItem2(long nStartIndex/*[in]*/)
{
  long pnSelected;
  OLECHECK(GetDefaultInterface()->getNextSelectedItem2(nStartIndex, (long*)&pnSelected));
  return pnSelected;
}

long __fastcall TWMPPlaylistCtrl::getNextCheckedItem2(long nStartIndex/*[in]*/)
{
  long pnChecked;
  OLECHECK(GetDefaultInterface()->getNextCheckedItem2(nStartIndex, (long*)&pnChecked));
  return pnChecked;
}

void __fastcall TWMPPlaylistCtrl::setSelectedState2(long nIndex/*[in]*/, 
                                                    VARIANT_BOOL vbSelected/*[in]*/)
{
  GetDefaultInterface()->setSelectedState2(nIndex/*[in]*/, vbSelected/*[in]*/);
}

void __fastcall TWMPPlaylistCtrl::setCheckedState2(long nIndex/*[in]*/, 
                                                   VARIANT_BOOL vbChecked/*[in]*/)
{
  GetDefaultInterface()->setCheckedState2(nIndex/*[in]*/, vbChecked/*[in]*/);
}

Wmplib_tlb::IWMPPlaylistPtr __fastcall TWMPPlaylistCtrl::get_Playlist(void)
{
  Wmplib_tlb::IWMPPlaylistPtr ppdispPlaylist;
  OLECHECK(GetDefaultInterface()->get_Playlist(&ppdispPlaylist));
  return ppdispPlaylist;
}

void __fastcall TWMPPlaylistCtrl::set_Playlist(Wmplib_tlb::IWMPPlaylistPtr ppdispPlaylist/*[in]*/)
{
  GetDefaultInterface()->set_Playlist(ppdispPlaylist/*[in]*/);
}

BSTR __fastcall TWMPPlaylistCtrl::get_columns(void)
{
  BSTR pbstrColumns = 0;
  OLECHECK(GetDefaultInterface()->get_columns((BSTR*)&pbstrColumns));
  return pbstrColumns;
}

void __fastcall TWMPPlaylistCtrl::set_columns(BSTR pbstrColumns/*[in]*/)
{
  GetDefaultInterface()->set_columns(pbstrColumns/*[in]*/);
}

long __fastcall TWMPPlaylistCtrl::get_columnCount(void)
{
  long pVal;
  OLECHECK(GetDefaultInterface()->get_columnCount((long*)&pVal));
  return pVal;
}

BSTR __fastcall TWMPPlaylistCtrl::get_columnOrder(void)
{
  BSTR pbstrColumnOrder = 0;
  OLECHECK(GetDefaultInterface()->get_columnOrder((BSTR*)&pbstrColumnOrder));
  return pbstrColumnOrder;
}

void __fastcall TWMPPlaylistCtrl::set_columnOrder(BSTR pbstrColumnOrder/*[in]*/)
{
  GetDefaultInterface()->set_columnOrder(pbstrColumnOrder/*[in]*/);
}

VARIANT_BOOL __fastcall TWMPPlaylistCtrl::get_columnsVisible(void)
{
  VARIANT_BOOL pVal;
  OLECHECK(GetDefaultInterface()->get_columnsVisible((VARIANT_BOOL*)&pVal));
  return pVal;
}

void __fastcall TWMPPlaylistCtrl::set_columnsVisible(VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_columnsVisible(pVal/*[in]*/);
}

VARIANT_BOOL __fastcall TWMPPlaylistCtrl::get_dropDownVisible(void)
{
  VARIANT_BOOL pVal;
  OLECHECK(GetDefaultInterface()->get_dropDownVisible((VARIANT_BOOL*)&pVal));
  return pVal;
}

void __fastcall TWMPPlaylistCtrl::set_dropDownVisible(VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_dropDownVisible(pVal/*[in]*/);
}

VARIANT_BOOL __fastcall TWMPPlaylistCtrl::get_playlistItemsVisible(void)
{
  VARIANT_BOOL pVal;
  OLECHECK(GetDefaultInterface()->get_playlistItemsVisible((VARIANT_BOOL*)&pVal));
  return pVal;
}

void __fastcall TWMPPlaylistCtrl::set_playlistItemsVisible(VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_playlistItemsVisible(pVal/*[in]*/);
}

VARIANT_BOOL __fastcall TWMPPlaylistCtrl::get_checkboxesVisible(void)
{
  VARIANT_BOOL pVal;
  OLECHECK(GetDefaultInterface()->get_checkboxesVisible((VARIANT_BOOL*)&pVal));
  return pVal;
}

void __fastcall TWMPPlaylistCtrl::set_checkboxesVisible(VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_checkboxesVisible(pVal/*[in]*/);
}

BSTR __fastcall TWMPPlaylistCtrl::get_backgroundColor(void)
{
  BSTR pbstrColor = 0;
  OLECHECK(GetDefaultInterface()->get_backgroundColor((BSTR*)&pbstrColor));
  return pbstrColor;
}

void __fastcall TWMPPlaylistCtrl::set_backgroundColor(BSTR pbstrColor/*[in]*/)
{
  GetDefaultInterface()->set_backgroundColor(pbstrColor/*[in]*/);
}

BSTR __fastcall TWMPPlaylistCtrl::get_foregroundColor(void)
{
  BSTR pbstrColor = 0;
  OLECHECK(GetDefaultInterface()->get_foregroundColor((BSTR*)&pbstrColor));
  return pbstrColor;
}

void __fastcall TWMPPlaylistCtrl::set_foregroundColor(BSTR pbstrColor/*[in]*/)
{
  GetDefaultInterface()->set_foregroundColor(pbstrColor/*[in]*/);
}

BSTR __fastcall TWMPPlaylistCtrl::get_disabledItemColor(void)
{
  BSTR pbstrColor = 0;
  OLECHECK(GetDefaultInterface()->get_disabledItemColor((BSTR*)&pbstrColor));
  return pbstrColor;
}

void __fastcall TWMPPlaylistCtrl::set_disabledItemColor(BSTR pbstrColor/*[in]*/)
{
  GetDefaultInterface()->set_disabledItemColor(pbstrColor/*[in]*/);
}

BSTR __fastcall TWMPPlaylistCtrl::get_itemPlayingColor(void)
{
  BSTR pbstrColor = 0;
  OLECHECK(GetDefaultInterface()->get_itemPlayingColor((BSTR*)&pbstrColor));
  return pbstrColor;
}

void __fastcall TWMPPlaylistCtrl::set_itemPlayingColor(BSTR pbstrColor/*[in]*/)
{
  GetDefaultInterface()->set_itemPlayingColor(pbstrColor/*[in]*/);
}

BSTR __fastcall TWMPPlaylistCtrl::get_itemPlayingBackgroundColor(void)
{
  BSTR pbstrBackgroundColor = 0;
  OLECHECK(GetDefaultInterface()->get_itemPlayingBackgroundColor((BSTR*)&pbstrBackgroundColor));
  return pbstrBackgroundColor;
}

void __fastcall TWMPPlaylistCtrl::set_itemPlayingBackgroundColor(BSTR pbstrBackgroundColor/*[in]*/)
{
  GetDefaultInterface()->set_itemPlayingBackgroundColor(pbstrBackgroundColor/*[in]*/);
}

BSTR __fastcall TWMPPlaylistCtrl::get_backgroundImage(void)
{
  BSTR pbstrImage = 0;
  OLECHECK(GetDefaultInterface()->get_backgroundImage((BSTR*)&pbstrImage));
  return pbstrImage;
}

void __fastcall TWMPPlaylistCtrl::set_backgroundImage(BSTR pbstrImage/*[in]*/)
{
  GetDefaultInterface()->set_backgroundImage(pbstrImage/*[in]*/);
}

VARIANT_BOOL __fastcall TWMPPlaylistCtrl::get_allowItemEditing(void)
{
  VARIANT_BOOL pVal;
  OLECHECK(GetDefaultInterface()->get_allowItemEditing((VARIANT_BOOL*)&pVal));
  return pVal;
}

void __fastcall TWMPPlaylistCtrl::set_allowItemEditing(VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_allowItemEditing(pVal/*[in]*/);
}

VARIANT_BOOL __fastcall TWMPPlaylistCtrl::get_allowColumnSorting(void)
{
  VARIANT_BOOL pVal;
  OLECHECK(GetDefaultInterface()->get_allowColumnSorting((VARIANT_BOOL*)&pVal));
  return pVal;
}

void __fastcall TWMPPlaylistCtrl::set_allowColumnSorting(VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_allowColumnSorting(pVal/*[in]*/);
}

BSTR __fastcall TWMPPlaylistCtrl::get_dropDownList(void)
{
  BSTR pbstrList = 0;
  OLECHECK(GetDefaultInterface()->get_dropDownList((BSTR*)&pbstrList));
  return pbstrList;
}

void __fastcall TWMPPlaylistCtrl::set_dropDownList(BSTR pbstrList/*[in]*/)
{
  GetDefaultInterface()->set_dropDownList(pbstrList/*[in]*/);
}

BSTR __fastcall TWMPPlaylistCtrl::get_dropDownToolTip(void)
{
  BSTR pbstrToolTip = 0;
  OLECHECK(GetDefaultInterface()->get_dropDownToolTip((BSTR*)&pbstrToolTip));
  return pbstrToolTip;
}

void __fastcall TWMPPlaylistCtrl::set_dropDownToolTip(BSTR pbstrToolTip/*[in]*/)
{
  GetDefaultInterface()->set_dropDownToolTip(pbstrToolTip/*[in]*/);
}

VARIANT_BOOL __fastcall TWMPPlaylistCtrl::get_copying(void)
{
  VARIANT_BOOL pVal;
  OLECHECK(GetDefaultInterface()->get_copying((VARIANT_BOOL*)&pVal));
  return pVal;
}

void __fastcall TWMPPlaylistCtrl::set_copying(VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_copying(pVal/*[in]*/);
}

BSTR __fastcall TWMPPlaylistCtrl::get_itemErrorColor(void)
{
  BSTR pbstrColor = 0;
  OLECHECK(GetDefaultInterface()->get_itemErrorColor((BSTR*)&pbstrColor));
  return pbstrColor;
}

void __fastcall TWMPPlaylistCtrl::set_itemErrorColor(BSTR pbstrColor/*[in]*/)
{
  GetDefaultInterface()->set_itemErrorColor(pbstrColor/*[in]*/);
}

long __fastcall TWMPPlaylistCtrl::get_itemCount(void)
{
  long pnItemCount;
  OLECHECK(GetDefaultInterface()->get_itemCount((long*)&pnItemCount));
  return pnItemCount;
}

Wmplib_tlb::IWMPMedia* __fastcall TWMPPlaylistCtrl::get_itemMedia(long nIndex/*[in]*/)
{
  Wmplib_tlb::IWMPMedia* ppMedia = 0;
  OLECHECK(GetDefaultInterface()->get_itemMedia(nIndex, (Wmplib_tlb::IWMPMedia**)&ppMedia));
  return ppMedia;
}

Wmplib_tlb::IWMPPlaylist* __fastcall TWMPPlaylistCtrl::get_itemPlaylist(long nIndex/*[in]*/)
{
  Wmplib_tlb::IWMPPlaylist* ppPlaylist = 0;
  OLECHECK(GetDefaultInterface()->get_itemPlaylist(nIndex, (Wmplib_tlb::IWMPPlaylist**)&ppPlaylist));
  return ppPlaylist;
}

BSTR __fastcall TWMPPlaylistCtrl::get_leftStatus(void)
{
  BSTR pbstrStatus = 0;
  OLECHECK(GetDefaultInterface()->get_leftStatus((BSTR*)&pbstrStatus));
  return pbstrStatus;
}

void __fastcall TWMPPlaylistCtrl::set_leftStatus(BSTR pbstrStatus/*[in]*/)
{
  GetDefaultInterface()->set_leftStatus(pbstrStatus/*[in]*/);
}

BSTR __fastcall TWMPPlaylistCtrl::get_rightStatus(void)
{
  BSTR pbstrStatus = 0;
  OLECHECK(GetDefaultInterface()->get_rightStatus((BSTR*)&pbstrStatus));
  return pbstrStatus;
}

void __fastcall TWMPPlaylistCtrl::set_rightStatus(BSTR pbstrStatus/*[in]*/)
{
  GetDefaultInterface()->set_rightStatus(pbstrStatus/*[in]*/);
}

VARIANT_BOOL __fastcall TWMPPlaylistCtrl::get_editButtonVisible(void)
{
  VARIANT_BOOL pVal;
  OLECHECK(GetDefaultInterface()->get_editButtonVisible((VARIANT_BOOL*)&pVal));
  return pVal;
}

void __fastcall TWMPPlaylistCtrl::set_editButtonVisible(VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_editButtonVisible(pVal/*[in]*/);
}

BSTR __fastcall TWMPPlaylistCtrl::get_dropDownImage(void)
{
  BSTR pbstrImage = 0;
  OLECHECK(GetDefaultInterface()->get_dropDownImage((BSTR*)&pbstrImage));
  return pbstrImage;
}

void __fastcall TWMPPlaylistCtrl::set_dropDownImage(BSTR pbstrImage/*[in]*/)
{
  GetDefaultInterface()->set_dropDownImage(pbstrImage/*[in]*/);
}

BSTR __fastcall TWMPPlaylistCtrl::get_dropDownBackgroundImage(void)
{
  BSTR pbstrImage = 0;
  OLECHECK(GetDefaultInterface()->get_dropDownBackgroundImage((BSTR*)&pbstrImage));
  return pbstrImage;
}

void __fastcall TWMPPlaylistCtrl::set_dropDownBackgroundImage(BSTR pbstrImage/*[in]*/)
{
  GetDefaultInterface()->set_dropDownBackgroundImage(pbstrImage/*[in]*/);
}

float __fastcall TWMPPlaylistCtrl::get_hueShift(void)
{
  float pVal;
  OLECHECK(GetDefaultInterface()->get_hueShift((float*)&pVal));
  return pVal;
}

void __fastcall TWMPPlaylistCtrl::set_hueShift(float pVal/*[in]*/)
{
  GetDefaultInterface()->set_hueShift(pVal/*[in]*/);
}

float __fastcall TWMPPlaylistCtrl::get_saturation(void)
{
  float pVal;
  OLECHECK(GetDefaultInterface()->get_saturation((float*)&pVal));
  return pVal;
}

void __fastcall TWMPPlaylistCtrl::set_saturation(float pVal/*[in]*/)
{
  GetDefaultInterface()->set_saturation(pVal/*[in]*/);
}

BSTR __fastcall TWMPPlaylistCtrl::get_statusColor(void)
{
  BSTR pbstrColor = 0;
  OLECHECK(GetDefaultInterface()->get_statusColor((BSTR*)&pbstrColor));
  return pbstrColor;
}

void __fastcall TWMPPlaylistCtrl::set_statusColor(BSTR pbstrColor/*[in]*/)
{
  GetDefaultInterface()->set_statusColor(pbstrColor/*[in]*/);
}

VARIANT_BOOL __fastcall TWMPPlaylistCtrl::get_toolbarVisible(void)
{
  VARIANT_BOOL pVal;
  OLECHECK(GetDefaultInterface()->get_toolbarVisible((VARIANT_BOOL*)&pVal));
  return pVal;
}

void __fastcall TWMPPlaylistCtrl::set_toolbarVisible(VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_toolbarVisible(pVal/*[in]*/);
}

BSTR __fastcall TWMPPlaylistCtrl::get_itemSelectedColor(void)
{
  BSTR pbstrColor = 0;
  OLECHECK(GetDefaultInterface()->get_itemSelectedColor((BSTR*)&pbstrColor));
  return pbstrColor;
}

void __fastcall TWMPPlaylistCtrl::set_itemSelectedColor(BSTR pbstrColor/*[in]*/)
{
  GetDefaultInterface()->set_itemSelectedColor(pbstrColor/*[in]*/);
}

BSTR __fastcall TWMPPlaylistCtrl::get_itemSelectedFocusLostColor(void)
{
  BSTR pbstrFocusLostColor = 0;
  OLECHECK(GetDefaultInterface()->get_itemSelectedFocusLostColor((BSTR*)&pbstrFocusLostColor));
  return pbstrFocusLostColor;
}

void __fastcall TWMPPlaylistCtrl::set_itemSelectedFocusLostColor(BSTR pbstrFocusLostColor/*[in]*/)
{
  GetDefaultInterface()->set_itemSelectedFocusLostColor(pbstrFocusLostColor/*[in]*/);
}

BSTR __fastcall TWMPPlaylistCtrl::get_itemSelectedBackgroundColor(void)
{
  BSTR pbstrColor = 0;
  OLECHECK(GetDefaultInterface()->get_itemSelectedBackgroundColor((BSTR*)&pbstrColor));
  return pbstrColor;
}

void __fastcall TWMPPlaylistCtrl::set_itemSelectedBackgroundColor(BSTR pbstrColor/*[in]*/)
{
  GetDefaultInterface()->set_itemSelectedBackgroundColor(pbstrColor/*[in]*/);
}

BSTR __fastcall TWMPPlaylistCtrl::get_itemSelectedBackgroundFocusLostColor(void)
{
  BSTR pbstrFocusLostColor = 0;
  OLECHECK(GetDefaultInterface()->get_itemSelectedBackgroundFocusLostColor((BSTR*)&pbstrFocusLostColor));
  return pbstrFocusLostColor;
}

void __fastcall TWMPPlaylistCtrl::set_itemSelectedBackgroundFocusLostColor(BSTR pbstrFocusLostColor/*[in]*/)
{
  GetDefaultInterface()->set_itemSelectedBackgroundFocusLostColor(pbstrFocusLostColor/*[in]*/);
}

BSTR __fastcall TWMPPlaylistCtrl::get_backgroundSplitColor(void)
{
  BSTR pbstrColor = 0;
  OLECHECK(GetDefaultInterface()->get_backgroundSplitColor((BSTR*)&pbstrColor));
  return pbstrColor;
}

void __fastcall TWMPPlaylistCtrl::set_backgroundSplitColor(BSTR pbstrColor/*[in]*/)
{
  GetDefaultInterface()->set_backgroundSplitColor(pbstrColor/*[in]*/);
}

BSTR __fastcall TWMPPlaylistCtrl::get_statusTextColor(void)
{
  BSTR pbstrColor = 0;
  OLECHECK(GetDefaultInterface()->get_statusTextColor((BSTR*)&pbstrColor));
  return pbstrColor;
}

void __fastcall TWMPPlaylistCtrl::set_statusTextColor(BSTR pbstrColor/*[in]*/)
{
  GetDefaultInterface()->set_statusTextColor(pbstrColor/*[in]*/);
}

IWMPCore3Ptr& TWMPCore::GetDefaultInterface()
{
  if (!m_DefaultIntf)
    Connect();
  return m_DefaultIntf;
}

_di_IUnknown __fastcall TWMPCore::GetDunk()
{
  _di_IUnknown diUnk;
  if (m_DefaultIntf) {
    IUnknownPtr punk = m_DefaultIntf;
    diUnk = LPUNKNOWN(punk);
  }
  return diUnk;
}

void __fastcall TWMPCore::Connect()
{
  if (!m_DefaultIntf) {
    _di_IUnknown punk = GetServer();
    m_DefaultIntf = punk;
    if (ServerData->EventIID != GUID_NULL)
      ConnectEvents(GetDunk());
  }
}

void __fastcall TWMPCore::Disconnect()
{
  if (m_DefaultIntf) {

    if (ServerData->EventIID != GUID_NULL)
      DisconnectEvents(GetDunk());
    m_DefaultIntf.Reset();
  }
}

void __fastcall TWMPCore::BeforeDestruction()
{
  Disconnect();
}

void __fastcall TWMPCore::ConnectTo(IWMPCore3Ptr intf)
{
  Disconnect();
  m_DefaultIntf = intf;
  if (ServerData->EventIID != GUID_NULL)
    ConnectEvents(GetDunk());
}

void __fastcall TWMPCore::InitServerData()
{
  static Oleserver::TServerData sd;
  sd.ClassID = CLSID_WMPCore;
  sd.IntfIID = __uuidof(IWMPCore3);
  sd.EventIID= __uuidof(_WMPCoreEvents);
  ServerData = &sd;
}

void __fastcall TWMPCore::InvokeEvent(int id, Oleserver::TVariantArray& params)
{
  switch(id)
  {
    case 5001: {
      if (OnOpenStateChange) {
        (OnOpenStateChange)(this, params[0]);
      }
      break;
      }
    case 5101: {
      if (OnPlayStateChange) {
        (OnPlayStateChange)(this, params[0]);
      }
      break;
      }
    case 5102: {
      if (OnAudioLanguageChange) {
        (OnAudioLanguageChange)(this, params[0]);
      }
      break;
      }
    case 5002: {
      if (OnStatusChange) {
        (OnStatusChange)(this);
      }
      break;
      }
    case 5301: {
      if (OnScriptCommand) {
        (OnScriptCommand)(this, params[0].bstrVal, params[1].bstrVal);
      }
      break;
      }
    case 5403: {
      if (OnNewStream) {
        (OnNewStream)(this);
      }
      break;
      }
    case 5401: {
      if (OnDisconnect) {
        (OnDisconnect)(this, params[0]);
      }
      break;
      }
    case 5402: {
      if (OnBuffering) {
        (OnBuffering)(this, params[0]);
      }
      break;
      }
    case 5501: {
      if (OnError) {
        (OnError)(this);
      }
      break;
      }
    case 5601: {
      if (OnWarning) {
        (OnWarning)(this, params[0], params[1], params[2].bstrVal);
      }
      break;
      }
    case 5201: {
      if (OnEndOfStream) {
        (OnEndOfStream)(this, params[0]);
      }
      break;
      }
    case 5202: {
      if (OnPositionChange) {
        (OnPositionChange)(this, params[0], params[1]);
      }
      break;
      }
    case 5203: {
      if (OnMarkerHit) {
        (OnMarkerHit)(this, params[0]);
      }
      break;
      }
    case 5204: {
      if (OnDurationUnitChange) {
        (OnDurationUnitChange)(this, params[0]);
      }
      break;
      }
    case 5701: {
      if (OnCdromMediaChange) {
        (OnCdromMediaChange)(this, params[0]);
      }
      break;
      }
    case 5801: {
      if (OnPlaylistChange) {
        (OnPlaylistChange)(this, params[0].pdispVal, (Wmplib_tlb::WMPPlaylistChangeEventType)(int)params[1]);
      }
      break;
      }
    case 5804: {
      if (OnCurrentPlaylistChange) {
        (OnCurrentPlaylistChange)(this, (Wmplib_tlb::WMPPlaylistChangeEventType)(int)params[0]);
      }
      break;
      }
    case 5805: {
      if (OnCurrentPlaylistItemAvailable) {
        (OnCurrentPlaylistItemAvailable)(this, params[0].bstrVal);
      }
      break;
      }
    case 5802: {
      if (OnMediaChange) {
        (OnMediaChange)(this, params[0].pdispVal);
      }
      break;
      }
    case 5803: {
      if (OnCurrentMediaItemAvailable) {
        (OnCurrentMediaItemAvailable)(this, params[0].bstrVal);
      }
      break;
      }
    case 5806: {
      if (OnCurrentItemChange) {
        (OnCurrentItemChange)(this, params[0].pdispVal);
      }
      break;
      }
    case 5807: {
      if (OnMediaCollectionChange) {
        (OnMediaCollectionChange)(this);
      }
      break;
      }
    case 5808: {
      if (OnMediaCollectionAttributeStringAdded) {
        (OnMediaCollectionAttributeStringAdded)(this, params[0].bstrVal, params[1].bstrVal);
      }
      break;
      }
    case 5809: {
      if (OnMediaCollectionAttributeStringRemoved) {
        (OnMediaCollectionAttributeStringRemoved)(this, params[0].bstrVal, params[1].bstrVal);
      }
      break;
      }
    case 5820: {
      if (OnMediaCollectionAttributeStringChanged) {
        (OnMediaCollectionAttributeStringChanged)(this, params[0].bstrVal, params[1].bstrVal, params[2].bstrVal);
      }
      break;
      }
    case 5810: {
      if (OnPlaylistCollectionChange) {
        (OnPlaylistCollectionChange)(this);
      }
      break;
      }
    case 5811: {
      if (OnPlaylistCollectionPlaylistAdded) {
        (OnPlaylistCollectionPlaylistAdded)(this, params[0].bstrVal);
      }
      break;
      }
    case 5812: {
      if (OnPlaylistCollectionPlaylistRemoved) {
        (OnPlaylistCollectionPlaylistRemoved)(this, params[0].bstrVal);
      }
      break;
      }
    case 5818: {
      if (OnPlaylistCollectionPlaylistSetAsDeleted) {
        (OnPlaylistCollectionPlaylistSetAsDeleted)(this, params[0].bstrVal, params[1]);
      }
      break;
      }
    case 5819: {
      if (OnModeChange) {
        (OnModeChange)(this, params[0].bstrVal, params[1]);
      }
      break;
      }
    case 5821: {
      if (OnMediaError) {
        (OnMediaError)(this, params[0].pdispVal);
      }
      break;
      }
    case 5823: {
      if (OnOpenPlaylistSwitch) {
        (OnOpenPlaylistSwitch)(this, params[0].pdispVal);
      }
      break;
      }
    case 5822: {
      if (OnDomainChange) {
        (OnDomainChange)(this, params[0].bstrVal);
      }
      break;
      }
    case 5824: {
      if (OnStringCollectionChange) {
        (OnStringCollectionChange)(this, params[0].pdispVal, (Wmplib_tlb::WMPStringCollectionChangeEventType)(int)params[1], params[2]);
      }
      break;
      }
    case 5825: {
      if (OnMediaCollectionMediaAdded) {
        (OnMediaCollectionMediaAdded)(this, params[0].pdispVal);
      }
      break;
      }
    case 5826: {
      if (OnMediaCollectionMediaRemoved) {
        (OnMediaCollectionMediaRemoved)(this, params[0].pdispVal);
      }
      break;
      }
    default:
      break;
  }
}

void __fastcall TWMPCore::close(void)
{
  GetDefaultInterface()->close();
}

void __fastcall TWMPCore::launchURL(BSTR bstrURL/*[in]*/)
{
  GetDefaultInterface()->launchURL(bstrURL/*[in]*/);
}

Wmplib_tlb::IWMPPlaylist* __fastcall TWMPCore::newPlaylist(BSTR bstrName/*[in]*/, 
                                                           BSTR bstrURL/*[in]*/)
{
  Wmplib_tlb::IWMPPlaylist* ppPlaylist = 0;
  OLECHECK(GetDefaultInterface()->newPlaylist(bstrName, bstrURL, (Wmplib_tlb::IWMPPlaylist**)&ppPlaylist));
  return ppPlaylist;
}

Wmplib_tlb::IWMPMedia* __fastcall TWMPCore::newMedia(BSTR bstrURL/*[in]*/)
{
  Wmplib_tlb::IWMPMedia* ppMedia = 0;
  OLECHECK(GetDefaultInterface()->newMedia(bstrURL, (Wmplib_tlb::IWMPMedia**)&ppMedia));
  return ppMedia;
}

BSTR __fastcall TWMPCore::get_URL(void)
{
  BSTR pbstrURL = 0;
  OLECHECK(GetDefaultInterface()->get_URL((BSTR*)&pbstrURL));
  return pbstrURL;
}

void __fastcall TWMPCore::set_URL(BSTR pbstrURL/*[in]*/)
{
  GetDefaultInterface()->set_URL(pbstrURL/*[in]*/);
}

Wmplib_tlb::WMPOpenState __fastcall TWMPCore::get_openState(void)
{
  Wmplib_tlb::WMPOpenState pwmpos;
  OLECHECK(GetDefaultInterface()->get_openState((Wmplib_tlb::WMPOpenState*)&pwmpos));
  return pwmpos;
}

Wmplib_tlb::WMPPlayState __fastcall TWMPCore::get_playState(void)
{
  Wmplib_tlb::WMPPlayState pwmpps;
  OLECHECK(GetDefaultInterface()->get_playState((Wmplib_tlb::WMPPlayState*)&pwmpps));
  return pwmpps;
}

Wmplib_tlb::IWMPControlsPtr __fastcall TWMPCore::get_controls(void)
{
  Wmplib_tlb::IWMPControlsPtr ppControl;
  OLECHECK(GetDefaultInterface()->get_controls(&ppControl));
  return ppControl;
}

Wmplib_tlb::IWMPSettingsPtr __fastcall TWMPCore::get_settings(void)
{
  Wmplib_tlb::IWMPSettingsPtr ppSettings;
  OLECHECK(GetDefaultInterface()->get_settings(&ppSettings));
  return ppSettings;
}

Wmplib_tlb::IWMPMediaPtr __fastcall TWMPCore::get_currentMedia(void)
{
  Wmplib_tlb::IWMPMediaPtr ppMedia;
  OLECHECK(GetDefaultInterface()->get_currentMedia(&ppMedia));
  return ppMedia;
}

void __fastcall TWMPCore::set_currentMedia(Wmplib_tlb::IWMPMediaPtr ppMedia/*[in]*/)
{
  GetDefaultInterface()->set_currentMedia(ppMedia/*[in]*/);
}

Wmplib_tlb::IWMPMediaCollectionPtr __fastcall TWMPCore::get_mediaCollection(void)
{
  Wmplib_tlb::IWMPMediaCollectionPtr ppMediaCollection;
  OLECHECK(GetDefaultInterface()->get_mediaCollection(&ppMediaCollection));
  return ppMediaCollection;
}

Wmplib_tlb::IWMPPlaylistCollectionPtr __fastcall TWMPCore::get_playlistCollection(void)
{
  Wmplib_tlb::IWMPPlaylistCollectionPtr ppPlaylistCollection;
  OLECHECK(GetDefaultInterface()->get_playlistCollection(&ppPlaylistCollection));
  return ppPlaylistCollection;
}

BSTR __fastcall TWMPCore::get_versionInfo(void)
{
  BSTR pbstrVersionInfo = 0;
  OLECHECK(GetDefaultInterface()->get_versionInfo((BSTR*)&pbstrVersionInfo));
  return pbstrVersionInfo;
}

Wmplib_tlb::IWMPNetworkPtr __fastcall TWMPCore::get_network(void)
{
  Wmplib_tlb::IWMPNetworkPtr ppQNI;
  OLECHECK(GetDefaultInterface()->get_network(&ppQNI));
  return ppQNI;
}

Wmplib_tlb::IWMPPlaylistPtr __fastcall TWMPCore::get_currentPlaylist(void)
{
  Wmplib_tlb::IWMPPlaylistPtr ppPL;
  OLECHECK(GetDefaultInterface()->get_currentPlaylist(&ppPL));
  return ppPL;
}

void __fastcall TWMPCore::set_currentPlaylist(Wmplib_tlb::IWMPPlaylistPtr ppPL/*[in]*/)
{
  GetDefaultInterface()->set_currentPlaylist(ppPL/*[in]*/);
}

Wmplib_tlb::IWMPCdromCollectionPtr __fastcall TWMPCore::get_cdromCollection(void)
{
  Wmplib_tlb::IWMPCdromCollectionPtr ppCdromCollection;
  OLECHECK(GetDefaultInterface()->get_cdromCollection(&ppCdromCollection));
  return ppCdromCollection;
}

Wmplib_tlb::IWMPClosedCaptionPtr __fastcall TWMPCore::get_closedCaption(void)
{
  Wmplib_tlb::IWMPClosedCaptionPtr ppClosedCaption;
  OLECHECK(GetDefaultInterface()->get_closedCaption(&ppClosedCaption));
  return ppClosedCaption;
}

VARIANT_BOOL __fastcall TWMPCore::get_isOnline(void)
{
  VARIANT_BOOL pfOnline;
  OLECHECK(GetDefaultInterface()->get_isOnline((VARIANT_BOOL*)&pfOnline));
  return pfOnline;
}

Wmplib_tlb::IWMPErrorPtr __fastcall TWMPCore::get_Error(void)
{
  Wmplib_tlb::IWMPErrorPtr ppError;
  OLECHECK(GetDefaultInterface()->get_Error(&ppError));
  return ppError;
}

BSTR __fastcall TWMPCore::get_status(void)
{
  BSTR pbstrStatus = 0;
  OLECHECK(GetDefaultInterface()->get_status((BSTR*)&pbstrStatus));
  return pbstrStatus;
}

Wmplib_tlb::IWMPDVDPtr __fastcall TWMPCore::get_dvd(void)
{
  Wmplib_tlb::IWMPDVDPtr ppDVD;
  OLECHECK(GetDefaultInterface()->get_dvd(&ppDVD));
  return ppDVD;
}


};     // namespace Wmplib_tlb


// *********************************************************************//
// The Register function is invoked by the IDE when this module is 
// installed in a Package. It provides the list of Components (including
// OCXes) implemented by this module. The following implementation
// informs the IDE of the OCX proxy classes implemented here.
// *********************************************************************//
namespace Wmplib_ocx
{

void __fastcall PACKAGE Register()
{
  // [1]
  TComponentClass cls_ocx[] = {
                              __classid(Wmplib_tlb::TWindowsMediaPlayer)
                           };
  RegisterComponents("ActiveX", cls_ocx,
                     sizeof(cls_ocx)/sizeof(cls_ocx[0])-1);
  // [17]
  TComponentClass cls_svr[] = {
                              __classid(Wmplib_tlb::TWMPButtonCtrl), 
                              __classid(Wmplib_tlb::TWMPListBoxCtrl), 
                              __classid(Wmplib_tlb::TWMPSliderCtrl), 
                              __classid(Wmplib_tlb::TWMPVideoCtrl), 
                              __classid(Wmplib_tlb::TWMPEffects), 
                              __classid(Wmplib_tlb::TWMPEqualizerSettingsCtrl), 
                              __classid(Wmplib_tlb::TWMPVideoSettingsCtrl), 
                              __classid(Wmplib_tlb::TWMPLibraryTreeCtrl), 
                              __classid(Wmplib_tlb::TWMPEditCtrl), 
                              __classid(Wmplib_tlb::TWMPMenuCtrl), 
                              __classid(Wmplib_tlb::TWMPAutoMenuCtrl), 
                              __classid(Wmplib_tlb::TWMPRegionalButtonCtrl), 
                              __classid(Wmplib_tlb::TWMPRegionalButton), 
                              __classid(Wmplib_tlb::TWMPCustomSliderCtrl), 
                              __classid(Wmplib_tlb::TWMPTextCtrl), 
                              __classid(Wmplib_tlb::TWMPPlaylistCtrl), 
                              __classid(Wmplib_tlb::TWMPCore)
                           };
  RegisterComponents("ActiveX", cls_svr,
                     sizeof(cls_svr)/sizeof(cls_svr[0])-1);
}

};     // namespace Wmplib_ocx
