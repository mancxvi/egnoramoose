#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "egnoramoose.h"

struct eg_row *eg_row_make(int len)
{
    struct eg_row *new_row = malloc(sizeof (struct eg_row));
    new_row->length = len;
    new_row->nodes = malloc(sizeof (int) * len);
    for (int i = 0; i < new_row->length; i++) {
        new_row->nodes[i] = 1;
    }

    return new_row;
}

void eg_row_destroy(struct eg_row *r)
{
    free(r->nodes);
    free(r);
}

void eg_row_print(struct eg_row *r)
{
    for (int i = 0; i < r->length; i++) {
        if (r->nodes[i] == 1) {
            printf("X ");
        }
        else if (r->nodes[i] == 0) {
            printf("  ");
        }
    }
}

Eg *eg_make(int sz, int srow, int scol)
{
    Eg *new_eg = malloc(sizeof (Eg));
    new_eg->size = sz;

    new_eg->rows = malloc(sizeof (struct eg_row *) * sz);
    for (int i = 0; i < sz; i++) {
        new_eg->rows[i] = eg_row_make(i+1);
    }

    new_eg->rows[srow]->nodes[scol] = 0;

    return new_eg;
}

void eg_destroy(Eg *e)
{
    for (int i = 0; i < e->size; i++) {
        eg_row_destroy(e->rows[i]);
    }
}

void eg_print(Eg *e)
{
    for (int i = 0; i < e->size; i++) {
        for (int j = 0; j < e->size - i; j++) {
            printf(" ");
        }
        eg_row_print(e->rows[i]);
        printf("\n");
    }
}

int eg_check(Eg *e, int row, int col)
{
    if (row > e->size || col > e->size || col > row) {
        fprintf(stderr, "Invalid pin selected\n");
        return -1;
    }

    return e->rows[row]->nodes[col];
}

int eg_set(Eg *e, int row, int col)
{
    int current = eg_check(e, row, col);
    if (current < 0) {
        return -1;
    }
    else if (current == 1) {
        fprintf(stderr, "Pin (%d, %d) already set\n", row, col);
        return -1;
    }
    else {
        e->rows[row]->nodes[col] = 1;
    }
    return 0;
}

int eg_clear(Eg *e, int row, int col)
{
    int current = eg_check(e, row, col);
    if (current < 0) {
        return -1;
    }
    else if (current == 0) {
        fprintf(stderr, "Pin (%d, %d) already clear", row, col);
        return -1;
    }
    else {
        e->rows[row]->nodes[col] = 0;
    }
    return 0;
}
