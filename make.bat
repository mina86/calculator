@echo off

if "%1" =="clean" goto CLEAN
@echo Calc requires Visual Studio 2005 and Boost libraries to be installed!

rem -- checking dependencies
if not exist %BOOST_PATH%/Boost/math/complex.hpp goto BOOSTERR
if exist "%VS90COMNTOOLS%vsvars32.bat" goto RUNBISON
if exist "%VS80COMNTOOLS%vsvars32.bat" goto RUNBISON
echo Environment variable VSxxCOMNTOOLS (where xx is version of Visual Studio) is not set by default.
echo Please locate your install folder and file vsvars32.bat. Add path to this file like this:
echo set VS80COMNTOOLS=E:\Program Files\Microsoft Visual Studio 9.0\Common7\Tools\
goto END

:RUNBISON
cd src
rem Trying to use Bison if available
bison parser.y
if %errorlevel% GTR 0 goto CPY_PARSER


:INSTALL
call "%VS80COMNTOOLS%vsvars32.bat"
call "%VS90COMNTOOLS%vsvars32.bat"
nmake -f calc_m8.mak %1
cd ..
move src\main.exe calc.exe

@echo To run calc, type: calc.exe
goto END


:CPY_PARSER
cd ..
@echo Bison is not installed or too old, trying to compile with own parser.
copy /Y msvc\*.* src
cd src
goto INSTALL

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
set ERRORLEVEL=1
goto END

:END
@echo on