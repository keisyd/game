#include<stdlib.h>
#include<stdio.h>
#include "Matrix_creator.h"
#include<math.h>
#include <string.h> //necessário para strcpy


int main(int argc, char *argv[]){

	/*Etapa de inicialização e criação da matriz*/

	int size = 0, z = 0,canGo=0;

	char ** matrix;
	
	Play person;

	Play *zombie = NULL;

	zombie = initialization(&size, &z, argv, &canGo, &person);
	
	if(canGo)
		return 0;

	matrix = creator(size, zombie, z, &person);	
	
	
	//loop
	
		int turns = 2, condition; 
		//turns é 2 para o primeiro ciclo correr bem sem perda de informação ao final do último ciclo, 
		canGo = 0;
		//desenho do primeiro ciclo
		system("clear"); 

		draw(size,matrix, &turns);

		while(verify(zombie, person, size, z, &condition))
		{
					
			do//escolha uma letra até que alguma letra valida seja escolhida
			{
				movePerson(matrix, &person, &canGo, zombie, z);
				
				if(canGo)	
					printf("\nEscolha uma letra valida"); 

			}while(canGo);
			
			moveZombie(matrix, zombie, &person, z);//movendo zombies

			system("clear"); //limpar a tela
			
			draw(size,matrix, &turns); //desenhar a matriz movida

			turns++;

		}
	
	analysis(person, zombie, z, condition, turns);
	
	return 0;
}
