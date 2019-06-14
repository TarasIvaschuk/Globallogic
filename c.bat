@echo off
gcc -std=c11 -Wall -fmax-errors=10 -Wextra %1.c -o %1.exe
timeout 5
