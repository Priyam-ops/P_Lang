#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <emscripten.h>

// Output buffer for web
static char output_buffer[50000];
static int output_pos = 0;

// Maximum loop iterations to prevent infinite loops
#define MAX_LOOP_ITERATIONS 100000

// Clear output buffer
EMSCRIPTEN_KEEPALIVE
void clear_output() {
    output_buffer[0] = '\0';
    output_pos = 0;
}

// Get output buffer
EMSCRIPTEN_KEEPALIVE
const char* get_output() {
    return output_buffer;
}

// Append to output buffer (replaces printf)
void web_print(const char* str) {
    int len = strlen(str);
    if (output_pos + len < sizeof(output_buffer) - 1) {
        strcpy(output_buffer + output_pos, str);
        output_pos += len;
    }
}

void web_print_int(int val) {
    char buf[32];
    sprintf(buf, "%d", val);
    web_print(buf);
}

// Data structures
typedef struct Node {
    int data;
    char *text;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct Variable {
    int value;
    int code;
    char symbol[100];
    struct Variable* next;
} Vr;

// Global variables
static Vr *global_variables = NULL;

// Function prototypes
void assignment(int token, char symbol[100], Vr **variables);
void arithmetic(Node** head);
void Bracket_Operator(Node** head);
void Logical_Operators(Node** head);
void Sundowner(Node** head);
Node* Jack(char *line, Vr **variables);
int doc(Node** head);
Node* show(Node* head);

// Assignment function
void assignment(int token, char symbol[100], Vr **variables) {
    Vr *current = *variables;
    while(current != NULL) {
        if(strcmp(current->symbol, symbol) == 0) {
            current->value = token;
            return;
        }
        current = current->next;
    }
    Vr *new = malloc(sizeof(Vr));
    new->value = token;
    strcpy(new->symbol, symbol);
    new->code = (*variables)->value;
    (*variables)->value--;
    new->next = NULL;

    current = *variables;
    if (current == NULL || current->next == NULL) {
        (*variables)->next = new;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new;
    }
}

// Arithmetic operations
void arithmetic(Node** head) {
    Node* current = *head;
    
    // Division
    while (current) {
        if (current->data == -9) {
            int prev = 0, next = 0;
            if (current->prev && current->prev->data > 0) prev = current->prev->data;
            if (current->next && current->next->data > 0) next = current->next->data;
            if (next == 0) {
                web_print("Division by zero error\n");
                current = current->next;
                continue;
            }
            int sum = prev / next;
            Node *new = malloc(sizeof(Node));
            new->text = NULL;
            new->data = sum;
            new->prev = current->prev->prev;
            new->next = current->next->next;
            if (current->prev->prev)
                current->prev->prev->next = new;
            if (current->next->next != NULL)
                current->next->next->prev = new;
        }
        current = current->next;
    }
    
    // Multiplication
    current = *head;
    while (current) {
        if (current->data == -8) {
            int prev = 0, next = 0;
            if (current->prev && current->prev->data > 0) prev = current->prev->data;
            if (current->next && current->next->data > 0) next = current->next->data;
            int sum = prev * next;
            Node *new = malloc(sizeof(Node));
            new->text = NULL;
            new->data = sum;
            new->prev = current->prev->prev;
            new->next = current->next->next;
            if (current->prev->prev)
                current->prev->prev->next = new;
            if (current->next->next != NULL)
                current->next->next->prev = new;
        }
        current = current->next;
    }
    
    // Addition
    current = *head;
    while (current) {
        if (current->data == -6) {
            int prev = 0, next = 0;
            if (current->prev && current->prev->data > 0) prev = current->prev->data;
            if (current->next && current->next->data > 0) next = current->next->data;
            int sum = prev + next;
            Node *new = malloc(sizeof(Node));
            new->text = NULL;
            new->data = sum;
            new->prev = current->prev->prev;
            new->next = current->next->next;
            if (current->prev->prev)
                current->prev->prev->next = new;
            if (current->next->next != NULL)
                current->next->next->prev = new;
        }
        current = current->next;
    }
    
    // Subtraction
    current = *head;
    while (current) {
        if (current->data == -7) {
            int prev = 0, next = 0;
            if (current->prev && current->prev->data > 0) prev = current->prev->data;
            if (current->next && current->next->data > 0) next = current->next->data;
            int sum = prev - next;
            Node *new = malloc(sizeof(Node));
            new->text = NULL;
            new->data = sum;
            new->prev = current->prev->prev;
            new->next = current->next->next;
            if (current->prev->prev)
                current->prev->prev->next = new;
            if (current->next->next != NULL)
                current->next->next->prev = new;
        }
        current = current->next;
    }
}

// Bracket operator
void Bracket_Operator(Node** head) {
    Node *current = *head;
    while (current != NULL) {
        if (current->data == -10) {  // '('
            Node *temp = current->next;
            while (temp != NULL && temp->data != -11) {
                temp = temp->next;
            }
            if (temp == NULL) {
                web_print("Error: Unmatched '(' found.\n");
                return;
            } else {
                Node *pointer = NULL;
                if (temp->next != NULL) {
                    pointer = temp->next;
                    temp->next = NULL;
                }
                arithmetic(&current);
                Node *tail = current;
                while (tail->next != NULL) {
                    tail = tail->next;
                }
                tail->next = pointer;
                current = pointer;
                continue;
            }
        }
        current = current->next;
    }
}

// Logical operators
void Logical_Operators(Node** head) {
    // Process NOT operator first
    Node *current = *head;
    while (current) {
        if (current->data == -31) {  // NOT operator
            if (current->next != NULL) {
                int next_val = 0;
                if (current->next->data == -19) {  // yes
                    next_val = 1;
                } else if (current->next->data == -20) {  // no
                    next_val = 0;
                } else if (current->next->data > 0) {
                    next_val = (current->next->data != 0) ? 1 : 0;
                }
                
                int result = !next_val;
                int result_token = result ? -19 : -20;
                
                Node *new = malloc(sizeof(Node));
                new->text = NULL;
                new->data = result_token;
                new->prev = current->prev;
                new->next = current->next->next;
                
                if (current->prev != NULL)
                    current->prev->next = new;
                if (current->next->next != NULL)
                    current->next->next->prev = new;
            }
        }
        current = current->next;
    }
    
    // Process AND operator
    current = *head;
    while (current) {
        if (current->data == -29) {  // AND operator
            if (current->prev != NULL && current->next != NULL) {
                int prev_val = 0, next_val = 0;
                
                if (current->prev->data == -19) prev_val = 1;
                else if (current->prev->data == -20) prev_val = 0;
                else if (current->prev->data > 0) prev_val = (current->prev->data != 0) ? 1 : 0;
                
                if (current->next->data == -19) next_val = 1;
                else if (current->next->data == -20) next_val = 0;
                else if (current->next->data > 0) next_val = (current->next->data != 0) ? 1 : 0;
                
                int result = prev_val && next_val;
                int result_token = result ? -19 : -20;
                
                Node *new = malloc(sizeof(Node));
                new->text = NULL;
                new->data = result_token;
                new->prev = current->prev->prev;
                new->next = current->next->next;
                
                if (current->prev->prev != NULL)
                    current->prev->prev->next = new;
                if (current->next->next != NULL)
                    current->next->next->prev = new;
            }
        }
        current = current->next;
    }
    
    // Process OR operator
    current = *head;
    while (current) {
        if (current->data == -30) {  // OR operator
            if (current->prev != NULL && current->next != NULL) {
                int prev_val = 0, next_val = 0;
                
                if (current->prev->data == -19) prev_val = 1;
                else if (current->prev->data == -20) prev_val = 0;
                else if (current->prev->data > 0) prev_val = (current->prev->data != 0) ? 1 : 0;
                
                if (current->next->data == -19) next_val = 1;
                else if (current->next->data == -20) next_val = 0;
                else if (current->next->data > 0) next_val = (current->next->data != 0) ? 1 : 0;
                
                int result = prev_val || next_val;
                int result_token = result ? -19 : -20;
                
                Node *new = malloc(sizeof(Node));
                new->text = NULL;
                new->data = result_token;
                new->prev = current->prev->prev;
                new->next = current->next->next;
                
                if (current->prev->prev != NULL)
                    current->prev->prev->next = new;
                if (current->next->next != NULL)
                    current->next->next->prev = new;
            }
        }
        current = current->next;
    }
}

// Comparison operators
void Sundowner(Node** head) {
    Node *current = *head;
    while (current != NULL) {
        if (current->data == -15) {  // =
            if (current->prev != NULL && current->next != NULL) {
                int stuff = (current->prev->data == current->next->data) ? -19 : -20;
                Node *new = malloc(sizeof(Node));
                new->text = NULL;
                new->data = stuff;
                new->prev = current->prev->prev;
                new->next = current->next->next;
                if (current->prev->prev)
                    current->prev->prev->next = new;
                if (current->next->next != NULL)
                    current->next->next->prev = new;
            }
        }
        if (current->data == -16) {  // >
            if (current->prev != NULL && current->next != NULL) {
                int stuff = (current->prev->data > current->next->data) ? -19 : -20;
                Node *new = malloc(sizeof(Node));
                new->text = NULL;
                new->data = stuff;
                new->prev = current->prev->prev;
                new->next = current->next->next;
                if (current->prev->prev)
                    current->prev->prev->next = new;
                if (current->next->next != NULL)
                    current->next->next->prev = new;
            }
        }
        if (current->data == -17) {  // <
            if (current->prev != NULL && current->next != NULL) {
                int stuff = (current->prev->data < current->next->data) ? -19 : -20;
                Node *new = malloc(sizeof(Node));
                new->text = NULL;
                new->data = stuff;
                new->prev = current->prev->prev;
                new->next = current->next->next;
                if (current->prev->prev)
                    current->prev->prev->next = new;
                if (current->next->next != NULL)
                    current->next->next->prev = new;
            }
        }
        if (current->data == -18) {  // !=
            if (current->prev != NULL && current->next != NULL) {
                int stuff = (current->prev->data != current->next->data) ? -19 : -20;
                Node *new = malloc(sizeof(Node));
                new->text = NULL;
                new->data = stuff;
                new->prev = current->prev->prev;
                new->next = current->next->next;
                if (current->prev->prev)
                    current->prev->prev->next = new;
                if (current->next->next != NULL)
                    current->next->next->prev = new;
            }
        }
        if (current->data == -23) {  // >=
            if (current->prev != NULL && current->next != NULL) {
                int stuff = (current->prev->data >= current->next->data) ? -19 : -20;
                Node *new = malloc(sizeof(Node));
                new->text = NULL;
                new->data = stuff;
                new->prev = current->prev->prev;
                new->next = current->next->next;
                if (current->prev->prev)
                    current->prev->prev->next = new;
                if (current->next->next != NULL)
                    current->next->next->prev = new;
            }
        }
        if (current->data == -22) {  // <=
            if (current->prev != NULL && current->next != NULL) {
                int stuff = (current->prev->data <= current->next->data) ? -19 : -20;
                Node *new = malloc(sizeof(Node));
                new->text = NULL;
                new->data = stuff;
                new->prev = current->prev->prev;
                new->next = current->next->next;
                if (current->prev->prev)
                    current->prev->prev->next = new;
                if (current->next->next != NULL)
                    current->next->next->prev = new;
            }
        }
        current = current->next;
    }
}

// Tokenizer
int Sam(char *command, Vr **variables) {
    const char *tokens[] = {
        /*0*/"",/*1*/"show", /*2*/"clear", /*3*/"help", /*4*/"exit",
        /*5*/"is",/*6*/"+", /*7*/"-", /*8*/"*", /*9*/"/", 
        /*10*/"(",/*11*/")",/*12*/"take",/*13*/"if",/*14*/"else",
        /*15*/"=",/*16*/">",/*17*/"<",/*18*/"!", /*19*/"yes", 
        /*20*/"no",/*21*/"while",/*22*/"<=",/*23*/">=",/*24*/"++",
        /*25*/"--",/*26*/"until",/*27*/"endwhile",/*28*/"enduntil",
        /*29*/"&",/*30*/"|",/*31*/"not"
    };
    int num_tokens = 32;
    
    char number[] = "0123456789";
    
    // Handle increment
    if (command[strlen(command)-1] == '+' && strlen(command) > 1 && command[strlen(command)-2] == '+') {
        command[strlen(command)-2] = '\0';
        Vr *current = *variables;
        while (current != NULL && strcmp(command, current->symbol) != 0) {
            current = current->next;
        }
        if (current != NULL) {
            current->value += 1;
        }
    }
    
    // Handle decrement
    if (command[strlen(command)-1] == '-' && strlen(command) > 1 && command[strlen(command)-2] == '-') {
        command[strlen(command)-2] = '\0';
        Vr *current = *variables;
        while (current != NULL && strcmp(command, current->symbol) != 0) {
            current = current->next;
        }
        if (current != NULL) {
            current->value -= 1;
        }
    }
    
    // Check if it's a variable
    Vr *current = *variables;
    while (current != NULL) {
        if (strcmp(command, current->symbol) == 0) {
            return current->value;
        }
        current = current->next;
    }
    
    // Check if it's a keyword
    for (int i = 0; i < num_tokens; i++) {
        if (strcmp(command, tokens[i]) == 0)
            return i * (-1);
    }
    
    // Check if it's a number
    int is_num = 1;
    for (int i = 0; i < strlen(command); i++) {
        int found = 0;
        for (int j = 0; j < strlen(number); j++) {
            if (command[i] == number[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            is_num = 0;
            break;
        }
    }
    
    if (is_num && strlen(command) > 0) {
        return atoi(command);
    }
    
    // String literal
    return -666;
}

// Lexer
Node* Jack(char *line, Vr **variables) {
    Node *head = NULL, *tail = NULL;
    char token[100];
    int i = 0, j = 0;
    int assign = 0;
    char imp_token[100];
    char last_symbol[100];
    int looking_for_operator = 0;
    int looking_for_operand = 0;
    int operator = 0;
    char *text = NULL;

    while (1) {
        char c = line[i];
        
        if (c == ' ' || c == '\0' || c == '\n') {
            if (j > 0) {
                token[j] = '\0';
                int val = Sam(token, variables);
                
                if (looking_for_operand) {
                    looking_for_operand = 0;
                    looking_for_operator = 0;
                    if (val > 0) {
                        if (operator == -6) {
                            Vr *current = *variables;
                            while (current->next != NULL) current = current->next;
                            current->value += val;
                        }
                        if (operator == -7) {
                            Vr *current = *variables;
                            while (current->next != NULL) current = current->next;
                            current->value -= val;
                        }
                        if (operator == -8) {
                            Vr *current = *variables;
                            while (current->next != NULL) current = current->next;
                            current->value *= val;
                        }
                        if (operator == -9 && val != 0) {
                            Vr *current = *variables;
                            while (current->next != NULL) current = current->next;
                            current->value /= val;
                        }
                    }
                }
                if (looking_for_operator) {
                    looking_for_operator = 0;
                    if (val == -6 || val == -7 || val == -8 || val == -9) {
                        looking_for_operand = 1;
                        operator = val;
                    }
                }
                
                if (val == -5) {
                    for (int k = 0; k < j; k++) {
                        imp_token[k] = last_symbol[k];
                    }
                    imp_token[j] = '\0';
                    assign = 1;
                }
                
                if ((assign && val > 0) || (assign && val == -666)) {
                    assign = 0;
                    looking_for_operator = 1;
                    if (val == -666) {
                        char new_string[100];
                        strcpy(new_string, imp_token);
                        strcat(new_string, " ");
                        strcat(new_string, token);
                        assignment(val, new_string, variables);
                    }
                    assignment(val, imp_token, variables);
                }
                
                if (val == -666) {
                    text = strdup(token);
                    Vr *current = *variables;
                    while (current != NULL) {
                        int match = 1;
                        int m_ind = 0;
                        for (int k = 0; token[k] != '\0'; k++) {
                            if(current->symbol[k] != token[k]){
                                match = 0;
                                m_ind = k+1;
                            }
                        }
                        m_ind += 2;
                        if (match) {
                            for (int k = m_ind; k < strlen(current->symbol); k++) {
                                text[k-m_ind] = current->symbol[k];
                            }
                            text[strlen(current->symbol)-m_ind] = '\0';
                        }
                        current = current->next;
                    }
                }
                
                Node *node = malloc(sizeof(Node));
                node->text = text;
                node->data = val;
                node->next = NULL;
                node->prev = tail;

                if (!head)
                    head = node;
                else
                    tail->next = node;
                tail = node;
                
                for (int k = 0; k < j; k++) {
                    last_symbol[k] = token[k];
                }
                last_symbol[j] = '\0';
                j = 0;
                text = NULL;
            }
            if (c == '\0') break;
        } else {
            token[j++] = c;
        }
        i++;
    }
    if (tail) tail->next = NULL;
    return head;
}

// Check condition result
int doc(Node** head) {
    if ((*head)->next) {
        if ((*head)->next->data == -19) {
            return 1;
        }
    }
    return 0;
}

// Show/print function
Node* show(Node* head) {
    head = head->next;
    if (head->data == -666) {
        for (int i = 0; head->text[i] != '\0'; i++) {
            if (head->text[i] == '_') {
                head->text[i] = ' ';
            }
        }
        web_print(head->text);
        web_print("\n");
    }
    else if (head->data == -19) {
        web_print("yes\n");
    }
    else if (head->data == -20) {
        web_print("no\n");
    }
    else {
        web_print_int(head->data);
        web_print("\n");
    }
    return head;
}

// Initialize compiler
EMSCRIPTEN_KEEPALIVE
void init_compiler() {
    clear_output();
    if (global_variables) {
        // Free previous variables
        Vr *current = global_variables;
        while (current) {
            Vr *next = current->next;
            free(current);
            current = next;
        }
    }
    global_variables = malloc(sizeof(Vr));
    global_variables->value = -50;
    global_variables->next = NULL;
}

// Run P_Lang code
EMSCRIPTEN_KEEPALIVE
const char* run_plang(const char* code) {
    clear_output();
    
    if (!global_variables) {
        init_compiler();
    }
    
    // Parse code line by line
    char *code_copy = strdup(code);
    char *line = strtok(code_copy, "\n");
    
    int in_loop = 0;
    char loop_line[300];
    int loop_type = 0;
    int skip_execution = 0;
    int if_true = 1;
    int loop_iterations = 0;
    
    // Store all lines for loop processing
    char lines[1000][300];
    int line_count = 0;
    char *temp_code = strdup(code);
    char *temp_line = strtok(temp_code, "\n");
    while (temp_line && line_count < 1000) {
        strcpy(lines[line_count], temp_line);
        line_count++;
        temp_line = strtok(NULL, "\n");
    }
    free(temp_code);
    
    int current_line = 0;
    int loop_start_line = 0;
    
    while (current_line < line_count) {
        if (loop_iterations++ > MAX_LOOP_ITERATIONS) {
            web_print("[Error: Maximum loop iterations exceeded - possible infinite loop]\n");
            break;
        }
        
        char buffer[300];
        strcpy(buffer, lines[current_line]);
        
        // Remove newline
        buffer[strcspn(buffer, "\n")] = 0;
        
        if (strlen(buffer) == 0) {
            current_line++;
            continue;
        }
        
        Node *tokens = Jack(buffer, &global_variables);
        if (!tokens) {
            current_line++;
            continue;
        }
        
        Bracket_Operator(&tokens);
        arithmetic(&tokens);
        Sundowner(&tokens);
        Logical_Operators(&tokens);
        
        Node *cur = tokens;
        
        while (cur) {
            if (cur->data <= -1) {
                switch (cur->data) {
                    case -1:  // show
                        if (!skip_execution)
                            cur = show(cur);
                        break;
                        
                    case -13:  // if
                        if (!skip_execution) {
                            if (doc(&cur)) {
                                if_true = 1;
                            } else {
                                if_true = 0;
                                skip_execution = 1;
                            }
                        }
                        break;
                        
                    case -14:  // else
                        if (if_true) {
                            skip_execution = 1;
                        } else {
                            skip_execution = 0;
                        }
                        break;
                        
                    case -21:  // while
                        if (!skip_execution) {
                            if (doc(&cur)) {
                                in_loop = 1;
                                loop_type = -21;
                                loop_start_line = current_line;
                                strcpy(loop_line, buffer);
                            } else {
                                skip_execution = 1;
                            }
                        }
                        break;
                        
                    case -27:  // endwhile
                        if (in_loop && loop_type == -21) {
                            Node *cond = Jack(loop_line, &global_variables);
                            Bracket_Operator(&cond);
                            arithmetic(&cond);
                            Sundowner(&cond);
                            Logical_Operators(&cond);
                            
                            int truth = doc(&cond);
                            
                            while (cond) {
                                Node *n = cond->next;
                                free(cond);
                                cond = n;
                            }
                            
                            if (truth == 1) {
                                current_line = loop_start_line;
                                while (tokens) {
                                    Node *n = tokens->next;
                                    free(tokens);
                                    tokens = n;
                                }
                                skip_execution = 0;
                                continue;
                            } else {
                                in_loop = 0;
                                skip_execution = 0;
                            }
                        } else if (skip_execution) {
                            skip_execution = 0;
                        }
                        break;
                        
                    case -26:  // until
                        if (!skip_execution) {
                            if (!doc(&cur)) {
                                in_loop = 1;
                                loop_type = -26;
                                loop_start_line = current_line;
                                strcpy(loop_line, buffer);
                            } else {
                                skip_execution = 1;
                            }
                        }
                        break;
                        
                    case -28:  // enduntil
                        if (in_loop && loop_type == -26) {
                            Node *cond = Jack(loop_line, &global_variables);
                            Bracket_Operator(&cond);
                            arithmetic(&cond);
                            Sundowner(&cond);
                            
                            int truth = doc(&cond);
                            
                            while (cond) {
                                Node *n = cond->next;
                                free(cond);
                                cond = n;
                            }
                            
                            if (truth == 0) {
                                current_line = loop_start_line;
                                while (tokens) {
                                    Node *n = tokens->next;
                                    free(tokens);
                                    tokens = n;
                                }
                                skip_execution = 0;
                                continue;
                            } else {
                                in_loop = 0;
                                skip_execution = 0;
                            }
                        } else if (skip_execution) {
                            skip_execution = 0;
                        }
                        break;
                }
            }
            cur = cur->next;
        }
        
        // Free tokens
        while (tokens) {
            Node *n = tokens->next;
            free(tokens);
            tokens = n;
        }
        
        skip_execution = 0;
        current_line++;
    }
    
    free(code_copy);
    return output_buffer;
}
