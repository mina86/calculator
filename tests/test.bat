
@echo off
set TEST_SRC=src
set MAIN_SRC=..\src
set BC=bc
set CALC=..\calc
set BUILD=%TEST_SRC%\build
set COMP=%TEST_SRC%\comp

if "x%1" == "x-h" goto USAGE
goto CHECK_CMD

:USAGE
	echo usage: $0 [option]
	echo option: -h  Print this messsage
	echo         xx  where xx is number of tests executed
	goto END

:CHECK_CMD
if "!TEST_SRC!" == "src" goto BUILD_ENV
echo Please run first 'cmd /V'. It enables dynamic variable substitution.
goto END
	
	
:BUILD_ENV
rem Checking if bc is available
echo 'bc' is required to run tests.
echo Checking for 'bc' program...
echo 2+1 | %BC% -l > nul
if %errorlevel% GTR 0 goto BCERR

echo "Building environment"

cd ..
call make.bat
if %errorlevel% GTR 0 exit %ERRORLEVEL%
@echo off
cd tests\src
call "%VS80COMNTOOLS%vsvars32.bat"
call "%VS90COMNTOOLS%vsvars32.bat"
nmake -f make_m8.mak
if %errorlevel% GTR 0 exit %ERRORLEVEL%
cd ..

echo "Testing correctness of calculating programs, bc and calc."

set TEST_NUM=100
if "%1" GTR 0 set TEST_NUM=%1

set TEST_MSG1=simple expressions
set TEST_MSG2=expressions with math functions
set TEST_MSG3=expressions with variables
set TEST_ARG1=
set TEST_ARG2=-f
set TEST_ARG3=-v

rem Running 3 tests...
set i=1
:TEST
echo Testing !TEST_MSG%i%!...

set j=0
:TEST_LOOP
echo %j% / %TEST_NUM%:

		%BUILD% !TEST_ARG%i%! > test.txt
		%CALC% -v -q < testcalc > cal1
		%BC% -l < testbc > cal2

		%COMP% cal1 cal2
		if %errorlevel% == 0 echo ok.
		if %errorlevel% GTR 0 exit 1

if "%j%" == "%TEST_NUM%" goto NEXT_TEST
set /A j=%j%+1
goto TEST_LOOP

:NEXT_TEST
if "%i%" == "2" goto END
set /A i=%i%+1
goto TEST

:BCERR
echo bc program not found. Please install bc, if you want to run tests.

:END
@echo on
