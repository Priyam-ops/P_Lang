# P_Lang (PLang) 🚀

<p align="center">
  <img src="https://img.shields.io/badge/Written%20in-C-blue?style=for-the-badge&logo=c" alt="Written in C">
  <img src="https://img.shields.io/badge/License-Open%20Source-green?style=for-the-badge" alt="License">
  <img src="https://img.shields.io/badge/Platform-Windows-lightgrey?style=for-the-badge&logo=windows" alt="Platform">
</p>

**PLang** is a modern, beginner-friendly programming language developed in C. It aims to fix the common pain points of C while providing a simpler, more intuitive syntax. PLang is designed to be faster than Python with a more user-friendly syntax than C.

---

## ✨ Features

- **Simple Syntax** - Human-readable keywords like `is` for assignment and `show` for output
- **Fast Execution** - Built on C for high performance
- **Easy to Learn** - Minimal boilerplate, perfect for beginners
- **VS Code Extension** - Syntax highlighting and code snippets available
- **Cross-Platform Scripts** - PowerShell and Batch scripts for Windows

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

### Logical Operators

| Operator | Description    | Example                |
|----------|----------------|------------------------|
| `NOT`    | Logical NOT    | `result is NOT flag`   |
| `AND`    | Logical AND    | `result is x AND y`    |
| `OR`     | Logical OR     | `result is x OR y`     |

**Example:**
```plang
flag1 is yes
flag2 is no
result is flag1 AND flag2
show result

result is flag1 OR flag2
show result

result is NOT flag1
show result
```

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
