#ifndef LIBXKBSWITCHWIN_H_INCLUDED
#define LIBXKBSWITCHWIN_H_INCLUDED


#include <windows.h>

#define MAX_LAYS 10
#define LBUF 3
#define KBUF_SIZE 256
#define BIGBUF 500

#if defined(_MSC_VER)
#define DX_EXPORT
#else
#define DX_EXPORT __declspec(dllexport)
#endif

char dtolower(char c);
int dxGetLayout(long a);
const char *  Xkb_Switch_getXkbLayout( const char * param /* unused */ );
const char *  Xkb_Switch_setXkbLayout( const char *  newgrp );
//char dxGetLocalizedCharByUS(char c, int layout);
const char *  Xkb_Switch_getLocalizedCharByUS( char c, const char * grp, int isUTF );

const char *  Xkb_Switch_getLocalizedCharByUSutf( char c, const char * grp );
const char *  Xkb_Switch_getLocalizedCharByUSansi( char c, const char * grp );
const char *  Xkb_Switch_getCurrentCharByUSutf(const char * curChar);
const char *  Xkb_Switch_getCurrentCharByUSansi(const char * curChar);
const char *  Xkb_Switch_getCurrentStringByUS(const char * curString);

#endif // LIBXKBSWITCHWIN_H_INCLUDED
