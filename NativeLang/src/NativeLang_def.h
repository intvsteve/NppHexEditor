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

#ifndef NATIVE_LANG_DEF_H
#define NATIVE_LANG_DEF_H

#include "PluginInterface.h"

/**
 * @fn			void NLChangeDialog(HINSTANCE hInst, HWND hNpp, HWND hWnd, LPCTSTR pszSection)
 * @brief		Changes the dialog language. Call function in e.g. WM_INITDIALOG.
 *
 * @param[in]	hInst			The instance handle of Notepad++.
 * @param[in]	hNpp			The window handle of Notepad++.
 * @param[in]	hWnd			The window handle of the dialog box.
 * @param[in]	pszSection		The section name in NativeLang.ini file.
 * @retval		void			Nothing
 *
 * @details		Add in NativeLang.ini a section like the following:\n
 *				\n
 *				['plugin_file_name' 'section_name']\n
 *				'resource_value'="new name"\n
 *				...\n
 *
 * @note		'&' sign for key selection supported, e.g. "&Cancel process"
 */
void NLChangeDialog(HINSTANCE hInst, HWND hNpp, HWND hWnd, LPCTSTR pszSection);

/**
 * @fn			void NLChangeNppMenu(HINSTANCE hInst, HWND hNpp, LPCTSTR pszPluginName, FuncItem* funcItem, UINT nbFunc)
 * @brief		Changes Notepad++ plugins menu. Call function on notification NPPN_TBMODIFICATION.
 *
 * @param[in]	hInst			The instance handle of Notepad++.
 * @param[in]	hNpp			The window handle of Notepad++.
 * @param[in]	pszPluginName	The name of plugin that was given to Notepad++ on by function getName().
 * @param[in]	funcItem		The funcItem struct that was given to Notepad++ by function getFuncsArray().
 * @param[in]	nbFunc			The size of the funcItem struct that was given to Notepad++ by function getFuncsArray().
 * @retval		void			Nothing
 *
 * @details		Add in NativeLang.ini a section like the following:\n
 *				\n
 *				['plugin_file_name' NppMenu]\n
 *				Main="new plugin name in Menu->Plugins"\n
 *				0="name of entry 0"\n
 *				...\n
 *
 * @note		'&' sign for key selection supported, e.g. "&Explorer..."
 */
void NLChangeNppMenu(HINSTANCE hInst, HWND hNpp, LPCTSTR pszPluginName, FuncItem* funcItem, UINT nbFunc);

/**
 * @fn			BOOL NLChangeMenu(HINSTANCE hInst, HWND hNpp, HMENU hMenu, LPCTSTR pszMenu, UINT mf_ByComPos)
 * @brief		Changes given plugin menu. Call function before ::TrackPopupMenu().
 *
 * @param[in]	hInst			The instance handle of Notepad++.
 * @param[in]	hNpp			The window handle of Notepad++.
 * @param[in]	hMenu			The menu handle of the plugin menu.
 * @param[in]	pszMenu			The section name in NativeLang.ini file.
 * @param[in]	mf_ByComPos		Use here MF_BYCOMMAND or MF_BYPOSITION.
 * @retval		BOOL			FALSE if mf_ByComPos is not correct set.
 *
 * @details		Add in NativeLang.ini a section like the following:\n
 *				\n
 *				['plugin_file_name' 'section name']\n
 *				menu_id_or_pos="new name"\n
 *				...\n
 *
 * @note		'&' sign for key selection supported, e.g. "&Open.."
 */
BOOL NLChangeMenu(HINSTANCE hInst, HWND hNpp, HMENU hMenu, LPCTSTR pszMenu, UINT mf_ByComPos);

/**
 * @fn			void NLChangeHeader(HINSTANCE hInst, HWND hNpp, HWND hHeader, LPCTSTR pszSection)
 * @brief		Change automatically the header text. Call function in e.g. WM_INITDIALOG.
 *
 * @param[in]	hInst			The instance handle of Notepad++.
 * @param[in]	hNpp			The window handle of Notepad++.
 * @param[in]	hHeader			The handle of header.
 * @param[in]	pszSection		The section name in NativeLang.ini file.
 * @retval		void			Nothing
 *
 * @details		Add in NativeLang.ini a section like the following:\n
 *				\n
 *				['plugin_file_name' 'section name']\n
 *				orig_name="new name"\n
 *				...\n
 */
void NLChangeHeader(HINSTANCE hInst, HWND hNpp, HWND hHeader, LPCTSTR pszSection);

/**
 * @fn			void NLChangeCombo(HINSTANCE hInst, HWND hNpp, HWND hCombo, LPCTSTR pszSection, UINT count)
 * @brief		Change automatically the combo text. Call function in e.g. WM_INITDIALOG.
 *
 * @param[in]	hInst			The instance handle of Notepad++.
 * @param[in]	hNpp			The window handle of Notepad++.
 * @param[in]	hCombo			The handle of combo box.
 * @param[in]	pszSection		The section name in NativeLang.ini file.
 * @param[in]	count			The count of combo elements.
 * @retval		void			Nothing
 *
 * @details		Add in NativeLang.ini a section like the following:\n
 *				\n
 *				['plugin_file_name' 'section name']\n
 *				pos_in_combo="new name"\n
 *				...\n
 */
void NLChangeCombo(HINSTANCE hInst, HWND hNpp, HWND hCombo, LPCTSTR pszSection, UINT count);

/**
 * @fn			UINT NLGetText(HINSTANCE hInst, HWND hNpp, LPCTSTR pszKey, LPTSTR pszText, UINT length)
 * @brief		ANSI version to get a language specific text by a key.
 *
 * @param[in]	hInst			The instance handle of Notepad++.
 * @param[in]	hNpp			The window handle of Notepad++.
 * @param[in]	pszKey			The key name in NativeLang.ini file.
 * @param[out]	pszText			The buffer to fill.
 * @param[in]	length			The maximum length of text buffer.
 * @retval		UINT			The size of the copied chars into pszText.
 *
 * @details		Add in NativeLang.ini a section like the following:\n
 *				\n
 *				['plugin_file_name' Text]\n
 *				key_name="text"\n
 *				...\n
 *
 * @note		Format tags are supported. Use % instead of \, e.g. %t %s %d %n
 */
UINT NLGetText(HINSTANCE hInst, HWND hNpp, LPCTSTR pszKey, LPTSTR pszText, UINT length);

/**
 * @fn			BOOL NLMessageBox(HINSTANCE hInst, HWND hNpp, LPCTSTR pszKey, UINT uType, HWND hDlg = NULL		)
 * @brief		Show message box identified by a key.
 *
 * @param[in]	hInst			The instance handle of Notepad++.
 * @param[in]	hNpp			The window handle of Notepad++.
 * @param[in]	pszKey			The key name in NativeLang.ini file.
 * @param[in]	uType			The buffer to fill.
 * @param[in]	hDlg			The buffer to fill.
 * @retval		INT				The parent associated handle.
 *
 * @details		Add in NativeLang.ini a section like the following:\n
 *				\n
 *				['plugin_file_name' Text]\n
 *				key_name="text%tcaption%t"\n
 *				...\n
 */
INT NLMessageBox(HINSTANCE hInst, HWND hNpp, LPCTSTR pszKey, UINT uType, HWND hDlg = NULL);

#endif	/* NATIVE_LANG_DEF_H */
