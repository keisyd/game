#ifndef MATRIX_CREATOR_H_INCLUDED
#define MATRIX_CREATOR_H_INCLUDED



typedef struct 
{
    int ID, xi, yi,xf,yf; // initial and final position
    int px, py;	//previous position
    float Distance;

}Play;

Play *initialization(FILE *conf,int *size, int *z);
char **creator(int size,FILE *conf, Play *zombies, int z, Play *person);
void draw(int size, char **matrix);
void move(char **matrix,  Play *zombie, Play *person, int z);
void analysis(Play person, Play *zombie, int z, int condition);
int verify(Play *zombie, Play person, int size, int z, int *condition);


#endif // MATRIX_CREATOR_H_INCLUDED
