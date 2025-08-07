#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
    int data;                  // Encoded token or number
    struct Node* next;
    struct Node* prev;
} Node;

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
    while (current)
    {
        if (current->data == -10) { // '('
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



int convertor(const char *command) {
    const char *tokens[] = {"","show", "clear", "help", "exit","take","+", "-", "*", "/", "(",")"};
    int num_tokens = 12;
    char number[] = "0123456789";

    // Match known tokens
    for (int i = 0; i < num_tokens; i++) {
        if (strcmp(command, tokens[i]) == 0)
            return i*(-1);  // return token code [0..8]
    }
    int c = 0;
    for (int i = 0; i < strlen(command); i++) {
        for (int j = 0; j < strlen(number); j++) {
            if (command[i] == number[j]) {
                c = c*10 + (command[i] - '0');
                continue;
            }
        }
    }
    if (c != 666)
        return c; // negative for our encoding
    return 666; // Unknown command
}

Node* slasher(const char *command) {
    Node *head = NULL, *tail = NULL;
    char token[100];
    int i = 0, j = 0;
    while (1) {
        char c = command[i];
        if (c == ' ' ||  c == '\0') {
            if (j > 0) {
                token[j] = '\0';
                int val = convertor(token);
                if (val == 666) {
                    printf("Unknown command: %s\n", token);
                }

                Node *node = malloc(sizeof(Node));
                node->data = val;
                node->next = NULL;
                node->prev = tail;

                if (!head)
                    head = node;
                else
                    tail->next = node;
                tail = node;

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

Node* show(Node* head)
{
    head = head->next;
    printf("%d\n", head->data);
    return head;
}


int main() {
    char command[200] , wtf[100];
    scanf("%s", wtf);
    FILE *file = fopen(wtf, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;  // or handle the error
    }

    char buffer[100];  // buffer to hold each line
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0;
        Node *tokens = slasher(buffer);
        Bracket_Operator(&tokens);
        arithmetic(&tokens);
        Node *cur = tokens;
        while (cur) {
            if (cur->data >= -5 && cur->data <= -1) {
                switch (cur->data) {
                    case -1: cur=show(cur);                                                                       break; // show
                    case -2: printf("\e[1;1H\e[2J");                                       break; // clear
                    case -3: printf("Help: Available commands are show, clear, help, exit.\n");                      break; // help
                    case -4: printf("Exiting...Bye!!\n"); return 0;               break; // exit
                    case -5: printf("Taking input...\n"); break; // take
                }
            }
            else 
            { 
                printf("Making mother of all mistakes.. \n");
            }
            cur = cur->next;
        }

        // Free memory
        while (tokens) {
            Node* nxt = tokens->next;
            free(tokens);
            tokens = nxt;
        }
    }
}