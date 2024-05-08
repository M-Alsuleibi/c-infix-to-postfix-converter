## Infix to Postfix Converter

This repository contains a C program that converts infix expressions to postfix expressions. Infix expressions are the standard mathematical expressions we're used to (e.g., `3 + 4 * 2`). Postfix expressions, also known as Reverse Polish Notation (RPN), place the operator after their operands (e.g., `3 4 2 * +`).

### Features

- Converts infix expressions to postfix expressions.
- Supports the basic arithmetic operators: `+`, `-`, `*`, `/`, `div`, and `mod`.
- Handles parentheses to ensure proper operator precedence.

### How to Use

1. Clone the repository to your local machine.
2. Compile the program using any C compiler (e.g., `gcc`).
3. Run the compiled executable.
4. Enter infix expressions at the prompt. Separate operands and operators with spaces. For example: `3 + 4 * 2`.

### Example

Input:
```
3 + 4 * 2;
10 mod 3 + 8 div 2 ;
```

Output:
```
3 4 2 * +
103MOD82DIV+
```
### Reference:
This code is based on [Chapter 2](https://drive.google.com/file/d/1MqXruiM849l0Eix4f5jot6pyy-fcVgOs/view?usp=sharing) of the book "[Compilers: Principles, Techniques, and Tools](https://libgen.is/book/index.php?md5=346B2177C8F721EE62872DCAF64B9F85)" by Alfred V. Aho, Ravi Sethi, and Jeffrey D. Ullman, published by Addison-Wesley in 1986.

### Contributing

Contributions are welcome! If you find any issues or have suggestions for improvements, feel free to open an issue or submit a pull request.

### License

This project is licensed under the [MIT License](LICENSE).

---