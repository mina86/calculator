@echo off

if "%1" =="clean" goto CLEAN
@echo Calc requires Visual Studio 2005 and Boost libraries to be installed!
if not exist %BOOST_PATH%/Boost/math/complex.hpp goto BOOSTERR

copy /Y msvc\*.* src
cd src
call "%VS80COMNTOOLS%vsvars32.bat"
nmake -f calc_m8.mak %1
cd ..
move src\main.exe calc.exe

@echo To run calc, type: calc.exe
goto END

:CLEAN
cd src
nmake -f calc_m8.mak %1
cd ..
del calc.exe
goto END

:BOOSTERR
@echo Boost libraries are unavailable.
@echo Please define environment variable BOOST_PATH. Example:
@echo set BOOST_PATH="C:\Program Files\boost\boost_1_34_1"
pause
goto END

:END
@echo on
