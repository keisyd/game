#ifndef MATRIX_CREATOR_H_INCLUDED
#define MATRIX_CREATOR_H_INCLUDED


typedef struct 
{
    int ID, xi, yi,xf,yf; // initial and final position
    int px, py;	//previous position
    float Distance;
    char PlayerName[20];

}Play;

Play *initialization(int *size, int *z, char **argv, int *canGo, Play *person);
char **creator(int size, Play *zombies, int z, Play *person);
void draw(int size, char **matrix, int *turns);
void moveZombie(char **matrix, Play *zombie, Play *person, int z);
void movePerson(char **matrix, Play *person, int *canGo);
void analysis(Play person, Play *zombie, int z, int condition, int turns);
int verify(Play *zombie, Play person, int size, int z, int *condition);


#endif // MATRIX_CREATOR_H_INCLUDED
