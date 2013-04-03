#include <stdio.h>

#include "libxkbswitchwin.h"

void printlang(char* uss, char* lang){
    char* buf;
    puts(lang);

    printf("<  ");
    int i = 0;
    while( uss[i] != 0 ){
        buf = Xkb_Switch_getLocalizedCharByUS( uss[i], lang );
        if( (strlen(buf) >  1) || (buf[0] != uss[i]) )
            printf("%c", uss[i]);
        i++;
    }
    putchar('\n');

    printf(">  ");
    i = 0;
    while( uss[i] != 0 ){
        buf = Xkb_Switch_getLocalizedCharByUS( uss[i], lang );
        if( (strlen(buf) >  1) || (buf[0] != uss[i]) )
            printf("%s", buf);
        i++;
    }
    putchar('\n');putchar('\n');
}

int main()
{
    char dName[4];
    char* uss = "qwertyuiop[]asdfghjkl;'zxcvbnm,.`/QWERTYUIOP{}ASDFGHJKL:\"ZXCVBNM<>?~!@#$%^&*()|1234567890-=";

    unsigned int i, n, Lid;
    HKL  lpList[MAX_LAYS];

    n = GetKeyboardLayoutList(0, NULL);
    n = GetKeyboardLayoutList(n, lpList);

    for(i=0; i<n; i++){
        Lid = ((unsigned int)lpList[i]) & 0x0000FFFF; /* bottom 16 bit */
        LCID localez = MAKELCID( (LANGID)Lid, SORT_DEFAULT);
        GetLocaleInfo(localez, LOCALE_SISO3166CTRYNAME, dName, LBUF);

        dName[0] = tolower(dName[0]);
        dName[1] = tolower(dName[1]);

        if( Lid != 1033) //US
            printlang(uss, dName);
    }
    /*printlang(uss, "ru");
    printlang(uss, "by");
    printlang(uss, "ua");
    printlang(uss, "de");*/
    return 0;
}
