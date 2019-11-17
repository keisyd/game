#ifndef MATRIX_CREATOR_H_INCLUDED
#define MATRIX_CREATOR_H_INCLUDED


typedef struct 
{
    int ID, xi, yi,xf,yf;
    float Distance;

}Play;

Play *initialization(FILE *conf,int *size, int *z);
char **creator(int size,FILE *conf, Play *zombies, int z, Play *person);
void draw(int size, char **matrix);
void move(char **matrix,  Play *zombie, Play *person, int z);
#endif // MATRIX_CREATOR_H_INCLUDED
