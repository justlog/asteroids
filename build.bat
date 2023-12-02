@echo off
setlocal
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" x64
cl /Zi /MD /Iinclude *.cpp /Femain.exe /link SDL2_ttf.lib SDL2.lib SDL2main.lib shell32.lib /subsystem:console
endlocal
