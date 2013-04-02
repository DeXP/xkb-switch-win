xkb-switch-win
==============

xkb-switch-lib API port to Win32/Win64. Needed for vim-xkbswitch plugin: http://www.vim.org/scripts/script.php?script_id=4503 (GitHub: https://github.com/lyokha/vim-xkbswitch ) .

In windows you need not only the plugin, but DLL-files from /bin folder. If you have 64-bit Vim, you need libxkbswitch64.dll. For 32-bit version use libxkbswitch32.dll. If you do not know - you can get both, plugin detects verion automatically.

By default you need to put DLL-file into top directory of Vim. Or you need to set g:XkbSwitchLib variable:
let g:XkbSwitchLib = 'c:\path\to\dll\libxkbswitch32.dll'  


==============

Author: Dmitry Hrabrov a.k.a. DeXPeriX


Original xkb-switch for Linux: https://github.com/ierton/xkb-switch 

