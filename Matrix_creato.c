#include<stdio.h>
#include "Matrix_creator.h"
#include<stdlib.h>
struct Play {
    int ID;
    float  Distance;

};


int main(){
    struct Play *zombie=NULL;
    FILE *conf;
    conf = fopen("config.txt","r");
     if (conf == NULL){
       printf("ERRO! O arquivo 'config.txt' de path: nao foi aberto!\n");
       system("exit");
     }

    int size=0, z=0;
    char ** matrix;

    itialization(conf,&size, &z);

    zombie = (struct Play *)malloc(sizeof(struct Play)*z);

    matrix = creator(size, conf,&zombie);
    zombie[0].ID =50;
    printf("zombie[0].ID = %d", zombie[0].ID);

    draw(size,matrix);

    return 0;
    }
// play *Zombie=NULL;
   //
