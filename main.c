#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "egnoramoose.h"

#define COMMAND_BUFSZ 10

void print_usage(void);
void game_loop(Eg *e);

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

    game_loop(eg);
    eg_destroy(eg);
    return 0;
}

void game_loop(Eg *e)
{
    char buffer[COMMAND_BUFSZ];
    int exit_status = 0;

    do {
        printf("\033[2J\033[;H");
        eg_print(e);
        printf("\n(J)ump, (N)ew, (Q)uit: ");
        fgets(buffer, COMMAND_BUFSZ, stdin);
        char command = toupper(buffer[0]);
        switch (command) {
        case 'J':
            printf("Enter row and column to jump: ");
            fgets(buffer, COMMAND_BUFSZ, stdin);
            int jrow;
            int jcol;
            if (sscanf(buffer, "%d%d", &jrow, &jcol) != 2) {
                printf("Please enter two numbers\n");
            }
            else {
                printf("Enter direction (L), (R), (UL), (UR), (LL), (LR): ");
                fgets(buffer, COMMAND_BUFSZ, stdin);
                for (unsigned long i = 0; i < strlen(buffer); i++) {
                    buffer[i] = toupper(buffer[i]);
                }
                if (!strcmp(buffer, "L\n")) {
                    eg_jump(e, jrow, jcol, LEFT);
                }
                if (!strcmp(buffer, "R\n")) {
                    eg_jump(e, jrow, jcol, RIGHT);
                }
                if (!strcmp(buffer, "UL\n")) {
                    eg_jump(e, jrow, jcol, U_LEFT);
                }
                else if (!strcmp(buffer, "UR\n")) {
                    eg_jump(e, jrow, jcol, U_RIGHT);
                }
                else if (!strcmp(buffer, "LL\n")) {
                    eg_jump(e, jrow, jcol, L_LEFT);
                }
                else if (!strcmp(buffer, "LR\n")) {
                    eg_jump(e, jrow, jcol, L_RIGHT);
                }
                else {
                    printf("Please enter a valid direction\n");
                }
            }
            break;
        case 'N':
            printf("Please enter a size: ");
            int nsize = 0;
            int nrow = 0;
            int ncol = 0;
            fgets(buffer, COMMAND_BUFSZ, stdin);
            if (sscanf(buffer, "%d", &nsize) != 1) {
                printf("Size must be a number\n");
            }
            printf("Please enter starting coordinates: ");
            fgets(buffer, COMMAND_BUFSZ, stdin);
            if (sscanf(buffer, "%d %d", &nrow, &ncol) != 2) {
                printf("Coordinates must be numbers");
            }
            Eg *new = eg_make(nsize, nrow, ncol);
            if (new == NULL) {
                printf("Invalid values entered for new board\n");
            }
            else {
                eg_destroy(e);
                e = new;
            }
            break;
        case 'Q':
            printf("Thank you for playing!\n");
            exit_status = 1;
        }
        if (eg_check_if_any_jumps(e) == 0) {
            printf("\033[2J\033[;H");
            eg_print(e);
            printf("Game over!\n");
            exit_status = 1;
        }
    } while (exit_status == 0);
}

void print_usage(void)
{
    fprintf(stderr, "Eg-no-ra-moose, a Cracker Barrel boredom simulator\n\n"
            "usage: `egnoramoose [SIZE] [SROW] [SCOL]`\n");
}
