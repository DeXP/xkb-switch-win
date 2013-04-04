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

    char* buf;
    int strl = 0;

    unsigned int i, j, n, Lid;
    LCID localez;
    HKL  lpList[MAX_LAYS];

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

            dprints("\n<  ");
            j = 0;
            while( uss[j] != 0 ){
                buf = Xkb_Switch_getLocalizedCharByUS( uss[j], lang );
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
            dprints("\n");

            dprints(">  ");
            j = 0;
            while( uss[j] != 0 ){
                buf = Xkb_Switch_getLocalizedCharByUS( uss[j], lang );
                strl=0;
                while(buf[strl]!=0) strl++;
                if( (strl >  1) || (buf[0] != uss[j]) )
                    dprints(buf);
                j++;
            }
            dprints("\n\n");


        }
    }
    return 0;
}
