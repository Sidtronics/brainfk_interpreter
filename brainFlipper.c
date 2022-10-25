/*

 Description: brainf*ck interpreter. Takes one argument which is path to brainf*ck source file.
 Author: Siddhesh Dharme
 License:

 The MIT License (MIT)

 Copyright (c) 2022 Siddhesh Dharme

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.

*/

#include <stdio.h>
#include <stdbool.h>

#define TAPE_SIZE 30000

char pmem[TAPE_SIZE] = {0};
char* ptr = pmem;
FILE* src;
        
bool processCmd(signed char cmd);

int main(int argc, char* argv[]) {
    
    if(argc != 2) return 1; 

    src = fopen(argv[1], "r");

    while(processCmd(getc(src)));

    fclose(src);
}

bool processCmd(signed char cmd) {

    long int loop_start;

    switch (cmd) {
            
            case '>':
                ++ptr;
                break;

            case '<':
                --ptr;
                break;

            case '+':
                ++(*ptr);
                break;

            case '-':
                --(*ptr);
                break;

            case '.':
                putchar(*ptr);
                break;

            case ',':
                *ptr = getchar();
                break;

            case '[':
                loop_start = ftell(src);
                while(*ptr) {
                    fseek(src, loop_start, SEEK_SET);
                    while(processCmd(getc(src)));
                }
                break;

            case ']':
                return false;

            case EOF:
                return false;

            default:
                break;
    }
    return true;
}