#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// SECTION 1: CONSTANT DEFINITIONS
// -------------------------------
// Maximum line length to read from file
#define MAX_LINE_LEN 256

// All valid token categories
const char *IMPERATIVE_STMTS[] = {"STOP", "ADD", "SUB", "MULT", "DIV", 
                                   "PRINT", "MOVER", "MOVEM", "COMP", "BC"};
const char *DECLARATIVE_STMTS[] = {"DS", "DC", "READ"};
const char *ASSEMBLER_DIRS[] = {"START", "END", "ORIGIN", "EQU", "LTORG"};
const char *CONDITION_CODES[] = {"LT", "LE", "GT", "GE", "EQ", "NE"};
const char *REGISTERS[] = {"AREG", "BREG", "CREG", "DREG"};

const int IMPERATIVE_COUNT = 10;
const int DECLARATIVE_COUNT = 3;
const int ASSEMBLER_DIRS_COUNT = 5;
const int CONDITION_CODES_COUNT = 6;
const int REGISTERS_COUNT = 4;

// SECTION 2: FUNCTION PROTOTYPES
// -------------------------------
bool is_in_category(const char *token, const char *category[], int count);
void validate_statement(int line_num, char *tokens[], int token_count);
void process_tokens(int line_num, char *line);

// SECTION 3: MAIN FUNCTION
// -----------------------
int main() {
    FILE *file = fopen("a.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file 'a.txt'\n");
        return 1;
    }

    char line[MAX_LINE_LEN];
    int line_num = 0;

    // Read each line from the file
    while (fgets(line, sizeof(line), file)) {
        line_num++;
        line[strcspn(line, "\n")] = '\0'; // Remove newline character
        process_tokens(line_num, line);
    }

    fclose(file);
    return 0;
}

// SECTION 4: FUNCTION DEFINITIONS
// -------------------------------

/*
 * Checks if a token exists in the specified category
 * Parameters:
 *   - token: The token to check
 *   - category: Array of valid strings for this category
 *   - count: Number of elements in the category array
 * Returns: 
 *   - true if token is found in category
 *   - false otherwise
 */
bool is_in_category(const char *token, const char *category[], int count) {
    for (int i = 0; i < count; i++) {
        if (strcmp(token, category[i]) == 0) {
            return true;
        }
    }
    return false;
}

/*
 * Validates a single assembly statement based on the number of tokens
 * Parameters:
 *   - line_num: Current line number being processed
 *   - tokens: Array of strings containing the statement tokens
 *   - token_count: Number of tokens in the array
 */
void validate_statement(int line_num, char *tokens[], int token_count) {
    bool has_error = false;

    // Check for 4 tokens
    if (token_count == 4) {
        const char *label = tokens[0];
        const char *mnemonic = tokens[1];
        const char *register_op = tokens[2];
        const char *memory_op = tokens[3];

        // CHECK 1: Validate label
        if (is_in_category(label, IMPERATIVE_STMTS, IMPERATIVE_COUNT) ||
            is_in_category(label, DECLARATIVE_STMTS, DECLARATIVE_COUNT) ||
            is_in_category(label, ASSEMBLER_DIRS, ASSEMBLER_DIRS_COUNT) ||
            is_in_category(label, CONDITION_CODES, CONDITION_CODES_COUNT) ||
            is_in_category(label, REGISTERS, REGISTERS_COUNT)) {
            printf("Error (Line %d): Invalid Symbolic Name '%s'\n", line_num, label);
            has_error = true;
        }

        // CHECK 2: Validate mnemonic instruction
        if (is_in_category(mnemonic, DECLARATIVE_STMTS, DECLARATIVE_COUNT) ||
            is_in_category(mnemonic, ASSEMBLER_DIRS, ASSEMBLER_DIRS_COUNT) ||
            is_in_category(mnemonic, CONDITION_CODES, CONDITION_CODES_COUNT) ||
            is_in_category(mnemonic, REGISTERS, REGISTERS_COUNT)) {
            printf("Error (Line %d): Invalid Mnemonic Instruction '%s'\n", line_num, mnemonic);
            has_error = true;
        }

        // CHECK 3: Validate register operand
        if (is_in_category(register_op, IMPERATIVE_STMTS, IMPERATIVE_COUNT) ||
            is_in_category(register_op, DECLARATIVE_STMTS, DECLARATIVE_COUNT) ||
            is_in_category(register_op, ASSEMBLER_DIRS, ASSEMBLER_DIRS_COUNT) ||
            is_in_category(register_op, CONDITION_CODES, CONDITION_CODES_COUNT)) {
            printf("Error (Line %d): Invalid Register Operand '%s'\n", line_num, register_op);
            has_error = true;
        }

        // CHECK 4: Validate memory operand
        if (is_in_category(memory_op, IMPERATIVE_STMTS, IMPERATIVE_COUNT) ||
            is_in_category(memory_op, DECLARATIVE_STMTS, DECLARATIVE_COUNT) ||
            is_in_category(memory_op, ASSEMBLER_DIRS, ASSEMBLER_DIRS_COUNT) ||
            is_in_category(memory_op, CONDITION_CODES, CONDITION_CODES_COUNT) ||
            is_in_category(memory_op, REGISTERS, REGISTERS_COUNT)) {
            printf("Error (Line %d): Invalid Symbolic Name (Memory Operand) '%s'\n", line_num, memory_op);
            has_error = true;
        }
    }
    // Check for 3 tokens
    else if (token_count == 3) {
        const char *label = tokens[0];
        const char *mnemonic = tokens[1];
        const char *memory_op = tokens[2];

        // CHECK 1: Validate label
        if (is_in_category(label, IMPERATIVE_STMTS, IMPERATIVE_COUNT) ||
            is_in_category(label, DECLARATIVE_STMTS, DECLARATIVE_COUNT) ||
            is_in_category(label, ASSEMBLER_DIRS, ASSEMBLER_DIRS_COUNT) ||
            is_in_category(label, CONDITION_CODES, CONDITION_CODES_COUNT) ||
            is_in_category(label, REGISTERS, REGISTERS_COUNT)) {
            printf("Error (Line %d): Invalid Symbolic Name '%s'\n", line_num, label);
            has_error = true;
        }

        // CHECK 2: Validate mnemonic instruction
        if (is_in_category(mnemonic, DECLARATIVE_STMTS, DECLARATIVE_COUNT) ||
            is_in_category(mnemonic, ASSEMBLER_DIRS, ASSEMBLER_DIRS_COUNT) ||
            is_in_category(mnemonic, CONDITION_CODES, CONDITION_CODES_COUNT) ||
            is_in_category(mnemonic, REGISTERS, REGISTERS_COUNT)) {
            printf("Error (Line %d): Invalid Mnemonic Instruction '%s'\n", line_num, mnemonic);
            has_error = true;
        }

        // CHECK 3: Validate memory operand
        if (is_in_category(memory_op, IMPERATIVE_STMTS, IMPERATIVE_COUNT) ||
            is_in_category(memory_op, DECLARATIVE_STMTS, DECLARATIVE_COUNT) ||
            is_in_category(memory_op, ASSEMBLER_DIRS, ASSEMBLER_DIRS_COUNT) ||
            is_in_category(memory_op, CONDITION_CODES, CONDITION_CODES_COUNT) ||
            is_in_category(memory_op, REGISTERS, REGISTERS_COUNT)) {
            printf("Error (Line %d): Invalid Symbolic Name (Memory Operand) '%s'\n", line_num, memory_op);
            has_error = true;
        }
    }
    // Check for 2 tokens
    else if (token_count == 2) {
        const char *label = tokens[0];
        const char *mnemonic = tokens[1];

        // CHECK 1: Validate label
        if (is_in_category(label, IMPERATIVE_STMTS, IMPERATIVE_COUNT) ||
            is_in_category(label, DECLARATIVE_STMTS, DECLARATIVE_COUNT) ||
            is_in_category(label, ASSEMBLER_DIRS, ASSEMBLER_DIRS_COUNT) ||
            is_in_category(label, CONDITION_CODES, CONDITION_CODES_COUNT) ||
            is_in_category(label, REGISTERS, REGISTERS_COUNT)) {
            printf("Error (Line %d): Invalid Symbolic Name '%s'\n", line_num, label);
            has_error = true;
        }

        // CHECK 2: Validate mnemonic instruction
        if (is_in_category(mnemonic, DECLARATIVE_STMTS, DECLARATIVE_COUNT) ||
            is_in_category(mnemonic, ASSEMBLER_DIRS, ASSEMBLER_DIRS_COUNT) ||
            is_in_category(mnemonic, CONDITION_CODES, CONDITION_CODES_COUNT) ||
            is_in_category(mnemonic, REGISTERS, REGISTERS_COUNT)) {
            printf("Error (Line %d): Invalid Mnemonic Instruction '%s'\n", line_num, mnemonic);
            has_error = true;
        }
    }
    // Check for 1 token
    else if (token_count == 1) {
        const char *mnemonic = tokens[0];

        // CHECK: Ensure it is only STOP or LTORG
        if (strcmp(mnemonic, "STOP") != 0 && strcmp(mnemonic, "LTORG") != 0) {
            printf("Error (Line %d): Invalid Mnemonic Instruction '%s'\n", line_num, mnemonic);
            has_error = true;
        }
    }

    // If no errors, print valid statement
    if (!has_error) {
        printf("[VALID] Line %d: ", line_num);
        for (int i = 0; i < token_count; i++) {
            printf("%s ", tokens[i]);
        }
        printf("\n");
    }
}

/*
 * Processes the tokens from a line of assembly code
 * Parameters:
 *   - line_num: Current line number being processed
 *   - line: The line of assembly code to process
 */
void process_tokens(int line_num, char *line) {
    char *tokens[10]; // Array to hold tokens
    int token_count = 0;

    // Tokenize the line using strtok
    char *token = strtok(line, " \t");
    while (token != NULL && token_count < 10) {
        tokens[token_count] = token;
        token_count++;
        token = strtok(NULL, " \t");
    }

    // Validate the statement based on the number of tokens
    validate_statement(line_num, tokens, token_count);
}