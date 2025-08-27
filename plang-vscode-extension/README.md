# PLang Language Support for VS Code

This extension provides syntax highlighting and language support for the PLang programming language.

## Features

- **Syntax Highlighting**: Full syntax highlighting for PLang keywords, operators, strings, numbers, and variables
- **Code Snippets**: Predefined snippets for common PLang patterns
- **Auto-completion**: Intelligent suggestions for PLang keywords and constructs
- **Bracket Matching**: Automatic bracket, parentheses, and quote pairing
- **Comment Support**: Line comment support with `//`

## Supported File Extensions

- `.pl` - PLang source files
- `.plang` - PLang source files

## Syntax Highlighting

The extension highlights the following PLang elements:

### Keywords (Blue)
- Control flow: `if`, `else`, `while`
- Commands: `show`, `clear`, `help`, `exit`, `take`
- Assignment: `is`

### Operators (Red/Orange)
- Arithmetic: `+`, `-`, `*`, `/`
- Comparison: `=`, `>`, `<`, `>=`, `<=`, `!=`
- Increment/Decrement: `++`, `--`

### Literals
- **Numbers** (Green): `123`, `456`
- **Strings** (Orange): `"Hello"`, `'World'`
- **Booleans** (Purple): `yes`, `no`, `true`, `false`

### Variables (White/Default)
- Variable names: `x`, `myVar`, `result`

## Code Snippets

Type these prefixes and press Tab to expand:

- `var` → Variable assignment
- `show` → Show statement
- `if` → If-else statement
- `while` → While loop
- `take` → Take input
- `program` → Basic program template
- `calc` → Arithmetic calculation
- `compare` → Comparison statement

## Example PLang Code

```plang
// Variables
x is 10
y is 20

// Calculation
result is x + y

// Output
show result
show "The sum is:"
show result

// Conditional
if result > 25
    show "Result is greater than 25"
else
    show "Result is 25 or less"

// Loop
counter is 0
while counter < 5
    show counter
    counter++
```

## Installation

1. Copy the extension folder to your VS Code extensions directory
2. Restart VS Code
3. Open any `.pl` or `.plang` file to see syntax highlighting

## Requirements

- VS Code 1.74.0 or higher

## Release Notes

### 1.0.0

- Initial release
- Basic syntax highlighting
- Code snippets
- Language configuration

## Contributing

Feel free to contribute to this extension by submitting issues or pull requests.

## License

MIT License
