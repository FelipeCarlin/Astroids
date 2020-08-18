@echo off

call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
set path=%~dp0;%path%

%~d0%
cd %~dp0%\..\..