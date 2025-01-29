# DLP-DHKE: Discrete Logarithm Problem and Diffie-Hellman Key Exchange

This repository contains a C implementation of the Discrete Logarithm Problem (DLP) and an example of how it can be used in the context of the Diffie-Hellman Key Exchange (DHKE). The code includes two approaches to solving the discrete logarithm problem: one based on modular arithmetic and another based on elliptic curves.

## Requirements

To compile and run this code, you will need:

- **GCC** (GNU Compiler Collection) to compile the C code.
- **GMP** (GNU Multiple Precision Arithmetic Library) to handle arithmetic operations with large numbers.

### Installing Dependencies

On Debian/Ubuntu-based systems, you can install the dependencies with the following commands:

```bash
sudo apt-get update
sudo apt-get install build-essential libgmp-dev
```

## Compilation

To compile the code, follow these steps:

1. Clone the repository or download the `dlp-dhke.c` file.
2. Navigate to the directory where the file is located.
3. Compile the code using GCC:

```bash
gcc -o dlp-dhke dlp-dhke.c -lgmp -lm
```

This will generate an executable named `dlp-dhke`.

## Execution

Once compiled, you can run the program with the following command:

```bash
./dlp-dhke
```

### Example Usage

The program performs two types of discrete logarithm searches:

1. **Discrete Logarithm Search in Modular Arithmetic**:
   - The program attempts to solve equations of the form \( g^x \equiv \beta \ (\text{mod} \ p) \) for different values of \( g \), \( \beta \), and \( p \).

2. **Discrete Logarithm Search in Elliptic Curves**:
   - The program attempts to solve equations of the form \( xG = P \) on elliptic curves defined over finite fields.

#### Expected Output

The program will print the results of the searches to the console, including the time it took to find each solution (if it exists). Here is an example of the output:

```
Searching...
Solution for 5^x ≡ 9012 (mod 10007): x = 1234
Logarithm found in 0.123456 seconds

Searching in curve E(1, 9) over GF(113)...
Solution for xG(47:22:1) = P(52:53:1): x = 5678
Logarithm found in 0.234567 seconds
```

## Code Structure

- **`mod_exp`**: Implements modular exponentiation.
- **`brute_force_logarithm`**: Implements a brute-force search to solve the discrete logarithm problem in modular arithmetic.
- **`ec_brute_force_logarithm`**: Implements a brute-force search to solve the discrete logarithm problem in elliptic curves.
- **`main`**: Contains usage examples and the logic to test the above functions.

## Contributions

If you would like to contribute to this project, feel free to fork the repository and submit a pull request with your improvements. Make sure to follow best coding practices and document any significant changes.

## Contact

If you have any questions or suggestions, please don't hesitate to reach out to me through my GitHub profile.

