#ifndef MATRIX_CREATOR_H_INCLUDED
#define MATRIX_CREATOR_H_INCLUDED

void itialization(FILE *conf,int *size, int *z);
char **creator(int size,FILE *conf, struct Play *zombies);
void draw(int size, char **matrix);

#endif // MATRIX_CREATOR_H_INCLUDED
