// Wait for Emscripten module to load
let Module = {
    onRuntimeInitialized: function() {
        document.getElementById('status').textContent = 'Ready';
        document.getElementById('status').className = 'status ready';
        console.log('P_Lang WebAssembly module loaded! ');
    }
};

// Initialize when DOM is ready
document.addEventListener('DOMContentLoaded', function() {
    const codeEditor = document.getElementById('code-editor');
    const output = document.getElementById('output');
    const runBtn = document.getElementById('run-btn');
    const clearBtn = document.getElementById('clear-btn');
    const exampleBtn = document.getElementById('example-btn');
    const status = document.getElementById('status');

    // Run button handler
    runBtn.addEventListener('click', function() {
        runCode();
    });

    // Clear button handler
    clearBtn.addEventListener('click', function() {
        codeEditor.value = '';
        output.textContent = '';
    });

    // Example code button
    exampleBtn.addEventListener('click', function() {
        codeEditor.value = `x is 5
y is 10
show Calculating... 

sum is x + y
show Sum:
show sum

diff is y - x
show Difference:
show diff

product is x * y
show Product:
show product

show ---_Loop_Demo_---
i is 1
while i <= 5 = yes
    show i
    i ++
endwhile

show ---_Conditionals_---
a is 15
if a > 10 = yes
    show a_is_greater_than_10
else
    show a_is_not_greater

show Done!`;
    });

    // Keyboard shortcut (Ctrl+Enter to run)
    codeEditor.addEventListener('keydown', function(e) {
        if (e.ctrlKey && e.key === 'Enter') {
            e.preventDefault();
            runCode();
        }
        
        // Tab support
        if (e.key === 'Tab') {
            e.preventDefault();
            const start = this.selectionStart;
            const end = this.selectionEnd;
            this.value = this. value.substring(0, start) + '    ' + this.value.substring(end);
            this.selectionStart = this.selectionEnd = start + 4;
        }
    });

    function runCode() {
        const code = codeEditor.value;
        
        if (! code.trim()) {
            output.textContent = 'Please enter some P_Lang code to run.';
            return;
        }

        status.textContent = 'Running... ';
        status.className = 'status running';
        output.textContent = '';

        try {
            // Check if WebAssembly module is loaded
            if (typeof Module._init_compiler === 'function') {
                // Initialize the compiler
                Module._init_compiler();
                
                // Allocate memory for the code string
                const codePtr = Module. allocateUTF8(code);
                
                // Run the code
                const resultPtr = Module._run_plang(codePtr);
                
                // Get the result
                const result = Module. UTF8ToString(resultPtr);
                
                // Free the allocated memory
                Module._free(codePtr);
                
                output.textContent = result || '(No output)';
                status. textContent = 'Completed';
                status.className = 'status ready';
            } else {
                // Fallback: Simple interpreter in JavaScript (for testing without WASM)
                output.textContent = runPLangJS(code);
                status.textContent = 'Completed (JS Mode)';
                status.className = 'status ready';
            }
        } catch (error) {
            output.textContent = 'Error: ' + error.message;
            status.textContent = 'Error';
            status. className = 'status error';
            console.error(error);
        }
    }

    // Fallback JavaScript interpreter (basic implementation)
    function runPLangJS(code) {
        let output = [];
        let variables = {};
        const lines = code.split('\n');
        
        let i = 0;
        let loopStack = [];
        let maxIterations = 10000;
        let iterations = 0;
        
        while (i < lines.length && iterations++ < maxIterations) {
            let line = lines[i]. trim();
            if (! line) { i++; continue; }
            
            const tokens = line.split(/\s+/);
            
            // Variable assignment: x is 10
            if (tokens. length >= 3 && tokens[1] === 'is') {
                const varName = tokens[0];
                const expr = tokens. slice(2).join(' ');
                variables[varName] = evaluateExpr(expr, variables);
                i++;
                continue;
            }
            
            // Show command
            if (tokens[0] === 'show') {
                const expr = tokens. slice(1).join(' ');
                let value = evaluateExpr(expr, variables);
                if (typeof value === 'string') {
                    value = value.replace(/_/g, ' ');
                }
                output.push(value);
                i++;
                continue;
            }
            
            // While loop
            if (tokens[0] === 'while') {
                const condition = tokens.slice(1, -2).join(' '); // Remove "= yes"
                if (evaluateCondition(condition, variables)) {
                    loopStack.push({ type: 'while', start: i, condition: condition });
                    i++;
                } else {
                    // Skip to endwhile
                    let depth = 1;
                    i++;
                    while (i < lines.length && depth > 0) {
                        if (lines[i].trim(). startsWith('while')) depth++;
                        if (lines[i].trim() === 'endwhile') depth--;
                        i++;
                    }
                }
                continue;
            }
            
            // Endwhile
            if (tokens[0] === 'endwhile') {
                if (loopStack.length > 0) {
                    const loop = loopStack[loopStack.length - 1];
                    if (evaluateCondition(loop.condition, variables)) {
                        i = loop.start + 1;
                    } else {
                        loopStack.pop();
                        i++;
                    }
                } else {
                    i++;
                }
                continue;
            }
            
            // Increment: x ++
            if (tokens. length >= 2 && tokens[1] === '++') {
                const varName = tokens[0];
                if (variables. hasOwnProperty(varName)) {
                    variables[varName]++;
                }
                i++;
                continue;
            }
            
            i++;
        }
        
        if (iterations >= maxIterations) {
            output.push('[Warning: Execution stopped - possible infinite loop]');
        }
        
        return output.join('\n');
    }
    
    function evaluateExpr(expr, variables) {
        const tokens = expr.split(/\s+/);
        
        // Single value
        if (tokens.length === 1) {
            const token = tokens[0];
            if (variables.hasOwnProperty(token)) {
                return variables[token];
            }
            const num = parseInt(token);
            if (! isNaN(num)) return num;
            return token; // String
        }
        
        // Simple binary expression: a + b
        if (tokens. length === 3) {
            let left = variables[tokens[0]] ??  parseInt(tokens[0]) ??  0;
            let right = variables[tokens[2]] ?? parseInt(tokens[2]) ?? 0;
            switch (tokens[1]) {
                case '+': return left + right;
                case '-': return left - right;
                case '*': return left * right;
                case '/': return right !== 0 ? Math.floor(left / right) : 0;
            }
        }
        
        return expr;
    }
    
    function evaluateCondition(condition, variables) {
        const tokens = condition.split(/\s+/);
        if (tokens.length >= 3) {
            let left = variables[tokens[0]] ?? parseInt(tokens[0]) ?? 0;
            let right = variables[tokens[2]] ?? parseInt(tokens[2]) ?? 0;
            switch (tokens[1]) {
                case '<': return left < right;
                case '>': return left > right;
                case '=': return left === right;
                case '<=': return left <= right;
                case '>=': return left >= right;
                case '! ': return left !== right;
            }
        }
        return false;
    }
});