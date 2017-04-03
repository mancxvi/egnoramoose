#include <stdio.h>
#include <string.h>

#include "egnoramoose.h"

#define COMMAND_BUFSZ 10

void print_usage(void);

int main(int argc, char *argv[])
{
    int size;
    int srow = 0;
    int scol = 0;
    if (argc == 1) {
        size = 5;
    }
    if (argc > 4) {
        fprintf(stderr, "Too many arguments\n");
        print_usage();
        return -1;
    }
    else if (argc > 1) {
        if (sscanf(argv[1], "%d", &size) != 1) {
            fprintf(stderr, "Invalid arguments\n");
            print_usage();
            return -1;
        }
        if (argc == 4) {
            if (sscanf(argv[2], "%d", &srow) != 1 ||
                sscanf(argv[3], "%d", &scol) != 1) {
                fprintf(stderr, "Invalid arguments\n");
                print_usage();
                return -1;
            }
        }
    }

    Eg *eg = eg_make(size, srow, scol);
    char buffer[COMMAND_BUFSZ];
    int exit_status = 0;

    do {
        eg_print(eg);
        printf("\n(J)ump, (N)ew, (Q)uit: ");
        fgets(buffer, COMMAND_BUFSZ, stdin);
        if (!strncmp(buffer, "J", COMMAND_BUFSZ) ||
            !strncmp(buffer, "j", COMMAND_BUFSZ)) {
            printf("Enter row and column to jump to: ");
        }
    } while (exit_status == 0);

    eg_destroy(eg);
    return 0;
}

void print_usage(void)
{
    fprintf(stderr, "Eg-no-ra-moose, a Cracker Barrel boredom simulator\n\n"
            "usage: `egnoramoose [SIZE] [SROW] [SCOL]`\n");
}
