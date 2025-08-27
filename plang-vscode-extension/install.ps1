#!/usr/bin/env pwsh
# PLang VS Code Extension Installer

Write-Host "Installing PLang Language Support for VS Code..." -ForegroundColor Cyan

# Get VS Code extensions directory
$vsCodeExtensionsPath = ""

if ($IsWindows -or $env:OS -eq "Windows_NT") {
    $vsCodeExtensionsPath = "$env:USERPROFILE\.vscode\extensions"
} elseif ($IsLinux) {
    $vsCodeExtensionsPath = "$env:HOME/.vscode/extensions" 
} elseif ($IsMacOS) {
    $vsCodeExtensionsPath = "$env:HOME/.vscode/extensions"
} else {
    # Fallback for Windows PowerShell 5.1
    $vsCodeExtensionsPath = "$env:USERPROFILE\.vscode\extensions"
}

Write-Host "VS Code extensions directory: $vsCodeExtensionsPath" -ForegroundColor Yellow

# Check if VS Code extensions directory exists
if (-not (Test-Path $vsCodeExtensionsPath)) {
    Write-Host "Creating VS Code extensions directory..." -ForegroundColor Yellow
    New-Item -ItemType Directory -Path $vsCodeExtensionsPath -Force | Out-Null
}

# Extension target directory
$extensionTargetDir = Join-Path $vsCodeExtensionsPath "plang-language-support-1.0.0"

# Remove existing installation if it exists
if (Test-Path $extensionTargetDir) {
    Write-Host "Removing existing PLang extension..." -ForegroundColor Yellow
    Remove-Item $extensionTargetDir -Recurse -Force
}

# Copy extension files
Write-Host "Installing PLang extension..." -ForegroundColor Green
$sourceDir = $PSScriptRoot

try {
    Copy-Item -Path $sourceDir -Destination $extensionTargetDir -Recurse -Force
    
    # Remove the installer script from the copied extension
    $installerPath = Join-Path $extensionTargetDir "install.ps1"
    if (Test-Path $installerPath) {
        Remove-Item $installerPath -Force
    }
    
    Write-Host "✅ PLang Language Support installed successfully!" -ForegroundColor Green
    Write-Host ""
    Write-Host "Next steps:" -ForegroundColor Cyan
    Write-Host "1. Restart VS Code" -ForegroundColor White
    Write-Host "2. Open any .pl or .plang file" -ForegroundColor White
    Write-Host "3. Enjoy syntax highlighting and code snippets!" -ForegroundColor White
    Write-Host ""
    Write-Host "Try creating a test file:" -ForegroundColor Yellow
    Write-Host "  echo 'x is 10' > test.pl" -ForegroundColor White
    Write-Host "  code test.pl" -ForegroundColor White
    
} catch {
    Write-Host "❌ Failed to install extension: $($_.Exception.Message)" -ForegroundColor Red
    exit 1
}
