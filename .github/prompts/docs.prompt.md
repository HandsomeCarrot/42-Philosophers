---
mode: edit
---
# AI Documentation Generation Workflow: Doxygen-Style

  

**Objective:** Cline, your task is to generate comprehensive, Doxygen-style documentation comments for all specified functions within the current file (if not instructed otherwise). These comments must be meticulously formatted and adhere to all guidelines below. The output should be directly insertable into the source code.

  

**Input:** Cline will receive a snippet or a file of source code in a supported language (e.g., C++, Java, Python, C#, JavaScript).

  

**Output:** For each function identified, Cline will generate a Doxygen-style comment block immediately preceding the function definition. The entire output will be in Markdown, with the Doxygen comments formatted as pre-formatted text (within triple backticks if presented as a standalone document, or directly as comments if integrated into a larger code generation process).

  

---

  

## I. General Principles for Cline:

  

1.  **Accuracy:** All information, especially parameter names, return types (inferred for description), and exception types, must precisely match the function's signature and behavior.

2.  **Clarity:** Descriptions should be clear, concise, and unambiguous. Use professional and formal language.

3.  **Completeness:** Document all aspects of the function as outlined in the structure. Do not omit required tags if applicable (e.g., `@param` for a function with parameters).

4.  **Order:** Generate documentation blocks for functions in the exact order they appear in the input code.

5.  **Idempotency (Conceptual):** If the same code is processed again, the generated documentation should ideally be identical, assuming the underlying code analysis is consistent.

  

---

  

## II. Core Documentation Block Structure:

  

Each function documentation block MUST follow this Doxygen-style structure:

  

```c

/**

 * @brief A concise, one-sentence summary of the function's purpose.

 *

 * (Optional) A more detailed description. This section is used if the

 * function's purpose, algorithm, side effects, or interactions are

 * complex and cannot be adequately explained in the brief summary.

 * Each new paragraph in the detailed description should start on a new

 * line, still adhering to the 80-character limit.

 *

 * @tparam T (If template) Description of template parameter T.

 * @param paramName Description of this specific parameter. Explain its

 *                  purpose, expected type/range (if not obvious from

 *                  type signature), and any special conditions.

 * @param anotherParam Description for the next parameter. (Repeat for all)

 *

 * @return Description of the value returned by the function. If the

 *         function is `void` or a constructor, this tag MUST be omitted.

 *         Specify what the return value represents.

 *

 * @throw ExceptionType Condition under which this exception is thrown.

 * @throws AnotherExceptionType (Repeat for all potential exceptions)

 *

 * @note Important usage notes, preconditions, postconditions, or

 *       any other critical information a developer needs to know

 *       before using this function.

 *

 * @warning Describe any potential pitfalls, critical limitations, or

 *          situations where the function might behave unexpectedly if

 *          not used carefully.

 *

 * @see RelatedFunctionNameOrConcept For further reading or related items.

 * @see AnotherRelatedItem

 *

 * @deprecated (If applicable) Reason for deprecation and alternative.

 */

```

  

---

  

## III. Detailed Tag-by-Tag Instructions:

  

1.  **Block Start/End:**

    *   Every documentation block MUST begin with `/**` on its own line.

    *   Every documentation block MUST end with `*/` on its own line.

    *   Intermediate lines MUST start with ` * ` (space, asterisk, space).

  

2.  **`@brief` (Mandatory)**

    *   **Content:** A single, imperative sentence summarizing the function's primary purpose (e.g., "Calculates the sum of two integers." not "This function calculates...").

    *   **Placement:** Must be the first tag after `/**`.

    *   **Formatting:** ` * @brief [Your concise summary here]`

  

3.  **Detailed Description (Optional, but Recommended for Complexity)**

    *   **Content:** Elaborate on the function's behavior, algorithms used, side effects, performance considerations, or any nuances not covered by `@brief`.

    *   **Placement:** Appears after `@brief` and before any other tags like `@param` or `@return`.

    *   **Formatting:**

        *   Begins with a blank comment line: ` * `

        *   Text starts on the next line: ` * [Detailed explanation starts here...]`

        *   New paragraphs also start with ` * ` on a new line, preceded by a blank ` * ` line.

  

4.  **`@tparam <template_parameter_name>` (Conditional)**

    *   **Condition:** Include for each template parameter in a template function or class.

    *   **Content:** Describe the purpose or constraints of the template parameter.

    *   **Placement:** Typically after the detailed description and before `@param`.

    *   **Formatting:** ` * @tparam T Description of template parameter T# AI Documentation Generation Workflow: Doxygen-Style

  

**Objective:** Cline, your task is to generate comprehensive, Doxygen-style documentation comments for all specified functions within a given file (if not instructed otherwise). These comments must be meticulously formatted and adhere to all guidelines below. The output should be directly insertable into the source code.

  

**Input:** Cline will receive a snippet or a file of source code in a supported language (e.g., C++, Java, Python, C#, JavaScript).

  

**Output:** For each function identified, Cline will generate a Doxygen-style comment block immediately preceding the function definition. The entire output will be in Markdown, with the Doxygen comments formatted as pre-formatted text (within triple backticks if presented as a standalone document, or directly as comments if integrated into a larger code generation process).

  

---

  

## I. General Principles for Cline:

  

1.  **Accuracy:** All information, especially parameter names, return types (inferred for description), and exception types, must precisely match the function's signature and behavior.

2.  **Clarity:** Descriptions should be clear, concise, and unambiguous. Use professional and formal language.

3.  **Completeness:** Document all aspects of the function as outlined in the structure. Do not omit required tags if applicable (e.g., `@param` for a function with parameters).

4.  **Order:** Generate documentation blocks for functions in the exact order they appear in the input code.

5.  **Idempotency (Conceptual):** If the same code is processed again, the generated documentation should ideally be identical, assuming the underlying code analysis is consistent.

  

---

  

## II. Core Documentation Block Structure:

  

Each function documentation block MUST follow this Doxygen-style structure:

  

```c

/**

 * @brief A concise, one-sentence summary of the function's purpose.

 *

 * (Optional) A more detailed description. This section is used if the

 * function's purpose, algorithm, side effects, or interactions are

 * complex and cannot be adequately explained in the brief summary.

 * Each new paragraph in the detailed description should start on a new

 * line, still adhering to the 80-character limit.

 *

 * @tparam T (If template) Description of template parameter T.

 * @param paramName Description of this specific parameter. Explain its

 *                  purpose, expected type/range (if not obvious from

 *                  type signature), and any special conditions.

 * @param anotherParam Description for the next parameter. (Repeat for all)

 *

 * @return Description of the value returned by the function. If the

 *         function is `void` or a constructor, this tag MUST be omitted.

 *         Specify what the return value represents.

 *

 * @throw ExceptionType Condition under which this exception is thrown.

 * @throws AnotherExceptionType (Repeat for all potential exceptions)

 *

 * @note Important usage notes, preconditions, postconditions, or

 *       any other critical information a developer needs to know

 *       before using this function.

 *

 * @warning Describe any potential pitfalls, critical limitations, or

 *          situations where the function might behave unexpectedly if

 *          not used carefully.

 *

 * @see RelatedFunctionNameOrConcept For further reading or related items.

 * @see AnotherRelatedItem

 *

 * @deprecated (If applicable) Reason for deprecation and alternative.

 */

```

  

---

  

## III. Detailed Tag-by-Tag Instructions:

  

1.  **Block Start/End:**

    *   Every documentation block MUST begin with `/**` on its own line.

    *   Every documentation block MUST end with `*/` on its own line.

    *   Intermediate lines MUST start with ` * ` (space, asterisk, space).

  

2.  **`@brief` (Mandatory)**

    *   **Content:** A single, imperative sentence summarizing the function's primary purpose (e.g., "Calculates the sum of two integers." not "This function calculates...").

    *   **Placement:** Must be the first tag after `/**`.

    *   **Formatting:** ` * @brief [Your concise summary here]`

  

3.  **Detailed Description (Optional, but Recommended for Complexity)**

    *   **Content:** Elaborate on the function's behavior, algorithms used, side effects, performance considerations, or any nuances not covered by `@brief`.

    *   **Placement:** Appears after `@brief` and before any other tags like `@param` or `@return`.

    *   **Formatting:**

        *   Begins with a blank comment line: ` * `

        *   Text starts on the next line: ` * [Detailed explanation starts here...]`

        *   New paragraphs also start with ` * ` on a new line, preceded by a blank ` * ` line.

  

4.  **`@tparam <template_parameter_name>` (Conditional)**

    *   **Condition:** Include for each template parameter in a template function or class.

    *   **Content:** Describe the purpose or constraints of the template parameter.

    *   **Placement:** Typically after the detailed description and before `@param`.

    *   **Formatting:** ` * @tparam T Description of template parameter T.`

  

5.  **`@param <parameter_name>` (Conditional)**

    *   **Condition:** Include one `@param` tag for EACH parameter listed in the function signature.

    *   **Content:**

        *   `<parameter_name>` MUST exactly match the name in the function signature.

        *   The description should explain the parameter's role, expected values/range, units (if applicable), and any default value if not obvious.

    *   **Placement:** After `@brief`/detailed description/`@tparam`. List in the same order as the function signature.

    *   **Formatting:** ` * @param paramName Description of this parameter.`

  

6.  **`@return` (Conditional)**

    *   **Condition:** Include if the function has a non-`void` return type. OMIT entirely for `void` functions and constructors/destructors.

    *   **Content:** Describe what the returned value represents and any special conditions related to it (e.g., "Returns the calculated area. Returns -1.0 on error.").

    *   **Placement:** After all `@param` tags.

    *   **Formatting:** ` * @return Description of the return value.`

  

7.  **`@throw <ExceptionType>` or `@throws <ExceptionType>` (Conditional)**

    *   **Condition:** Include for each distinct type of exception the function might explicitly throw.

    *   **Content:**

        *   `<ExceptionType>` should be the actual type of the exception (e.g., `std::out_of_range`, `IOException`).

        *   The description should state the specific condition(s) under which this exception is thrown.

    *   **Placement:** After `@return`.

    *   **Formatting:** ` * @throw std::runtime_error If the input file cannot be opened.`

  

8.  **`@note` (Optional)**

    *   **Content:** Provide important usage information, preconditions (what must be true before calling), postconditions (what will be true after calling if successful), or non-obvious details critical for correct usage.

    *   **Placement:** Typically after `@throw`/`@throws`.

    *   **Formatting:** ` * @note This function is not thread-safe.`

  

9.  **`@warning` (Optional)**

    *   **Content:** Highlight potential dangers, critical limitations, or common mistakes developers might make when using the function.

    *   **Placement:** After `@note`.

    *   **Formatting:** ` * @warning Modifying the input array during execution leads to

 *          undefined behavior.`

  

10. **`@see <reference>` (Optional)**

    *   **Content:** Refer to other related functions, classes, documents, or concepts. This helps users find related information.

    *   **Placement:** After `@warning`.

    *   **Formatting:** ` * @see otherFunction()`

    *   **Formatting:** ` * @see MyClassName::anotherMethod`

    *   **Formatting:** ` * @see "The official algorithm specification document"`

  

11. **`@deprecated` (Conditional)**

    *   **Condition:** If the function is deprecated.

    *   **Content:** Briefly explain why it's deprecated and what alternative function or approach should be used instead.

    *   **Placement:** Usually one of the last tags.

    *   **Formatting:** ` * @deprecated This function will be removed in v3.0. Use

 *             newShinyFunction() instead.`

  

---

  

## IV. Strict Formatting Rules:

  

1.  **Maximum Line Length: 80 Characters (ABSOLUTE)**

    *   **Scope:** This limit applies to EVERY line within the `/** ... */` comment block, including leading spaces, the `*`, the tag, and the text.

    *   **Line Breaking Strategy for Descriptions:**

        *   Break lines at natural word boundaries (spaces).

        *   Do NOT break words across lines.

        *   When a description for a tag (e.g., `@param`, `@return`, detailed description) exceeds the remaining space on its initial line:

            1.  Complete the word if possible within the 80-char limit.

            2.  Move the rest of the description to the next line.

            3.  The continuation line MUST start with ` * ` (space, asterisk, space) and then be indented to align with the text of the first line of that tag's description. The alignment point is typically after the tag itself.

                *   Example for `@param`:

                    ```c

                    /**

                     * @param veryLongParameterName This is a very long description

                     *                          that needs to be wrapped onto

                     *                          multiple lines for clarity.

                     * @param shortParam        A shorter description.

                     */

                    ```

                *   Example for detailed description:

                    ```c

                    /**

                     * @brief Short summary.

                     *

                     * This is the start of a very long and detailed explanation of

                     * what the function does, how it works, and any important

                     * considerations that the user of this function must be aware

                     * of before they attempt to integrate it into their own code.

                     *

                     * Another paragraph might start here, also adhering to the line

                     * limit and proper indentation for readability.

                     */

                    ```

    *   **Tooling:** Cline should internally calculate line length precisely.

  

2.  **Indentation:**

    *   The `/**` and `*/` lines should align with the indentation level of the function they document, or have no indent if at the global scope.

    *   All intermediate lines (` * ...`) should have their asterisk `*` aligned with the first asterisk of the `/**`.

  

3.  **Parameter and Exception Order:**

    *   `@param` tags must be listed in the same order as the parameters appear in the function signature.

    *   `@throw` (or `@throws`) tags can be listed in any logical order, but grouping by likelihood or severity is good practice if discernible.

  

4.  **Empty Lines:**

    *   A single empty comment line (` * `) should be used to separate the `@brief` from the detailed description (if present).

    *   A single empty comment line (` * `) can be used to separate logical groups of tags (e.g., all `@param`s from `@return`), or before a new paragraph in the detailed description, for improved readability, as long as it doesn't violate other rules.

  

5.  **Type Inference for Descriptions:**

    *   While Doxygen can often infer types, your descriptions for `@param` and `@return` should be written as if the reader might not immediately see the function signature. For example, instead of "@param data The data.", prefer "@param data A vector of integers representing user scores." (if `data` is `std::vector<int>`). The AI should infer the type from the code to write such a description.

  

---

  

## V. Cline's Workflow Steps:

  

1.  **Receive Code:** Accept the source code as input.

2.  **Parse Code:**

    *   Identify all function definitions (including constructors, destructors, template functions, member functions, static functions, free functions).

    *   For each function, extract:

        *   Function name.

        *   Return type (including `void`).

        *   Parameter list (names and types).

        *   Template parameters (if any).

        *   Explicitly thrown exceptions (requires deeper analysis, e.g., looking for `throw` statements or `noexcept(false)` in C++).

3.  **Iterate Through Functions:** Process functions one by one, in the order they appear in the source code.

4.  **For Each Function - Generate Documentation Block:**

    a.  **Initiate Block:** Start with `/**`.

    b.  **`@brief`:** Analyze the function's name, parameters, and (if possible through light semantic analysis) its body to generate a concise summary.

    c.  **Detailed Description:** If the function's logic is complex (e.g., multiple branches, loops, complex calculations, significant side-effects), generate a more detailed explanation.

    d.  **`@tparam`:** If template parameters exist, list and describe each.

    e.  **`@param`:** For each parameter, generate a description. Use its name and inferred type to guide the description.

    f.  **`@return`:** If not `void` and not a constructor/destructor, describe the return value.

    g.  **`@throw`/`@throws`:** If exception analysis reveals potential throws, document them.

    h.  **`@note`, `@warning`, `@see`:** Generate these if the AI can infer relevant information or if specific patterns are detected (e.g., use of global variables might warrant a `@note` or `@warning` about side effects). Initially, these might be harder to generate automatically without more sophisticated understanding or explicit hints. Focus on getting the core tags right first.

    i.  **`@deprecated`:** Only if the function is explicitly marked or known to be deprecated.

    j.  **Line Wrapping and Formatting:** Meticulously apply the 80-character line limit and indentation rules to all generated text within the comment block. This step is critical and must be applied *during* generation of each line.

    k.  **Terminate Block:** End with `*/`.

5.  **Assemble Output:** Concatenate all generated documentation blocks (each immediately preceding its respective function in an ideal scenario, or as a list of blocks if that's the workflow).

  

---

  

## VI. Example of AI-Generated Output:

  

**Input Code (C++):**

```c

#include <vector>

#include <string>

#include <stdexcept>

  

namespace MathUtils {

  

template<typename T>

T calculateSum(const std::vector<T>& numbers, bool& success) {

    if (numbers.empty()) {

        success = false;

        throw std::invalid_argument("Input vector cannot be empty.");

    }

    T sum = T(); // Default constructor (0 for numeric types)

    for (const T& num : numbers) {

        sum += num;

    }

    success = true;

    // Note: Potential overflow for numeric types is not handled here.

    return sum;

}

  

} // namespace MathUtils

```

  

**Cline's Generated Documentation:**

```c

/**

 * @brief Calculates the sum of all elements in a vector of numbers.

 *

 * This function iterates through the provided vector, accumulating the

 * sum of its elements. The type of the elements and the sum is

 * determined by the template parameter T. It updates a boolean flag

 * to indicate the success or failure of the operation.

 *

 * @tparam T The numeric type of the elements in the vector and the sum.

 * @param numbers A constant reference to a vector of elements of type T.

 *                The vector whose elements are to be summed.

 * @param success A reference to a boolean flag that will be set to true

 *                if the summation is successful (vector not empty),

 *                and false otherwise.

 * @return The calculated sum of the elements in the vector.

 * @throw std::invalid_argument If the input `numbers` vector is empty.

 * @note The caller is responsible for ensuring that the sum does not

 *       overflow the capacity of type T.

 * @see MathUtils::anotherRelatedFunction() // Hypothetical

 */

```

*(Self-correction: The example above shows the comment block. If the AI were to output the full code with the comment, it would be placed directly above the `template<typename T>` line.)*

  

---

  

## VII. Key Considerations for Cline's Implementation:

  

*   **Robust Parsing:** Cline needs a reliable parser for the target language(s) to accurately extract function signatures and other relevant details.

*   **Semantic Understanding (Basic):** To generate meaningful descriptions (especially for `@brief` and detailed descriptions), some level of semantic understanding of common programming constructs and naming conventions is beneficial.

*   **Configurability (Future):** While these instructions are specific, consider if Cline could eventually allow some customization (e.g., different line length, preferred Doxygen tags). For now, adhere strictly to these.

*   **Handling Edge Cases:**

    *   Functions with no parameters: No `@param` tags.

    *   `void` functions / Constructors / Destructors: No `@return` tag.

    *   Overloaded functions: Document each overload separately.

    *   Functions with very long names or many parameters: The 80-character limit will be challenging; prioritize correct line breaking..`

  

5.  **`@param <parameter_name>` (Conditional)**

    *   **Condition:** Include one `@param` tag for EACH parameter listed in the function signature.

    *   **Content:**

        *   `<parameter_name>` MUST exactly match the name in the function signature.

        *   The description should explain the parameter's role, expected values/range, units (if applicable), and any default value if not obvious.

    *   **Placement:** After `@brief`/detailed description/`@tparam`. List in the same order as the function signature.

    *   **Formatting:** ` * @param paramName Description of this parameter.`

  

6.  **`@return` (Conditional)**

    *   **Condition:** Include if the function has a non-`void` return type. OMIT entirely for `void` functions and constructors/destructors.

    *   **Content:** Describe what the returned value represents and any special conditions related to it (e.g., "Returns the calculated area. Returns -1.0 on error.").

    *   **Placement:** After all `@param` tags.

    *   **Formatting:** ` * @return Description of the return value.`

  

7.  **`@throw <ExceptionType>` or `@throws <ExceptionType>` (Conditional)**

    *   **Condition:** Include for each distinct type of exception the function might explicitly throw.

    *   **Content:**

        *   `<ExceptionType>` should be the actual type of the exception (e.g., `std::out_of_range`, `IOException`).

        *   The description should state the specific condition(s) under which this exception is thrown.

    *   **Placement:** After `@return`.

    *   **Formatting:** ` * @throw std::runtime_error If the input file cannot be opened.`

  

8.  **`@note` (Optional)**

    *   **Content:** Provide important usage information, preconditions (what must be true before calling), postconditions (what will be true after calling if successful), or non-obvious details critical for correct usage.

    *   **Placement:** Typically after `@throw`/`@throws`.

    *   **Formatting:** ` * @note This function is not thread-safe.`

  

9.  **`@warning` (Optional)**

    *   **Content:** Highlight potential dangers, critical limitations, or common mistakes developers might make when using the function.

    *   **Placement:** After `@note`.

    *   **Formatting:** ` * @warning Modifying the input array during execution leads to

 *          undefined behavior.`

  

10. **`@see <reference>` (Optional)**

    *   **Content:** Refer to other related functions, classes, documents, or concepts. This helps users find related information.

    *   **Placement:** After `@warning`.

    *   **Formatting:** ` * @see otherFunction()`

    *   **Formatting:** ` * @see MyClassName::anotherMethod`

    *   **Formatting:** ` * @see "The official algorithm specification document"`

  

11. **`@deprecated` (Conditional)**

    *   **Condition:** If the function is deprecated.

    *   **Content:** Briefly explain why it's deprecated and what alternative function or approach should be used instead.

    *   **Placement:** Usually one of the last tags.

    *   **Formatting:** ` * @deprecated This function will be removed in v3.0. Use

 *             newShinyFunction() instead.`

  

---

  

## IV. Strict Formatting Rules:

  

1.  **Maximum Line Length: 80 Characters (ABSOLUTE)**

    *   **Scope:** This limit applies to EVERY line within the `/** ... */` comment block, including leading spaces, the `*`, the tag, and the text.

    *   **Line Breaking Strategy for Descriptions:**

        *   Break lines at natural word boundaries (spaces).

        *   Do NOT break words across lines.

        *   When a description for a tag (e.g., `@param`, `@return`, detailed description) exceeds the remaining space on its initial line:

            1.  Complete the word if possible within the 80-char limit.

            2.  Move the rest of the description to the next line.

            3.  The continuation line MUST start with ` * ` (space, asterisk, space) and then be indented to align with the text of the first line of that tag's description. The alignment point is typically after the tag itself.

                *   Example for `@param`:

                    ```c

                    /**

                     * @param veryLongParameterName This is a very long description

                     *                          that needs to be wrapped onto

                     *                          multiple lines for clarity.

                     * @param shortParam        A shorter description.

                     */

                    ```

                *   Example for detailed description:

                    ```c

                    /**

                     * @brief Short summary.

                     *

                     * This is the start of a very long and detailed explanation of

                     * what the function does, how it works, and any important

                     * considerations that the user of this function must be aware

                     * of before they attempt to integrate it into their own code.

                     *

                     * Another paragraph might start here, also adhering to the line

                     * limit and proper indentation for readability.

                     */

                    ```

    *   **Tooling:** Cline should internally calculate line length precisely.

  

2.  **Indentation:**

    *   The `/**` and `*/` lines should align with the indentation level of the function they document, or have no indent if at the global scope.

    *   All intermediate lines (` * ...`) should have their asterisk `*` aligned with the first asterisk of the `/**`.

  

3.  **Parameter and Exception Order:**

    *   `@param` tags must be listed in the same order as the parameters appear in the function signature.

    *   `@throw` (or `@throws`) tags can be listed in any logical order, but grouping by likelihood or severity is good practice if discernible.

  

4.  **Empty Lines:**

    *   A single empty comment line (` * `) should be used to separate the `@brief` from the detailed description (if present).

    *   A single empty comment line (` * `) can be used to separate logical groups of tags (e.g., all `@param`s from `@return`), or before a new paragraph in the detailed description, for improved readability, as long as it doesn't violate other rules.

  

5.  **Type Inference for Descriptions:**

    *   While Doxygen can often infer types, your descriptions for `@param` and `@return` should be written as if the reader might not immediately see the function signature. For example, instead of "@param data The data.", prefer "@param data A vector of integers representing user scores." (if `data` is `std::vector<int>`). The AI should infer the type from the code to write such a description.

  

---

  

## V. Cline's Workflow Steps:

  

1.  **Receive Code:** Accept the source code as input.

2.  **Parse Code:**

    *   Identify all function definitions (including constructors, destructors, template functions, member functions, static functions, free functions).

    *   For each function, extract:

        *   Function name.

        *   Return type (including `void`).

        *   Parameter list (names and types).

        *   Template parameters (if any).

        *   Explicitly thrown exceptions (requires deeper analysis, e.g., looking for `throw` statements or `noexcept(false)` in C++).

3.  **Iterate Through Functions:** Process functions one by one, in the order they appear in the source code.

4.  **For Each Function - Generate Documentation Block:**

    a.  **Initiate Block:** Start with `/**`.

    b.  **`@brief`:** Analyze the function's name, parameters, and (if possible through light semantic analysis) its body to generate a concise summary.

    c.  **Detailed Description:** If the function's logic is complex (e.g., multiple branches, loops, complex calculations, significant side-effects), generate a more detailed explanation.

    d.  **`@tparam`:** If template parameters exist, list and describe each.

    e.  **`@param`:** For each parameter, generate a description. Use its name and inferred type to guide the description.

    f.  **`@return`:** If not `void` and not a constructor/destructor, describe the return value.

    g.  **`@throw`/`@throws`:** If exception analysis reveals potential throws, document them.

    h.  **`@note`, `@warning`, `@see`:** Generate these if the AI can infer relevant information or if specific patterns are detected (e.g., use of global variables might warrant a `@note` or `@warning` about side effects). Initially, these might be harder to generate automatically without more sophisticated understanding or explicit hints. Focus on getting the core tags right first.

    i.  **`@deprecated`:** Only if the function is explicitly marked or known to be deprecated.

    j.  **Line Wrapping and Formatting:** Meticulously apply the 80-character line limit and indentation rules to all generated text within the comment block. This step is critical and must be applied *during* generation of each line.

    k.  **Terminate Block:** End with `*/`.

5.  **Assemble Output:** Concatenate all generated documentation blocks (each immediately preceding its respective function in an ideal scenario, or as a list of blocks if that's the workflow).

  

---

  

## VI. Example of AI-Generated Output:

  

**Input Code (C++):**

```c

#include <vector>

#include <string>

#include <stdexcept>

  

namespace MathUtils {

  

template<typename T>

T calculateSum(const std::vector<T>& numbers, bool& success) {

    if (numbers.empty()) {

        success = false;

        throw std::invalid_argument("Input vector cannot be empty.");

    }

    T sum = T(); // Default constructor (0 for numeric types)

    for (const T& num : numbers) {

        sum += num;

    }

    success = true;

    // Note: Potential overflow for numeric types is not handled here.

    return sum;

}

  

} // namespace MathUtils

```

  

**Cline's Generated Documentation:**

```c

/**

 * @brief Calculates the sum of all elements in a vector of numbers.

 *

 * This function iterates through the provided vector, accumulating the

 * sum of its elements. The type of the elements and the sum is

 * determined by the template parameter T. It updates a boolean flag

 * to indicate the success or failure of the operation.

 *

 * @tparam T The numeric type of the elements in the vector and the sum.

 * @param numbers A constant reference to a vector of elements of type T.

 *                The vector whose elements are to be summed.

 * @param success A reference to a boolean flag that will be set to true

 *                if the summation is successful (vector not empty),

 *                and false otherwise.

 * @return The calculated sum of the elements in the vector.

 * @throw std::invalid_argument If the input `numbers` vector is empty.

 * @note The caller is responsible for ensuring that the sum does not

 *       overflow the capacity of type T.

 * @see MathUtils::anotherRelatedFunction() // Hypothetical

 */

```

*(Self-correction: The example above shows the comment block. If the AI were to output the full code with the comment, it would be placed directly above the `template<typename T>` line.)*

  

---

  

## VII. Key Considerations for Cline's Implementation:

  

*   **Robust Parsing:** Cline needs a reliable parser for the target language(s) to accurately extract function signatures and other relevant details.

*   **Semantic Understanding (Basic):** To generate meaningful descriptions (especially for `@brief` and detailed descriptions), some level of semantic understanding of common programming constructs and naming conventions is beneficial.

*   **Configurability (Future):** While these instructions are specific, consider if Cline could eventually allow some customization (e.g., different line length, preferred Doxygen tags). For now, adhere strictly to these.

*   **Handling Edge Cases:**

    *   Functions with no parameters: No `@param` tags.

    *   `void` functions / Constructors / Destructors: No `@return` tag.

    *   Overloaded functions: Document each overload separately.

    *   Functions with very long names or many parameters: The 80-character limit will be challenging; prioritize correct line breaking.