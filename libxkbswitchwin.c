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

char lName[LBUF+1];

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
        GetLocaleInfo(localez, LOCALE_SISO639LANGNAME, lName, LBUF);

        if( (lName[0]=='e') && (lName[1]=='n') ){
            /* Replace 'en' string to 'us' */
            lName[0] = 'u';
            lName[1] = 's';
            lName[2] = 0;
        }
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
        GetLocaleInfo(localez, LOCALE_SISO639LANGNAME, lName, LBUF);
        if( (hwnd) && (newgrp[0] == lName[0]) && (newgrp[1] == lName[1]) ){
            currentLayout = lpList[i];
            PostMessage(hwnd,WM_INPUTLANGCHANGEREQUEST,0,(LPARAM)(currentLayout));
            return lName;
        }
    }
    return NULL;
}
