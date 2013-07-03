xkb-switch-win
==============

xkb-switch-lib API port to Win32/Win64. Needed for [vim-xkbswitch plugin](http://www.vim.org/scripts/script.php?script_id=4503) (GitHub: https://github.com/lyokha/vim-xkbswitch ) .


Installation and configuring
----------------------------

In windows you need not only the plugin, but DLL-files from [latest release](https://github.com/DeXP/xkb-switch-win/releases). If you have 64-bit Vim, you need libxkbswitch64.dll. For 32-bit version use libxkbswitch32.dll. If you do not know - you can get both, plugin detects version automatically.

By default you need to put DLL-file into top directory of Vim (where vim.exe is located). Or you need to set g:XkbSwitchLib variable:

```vim
let g:XkbSwitchLib = 'c:\path\to\dll\libxkbswitch32.dll' 
```


Character maps
--------------

Currently only Russian winkeys layout translation map ('ru') is supported out of the box for vim-xkbswitch. But you can create your own layout-file, and 'charmapgen' can help you.

Charmap generator outputs current installed in system charmaps to console. The easiest way to do that - download 'charmapgen32.exe' and 'charmapgen.bat' from [/charmap](https://github.com/DeXP/xkb-switch-win/tree/master/charmap) directory. Than double click on bat-file - a new file will be appeared in current directory.

Than put 'charmap.txt' to your top directory of Vim (where vim.exe is located). You can see languages in this file. Than add needed languages to vimrc :

```vim
let g:XkbSwitchIMappingsTrData = 'charmap.txt'
let g:XkbSwitchIMappings = ['ru', 'by', 'ua']
```

You can see samples of charmap files in [/charmap](https://github.com/DeXP/xkb-switch-win/tree/master/charmap) directory.


Authors
-------

Author: Dmitry Hrabrov a.k.a. DeXPeriX


Original xkb-switch for Linux: https://github.com/ierton/xkb-switch 

