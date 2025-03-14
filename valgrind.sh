#!/bin/bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind_output.txt ./your_program

