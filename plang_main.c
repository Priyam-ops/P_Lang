#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("PLang Interpreter v1.0\n");
        printf("Usage: plang <source_file>\n");
        printf("Example: plang myprogram.pl\n");
        return 1;
    }
    
    char *source_file = argv[1];
    
    // Check if file exists
    FILE *test = fopen(source_file, "r");
    if (!test) {
        printf("Error: File '%s' not found!\n", source_file);
        return 1;
    }
    fclose(test);
    
    printf("Running '%s'...\n", source_file);
    
    // Create command to run the actual interpreter with filename as argument
    char command[512];
    snprintf(command, sizeof(command), "plang_compiler.exe \"%s\"", source_file);
    
    // Execute the interpreter
    int result = system(command);
    return result;
}
