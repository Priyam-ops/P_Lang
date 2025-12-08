// Import the WebAssembly module
import init, { fibonacci, greet } from '../pkg/my_wasm_app.js';

async function main() {
    // Initialize the Wasm module
    await init();
    
    // Now you can use Wasm functions
    document.getElementById('calc-btn').addEventListener('click', () => {
        const n = parseInt(document.getElementById('num-input').value);
        const result = fibonacci(n);
        document.getElementById('result').textContent = result;
    });
    
    // Call greet function
    greet('WebAssembly');
}

main();