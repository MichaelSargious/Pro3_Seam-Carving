#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


unsigned int factorial(int n);
unsigned int gaussian_sum(int n);


int main(int argc, char* argv[]) {
    int option;

    while((option = getopt(argc, argv, "f:g:")) != -1) {
        switch(option) {
            case 'f':
                printf("factorial(%d) = %u\n", atoi(optarg), factorial(atoi(optarg)));
                break;

            case 'g':
                printf("gaussian_sum(%d) = %u\n", atoi(optarg), gaussian_sum(atoi(optarg)));
                break;

            default:
                fprintf(stderr, "Usage: %s [-f value] [-g value]\n", argv[0]);
                return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}


unsigned int factorial(int n) {
    assert(n >= 0);

    if(n > 1) {
        return n * factorial(n - 1);
    } else {
        return 1;
    }
}


unsigned int gaussian_sum(int n) {
    assert(n >= 0);

    return n * (n + 1) / 2;
}
