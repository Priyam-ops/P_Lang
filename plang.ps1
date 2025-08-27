#!/usr/bin/env pwsh
# PLang Interpreter Script
# Usage: .\plang.ps1 <source_file>
# Example: .\plang.ps1 myprogram.pl

param([string]$SourceFile)

if (-not $SourceFile) {
    Write-Host "PLang Interpreter v1.0" -ForegroundColor Cyan
    Write-Host "Usage: .\plang.ps1 <source_file>" -ForegroundColor Yellow
    Write-Host "Example: .\plang.ps1 myprogram.pl" -ForegroundColor Yellow
    exit 1
}

if (-not (Test-Path $SourceFile)) {
    Write-Host "Error: File '$SourceFile' not found!" -ForegroundColor Red
    exit 1
}

# Step 1: Ensure the PLang interpreter/compiler is built
if (-not (Test-Path "plang_compiler.exe") -or 
    (Test-Path "plang_compiler.c" -and (Get-Item "plang_compiler.c").LastWriteTime -gt (Get-Item "plang_compiler.exe").LastWriteTime)) {
    
    Write-Host "Building PLang interpreter..." -ForegroundColor Yellow
    
    if (Get-Command gcc -ErrorAction SilentlyContinue) {
        gcc -o plang_compiler.exe plang_compiler.c
    } elseif (Get-Command clang -ErrorAction SilentlyContinue) {
        clang -o plang_compiler.exe plang_compiler.c
    } elseif (Get-Command cl -ErrorAction SilentlyContinue) {
        cl /Fe:plang_compiler.exe plang_compiler.c
    } else {
        Write-Host "Error: No C compiler found (gcc, clang, or cl needed)" -ForegroundColor Red
        exit 1
    }
    
    if (-not (Test-Path "plang_compiler.exe")) {
        Write-Host "Error: Failed to build PLang interpreter" -ForegroundColor Red
        exit 1
    }
}

# Step 2: Execute the PLang program directly
Write-Host "Running '$SourceFile'..." -ForegroundColor Green

# Run the interpreter with filename as command line argument
$process = Start-Process -FilePath ".\plang_compiler.exe" -ArgumentList "`"$SourceFile`"" -Wait -PassThru -NoNewWindow
exit $process.ExitCode
