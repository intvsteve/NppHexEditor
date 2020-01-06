/**
 * @author		Jens Lorenz		<jens.plugin.npp@gmx.de>
 * @version		1.2
 * @date		2007
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * @note		This is the interface to NativeLang.dll plugin.\n
 *				You need only to include this file into your project and\n
 *				call the particular function to change language of dialogs\n
 *				combo boxes, Notepad++ menu, menus, list headers.\n
 *				Or get only the new text. Only one language can be supported\n
 *				at once. The translations are stored in NativeLang.ini\n
 *				in the plugins config folder. NativeLang.ini needs is \n
 *				formatted in USC2-little endian.\n
 */

#include "NativeLang_def.h"
#include <shlwapi.h>
#include <tchar.h>

CONST TCHAR NATIVE_LANG_NAME[] = _T("NativeLang.dll");

typedef enum eNatLangMsg {
	NPP_NATLANG_CHANGEDLG,			/*!< enum change complete dialog info			*/
	NPP_NATLANG_CHANGENPPMENU,		/*!< enum change plugins menu of Notepad++		*/
	NPP_NATLANG_CHANGEMENU,			/*!< enum change another menu					*/
	NPP_NATLANG_CHANGEHEADER,		/*!< enum change header elements				*/
	NPP_NATLANG_CHANGECOMBO,		/*!< enum change combo elements					*/
	NPP_NATLANG_GETTEXT,			/*!< enum get text via key name					*/
} eNatLangMsg;

/** This struct is only necessary for the communication between this interface 
 *	and NativeLang plugin
 */
typedef struct tNatLangInfo {
	HANDLE		hCtrl;				/*!< HWND or HMENU								*/
	LPCTSTR		pszCtrl;			/*!< section name								*/
	LRESULT		lRes;				/*!< result value								*/
	WPARAM		wParam;				/*!< additional information						*/
	LPARAM		lParam;				/*!< additional information						*/
} tNatLangInfo;

void NLChangeDialog(HINSTANCE hInst, HWND hNpp, HWND hWnd, LPCTSTR pszSection)
{
	TCHAR		szPath[MAX_PATH];
	::GetModuleFileName((HMODULE)hInst, szPath, MAX_PATH);

	tNatLangInfo		nli;
	nli.hCtrl			= hWnd;
	nli.pszCtrl			= pszSection;

	CommunicationInfo	ci;
	ci.srcModuleName	= PathFindFileName(szPath);
	ci.internalMsg		= NPP_NATLANG_CHANGEDLG;
	ci.info				= &nli;
	::SendMessage(hNpp, NPPM_MSGTOPLUGIN, (WPARAM)NATIVE_LANG_NAME, (LPARAM)&ci);
}

void NLChangeNppMenu(HINSTANCE hInst, HWND hNpp, LPCTSTR pszPluginName, FuncItem* funcItem, UINT nbFunc)
{
	TCHAR		szPath[MAX_PATH];
	::GetModuleFileName((HMODULE)hInst, szPath, MAX_PATH);

	tNatLangInfo		nli;
	nli.hCtrl			= NULL;
	nli.pszCtrl			= pszPluginName;
	nli.wParam			= nbFunc;
	nli.lParam			= (LPARAM)funcItem;

	CommunicationInfo	ci;
	ci.srcModuleName	= PathFindFileName(szPath);
	ci.internalMsg		= NPP_NATLANG_CHANGENPPMENU;
	ci.info				= &nli;
	::SendMessage(hNpp, NPPM_MSGTOPLUGIN, (WPARAM)NATIVE_LANG_NAME, (LPARAM)&ci);
}

BOOL NLChangeMenu(HINSTANCE hInst, HWND hNpp, HMENU hMenu, LPCTSTR pszMenu, UINT mf_ByComPos)
{
	TCHAR		szPath[MAX_PATH];
	::GetModuleFileName((HMODULE)hInst, szPath, MAX_PATH);

	tNatLangInfo		nli;
	nli.hCtrl			= hMenu;
	nli.pszCtrl			= pszMenu;
	nli.lRes			= 0;
	nli.wParam			= mf_ByComPos;

	CommunicationInfo	ci;
	ci.srcModuleName	= PathFindFileName(szPath);
	ci.internalMsg		= NPP_NATLANG_CHANGEMENU;
	ci.info				= &nli;
	::SendMessage(hNpp, NPPM_MSGTOPLUGIN, (WPARAM)NATIVE_LANG_NAME, (LPARAM)&ci);

	return (BOOL)nli.lRes;
}

void NLChangeHeader(HINSTANCE hInst, HWND hNpp, HWND hHeader, LPCTSTR pszSection)
{
	TCHAR		szPath[MAX_PATH];
	::GetModuleFileName((HMODULE)hInst, szPath, MAX_PATH);

	tNatLangInfo		nli;
	nli.hCtrl			= hHeader;
	nli.pszCtrl			= pszSection;

	CommunicationInfo	ci;
	ci.srcModuleName	= PathFindFileName(szPath);
	ci.internalMsg		= NPP_NATLANG_CHANGEHEADER;
	ci.info				= &nli;
	::SendMessage(hNpp, NPPM_MSGTOPLUGIN, (WPARAM)NATIVE_LANG_NAME, (LPARAM)&ci);
}

void NLChangeCombo(HINSTANCE hInst, HWND hNpp, HWND hCombo, LPCTSTR pszSection, UINT count)
{
	TCHAR		szPath[MAX_PATH];
	::GetModuleFileName((HMODULE)hInst, szPath, MAX_PATH);

	tNatLangInfo		nli;
	nli.hCtrl			= hCombo;
	nli.pszCtrl			= pszSection;
	nli.wParam			= count;

	CommunicationInfo	ci;
	ci.srcModuleName	= PathFindFileName(szPath);
	ci.internalMsg		= NPP_NATLANG_CHANGECOMBO;
	ci.info				= &nli;
	::SendMessage(hNpp, NPPM_MSGTOPLUGIN, (WPARAM)NATIVE_LANG_NAME, (LPARAM)&ci);
}

UINT NLGetText(HINSTANCE hInst, HWND hNpp, LPCTSTR pszKey, LPTSTR pszText, UINT length)
{
	TCHAR		szPath[MAX_PATH];
	::GetModuleFileName((HMODULE)hInst, szPath, MAX_PATH);

	tNatLangInfo		nli;
	nli.hCtrl			= NULL;
	nli.pszCtrl			= pszKey;
	nli.lRes			= 0;
	nli.wParam			= length;
	nli.lParam			= (LPARAM)&pszText;

	CommunicationInfo	ci;
	ci.srcModuleName	= PathFindFileName(szPath);
	ci.internalMsg		= NPP_NATLANG_GETTEXT;
	ci.info				= &nli;
	::SendMessage(hNpp, NPPM_MSGTOPLUGIN, (WPARAM)NATIVE_LANG_NAME, (LPARAM)&ci);

	return (UINT)nli.lRes;
}

INT NLMessageBox(HINSTANCE hInst, HWND hNpp, LPCTSTR pszKey, UINT uType, HWND hDlg /* = NULL */)
{
	if (hDlg == NULL)
		hDlg = hNpp;

	LPTSTR	wPtr = NULL;
	TCHAR	text[MAX_PATH]	= {0};
	if (NLGetText(hInst, hNpp, pszKey, text, MAX_PATH)) {
		TCHAR *context = NULL;
		wPtr = _tcstok_s(text, _T("\t"), &context);
		context = NULL;
		wPtr = _tcstok_s(NULL, _T("\t"), &context);
		return ::MessageBox(hDlg, text, wPtr, uType);
	}
	return FALSE;
}
