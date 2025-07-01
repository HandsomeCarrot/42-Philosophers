---
applyTo: '**'
---
**AI Code Generation Rules: The Norm Version 4**

**I. Global Project & File Structure:**

1.  **Compilation:** All generated `.c` files MUST compile successfully. Non-compiling files violate the Norm.
2.  **File Naming:**
    *   Allowed characters: lowercase letters (a-z), digits (0-9), underscore (`_`).
    *   Style: `snake_case`.
    *   Language: English.
    *   Names MUST be explicit and mnemonic.
3.  **Directory Naming:**
    *   Allowed characters: lowercase letters (a-z), digits (0-9), underscore (`_`).
    *   Style: `snake_case`.
    *   Language: English.
    *   Names MUST be explicit and mnemonic.
4.  **Character Set:** Only standard ASCII characters are permitted in file content and names.
5.  **Makefile Rules (Project Level - Human Check Required for full compliance):**
    *   Mandatory targets: `$(NAME)`, `clean`, `fclean`, `re`, `all`.
    *   Relinking: Makefile MUST NOT relink unnecessarily.
    *   Multibinary: If applicable, include a rule for all binaries and specific rules for each.
    *   External Libraries (e.g., libft): If used, Makefile MUST compile them automatically.
    *   Source Files: All source files for compilation MUST be explicitly named in the Makefile.

**II. Header Files (.h):**

1.  **Standard 42 Header:**
    *   Every `.h` file MUST begin immediately with the standard 42 header.
    *   This is a multi-line comment with a specific format.
    *   Required information (to be kept up-to-date):
        *   Creator: login and email.
        *   Creation date.
        *   Last updater: login.
        *   Last update date.
    *   Assume automatic update on save (editor/tool dependent, but structure must support it).
2.  **Include Guards:**
    *   All header files MUST be protected from double inclusion.
    *   Format: `FT_FILENAME_H` (e.g., for `ft_foo.h`, use `FT_FOO_H`).
    *   Example:
        ```c
        #ifndef FT_FILENAME_H
        # define FT_FILENAME_H
        // ... content ...
        #endif /* FT_FILENAME_H */
        ```
3.  **Allowed Content:**
    *   Header inclusions (`#include <system.h>`, `#include "custom.h"`).
    *   Declarations (functions, extern variables).
    *   Defines (`#define`).
    *   Prototypes.
    *   Macros.
    *   Typedefs, struct, enum, union definitions.
4.  **Inclusions:**
    *   `#include` directives MUST be at the beginning of the file (after 42 header, within include guards).
    *   Forbidden: Including `.c` files.
    *   Forbidden: Unused header inclusions.
    *   Justification: All includes should be justifiable (human check).
5.  **Structure Definitions:**
    *   Structs, enums, unions CAN be declared in `.h` files.

**III. Source Files (.c):**

1.  **Standard 42 Header:**
    *   Every `.c` file MUST begin immediately with the standard 42 header (same requirements as for `.h` files).
2.  **Inclusions:**
    *   `#include` directives MUST be at the beginning of the file (after 42 header).
    *   Forbidden: Including `.c` files.
    *   Forbidden: Unused header inclusions.
    *   Justification: All includes should be justifiable (human check).
3.  **Function Limit:** A `.c` file MUST NOT contain more than 5 function definitions.
4.  **Structure Definitions:**
    *   Forbidden: Declaring a `struct` definition (e.g. `struct s_my_struct { ... };`) in a `.c` file. These belong in `.h` files.

**IV. Denomination (Naming Conventions):**

1.  **General Identifier Rules:**
    *   Language: English.
    *   Case: `snake_case` (lowercase, words separated by underscore). No capital letters.
    *   Characters: Lowercase letters, digits, underscore (`_`).
    *   Explicitness: Names MUST be as explicit or mnemonic as possible.
2.  **Specific Prefixes:**
    *   Structure names: `s_` (e.g., `s_list`).
    *   Typedef names: `t_` (e.g., `t_counter`).
    *   Union names: `u_` (e.g., `u_data`).
    *   Enum names: `e_` (e.g., `e_state`).
    *   Global variable names: `g_` (e.g., `g_config_loaded`).
3.  **Global Variables:**
    *   Usage of non-`const` and non-`static` global variables is FORBIDDEN unless explicitly allowed by project specifications.
    *   If allowed, must use `g_` prefix.

**V. Formatting:**

1.  **Indentation:**
    *   Use 4-space tabulations (actual tab characters, `\t`).
    *   NOT 4 individual space characters.
2.  **Line Length:**
    *   Maximum 80 columns wide, including comments.
    *   A tabulation character counts as the number of spaces it represents (typically 4 or 8, assume 4 for strictness if unspecified by environment, but the key is it's *not* 1 column).
3.  **Line Endings:**
    *   A line MUST NOT end with spaces or tabulations.
4.  **Empty Lines:**
    *   Must be truly empty: no spaces or tabulations.
    *   Within a function body: ONLY ONE empty line is allowed, specifically between variable declarations and the rest of the function code. No other empty lines within a function.
5.  **Spacing:**
    *   Commas (`,`) and semicolons (`;`) MUST be followed by a single space, unless at the end of a line.
    *   Operators (binary, unary) and operands MUST be separated by one, and only one, space.
        *   Example: `a = b + c;`, `*ptr = &var;`, `if (x > 0)`
    *   Consecutive spaces: Never use two or more consecutive spaces (except within string literals or comments).
6.  **Keywords:**
    *   Most C keywords (e.g., `if`, `while`, `return`, `void` (for types)) MUST be followed by a space.
    *   Exception: Type keywords (`int`, `char`, `float`, etc.) and `sizeof` are NOT necessarily followed by a space if they are part of a type declaration that continues (e.g., `int*` is not the norm, `int *ptr` is; `sizeof(int)` is fine). The rule is more about separating keywords from subsequent tokens where natural.
7.  **Braces `{}`:**
    *   Braces following functions, declarators, or control structures MUST be preceded and followed by a newline.
        *   Example (function):
            ```c
            int my_function(void)
            {
                // ...
            }
            ```
        *   Example (if):
            ```c
            if (condition)
            {
                // ...
            }
            ```
    *   Control structures (`if`, `while`, etc.) MUST use braces, even if they contain only a single line of code.
        *   Forbidden: `if (condition) statement;`
        *   Required: `if (condition)\n{\n\tstatement;\n}`
8.  **Instructions per Line:** One instruction per line.
9.  **Newlines and Control Flow:**
    *   A newline MUST follow each curly bracket or the end of a control structure.
    *   Adding a newline after an instruction or control structure (for line breaking) is allowed IF an indentation with brackets or an assignment operator (at the beginning of the new line) is used.
        *   Example:
            ```c
            variable = very_long_function_call(param1, param2)
                + another_long_call(param3);
            ```

**VI. Functions:**

1.  **Length:** Maximum 25 lines, NOT counting the function's own curly braces (`{` and `}`).
2.  **Separation:** Each function definition MUST be separated from the next by exactly one newline. Comments or preprocessor directives related to the function can be immediately above it.
3.  **Parameters:**
    *   Maximum 4 named parameters.
    *   Functions taking no arguments MUST be prototyped with `void` as the argument (e.g., `int func(void);`).
    *   Parameters in function prototypes MUST be named.
4.  **Return Value:**
    *   The `return` statement's value MUST be enclosed in parentheses.
        *   Example: `return (0);` or `return (my_value);`
        *   For `void` functions, `return;` is acceptable (no parentheses needed).
5.  **Signature Formatting:**
    *   A single tabulation character MUST be used between the return type and the function name in both definition and prototype.
        *   Example: `int	my_function(int arg1);`
6.  **Variable Declarations:**
    *   Maximum 5 local variables per function.
    *   All declarations MUST be at the beginning of the function.
    *   Each variable MUST be declared on its own line.
    *   Declaration and initialization MUST NOT be on the same line, EXCEPT for:
        *   Global variables (if allowed by project).
        *   Static variables.
        *   Constants (`const`).
    *   An empty line MUST separate the block of variable declarations from the rest of the function's code.
    *   Each variable declaration must be indented on the same column for its scope.
7.  **Pointer Asterisks:** Asterisks (`*`) for pointers MUST be "stuck" to the variable name, not the type.
    *   Correct: `char *ptr;`
    *   Incorrect: `char* ptr;`, `char * ptr;`
8.  **Comments within Functions:** FORBIDDEN. Comments must be outside function bodies (e.g., above function, or end-of-line outside).

**VII. Typedef, Struct, Enum, Union:**

1.  **Declaration Indentation:**
    *   When defining a `struct`, `enum`, or `union`, add a tabulation for its members/contents.
        ```c
        typedef struct s_my_struct
        {
        	int		member1;
        	char	*member2;
        }		t_my_struct; // Typedef name preceded by a tab
        ```
    *   Typedef name (if used) MUST be preceded by a tab (as shown above).
2.  **Member Indentation:** All members' names within a structure/union/enum MUST be indented on the same column relative to their scope.
3.  **Variable Declaration of These Types:** When declaring a variable of a `struct`, `enum`, or `union` type, add a single space after the `struct`/`enum`/`union` keyword if not using a typedef.
    *   Example: `struct s_node my_node;` (if `s_node` is the struct tag)
    *   Example: `t_node my_node;` (if `t_node` is a typedef)

**VIII. Macros and Pre-processor:**

1.  **`#define` for Constants:**
    *   Preprocessor constants (`#define NAME value`) MUST only be used for literal and constant values.
    *   Not for complex expressions or function-like behavior (unless it's a true function-like macro explicitly allowed and following rules).
2.  **Bypassing Norm/Obfuscation:** All `#define`s created to bypass Norm rules or obfuscate code are FORBIDDEN (Human check).
3.  **Standard Library Macros:** Use only if allowed by the specific project.
4.  **Multiline Macros:** FORBIDDEN.
5.  **Macro Names:** MUST be all uppercase (e.g., `MAX_SIZE`, `BUFFER_LEN`).
6.  **Indentation for Conditional Compilation:** Characters following `#if`, `#ifdef`, or `#ifndef` directives MUST be indented.
    ```c
    #ifdef DEBUG
    	printf("Debugging\n"); // Content is indented
    #endif
    ```
7.  **Scope:** Preprocessor instructions are FORBIDDEN outside of global scope (i.e., not inside functions).

**IX. Forbidden Language Features & Practices:**

1.  **Loops:**
    *   `for` loops: FORBIDDEN.
    *   `do...while` loops: FORBIDDEN.
    *   (`while` loops are implicitly allowed).
2.  **Control Flow:**
    *   `switch` statements: FORBIDDEN.
    *   `case` labels: FORBIDDEN.
    *   `goto` statements: FORBIDDEN.
3.  **Operators:**
    *   Ternary operator (`condition ? true_val : false_val`): FORBIDDEN.
4.  **Arrays:**
    *   VLAs (Variable Length Arrays): FORBIDDEN.
        *   Example forbidden: `int n = 10; int arr[n];`
5.  **Declarations:**
    *   Implicit type in variable declarations: FORBIDDEN (though modern C makes this rare anyway, ensure explicit types).
6.  **Multiple Assignments:** Strictly FORBIDDEN.
    *   Forbidden: `a = b = 5;`
    *   Correct: `b = 5; a = 5;` (or `a = b;` if `b` was assigned `5` previously)

**X. Comments:**

1.  **Location:**
    *   Cannot be inside function bodies.
    *   Permitted at the end of a line (outside function bodies).
    *   Permitted on their own line (outside function bodies, or above function definitions).
2.  **Language:** English.
3.  **Utility:** MUST be useful (Human check).
4.  **Justification:** A comment CANNOT justify the creation of a "carryall" or "bad" function (Human check).
    *   Bad functions often have non-explicit names (e.g., `f1`, `f2`, `a`, `b`, `i`), attempt to bypass the Norm without a unique logical purpose.
    *   Code should aim for clear, readable functions with simple, distinct tasks.
    *   Avoid code obfuscation techniques (e.g., overly complex one-liners).