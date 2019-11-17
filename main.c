#include<stdlib.h>
#include<stdio.h>
#include "Matrix_creator.h"


int main(){

	/*Etapa de inicialização e criação da matriz*/

	FILE *conf;

	conf = fopen("config.txt","r");

		if (conf == NULL)
		{
			printf("ERRO! O arquivo 'config.txt' de path: nao foi aberto!\n");
			system("exit");
		}


	int size = 0, z = 0;

	char ** matrix;
	
	Play person;
	Play *zombie = NULL;

	zombie = initialization(conf, &size, &z);

	matrix = creator(size, conf, zombie, z, &person);
	
	fclose(conf);
	
	//loop

	int turnos = 0;

		do{
			system("clear");
			draw(size,matrix);
			move(matrix, zombie, &person,z);
		
			turnos++;

		}while(1);

	return 0;
}
