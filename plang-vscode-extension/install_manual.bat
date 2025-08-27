@echo off
echo Installing PLang Language Support for VS Code...

:: Get the VS Code extensions directory
set "VSCODE_EXTENSIONS=%USERPROFILE%\.vscode\extensions"

:: Create extensions directory if it doesn't exist
if not exist "%VSCODE_EXTENSIONS%" (
    echo Creating VS Code extensions directory...
    mkdir "%VSCODE_EXTENSIONS%"
)

:: Set target directory
set "TARGET_DIR=%VSCODE_EXTENSIONS%\plang-language-support-1.0.0"

:: Remove existing installation
if exist "%TARGET_DIR%" (
    echo Removing existing PLang extension...
    rmdir /s /q "%TARGET_DIR%"
)

:: Copy files
echo Installing PLang extension...
xcopy /E /I /Y "%~dp0" "%TARGET_DIR%"

:: Remove installer from the copied extension
if exist "%TARGET_DIR%\install_manual.bat" (
    del "%TARGET_DIR%\install_manual.bat"
)

echo.
echo ✅ PLang Language Support installed successfully!
echo.
echo Next steps:
echo 1. Restart VS Code
echo 2. Open any .pl or .plang file  
echo 3. Enjoy syntax highlighting and code snippets!
echo.
echo Try creating a test file:
echo   echo x is 10 ^> test.pl
echo   code test.pl
echo.
pause
