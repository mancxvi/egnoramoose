#ifndef EGNORAMOOSE_H
#define EGNORAMOOSE_H

enum loc { U_LEFT, U_RIGHT, L_LEFT, L_RIGHT };

struct eg_row
{
    int length;
    int *nodes;
};

typedef struct eg
{
    int size;
    struct eg_row **rows;
} Eg;

struct eg_row *eg_row_make(int len);
void eg_row_destroy(struct eg_row *r);
void eg_row_print(struct eg_row *r);

Eg *eg_make(int sz, int srow, int scol);
void eg_destroy(Eg *e);
void eg_print(Eg *e);

int eg_check(Eg *e, int row, int col);
int eg_set(Eg *e, int row, int col);
int eg_clear(Eg *e, int row, int col);
int eg_jump(Eg *e, int row, int col, enum loc dir);

#endif /* EGNORAMOOSE_H */
