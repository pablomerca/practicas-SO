#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int target;

void vuln(char *string) {
    printf(string);
    // target esta pusheado despues de string
    if (target) {
        printf("you have modified the target :)\n");
    }
}

// donde esta target que es una variable global???

int main(int argc, char **argv) {
    vuln(argv[1]);
}