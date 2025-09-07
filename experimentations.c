#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct Node {
    int data;                  // Encoded token or number
    char *text;             // Optional text for string tokens
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct Variable{
    int value;
    int code;
    char symbol[100];
    struct Variable* next;
} Vr;

void assignment(int token, char symbol[100], Vr **variables) {
    Vr *current = *variables;
    while(current)
    {   
        if(strcmp(current->symbol, symbol) == 0)
        {
            current->value = token;
            return;
        }
        current = current->next;
    }
    Vr *new = malloc(sizeof(Vr));
    new->value = token;

    strcpy(new->symbol, symbol);
    new->code = (*variables)->value;  // Check: is this needed?
    (*variables)->value--;

    new->next = NULL;

    current = *variables;
    if (current == NULL || current->next == NULL) {
        // First real variable
        (*variables)->next = new;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new;
    }
}

void arithmetic(Node** head) {
    Node* current = *head;
    while (current) {
        if (current->data == -9) {  // Division operator
            int prev , next;
            prev = next = 0;
            if (current->prev && current->prev->data > 0) {
                prev = current->prev->data;
            }
            if (current->next && current->next->data > 0) {
                next = current->next->data;
            }
            
            if (next == 0) {
                printf("Division by zero error\n");
                // Replace with error value (0) instead of leaving broken nodes
                Node *new = malloc(sizeof(Node));
                new->text = NULL;
                new->data = 0;  // Set result to 0 for division by zero
                new->prev = current->prev ? current->prev->prev : NULL;
                new->next = current->next ? current->next->next : NULL;
                
                if (new->prev) {
                    new->prev->next = new;
                }
                if (new->next) {
                    new->next->prev = new;
                }
                
                // Update head if necessary
                if (current->prev && current->prev->prev == NULL) {
                    *head = new;
                }
                
                current = new->next;
                continue;
            }
            
            int sum = prev / next;
            Node *new = malloc(sizeof(Node));
            new->text = NULL;
            new->data = sum;
            new->prev = current->prev ? current->prev->prev : NULL;
            new->next = current->next ? current->next->next : NULL;
            
            if (new->prev) {
                new->prev->next = new;
            }
            if (new->next) {
                new->next->prev = new;
            }
            
            // Update head if necessary
            if (current->prev && current->prev->prev == NULL) {
                *head = new;
            }
        }
        current = current->next;
    }
    
    current = *head;
    while (current) {
        if (current->data == -8) {  // Multiplication
            int prev , next;
            prev = next = 0;
            if (current->prev && current->prev->data > 0) {
                prev = current->prev->data;
            }
            if (current->next && current->next->data > 0) {
                next = current->next->data;
            }
            int sum = prev *  next;
            Node *new = malloc(sizeof(Node));
            new->text = NULL;
            new->data = sum;
            new->prev = current->prev ? current->prev->prev : NULL;
            new->next = current->next ? current->next->next : NULL;
            
            if (new->prev) {
                new->prev->next = new;
            }
            if (new->next) {
                new->next->prev = new;
            }
            
            // Update head if necessary
            if (current->prev && current->prev->prev == NULL) {
                *head = new;
            }
        }
        current = current->next;
    }
    current = *head;
    while (current) {
        if (current->data == -6) {  // Addition
            int prev , next;
            prev = next = 0;
            if (current->prev && current->prev->data > 0) {
                prev = current->prev->data;
            }
            if (current->next && current->next->data > 0) {
                next = current->next->data;
            }
            int sum = prev +  next;
            Node *new = malloc(sizeof(Node));
            new->text = NULL;
            new->data = sum;
            new->prev = current->prev ? current->prev->prev : NULL;
            new->next = current->next ? current->next->next : NULL;
            
            if (new->prev) {
                new->prev->next = new;
            }
            if (new->next) {
                new->next->prev = new;
            }
            
            // Update head if necessary
            if (current->prev && current->prev->prev == NULL) {
                *head = new;
            }
        }
        current = current->next;
    }
    current = *head;
    while (current) {
        if (current->data == -7) {  // Subtraction
            int prev , next;
            prev = next = 0;
            if (current->prev && current->prev->data > 0) {
                prev = current->prev->data;
            }
            if (current->next && current->next->data > 0) {
                next = current->next->data;
            }
            int sum = prev -  next;
            Node *new = malloc(sizeof(Node));
            new->text = NULL;
            new->data = sum;
            new->prev = current->prev ? current->prev->prev : NULL;
            new->next = current->next ? current->next->next : NULL;
            
            if (new->prev) {
                new->prev->next = new;
            }
            if (new->next) {
                new->next->prev = new;
            }
            
            // Update head if necessary
            if (current->prev && current->prev->prev == NULL) {
                *head = new;
            }
        }
        current = current->next;
    }
}


void Bracket_Operator(Node** head)
{
    Node *current = *head;
    while (current)
    {
        if (current->data == -10) {  // '('
            Node *temp = current->next;
            while (temp && temp->data != -11) { 
                temp = temp->next;
            }
            if (temp == NULL) {
                printf("Error: Unmatched '(' found.\n");
                return;
            }
            else{
                Node *pointer = NULL;
                if (temp->next!=NULL)
                {
                    pointer = temp->next;
                    temp->next = NULL;
                }
                arithmetic(&current);
                while (current->next != NULL) {
                    current = current->next;
                }
                current->next = pointer; // Link the rest of the list
            }
        }
            
        current = current->next;
    }
}

void Sundowner(Node** head) 
{
    Node *current = *head;
    while(current){
        if (current->data == -15) { 
            if (current->prev != NULL && current->next != NULL) {
               int stuff = -19;
               if (current->prev->data == current->next->data){
                    Node *new = malloc(sizeof(Node));
                    new->text = NULL;
                    new->data = stuff;
                    new->prev = current->prev->prev;
                    new->next = current->next->next;
                    current->prev->prev->next = new;
                    if (current->next->next != NULL){
                        current->next->next->prev = new;
                    }
               }
                else {
                    stuff = -20;
                    Node *new = malloc(sizeof(Node));
                    new->text = NULL;
                    new->data = stuff;
                    new->prev = current->prev->prev;
                    new->next = current->next->next;
                    current->prev->prev->next = new;
                    if (current->next->next != NULL){
                        current->next->next->prev = new;
                    }
                }
                
            }

        }
        if (current->data == -16) { 
            if (current->prev != NULL && current->next != NULL) {
               int stuff = -19;
               if (current->prev->data > current->next->data){
                    Node *new = malloc(sizeof(Node));
                    new->text = NULL;
                    new->data = stuff;
                    new->prev = current->prev->prev;
                    new->next = current->next->next;
                    current->prev->prev->next = new;
                    if (current->next->next != NULL){
                        current->next->next->prev = new;
                    }
               }
                else {
                    stuff = -20;
                    Node *new = malloc(sizeof(Node));
                    new->text = NULL;
                    new->data = stuff;
                    new->prev = current->prev->prev;
                    new->next = current->next->next;
                    current->prev->prev->next = new;
                    if (current->next->next != NULL){
                        current->next->next->prev = new;
                    }
                }
                
            }

        }
        if (current->data == -17) { 
            if (current->prev != NULL && current->next != NULL) {
               int stuff = -19;
               if (current->prev->data < current->next->data){
                    Node *new = malloc(sizeof(Node));
                    new->text = NULL;
                    new->data = stuff;
                    new->prev = current->prev->prev;
                    new->next = current->next->next;
                    current->prev->prev->next = new;
                    if (current->next->next != NULL){
                        current->next->next->prev = new;
                    }
               }
                else {
                    stuff = -20;
                    Node *new = malloc(sizeof(Node));
                    new->text = NULL;
                    new->data = stuff;
                    new->prev = current->prev->prev;
                    new->next = current->next->next;
                    current->prev->prev->next = new;
                    if (current->next->next != NULL){
                        current->next->next->prev = new;
                    }
                }
                
            }

        }
        if (current->data == -18) { 
            if (current->prev != NULL && current->next != NULL) {
               int stuff = -19;
               if (current->prev->data != current->next->data){
                    Node *new = malloc(sizeof(Node));
                    new->text = NULL;
                    new->data = stuff;
                    new->prev = current->prev->prev;
                    new->next = current->next->next;
                    current->prev->prev->next = new;
                    if (current->next->next != NULL){
                        current->next->next->prev = new;
                    }
               }
                else {
                    stuff = -20;
                    Node *new = malloc(sizeof(Node));
                    new->text = NULL;
                    new->data = stuff;
                    new->prev = current->prev->prev;
                    new->next = current->next->next;
                    current->prev->prev->next = new;
                    if (current->next->next != NULL){
                        current->next->next->prev = new;
                    }
                }
                
            }

        }
        if (current->data == -23) { 
            if (current->prev != NULL && current->next != NULL) {
               int stuff = -19;
               if (current->prev->data >= current->next->data){
                    Node *new = malloc(sizeof(Node));
                    new->text = NULL;
                    new->data = stuff;
                    new->prev = current->prev->prev;
                    new->next = current->next->next;
                    current->prev->prev->next = new;
                    if (current->next->next != NULL){
                        current->next->next->prev = new;
                    }
               }
                else {
                    stuff = -20;
                    Node *new = malloc(sizeof(Node));
                    new->text = NULL;
                    new->data = stuff;
                    new->prev = current->prev->prev;
                    new->next = current->next->next;
                    current->prev->prev->next = new;
                    if (current->next->next != NULL){
                        current->next->next->prev = new;
                    }
                }
                
            }

        }
        if (current->data == -22) { 
            if (current->prev != NULL && current->next != NULL) {
               int stuff = -19;
               if (current->prev->data <= current->next->data){
                    Node *new = malloc(sizeof(Node));
                    new->text = NULL;
                    new->data = stuff;
                    new->prev = current->prev->prev;
                    new->next = current->next->next;
                    current->prev->prev->next = new;
                    if (current->next->next != NULL){
                        current->next->next->prev = new;
                    }
               }
                else {
                    stuff = -20;
                    Node *new = malloc(sizeof(Node));
                    new->text = NULL;
                    new->data = stuff;
                    new->prev = current->prev->prev;
                    new->next = current->next->next;
                    current->prev->prev->next = new;
                    if (current->next->next != NULL){
                        current->next->next->prev = new;
                    }
                }
                
            }

        }
        current = current->next;
    }
}

int Sam(char *command, Vr **variables) {
    const char *tokens[] = {/*0*/"",/*1*/"show", /*2*/"clear", /*3*/"help", /*4*/"exit",/*5*/"is",/*6*/"+", /*7*/"-", /*8*/"*", /*9*/"/", /*10*/"(",/*11*/")",/*12*/"take",/*13*/"if",/*14*/"else",/*15*/"=",/*16*/">",/*17*/"<",/*18*/"!", /*19*/"yes", /*20*/"no",/*21*/"while",/*22*/"<=",/*23*/">=",/*24*/"++",/*25*/"--",/*26*/"until"};
    int num_tokens = 27;
    char number[] = "0123456789";
    if (command[strlen(command)-1] == '+' && command[strlen(command)-2] == '+') {
        command[strlen(command)-2] = '\0';
        Vr *current = *variables;
        while (current != NULL && strcmp(command, current->symbol) != 0) {
            current = current->next;
        }
        if (current != NULL) {
            current->value+=1;
        }
    }

    if (command[strlen(command)-1] == '-' && command[strlen(command)-2] == '-') {
        command[strlen(command)-2] = '\0';
        Vr *current = *variables;
        while (current != NULL && strcmp(command, current->symbol) != 0) {
            current = current->next;
        }
        if (current != NULL) {
            current->value-=1;
        }
    }

    // Check for variable assignment



    Vr *current = *variables;
    while (current != NULL) {
        if (strcmp(command, current->symbol) == 0) {
            return current->value; // Return the value of the variable
        }
        current = current->next;
    }
    // Match known tokens
    for (int i = 0; i < num_tokens; i++) {
        if (strcmp(command, tokens[i]) == 0)
            return i*(-1);  // return token code [0..8]
    }
    int is_num;
    int c = 0; 
    for (int i = 0; i < strlen(command); i++) {
        is_num = 0;
        for (int j = 0; j < strlen(number); j++) {
            if (command[i] == number[j]) {
                is_num = 1;
                c = c*10 + (command[i] - '0');
                continue;
            }
            if (command[i] == '+') {
                is_num = 1;
            }
        }
        if (!is_num) {
            return -666;
        }
    }
    if (c != 666)
        return c; // negative for our encoding
    return 666; // Unknown command
}

Node* Jack(const char *command, Vr **variables) {
    Node *head = NULL, *tail = NULL;
    char token[100],new_string[100];
    char *text;
    char imp_token[100];
    int looking_for_operator = 0;
    int operator = 0;
    int looking_for_operand = 0;
    int input = 0;
    int assign = 0;
    int is_str = 0;
    char last_symbol[100];
    int i = 0, j = 0;
    while (1) {
        char c = command[i];
        if (c == ' ' ||  c == '\0') {
            if (j > 0) {
                text = NULL;
                token[j] = '\0';
                int val = Sam(token, variables);
                if (val == -24) {
                    
                    Vr *current = *variables;
                    while (current != NULL && strcmp(current->symbol, last_symbol) != 0) {
                        current = current->next;
                    }
                    if (current != NULL) {
                        current->value+=1;
                    }
                }
                if (val == -25) { 
                    Vr *current = *variables;
                    while (current != NULL && strcmp(current->symbol, last_symbol) != 0) {
                        current = current->next;
                    }
                    if (current != NULL) {
                        current->value-=1;
                    }
                }
                if (looking_for_operand) {
                    looking_for_operand = 0;
                    looking_for_operator = 0;
                    if (val > 0) {
                        if (operator == -6) {
                            Vr *current = *variables;
                            while (current->next != NULL) {
                                current = current->next;
                            }
                            current->value+=val;
                        }
                        if (operator == -7) {
                            Vr *current = *variables;
                            while (current->next != NULL) {
                                current = current->next;
                            }
                            current->value-=val;
                        }
                        if (operator == -8) {
                            Vr *current = *variables;
                            while (current->next != NULL) {
                                current = current->next;
                            }
                            current->value*=val;
                        }
                        if (operator == -9&& val!=0) {
                            Vr *current = *variables;
                            while (current->next != NULL) {
                                current = current->next;
                            }
                            current->value/=val;
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
                if (input) 
                {
                    input = 0;
                    Vr *new = malloc(sizeof(Vr));
                    strcpy(new->symbol, token);
                    
                    // Flush output and get user input properly
                    printf("Enter value for %s: ", token);
                    fflush(stdout);
                    
                    // Use direct console input to avoid redirection issues
                    char input_buffer[100];
                    if (fgets(input_buffer, sizeof(input_buffer), stdin)) {
                        new->value = atoi(input_buffer);
                    } else {
                        new->value = 0;
                    }
                    
                    new->code = (*variables)->value;
                    (*variables)->value--;

                    new->next = NULL;

                    Vr *current = *variables;
                    if (current == NULL) {
                        (*variables)->next = new;
                    } else {
                        while (current->next != NULL) {
                            current = current->next;
                        }
                        current->next = new;
                    }
                }
                if (val==-12){
                    input = 1;
                }
                if (val == -5)
                {
                    for (int k = 0; k < j; k++) {
                        imp_token[k] = last_symbol[k];
                    }
                    imp_token[j] = '\0';
                    assign = 1;
                }
                
                if ((assign && val > 0) || (assign && val == -666))  // If it's an assignment
                {
                    assign = 0;
                    looking_for_operator = 1;
                    if (val == -666) {
                        char new_string[100];
                        char *l = new_string;
                        char *n = imp_token;
                        while (*n!= '\0')
                        {
                            *l = *n;
                            l++;
                            n++;
                        }
                        *l = ' ';
                        l++;
                        n = token;
                        while (*n!= '\0')
                        {
                            *l = *n;
                            l++;
                            n++;
                        }
                        *l = '\0';
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
                        m_ind+=2;
                        if (match) {
                            for (int k=m_ind; k<strlen(current->symbol); k++) {
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
                last_symbol[j] = '\0';  // Store the last symbol for assignment
                j = 0;
            }
            if (c == '\0') break;
        } else {
            token[j++] = c;
        }
        i++;
    }
    tail->next = NULL; 
    return head;
}

int doc(Node** head)
{
    if ((*head)->next )
    {   
        if ((*head)->next->data == -19)
        {
            return 1;
        }
    }
    return 0;
}

Node* show(Node* head)
{
    head = head->next;
    if (head->data == -666)
    {
        printf("%s\n", head->text);
    }
    else if (head->data == -19){
        printf("yes\n");
    }
    else if (head->data == -20){
        printf("no\n");
    }
    else {
        printf("%d\n", head->data);
    }
    
    return head;
}

// Function to read entire file content preserving all newlines and tabs
char* read_entire_file(const char* filename) {
    FILE *file = fopen(filename, "rb");  // Binary mode preserves all characters
    if (!file) {
        printf("Error opening file: %s\n", filename);
        return NULL;
    }
    
    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    if (file_size <= 0) {
        printf("Error: File is empty or invalid size\n");
        fclose(file);
        return NULL;
    }
    
    // Allocate buffer for entire file + null terminator
    char *content = malloc(file_size + 1);
    if (!content) {
        printf("Error: Memory allocation failed\n");
        fclose(file);
        return NULL;
    }
    
    // Read entire file
    size_t bytes_read = fread(content, 1, file_size, file);
    content[bytes_read] = '\0';  // Null terminate
    
    fclose(file);
    return content;  // Caller must free() this memory
}


int main(int argc, char *argv[]) {

    int exit_status = 0;
    int exited_if = 0;
    int in_while = 0;
    int if_true = 1;
    Vr *variables = malloc(sizeof(Vr));
    variables->next = NULL;
    variables->value = -50;
    
    char wtf[100];
    if (argc > 1) {
        // Filename provided as command line argument
        strcpy(wtf, argv[1]);
    } else {
        // Filename provided via stdin (for backward compatibility)
        printf("Enter filename: ");
        fflush(stdout);
        scanf("%s", wtf);
    }
    
    
    // Read entire file content preserving all formatting
    char *full_content = read_entire_file(wtf);
    if (!full_content) {
        return 1;  // Error already printed by read_entire_file
    }
    
    // Process the entire content as one unit (preserves \n and \t)
    Node *tokens = Jack(full_content, &variables);
    Bracket_Operator(&tokens);
    arithmetic(&tokens);
    Sundowner(&tokens);
    
    Node *cur = tokens;
    while (cur) {
        if (cur->data <= -1) {
            switch (cur->data) {
                case -1: cur=show(cur);                                                                       break; // show
                case -2: printf("\e[1;1H\e[2J");                                       break; // clear
                case -3: printf("Help: Available commands are show, clear, help, exit.\n");                      break; // help
                case -4: printf("Exiting...Bye!!\n"); 
                        free(full_content);  // Clean up memory
                        // Free remaining tokens
                        while (tokens) {
                            Node* nxt = tokens->next;
                            free(tokens);
                            tokens = nxt;
                        }
                        return 0;               break; // exit
                case -13:if (doc(&cur)){ 
                            if_true = 0;
                            cur = cur->next; 
                            continue; 
                        } else {
                            exit_status = 1;
                        }
                        break; 
                
                case -21: if (doc(&cur)){ 
                            in_while = 1;
                            cur = cur->next; 
                            continue; 
                        } else {
                            exit_status = 1;
                        }
                        break;
                case -14:if (if_true) {
                            if_true = 1; 
                            exited_if = 0;
                            cur = cur->next;
                            continue;
                        } else exit_status = 1;
            }
        }
        
        if (exit_status) {
            exit_status = 0;
            exited_if = 1;
            break;
        }
        if (in_while && cur->next == NULL)
        {   
            // Re-process the content for while loop
            Node* temp_tokens = tokens;
            tokens = Jack(full_content, &variables);
            in_while = 0;
            Bracket_Operator(&tokens);
            arithmetic(&tokens);
            Sundowner(&tokens);
            
            // Free old tokens
            while (temp_tokens) {
                Node* nxt = temp_tokens->next;
                free(temp_tokens);
                temp_tokens = nxt;
            }
            
            cur = tokens;
            continue;
        }
        cur = cur->next;
    }

    // Free memory
    free(full_content);
    while (tokens) {
        Node* nxt = tokens->next;
        free(tokens);
        tokens = nxt;
    }
}