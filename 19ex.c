#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
// Enum for node types (numbers and operators)
typedef enum { NUM, ADD, SUB, MUL, DIV } NodeType;
// Structure for AST nodes
typedef struct Node {
    NodeType type;     // Type of node (NUM, ADD, SUB, MUL, DIV)
    union {
        int value;     // Holds the value for NUM nodes
        struct {       // Holds children for operator nodes
            struct Node* left;
            struct Node* right;
        };
    };
} Node;
// Function to create a number node
Node* createNumberNode(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->type = NUM;
    node->value = value;
    return node;
}
// Function to create an operator node
Node* createOperatorNode(NodeType type, Node* left, Node* right) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->type = type;
    node->left = left;
    node->right = right;
    return node;
}
// Function to print the AST (in-order traversal)
void printAST(Node* node) {
    if (node == NULL) return;  
    if (node->type == NUM) {
        printf("%d", node->value);
    } else {
        printf("(");
        printAST(node->left);
        switch (node->type) {
            case ADD: printf(" + "); break;
            case SUB: printf(" - "); break;
            case MUL: printf(" * "); break;
            case DIV: printf(" / "); break;
            default: break;
        }
        printAST(node->right);
        printf(")");
    }
}
// Function to parse a number from the expression
int parseNumber(const char** expr) {
    int result = 0;
    while (isdigit(**expr)) {
        result = result * 10 + (**expr - '0');
        (*expr)++;
    }
    return result;
}
// Function to parse terms (handles multiplication and division)
Node* parseTerm(const char** expr) {
    Node* node = parseNumber(expr);  
    while (**expr == '*' || **expr == '/') {
        char op = **expr;
        (*expr)++;
        Node* right = parseNumber(expr);
        if (op == '*') {
            node = createOperatorNode(MUL, node, right);
        } else {
            node = createOperatorNode(DIV, node, right);
        }
    }
    return node;
}
// Function to parse expressions (handles addition and subtraction)
Node* parseExpression(const char** expr) {
    Node* node = parseTerm(expr);  
    while (**expr == '+' || **expr == '-') {
        char op = **expr;
        (*expr)++;
        Node* right = parseTerm(expr);
        if (op == '+') {
            node = createOperatorNode(ADD, node, right);
        } else {
            node = createOperatorNode(SUB, node, right);
        }
    }
    return node;
}
// Main function to parse and print the AST
int main() {
    const char* expression = "3 + 5 * 2";
    printf("Expression: %s\n", expression);  
    Node* ast = parseExpression(&expression);
    printf("Abstract Syntax Tree (In-order): ");
    printAST(ast);
    printf("\n");
    return 0;
}
