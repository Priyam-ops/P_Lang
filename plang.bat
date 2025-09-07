@echo off
setlocal EnableDelayedExpansion

:: PLang Interpreter Batch Script
:: Usage: plang.bat <source_file>
:: Example: plang.bat myprogram.pl

if "%1"=="" (
    echo PLang Interpreter v1.0
    echo Usage: plang.bat ^<source_file^>
    echo Example: plang.bat myprogram.pl
    exit /b 1
)

set SOURCE_FILE=%1

:: Check if source file exists
if not exist "%SOURCE_FILE%" (
    echo Error: File '%SOURCE_FILE%' not found!
    exit /b 1
)

:: Step 1: Ensure the PLang interpreter is built
goto :build_interpreter

:: Check if source is newer than executable (basic check)
for %%i in ("plang_compiler.c") do set SOURCE_TIME=%%~ti
for %%i in ("plang_compiler.exe") do set EXE_TIME=%%~ti
if "%SOURCE_TIME%" GTR "%EXE_TIME%" goto :build_interpreter

goto :run_program

:build_interpreter
echo Building PLang interpreter...

:: Try different compilers
gcc --version >nul 2>&1
if %ERRORLEVEL%==0 (
    gcc -o plang_compiler.exe plang_compiler.c
    if %ERRORLEVEL%==0 goto :run_program
)

clang --version >nul 2>&1
if %ERRORLEVEL%==0 (
    clang -o plang_compiler.exe plang_compiler.c
    if %ERRORLEVEL%==0 goto :run_program
)

cl >nul 2>&1
if %ERRORLEVEL%==9009 goto :no_compiler
cl /Fe:plang_compiler.exe plang_compiler.c >nul 2>&1
if %ERRORLEVEL%==0 goto :run_program

:no_compiler
echo Error: No C compiler found (gcc, clang, or cl needed)
exit /b 1

:run_program
echo Running '%SOURCE_FILE%'...

:: Run interpreter with filename as command line argument
plang_compiler.exe "%SOURCE_FILE%"
set EXIT_CODE=%ERRORLEVEL%

exit /b %EXIT_CODE%
