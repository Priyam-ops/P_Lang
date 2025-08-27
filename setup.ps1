#!/usr/bin/env pwsh
# PLang Setup Script - Creates the interpreter system
# Run this once to set up PLang like Python

Write-Host "Setting up PLang Interpreter..." -ForegroundColor Cyan

# Step 1: Build the core interpreter
Write-Host "Building core interpreter..." -ForegroundColor Yellow

if (Get-Command gcc -ErrorAction SilentlyContinue) {
    $compiler = "gcc"
} elseif (Get-Command clang -ErrorAction SilentlyContinue) {
    $compiler = "clang"
} elseif (Get-Command cl -ErrorAction SilentlyContinue) {
    $compiler = "cl"
} else {
    Write-Host "Error: No C compiler found (gcc, clang, or cl needed)" -ForegroundColor Red
    exit 1
}

Write-Host "Using $compiler..." -ForegroundColor Green

# Build the interpreter engine
if ($compiler -eq "cl") {
    & $compiler /Fe:plang_compiler.exe plang_compiler.c
} else {
    & $compiler -o plang_compiler.exe plang_compiler.c
}

if (-not (Test-Path "plang_compiler.exe")) {
    Write-Host "Error: Failed to build interpreter engine" -ForegroundColor Red
    exit 1
}

# Step 2: Build the main PLang executable
Write-Host "Building main PLang executable..." -ForegroundColor Yellow

if ($compiler -eq "cl") {
    & $compiler /Fe:plang.exe plang_main.c
} else {
    & $compiler -o plang.exe plang_main.c
}

if (-not (Test-Path "plang.exe")) {
    Write-Host "Error: Failed to build main executable" -ForegroundColor Red
    exit 1
}

Write-Host "`nSetup complete! PLang is ready to use." -ForegroundColor Green
Write-Host "`nUsage examples:" -ForegroundColor Cyan
Write-Host "  .\plang.exe myprogram.pl" -ForegroundColor White
Write-Host "  .\plang.ps1 myprogram.pl" -ForegroundColor White
Write-Host "  plang.bat myprogram.pl" -ForegroundColor White

# Create a simple test program
$TestProgram = @"
x is 10
y is 20
z is x + y
show z
show "Hello from PLang!"
"@

$TestProgram | Out-File -FilePath "test.pl" -Encoding UTF8

Write-Host "`nCreated test.pl - try running:" -ForegroundColor Yellow
Write-Host "  .\plang.exe test.pl" -ForegroundColor White
