/* Charmapgen for vim-xkbswitch (Win32/Win64)
 * Copyright (C) 2013 Dmitry Hrabrov a.k.a. DeXPeriX
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include <windows.h>

#include "libxkbswitchwin.h"


#if !defined(_MSC_VER)
int smain(){

    inline
#endif
    int dprints(const char* buf){
        DWORD wrt;
        int cnt=0;
        while(buf[cnt]!=0) cnt++;
        WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), buf, cnt, &wrt, NULL);
        return wrt;
    }

#if defined(_MSC_VER)
int smain(){
#endif

    char lang[4];
    char* uss = "qwertyuiop[]asdfghjkl;'zxcvbnm,.`/QWERTYUIOP{}ASDFGHJKL:\"ZXCVBNM<>?~!@#$%^&*()|1234567890-=";

    int isUTF = 0;

    char* buf;
    int strl = 0;

    unsigned int i, j, n, cc, Lid;
    LCID localez;
    HKL  lpList[MAX_LAYS];


    char* cmdline = (char *)GetCommandLineA();
    int clen = 0;
    while( cmdline[clen]!= 0 ) clen++;
    cc = 0;
    while( (cc < clen) && ( cmdline[cc]!= ' ' ) ) cc++;
    while( cmdline[cc] == ' ' ) cc++;
    while( cmdline[cc] == '-' ) cc++;
    while( cmdline[cc] == '/' ) cc++;
    switch( cmdline[cc] ){
        case 'u': isUTF = 1; break;
        case '?':
        case 'h':
            dprints("Character map generator for vim-xkbswitch. Outputs current installed in system charmaps to STDOUT (standart console output)\r\n");
            dprints("default output encoding - system encoding\r\n\r\n");
            dprints("Usage:\r\n");
            dprints("\tcharmapgen.exe [option]\r\n");
            dprints("Where [option] is one of:\r\n");
            dprints("\t/? , -h , --help  -  this help\r\n");
            dprints("\t/u , -utf, --unicode  -  set output encoding to UTF-8\r\n");
            dprints("\r\nAuthor: Dmitry Hrabrov a.k.a. DeXPeriX\r\n");
            return 0;
        break;
    }

    n = GetKeyboardLayoutList(0, NULL);
    n = GetKeyboardLayoutList(n, lpList);

    for(i=0; i<n; i++){
        Lid = ((unsigned int)lpList[i]) & 0x0000FFFF; /* bottom 16 bit */
        localez = MAKELCID( (LANGID)Lid, SORT_DEFAULT);
        GetLocaleInfo(localez, LOCALE_SISO3166CTRYNAME, lang, LBUF);

        lang[0] = dtolower(lang[0]);
        lang[1] = dtolower(lang[1]);

        if( Lid != 1033){ //US
            dprints(lang);

            dprints("\r\n<  ");
            j = 0;
            while( uss[j] != 0 ){
                buf = Xkb_Switch_getLocalizedCharByUS( uss[j], lang, isUTF );
                strl=0;
                while(buf[strl]!=0) strl++;
                if( (strl >  1) || (buf[0] != uss[j]) ){
                    /*printf("%c", uss[i]);*/
                    buf[0] = uss[j];
                    buf[1] = 0;
                    dprints(buf);
                }
                j++;
            }
            dprints("\r\n");

            dprints(">  ");
            j = 0;
            while( uss[j] != 0 ){
                buf = Xkb_Switch_getLocalizedCharByUS( uss[j], lang, isUTF );
                strl=0;
                while(buf[strl]!=0) strl++;
                if( (strl >  1) || (buf[0] != uss[j]) )
                    dprints(buf);
                j++;
            }
            dprints("\r\n\r\n");


        }
    }
    return 0;
}
