# GNL Tester

This tester is designed to help you test your implementation of the `get_next_line` function. It provides a variety of test cases to ensure your function works correctly under different scenarios.

## Usage

To use this tester, follow the steps below:

1. **Clone the repository:**

   ```sh
   git clone <repository_url>
   cd Universe42/Testor/gnl_tester
   ```

2. **Compile the tester:**

   Use the provided Makefile to compile the tester. Simply run:

   ```sh
   make
   ```

3. **Run the tests:**

   After compiling, you can run the tests by executing the generated binary:

   ```sh
   ./gnl_tester
   ```

   The tester will run a series of tests with different buffer sizes and display the results.

## Test Cases

The tester includes a variety of test cases located in the `test_cases` directory. Each test case has a corresponding expected output file in the `expected_output` directory. The tester will compare the output of your `get_next_line` function with the expected output to determine if the test passes.

## Program Examples

If you want to see examples of how to test your `get_next_line` function, you can refer to the `examples` directory. It contains sample programs that demonstrate how to use the tester with different buffer sizes and test cases.

## Custom Tests

You can add your own test cases by placing input files in the `test_cases` directory and their corresponding expected output files in the `expected_output` directory. The tester will automatically include them in the test run.

## Cleaning Up

To clean up the compiled files, you can run:

```sh
make clean
```
This will remove the generated binary and object files.
## License
This project is licensed under the MIT License. See the [LICENSE](../LICENSE) file for details.
Happy testing!