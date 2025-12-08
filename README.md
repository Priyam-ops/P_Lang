# P_Lang (PLang) 🚀

<p align="center">
  <img src="https://img.shields.io/badge/Written%20in-C-blue?style=for-the-badge&logo=c" alt="Written in C">
  <img src="https://img.shields.io/badge/WebAssembly-Enabled-purple?style=for-the-badge&logo=webassembly" alt="WebAssembly">
  <img src="https://img.shields.io/badge/License-Open%20Source-green?style=for-the-badge" alt="License">
  <img src="https://img.shields.io/badge/Platform-Cross--Platform-lightgrey?style=for-the-badge" alt="Platform">
</p>

**PLang** is a modern, beginner-friendly programming language developed in C. It aims to fix the common pain points of C while providing a simpler, more intuitive syntax. PLang is designed to be faster than Python with a more user-friendly syntax than C.

---

## ✨ Features

- **Simple Syntax** - Human-readable keywords like `is` for assignment and `show` for output
- **Fast Execution** - Built on C for high performance
- **WebAssembly Support** - Run in the browser with near-native speed
- **Easy to Learn** - Minimal boilerplate, perfect for beginners
- **VS Code Extension** - Syntax highlighting and code snippets available
- **Cross-Platform** - Windows, Linux, macOS, and Web

---

## 📦 Installation

### Prerequisites

You need a C compiler installed on your system:
- **GCC** (MinGW on Windows)
- **Clang**
- **MSVC** (Visual Studio)

### Quick Setup

1. **Clone the repository:**
   ```bash
   git clone https://github.com/Priyam-ops/P_Lang.git
   cd P_Lang
   ```

2. **Run the setup script (PowerShell):**
   ```powershell
   .\setup.ps1
   ```

3. **Or compile manually:**
   ```bash
   gcc -o plang_compiler.exe plang_compiler.c
   ```

---

## 🚀 Running PLang Programs

PLang source files use the `.pl` or `.plang` extension.

### Using PowerShell:
```powershell
.\plang.ps1 myprogram.pl
```

### Using Batch (CMD):
```batch
plang.bat myprogram.pl
```

### Direct Execution:
```bash
.\plang_compiler.exe myprogram.pl
```

---

## 📖 Language Syntax

### Variables

Use `is` for variable assignment:

```plang
x is 10
y is 20
name is "Hello_World"
flag is yes
```

> **Note:** Use underscores `_` for spaces in strings (they are converted to spaces when displayed).

### Output

Use `show` to print values:

```plang
show "Welcome to PLang!"
show x
show result
```

### Arithmetic Operations

PLang supports standard arithmetic operators:

| Operator | Description    | Example          |
|----------|----------------|------------------|
| `+`      | Addition       | `sum is x + y`   |
| `-`      | Subtraction    | `diff is y - x`  |
| `*`      | Multiplication | `prod is x * y`  |
| `/`      | Division       | `quot is y / x`  |

**Example:**
```plang
x is 10
y is 20
sum is x + y
product is x * y
show sum
show product
```

### Parentheses for Order of Operations

```plang
result is (x + y) * 2 - 1
show result
```

### Increment and Decrement

```plang
counter is 0
counter++
counter--
```

### Comparison Operators

| Operator | Description              |
|----------|--------------------------|
| `=`      | Equal to                 |
| `>`      | Greater than             |
| `<`      | Less than                |
| `>=`     | Greater than or equal to |
| `<=`     | Less than or equal to    |
| `!=`     | Not equal to             |

### Conditional Statements

```plang
if x > 10
    show "x is greater than 10"
else
    show "x is 10 or less"
```

### While Loops

```plang
counter is 0
while counter < 5
    show counter
    counter++
```

### User Input

Use `take` to get input from the user:

```plang
take userInput
show userInput
```

### Built-in Commands

| Command | Description                          |
|---------|--------------------------------------|
| `show`  | Print a value or string to console   |
| `clear` | Clear the console screen             |
| `help`  | Display available commands           |
| `exit`  | Exit the program                     |
| `take`  | Get user input                       |

### Boolean Values

PLang supports boolean values:
- `yes` / `true` - represents true
- `no` / `false` - represents false

### Comments

Use `//` for single-line comments:

```plang
// This is a comment
x is 10  // This is also a comment
```

---

## 📝 Complete Example Program

```plang
// PLang Demo Program

// Variable declarations
x is 10
y is 20
name is "PLang"

// Arithmetic
sum is x + y
difference is y - x
product is x * y

// Output
show "Welcome to PLang!"
show name
show sum

// Conditional
if sum > 25
    show "Sum is greater than 25"
else
    show "Sum is 25 or less"

// Loop
counter is 0
while counter < 5
    show counter
    counter++

// Exit
show "Goodbye!"
exit
```

---

## 🎨 VS Code Extension

PLang comes with a VS Code extension for enhanced development experience!

### Features:
- ✅ Syntax Highlighting
- ✅ Code Snippets
- ✅ Auto-completion
- ✅ Bracket Matching
- ✅ Comment Support

### Installation:
1. Navigate to the `plang-vscode-extension` folder
2. Run `install_manual.bat` or copy the folder to your VS Code extensions directory
3. Restart VS Code

### Code Snippets:

| Prefix    | Description              |
|-----------|--------------------------|
| `var`     | Variable assignment      |
| `show`    | Show statement           |
| `if`      | If-else statement        |
| `while`   | While loop               |
| `take`    | Take input               |
| `program` | Basic program template   |

---

## 📁 Project Structure

```
P_Lang/
├── plang_compiler.c          # Main compiler/interpreter source
├── plang.ps1                 # PowerShell runner script
├── plang.bat                 # Batch runner script
├── setup.ps1                 # Setup/installation script
├── plang-vscode-extension/   # VS Code extension
│   ├── package.json
│   ├── syntaxes/
│   └── snippets/
├── CONTRIBUTING.md           # Contribution guidelines
├── LICENSE                   # License file
└── README.md                 # This file
```

---

## 🤝 Contributing

Contributions are welcome! Please read our [Contributing Guidelines](CONTRIBUTING.md) before submitting a pull request.

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

---

## 📊 Language Composition

| Language   | Percentage |
|------------|------------|
| C          | 84%        |
| PowerShell | 9.4%       |
| Batchfile  | 4%         |
| Raku       | 2.4%       |
| Other      | 0.2%       |

---

## 🌐 Web Version (WebAssembly)

P_Lang now runs in your browser using WebAssembly! Try it online or deploy your own instance.

### Features

- **Run P_Lang in the browser** - No installation required
- **Fast execution** - Compiled to WebAssembly for near-native performance
- **Full language support** - All P_Lang features available
- **Interactive editor** - Syntax highlighting and keyboard shortcuts
- **Example code** - Load and run sample programs

### Try It Online

Visit the online compiler at: `https://your-deployment.vercel.app` (after deployment)

### Deploy Your Own Instance

#### Prerequisites

- Node.js and npm (for building WASM locally, optional)
- Emscripten SDK (for building WASM, optional - GitHub Actions handles this automatically)
- Vercel account (for deployment)

#### Deployment Steps

1. **Fork this repository** on GitHub

2. **Connect to Vercel:**
   - Go to [Vercel](https://vercel.com)
   - Import your forked repository
   - Configure the project:
     - Framework Preset: Other
     - Root Directory: `./`
     - Output Directory: `docs`
   - Deploy!

3. **Automatic Builds:**
   - The GitHub Actions workflow (`.github/workflows/build-wasm.yml`) automatically builds WebAssembly files on push to `main`
   - WASM files are committed back to the repository
   - Vercel automatically redeploys when new commits are pushed

#### Local Development

1. **Build WebAssembly locally (optional):**
   ```bash
   # Install Emscripten
   git clone https://github.com/emscripten-core/emsdk.git
   cd emsdk
   ./emsdk install latest
   ./emsdk activate latest
   source ./emsdk_env.sh
   
   # Build WASM
   cd /path/to/P_Lang
   npm run build:wasm
   ```

2. **Run local development server:**
   ```bash
   npm install
   npm run dev
   # Open http://localhost:3000 in your browser
   ```

### Files Structure

```
docs/
├── index.html       # Web interface
├── style.css        # Styling
├── app.js           # JavaScript logic with fallback interpreter
├── plang.js         # Generated: Emscripten loader (auto-generated by GitHub Actions)
└── plang.wasm       # Generated: WebAssembly binary (auto-generated by GitHub Actions)

plang_compiler_wasm.c  # WebAssembly-adapted compiler source
package.json           # npm configuration with build scripts
vercel.json            # Vercel deployment configuration
.github/workflows/
└── build-wasm.yml     # GitHub Actions workflow for building WASM
```

### How It Works

1. **Source Code:** `plang_compiler_wasm.c` is a modified version of the compiler:
   - Removed platform-specific dependencies (conio.h)
   - Replaced file I/O with string processing
   - Replaced printf with output buffer system
   - Added Emscripten exports for JavaScript interop
   - Added loop iteration limits to prevent infinite loops

2. **Build Process:** GitHub Actions uses Emscripten to compile C to WebAssembly

3. **Web Interface:** JavaScript loads the WASM module and provides:
   - Code editor with syntax highlighting
   - Execution bridge between JavaScript and WASM
   - Fallback JavaScript interpreter (works without WASM)
   - Keyboard shortcuts (Ctrl+Enter to run)

### Keyboard Shortcuts

- **Ctrl+Enter** - Run code
- **Tab** - Insert 4 spaces (indent)

---

## 📜 License

This project is open source. See the [LICENSE](LICENSE) file for details.

---

## 🙏 Acknowledgments

- Built with ❤️ using C
- Inspired by the need for a simpler, faster programming language

---

<p align="center">
  <b>Happy Coding with PLang! 🎉</b>
</p>
