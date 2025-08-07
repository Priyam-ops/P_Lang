#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//----------------- Data Structure -----------------

typedef struct Node {
    int data;                  // Encoded token or number
    struct Node* next;
    struct Node* prev;
} Node;

//----------------- Lexical Helper -----------------

// Returns token code, negative numbers are encoded as -[value], unknown = 666
int convertor(const char *command) {
    // Command tokens
    const char *tokens[] = {"show", "clear", "help", "exit", "+", "-", "*", "/", ","};
    int num_tokens = 9;

    // Match known tokens
    for (int i = 0; i < num_tokens; i++) {
        if (strcmp(command, tokens[i]) == 0)
            return i;  // return token code [0..8]
    }

    // Check for integer
    int is_num = 1, idx = 0;
    int len = strlen(command);
    int number = 0;

    // Handles optional sign
    int sign = 1;
    if (command[0] == '-') {
        sign = -1;
        idx++;
    }
    for (; idx < len; idx++) {
        if (!isdigit(command[idx])) {
            is_num = 0;
            break;
        }
        number = number * 10 + (command[idx] - '0');
    }
    if (is_num && len != 0)
        return -sign * number;    // negative for our encoding

    return 666; // Unknown command
}

//----------------- Tokenizer -----------------

Node* slasher(const char *command) {
    Node *head = NULL, *tail = NULL;
    char token[100];
    int i = 0, j = 0;
    while (1) {
        char c = command[i];
        if (c == ' ' || c == '\0') {
            if (j > 0) {
                token[j] = '\0';
                int val = convertor(token);

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
    return head;
}

//----------------- Command Implementations -----------------

void show(Node *head) {
    Node *cur = head;
    printf("Tokens: ");
    while (cur) {
        if (cur->data >= 0 && cur->data <= 3)
            printf("[%d:COMMAND] ", cur->data);
        else if (cur->data < 0)
            printf("[NUM:%d] ", -cur->data);
        else
            printf("[UNK:%d] ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

void help() {
    printf("Available commands:\n");
    printf("show      -- show entered tokens\n");
    printf("clear     -- show info about 'clear'\n");
    printf("help      -- this message\n");
    printf("exit      -- quit\n");
    printf("Integers  -- just type numbers\n");
}

void clear() {
    printf("Functionality for 'clear' not implemented.\n");
}

//----------------- Main Interpreter Loop -----------------

int main() {
    char command[200];

    while (1) {
        printf(">>> ");
        fflush(stdout);
        if (!fgets(command, sizeof(command), stdin))
            break;
        // Remove trailing newline
        command[strcspn(command, "\n")] = 0;

        Node *tokens = slasher(command);

        Node *cur = tokens;
        int exit_flag = 0;
        while (cur) {
            if (cur->data >= 0 && cur->data <= 3) {
                switch (cur->data) {
                    case 0: show(tokens);                break; // show
                    case 1: clear();                     break; // clear
                    case 2: help();                      break; // help
                    case 3: exit_flag = 1;               break; // exit
                }
            }
            cur = cur->next;
        }

        // Free memory
        while (tokens) {
            Node* nxt = tokens->next;
            free(tokens);
            tokens = nxt;
        }
        if (exit_flag) break;
    }
    printf("Bye!\n");
    return 0;
}
