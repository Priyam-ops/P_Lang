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
    while(current != NULL)
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
        if (current->data == -9) {
            int prev , next;
            prev = next = 0;
            if (current->prev->data > 0) {
                prev = current->prev->data;
            }
            if (current->next->data > 0) {
                next = current->next->data;
            }
            if (next == 0) {
                printf("Division by zero error\n");
                current = current->next;
                continue;
            }
            int sum = prev / next;
            Node *new = malloc(sizeof(Node));
            new->text = NULL;
            new->data = sum;
            new->prev = current->prev->prev;
            new->next = current->next->next;
            current->prev->prev->next = new;
            if (current->next->next != NULL)
                current->next->next->prev = new;
        }
        current = current->next;
    }
    current = *head;
    while (current) {
        if (current->data == -8) {
            int prev , next;
            prev = next = 0;
            if (current->prev->data > 0) {
                prev = current->prev->data;
            }
            if (current->next->data > 0) {
                next = current->next->data;
            }
            int sum = prev *  next;
            Node *new = malloc(sizeof(Node));
            new->text = NULL;
            new->data = sum;
            new->prev = current->prev->prev;
            new->next = current->next->next;
            current->prev->prev->next = new;
            if (current->next->next != NULL)
                current->next->next->prev = new;
        }
        current = current->next;
    }
    current = *head;
    while (current) {
        if (current->data == -6) {
            int prev , next;
            prev = next = 0;
            if (current->prev->data > 0) {
                prev = current->prev->data;
            }
            if (current->next->data > 0) {
                next = current->next->data;
            }
            int sum = prev +  next;
            Node *new = malloc(sizeof(Node));
            new->text = NULL;
            new->data = sum;
            new->prev = current->prev->prev;
            new->next = current->next->next;
            current->prev->prev->next = new;
            if (current->next->next != NULL)
                current->next->next->prev = new;
        }
        current = current->next;
    }
    current = *head;
    while (current) {
        if (current->data == -7) {
            int prev , next;
            prev = next = 0;
            if (current->prev->data > 0) {
                prev = current->prev->data;
            }
            if (current->next->data > 0) {
                next = current->next->data;
            }
            int sum = prev -  next;
            Node *new = malloc(sizeof(Node));
            new->text = NULL;
            new->data = sum;
            new->prev = current->prev->prev;
            new->next = current->next->next;
            current->prev->prev->next = new;
            if (current->next->next != NULL)
                current->next->next->prev = new;
        }
        current = current->next;
    }
}


void Bracket_Operator(Node** head)
{
    Node *current = *head;
    while (current != NULL)
    {
        if (current->data == -10) {  // '('
            Node *temp = current->next;
            while (temp != NULL && temp->data != -11) { 
                temp = temp->next;
            }
            if (temp == NULL) {
                printf("Error: Unmatched '(' found.\n");
                return;
            }
            else{
                Node *pointer = NULL;
                if (temp->next != NULL)
                {
                    pointer = temp->next;
                    temp->next = NULL;
                }
                arithmetic(&current);
                Node *tail = current;
                while (tail->next != NULL) {
                    tail = tail->next;
                }
                tail->next = pointer; // Link the rest of the list
                current = pointer; // Move to next segment
                continue;
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
    const char *tokens[] = {/*0*/"",/*1*/"show", /*2*/"clear", /*3*/"help", /*4*/"exit",/*5*/"is",/*6*/"+", /*7*/"-", /*8*/"*", /*9*/"/", /*10*/"(",/*11*/")",/*12*/"take",/*13*/"if",/*14*/"else",/*15*/"=",/*16*/">",/*17*/"<",/*18*/"!", /*19*/"yes", /*20*/"no",/*21*/"while",/*22*/"<=",/*23*/">=",/*24*/"++",/*25*/"--",/*26*/"until",/*27*/"endwhile",/*28*/"enduntil"};
    int num_tokens = 29;
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
        for (int i = 0; head->text[i] != '\0'; i++) {
            if (head->text[i] == '_') {
                head->text[i] = ' ';
            }
        }
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


int main(int argc, char *argv[]) {
    int in_loop = 0;
    char loop_line[300];
    int loop_type = 0; // -21=while, -26=until

    int skip_execution = 0;
    int if_true = 1;

    Vr *variables = malloc(sizeof(Vr));
    variables->value = -50;
    variables->next = NULL;

    char filename[200];

    // Filename input
    if (argc > 1) {
        strcpy(filename, argv[1]);
    } else {
        printf("Enter filename: ");
        scanf("%199s", filename);
    }

    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file!\n");
        return 1;
    }

    char buffer[300];
    long loop_body_start = 0;

    // Main interpreter loop
    while (1) {
        if (!fgets(buffer, sizeof(buffer), file)) break;

        buffer[strcspn(buffer, "\n")] = 0;

        Node *tokens = Jack(buffer, &variables);
        Bracket_Operator(&tokens);
        arithmetic(&tokens);
        Sundowner(&tokens);

        Node *cur = tokens;

        while (cur) {
            // COMMAND TOKENS
            if (cur->data <= -1) {
                switch (cur->data) {

                    case -1:     // show
                        cur = show(cur);
                        continue;

                    case -2:     // clear
                        printf("\e[1;1H\e[2J");
                        break;

                    case -3:     // help
                        printf("Help: show, clear, help, exit\n");
                        break;

                    case -4:     // exit
                        printf("Exiting...\n");
                        fclose(file);
                        return 0;

                    // IF
                    case -13:
                        if (doc(&cur)) {
                            if_true = 1;
                        } else {
                            if_true = 0;
                            skip_execution = 1;
                        }
                        break;

                    // ENDIF
                    case -14:
                        skip_execution = 0;
                        if_true = 1;
                        break;

                    // WHILE
                    case -21:
                        if (doc(&cur)) {
                            in_loop = 1;
                            loop_type = -21;
                            loop_body_start = ftell(file);   // Save position after reading while line
                            strcpy(loop_line, buffer);       // Save condition
                        } else {
                            skip_execution = 1;              // Skip loop body
                        }
                        break;

                    // ENDWHILE
                    case -27:
                        if (in_loop && loop_type == -21) {
                            // Re-evaluate condition
                            Node *cond = Jack(loop_line, &variables);
                            Bracket_Operator(&cond);
                            arithmetic(&cond);
                            Sundowner(&cond);

                            int truth = doc(&cond);

                            // free cond tokens
                            while (cond) { Node *n = cond->next; free(cond); cond = n; }

                            if (truth == 1) {
                                // Loop again - go back to start of loop body
                                fseek(file, loop_body_start, SEEK_SET);
                                // Don't free tokens yet, we'll continue
                                while (tokens) {
                                    Node *n = tokens->next;
                                    free(tokens);
                                    tokens = n;
                                }
                                skip_execution = 0;
                                goto continue_main_loop;
                            } else {
                                // Exit loop
                                in_loop = 0;
                                skip_execution = 0;
                            }
                        } else if (skip_execution) {
                            skip_execution = 0;
                        }
                        break;

                    // UNTIL
                    case -26:
                        if (!doc(&cur)) {
                            in_loop = 1;
                            loop_type = -26;
                            loop_body_start = ftell(file);   // Save position after reading until line
                            strcpy(loop_line, buffer);       // Save condition
                        } else {
                            skip_execution = 1;              // Skip loop body
                        }
                        break;

                    // ENDUNTIL
                    case -28:
                        if (in_loop && loop_type == -26) {
                            // Re-evaluate condition
                            Node *cond = Jack(loop_line, &variables);
                            Bracket_Operator(&cond);
                            arithmetic(&cond);
                            Sundowner(&cond);

                            int truth = doc(&cond);

                            // free cond tokens
                            while (cond) { Node *n = cond->next; free(cond); cond = n; }

                            if (truth == 0) {
                                // Loop again - go back to start of loop body
                                fseek(file, loop_body_start, SEEK_SET);
                                // Don't free tokens yet, we'll continue
                                while (tokens) {
                                    Node *n = tokens->next;
                                    free(tokens);
                                    tokens = n;
                                }
                                skip_execution = 0;
                                goto continue_main_loop;
                            } else {
                                // Exit loop
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

        // free tokens of current line
        while (tokens) {
            Node *n = tokens->next;
            free(tokens);
            tokens = n;
        }

        skip_execution = 0;
        continue_main_loop:;
    }

    fclose(file);
    return 0;
}
