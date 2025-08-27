# Alternative Installation Methods for PLang VS Code Extension

## Method 1: PowerShell Script (Already Done! ✅)
The extension has been successfully installed using the PowerShell script.

## Method 2: Manual Batch File
If PowerShell doesn't work, run:
```cmd
install_manual.bat
```

## Method 3: Manual Copy (Foolproof)
1. Open File Explorer
2. Navigate to: `%USERPROFILE%\.vscode\extensions`
3. Create a new folder: `plang-language-support-1.0.0`
4. Copy all files from the extension folder into this new folder
5. Restart VS Code

## Method 4: VS Code Developer Extension Install
1. Open VS Code
2. Press `Ctrl+Shift+P`
3. Type "Extensions: Install from VSIX"
4. Browse to the extension folder
5. Select the extension files

## Method 5: Command Line (if you have VSCE)
```bash
npm install -g vsce
vsce package
code --install-extension plang-language-support-1.0.0.vsix
```

## Verification Steps

After installation, verify it works:

1. **Restart VS Code**
2. **Create a test file:**
   ```
   echo "x is 10" > test.pl
   ```
3. **Open the file:**
   ```
   code test.pl
   ```
4. **Check for syntax highlighting:**
   - `x` should be white/default color
   - `is` should be blue (keyword)
   - `10` should be green (number)

## Troubleshooting

If syntax highlighting doesn't appear:
1. Check VS Code status bar shows "PLang" as the language
2. Right-click in the file → "Change Language Mode" → Select "PLang"
3. Check the file extension is `.pl` or `.plang`

## File Locations

- **Windows:** `%USERPROFILE%\.vscode\extensions\plang-language-support-1.0.0\`
- **Mac:** `~/.vscode/extensions/plang-language-support-1.0.0/`
- **Linux:** `~/.vscode/extensions/plang-language-support-1.0.0/`
