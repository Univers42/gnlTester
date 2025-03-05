# GNL Tester

This tester is designed to help you validate your implementation of the `get_next_line` function. It provides a variety of test cases to ensure your function handles different scenarios correctly.

## Project Structure

- **bigfiles**: (Beta) Currently unused, reserved for future test sequences.
- **examples**: (Beta) Contains sample outputs to illustrate expected behavior.
- **expected_output**: Stores the reference output files for comparison.
- **header**: Provides organization for the implementation due to its complexity.
- **helpers**: Contains functions and logic that support the program's execution.
- **outputs**: Stores logs; if errors occur, they will be recorded here.
- **programs**: If issues arise with the tester, they may originate from this directory.
- **test_cases**: Contains various edge cases to thoroughly test your function.

## Usage

To use this tester, follow these steps:

### 1. Clone the Repository

```sh
cd <path_to_project_root>
git clone <repository_url>
cd gnl_tester
```

### 2. Compile the Tester

Use the provided Makefile to compile the tester:

```sh
# Compile all functions in NORMAL mode
make

# Compile all functions in STRICT mode
make MODE=strict
```

### 3. Run the Tests

After compilation, execute the following commands to run the tests:

```sh
# Run mandatory part
test make m

# Run bonus part
make b

#I advice you to use the program you have currently two mode
# short
# detailed
./tester short
./tester_bonus short 
# or
./tester detailed
./tester_bonus detailed

```

The tester will execute multiple test cases with different buffer sizes and display the results.
### `./tester short`
![image](https://github.com/user-attachments/assets/a8fb9a27-5835-4abe-9c1a-b41c43c55898)
### `./tester detailed`
![image](https://github.com/user-attachments/assets/0c35f808-0438-4cb6-92eb-667491395fb8)
> and globally it does the same with the bonus version
### `when you compile it has this behavior`
![image](https://github.com/user-attachments/assets/db752624-1b56-4fc1-8326-78ee40ff74bc)

## Test Cases

The `test_cases` directory includes various test cases, each with a corresponding expected output file in `expected_output`. The tester compares your `get_next_line` function’s output against these files to determine pass or fail status.

## Program Examples

To see how `get_next_line` should behave, refer to the `examples` directory. It contains sample programs demonstrating how to test different buffer sizes and scenarios.

## Custom Tests

To add your own test cases, place input files in the `test_cases` directory and their corresponding expected output files in `expected_output`. The tester will automatically include them in the test run.

## Cleaning Up

To remove compiled binaries and object files, run:

```sh
make fclean
```

## License
This project is licensed under the MIT License. See the [LICENSE](../LICENSE) file for details.

Happy testing!
