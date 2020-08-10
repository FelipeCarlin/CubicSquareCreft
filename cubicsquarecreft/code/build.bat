@echo off

set CommonCompilerFlags= -MTd -nologo -Gm- -GR- -EHa- -Od -Oi -WX -W4 -wd4201 -wd4100 -wd4189 -wd4505 -DCSC_INTERNAL=1 -DCSC_SLOW=1 -DCSC_WIN32=1 -FC -Z7 
set CommonLinkerFlags= -incremental:no -opt:ref user32.lib Gdi32.lib winmm.lib Opengl32.lib

IF NOT EXIST ..\..\build mkdir ..\..\build
pushd ..\..\build

REM 64-bit build
del *.pdb > NUL 2> NUL
cl %CommonCompilerFlags% ..\cubicsquarecreft\code\cubicsquarecreft.cpp -Fmcubicsquarecreft.map -LD /link -incremental:no -opt:ref /PDB:cubicsquarecreft_%random%.pdb /EXPORT:GameGetSoundSamples /EXPORT:GameUpdateAndRender
cl %CommonCompilerFlags% ..\cubicsquarecreft\code\win32_cubicsquarecreft.cpp -Fmwin32_cubicsquarecreft.map /link %CommonLinkerFlags%
popd