/* xkb-switch-lib API port to Win32/Win64
 * Copyright (C) 2013 Dmitry Hrabrov a.k.a. DeXPeriX
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include <windows.h>

#define MAX_LAYS 10
#define LBUF 3
#define KBUF_SIZE 256


char lName[LBUF+1];
char aName[LBUF+1];
char keybuf[KBUF_SIZE];


BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    lName[0] = 0;
    lName[1] = 0;
    lName[2] = 0;
    return TRUE; // succesful
}

inline char dtolower(char c){
    if( (c>='A') && (c<='Z') ) c = c - 'A' + 'a';
    return c;
}


__declspec(dllexport)
const char *  Xkb_Switch_getXkbLayout( const char * param /* unused */ ){
    unsigned int x;
    HWND hwnd;
    DWORD threadId;
    HKL currentLayout;
    LCID localez;

    hwnd = GetForegroundWindow();
    if( hwnd ){
        threadId = GetWindowThreadProcessId(hwnd, NULL);
        currentLayout = GetKeyboardLayout(threadId);
        x = (unsigned int)currentLayout & 0x0000FFFF;
        localez = MAKELCID( (LANGID)x, SORT_DEFAULT);
        GetLocaleInfo(localez, LOCALE_SISO3166CTRYNAME, lName, LBUF);

        lName[0] = dtolower(lName[0]);
        lName[1] = dtolower(lName[1]);
        lName[2] = 0;
        return lName;
    } else return NULL;
}


__declspec(dllexport)
const char *  Xkb_Switch_setXkbLayout( const char *  newgrp ){
    unsigned int i, n, Lid;
    HKL  lpList[MAX_LAYS];
    HKL  currentLayout;
    HWND hwnd;

    if ( newgrp == NULL || newgrp[ 0 ] == '\0' ) return NULL;

    n = GetKeyboardLayoutList(0, NULL);
    n = GetKeyboardLayoutList(n, lpList);
    hwnd = GetForegroundWindow();

    for(i=0; i<n; i++){
        Lid = ((unsigned int)lpList[i]) & 0x0000FFFF; /* bottom 16 bit */
        LCID localez = MAKELCID( (LANGID)Lid, SORT_DEFAULT);
        GetLocaleInfo(localez, LOCALE_SISO3166CTRYNAME, lName, LBUF);
        if(
           (hwnd) &&
           ( dtolower(newgrp[0]) == dtolower(lName[0]) ) &&
           ( dtolower(newgrp[1]) == dtolower(lName[1]) )
        ){
            currentLayout = lpList[i];
            PostMessage(hwnd,WM_INPUTLANGCHANGEREQUEST,0,(LPARAM)(currentLayout));
            return lName;
        }
    }
    return NULL;
}


__declspec(dllexport)
const char *  Xkb_Switch_getLocalizedCharByUS( char c, const char * grp ){
    unsigned int i, n, Lid;
    HKL  lpList[MAX_LAYS];
    HKL  currentLayout;

    short key, topkey;
    char keyboardState[KBUF_SIZE];
    unsigned long wbuf = 0;
    int canConvert = 0;

    n = GetKeyboardLayoutList(0, NULL);
    n = GetKeyboardLayoutList(n, lpList);

    //key = VkKeyScan(c);
    key = VkKeyScanEx(c, 1033); //get key from us-layout
    topkey = (key & 0xFF00) >> 8;

    keybuf[0] = 0;
    keybuf[1] = 0;
    keybuf[2] = 0;
    for(i=0; i< ( sizeof(keyboardState)/sizeof(keyboardState[0]) ); i++) keyboardState[i] = 0;
    if( topkey & 1 ) keyboardState[VK_SHIFT] = 0xFF;
    if( topkey & 2 ) keyboardState[VK_CONTROL] = 0xFF;
    if( topkey & 4 ) keyboardState[VK_MENU] = 0xFF;

    for(i=0; i<n; i++){
        Lid = ((unsigned int)lpList[i]) & 0x0000FFFF; /* bottom 16 bit */
        currentLayout = lpList[i];
        LCID localez = MAKELCID( (LANGID)Lid, SORT_DEFAULT);
        GetLocaleInfo(localez, LOCALE_SISO3166CTRYNAME, aName, LBUF);
        if(
           ( dtolower(grp[0]) == dtolower(aName[0]) ) &&
           ( dtolower(grp[1]) == dtolower(aName[1]) )
        ){
            //res = MapVirtualKeyEx(key, DMAPVK_VK_TO_CHAR, currentLayout);
            //canConvert = ToUnicodeEx( key, 0, keyboardState, keybuf, KBUF_SIZE, 0, currentLayout );
            canConvert = ToAsciiEx( key, 0, keyboardState, &wbuf, 0, currentLayout );
            if( canConvert > 0 ){
                keybuf[0] = wbuf;
                keybuf[canConvert] = 0;
            }
        }
    }

    return keybuf;
}


__declspec(dllexport)
const char *  Xkb_Switch_getCurrentCharByUS(const char * curChar){
    char c = curChar[0];
    return Xkb_Switch_getLocalizedCharByUS( c, Xkb_Switch_getXkbLayout(NULL) );
}
