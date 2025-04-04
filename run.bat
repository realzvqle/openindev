@echo off



xmake
copy SDL2.dll build\windows\x86_64\release\SDL2.dll
robocopy resources build\windows\x86_64\release\resources /s
xmake run