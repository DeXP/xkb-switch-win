@echo off
rem Charmap generator runner

if exist charmapgen32.exe (
    charmapgen32.exe > charmap.txt
	echo File 'charmap.txt' generated
	pause
) else (
    if exist charmapgen64.exe (
        charmapgen64.exe > charmap.txt
        echo File 'charmap.txt' generated
        pause
    ) else (
        echo There is no charmapgen32.exe or charmapgen64.exe ...
        pause
    )
)

