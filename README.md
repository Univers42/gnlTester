# Get Next Line Ultimate Tester

A comprehensive tester for the 42 School "get_next_line" project with beautiful visuals, real-time progress tracking, and thorough test cases.

![GNL Tester Banner](https://i.imgur.com/placeholder.png)

## Features

- **Visual Feedback**: Beautiful console UI with color-coded results
- **Comprehensive Testing**: Tests across multiple BUFFER_SIZE values
- **Real-time Progress**: Live tracking of test progress with animation
- **Detailed Results**: Clear pass/fail indicators for each test case
- **Bonus Support**: Tests for both mandatory and bonus parts

## Directory Structure

```
gnlTester/
├── header/               # Header files
│   ├── defines.h         # ANSI color codes and other definitions
│   ├── globals.h         # Global variable declarations
│   ├── test_utils.h      # Testing utility function declarations
│   ├── test_files.h      # Test file definitions
│   └── cosmetics.h       # UI element function declarations
├── helpers/              # Implementation files
│   ├── globals.c         # Global variable definitions
│   ├── test_utils.c      # Testing utility functions
│   ├── test_files.c      # Test file array implementation
│   └── cosmetics_utils.c # UI element implementations
├── programs/             # Main program files
│   ├── main.c            # Main program for mandatory part
│   └── main_bonus.c      # Main program for bonus part
├── test_cases/           # Test input files
├── expected_output/      # Expected output files
├── outputs/              # Directory for test outputs
└── Makefile              # Build system
```

## How the Tester Works

### Testing Framework

1. **File Comparison**: The core testing mechanism reads each test file with `get_next_line()`, writes the output to a temporary file, and compares it with the expected output.

2. **Progress Tracking**: For real-time progress monitoring, the tester keeps track of completed tests and total tests.

3. **Multithreading**: In "short" mode, an animation thread runs parallel to the testing thread, providing a real-time progress bar.

4. **Buffer Size Testing**: The tester automatically runs tests with multiple BUFFER_SIZE values (from 1 to 1048576) to ensure your implementation works correctly regardless of buffer size.

### Testing Modes

The tester offers two main modes:

- **Detailed Mode**: Shows results for each individual test file, perfect for debugging.
- **Short Mode**: Displays an animated progress bar, ideal for quick verification.

### Bonus Testing

The bonus tester specifically checks if your implementation can handle multiple file descriptors simultaneously, which is the key requirement of the bonus part.

## How to Use

### Installation

1. Clone this repository near your get_next_line implementation:

```bash
git clone https://github.com/yourusername/gnlTester.git
```

2. Make sure your get_next_line files are in the parent directory or update the GNL_PATH in the Makefile.

### Running Tests

**Basic Usage**:

```bash
# Compile the tester
make

# Run tests with detailed output
./tester detailed

# Run tests with animated progress bar
./tester short

# Run bonus tests
./tester_bonus
```

**Custom Buffer Size Testing**:

You can test a specific BUFFER_SIZE by recompiling with the flag:

```bash
gcc -D BUFFER_SIZE=42 -o tester main.o test_utils.o helpers/globals.o helpers/test_files.o helpers/cosmetics_utils.o ../get_next_line.c ../get_next_line_utils.c
./tester
```

### Adding Custom Tests

1. Add your test input file to `test_cases/`
2. Create the expected output file in `expected_output/` with the same name
3. Add the file pair to the TEST_FILES array in `helpers/test_files.c`

## Implementation Details

### Thread-Safe Progress Tracking

The tester uses mutex locks to ensure thread-safe updates to the progress counters:

```c
pthread_mutex_lock(&progress_mutex);
completed_tests++;
pthread_mutex_unlock(&progress_mutex);
```

### Animation System

The animation system uses ANSI escape codes for terminal control:
- Carriage return (`\r`) for updating the same line
- Color codes for visual distinction
- Unicode characters for smooth visual elements

### Test Validation

Tests are validated by comparing files byte-by-byte, with special handling for different line ending styles:

```c
int compare_files(const char *file1, const char *file2) {
    // Reads both files character by character
    // Handles different line endings (LF vs CRLF)
    // Returns 1 on match, 0 on mismatch
}
```

## Troubleshooting

### Common Issues

1. **Missing GNL Files**: Ensure your get_next_line implementation is in the parent directory or update GNL_PATH in the Makefile.

2. **Compilation Errors**: Make sure your get_next_line compiles without warnings using the same flags.

3. **Test Failures**: Check the specific failing test cases in detailed mode to understand what's wrong.

### Debugging Tips

- **Memory Leaks**: Run the tester with Valgrind to check for memory leaks.
- **Line Ending Issues**: If you're working across different OSes, be careful with line endings.
- **Edge Cases**: Pay special attention to empty files, files ending without newlines, and very large files.

## License

This project is available under the MIT License.

## Acknowledgements

- Thanks to the 42 community for inspiration and test cases
- Special thanks to contributors who helped improve this tester