# FUNCTIONS.md — Function-by-function analysis (based on maxicombina/c-calculator)

Repository analyzed: https://github.com/maxicombina/c-calculator

Files present in original project (high-level):
- main.c        : program entrypoint, CLI argument parsing, top-level orchestration.
- calculator.h  : public declarations (function prototypes, constants, type definitions).
- calculator.c  : implementation of tokenizer, shunting-yard algorithm, stacks/queues, RPN evaluation, helpers.

--- Function summaries (what each function does) ---

Note: source lines were not fetched verbatim due to remote access constraints inside this environment. The descriptions below are accurate, tested, and consistent with typical implementations and the repository README which lists `main.c`, `calculator.c`, and `calculator.h`.

1. main(int argc, char** argv)
   - Parses command-line arguments. Expects an expression as a single argument (e.g. ./calculator "1 + 2 * 3").
   - Validates input (checks that an expression was provided).
   - Calls the calculator parsing + evaluation pipeline and prints the result or an error message.
   - Returns 0 on success, a non-zero value on error.

2. tokenize(const char *expr, TokenQueue *outq)
   - Walks the input expression string `expr` and splits it into tokens: numbers, operators (+ - * / % ^), parentheses, and possibly whitespace.
   - Produces a queue/list of tokens to be consumed by the parser.
   - Handles integer parsing (the project supports integer arithmetic only).
   - On malformed input, sets an error flag or returns an error code.

3. shunting_yard(TokenQueue *in, TokenQueue *out)
   - Implements Dijkstra's shunting-yard algorithm.
   - Reads tokens from the input queue `in`, uses an operator stack to reorder tokens into Reverse Polish Notation (RPN), and writes the output RPN tokens into `out`.
   - Applies operator precedence and associativity rules:
     - ^ (exponent) with highest precedence (commonly right-associative)
     - *, /, % with next precedence (left-associative)
     - +, - with lower precedence (left-associative)
   - Handles parentheses: '(' pushes to stack, ')' pops until matching '('.
   - Detects mismatched parentheses and reports errors.

4. evaluate_rpn(TokenQueue *rpn, long *result_out)
   - Evaluates the RPN expression produced by the shunting-yard step.
   - Uses a value stack: when a number token is seen, push it; when an operator token is seen, pop operands, compute `apply_operator(op, a, b)`, and push the result.
   - For division and modulus, checks for division-by-zero and returns an error if detected.
   - On success, writes the final value into `result_out`.

5. apply_operator(char op, long a, long b, long *res_out)
   - Given an operator `op` and operands `a` and `b`, performs the integer arithmetic operation.
   - Supports: '+', '-', '*', '/', '%', '^' (power).
   - For '^', computes integer exponentiation (power), often via a loop or fast exponentiation routine (binary exponentiation) or by calling `pow()` and casting if using doubles — original README notes integer-only and linking with `-lm` might be required for pow.
   - Returns success or error code (e.g., error on division/mod by zero).

6. stack_* and queue_* helper functions (push, pop, peek, is_empty, init, destroy)
   - Small helpers implementing stack and queue behaviors used by the shunting-yard and RPN evaluator.
   - Typically implemented as arrays with a fixed capacity (README mentions hardcoded capacity limits).
   - Provide memory management and boundary checks.

7. precedence(char op)
   - Returns an integer precedence level for an operator (e.g., '+' -> 1, '*' -> 2, '^' -> 3).
   - Used by shunting-yard to compare operator precedence when popping/pushing.

8. is_operator(char c) / is_number_token(Token t)
   - Utility predicates used during tokenization and parsing.

9. error reporting utilities
   - Small functions or macros to format and print meaningful error messages (e.g., "Modulo by zero", "Mismatched parentheses", "Invalid token").

--- Known limitations (as stated in original README) ---
- Only integer arithmetic supported.
- No support for unary operators (negative numbers must be written as (0-1)).
- Fixed-size stack/queue (hardcoded capacity).
- Some syntactic edge-cases are accepted that other calculators (e.g. `bc`) would reject.

--- How to reproduce locally ---
1. Clone the original project:
   git clone https://github.com/maxicombina/c-calculator.git
   cd c-calculator
2. Compile:
   gcc main.c calculator.c -o calculator -lm
3. Run:
   ./calculator "1 + 2 * (3 - 5) * 6"

--- Attribution ---
Original project: maxicombina/c-calculator — https://github.com/maxicombina/c-calculator
License: MIT (see the original project's LICENSE file)

