@echo off

set CommonCompilerFlags= -MTd -nologo -Gm- -GR- -EHa- -Od -Oi -WX -W4 -wd4201 -wd4100 -wd4189 -wd4505 -DASTROIDS_INTERNAL=1 -DASTROIDS_SLOW=1 -DASTROIDS_WIN32=1 -FC -Z7 
set CommonLinkerFlags= -incremental:no -opt:ref user32.lib Gdi32.lib winmm.lib Opengl32.lib 
REM set ResourceLinkerFlags = win32_astroids_resources.res

IF NOT EXIST ..\..\build mkdir ..\..\build
pushd ..\..\build

REM Resources build
REM rc /fo win32_astroids_resources.res ..\astroids\code\win32_astroids_resources.rc

REM 64-bit build
del *.pdb > NUL 2> NUL
REM cl %CommonCompilerFlags% ..\astroids\code\astroids.cpp -Fmastroids.map -LD /link -incremental:no -opt:ref /PDB:astroids_%random%.pdb /EXPORT:GameGetSoundSamples /EXPORT:GameUpdateAndRender
cl %CommonCompilerFlags% ..\astroids\code\win32_astroids.cpp -Fmwin32_astroids.map /link %CommonLinkerFlags% %ResourceLinkerFlags%
popd