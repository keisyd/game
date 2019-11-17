#include<stdlib.h>
#include<stdio.h>
#include "Matrix_creator.h"

void red() { //impressão vermelho
printf("\033[1;31m");
}
void green() { //impressão verde
printf("\033[1;32m");
}
void yellow() { //impressão amarelo
printf("\033[0;33m");
}
void yellow_bold() { //impressão amarelo negrito
printf("\033[1;33m");
}
void reset() { //reseta para o padrão de cor normal.
printf("\033[0m");
}



Play *initialization(FILE *conf,int *size, int *z) {

	Play *zombie = NULL;

	fscanf(conf,"%d\n", size);	
	fscanf(conf,"%d\n", z);

	zombie = (Play *)malloc(sizeof(Play)*(*z));

	return zombie;
	
}

char **creator(int size, FILE *conf,  Play *zombies, int z, Play *person) {
	int p1, p2;

	// Alocação da matriz

	char **matrix = (char **)malloc(sizeof(char *)*size);

	for(int i=0; i<size; i++)
	{
		matrix[i] = (char *)malloc(sizeof(char)*size);
	}

	//Matriz toda preenchida por '*'
	for(int i=0; i<size; i++)	//Matriz toda preenchida por '*'
	{
		for(int j=0; j<size; j++)
		{
			matrix[i][j] = '*';
		}
	}

	//quantidade de zombies

	//inseindo os zumbis na matriz
	//e determinandos ID's e posições na struct

	for(int i=0; i<z; i++)
	{
		fscanf(conf,"%d %d\n",&p1, &p2);
		matrix[p1][p2] = 'Z';
		zombies[i].ID = i;
		zombies[i].yi = p1;
		zombies[i].xi = p2;
		zombies[i].yf = p1;
		zombies[i].xf = p2;

	}

	//inserir pessoa
	int c_position = size/2;

	(*person).xi = c_position;
	person->yi = c_position;
	(*person).xf = c_position;
	person->yf = c_position;
	
	matrix[c_position][c_position] = 'P';
	
	return matrix;
}

void draw(int size, char **matrix) 
{
	//essa função desenha a matriz	
	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size; j++)
		{
			switch(matrix[i][j])
			{
				case '*':
					yellow_bold();
					printf(" %c ",matrix[i][j]);
					reset();
					break;
				case 'Z':
					red();
					printf(" %c ",matrix[i][j]);
					reset();
					break;
				case 'P':
					green();
					printf(" %c ",matrix[i][j]);
					reset();
					break;
			}
		}
		printf("\n");
	}
}

void move(char **matrix, Play *zombie, Play *person, int z)
{
	char tecla;
	matrix[person->yf][person->xf] = '*';

	for(int i; i<z; i++)
	{
		
		matrix[zombie[i].yf][zombie[i].xf] ='*';

		if(person->xf < zombie[i].xf)
			zombie[i].xf--;
		else if(person->yf<zombie[i].yf)
			zombie[i].yf--;
		else if(person->xf>zombie[i].xf)
			zombie[i].xf++;
		else if(person->yf>zombie[i].yf)
			zombie[i].yf++;

		matrix[zombie[i].yf][zombie[i].xf] ='Z';
	
	}	
	scanf("%c",&tecla);
	while(getc(stdin)!='\n'){} //não aceitar mais de uma letra

	/*Cima*/
	if(tecla == 'W'|| tecla == 'w' || tecla == '8')
	{
		
		person->yf--;
		matrix[person->yf][person->xf] = 'P';		
	}
	//Baixo
	if(tecla == 'X'|| tecla == 'x' || tecla == '2')
	{
		
		person->yf++;
		matrix[person->yf][person->xf] = 'P';		
	}
	//Direita
	if(tecla == 'D'|| tecla == 'd' || tecla == '6')
	{
		
		person->xf++;
		matrix[person->yf][person->xf] = 'P';		
	}
	//Esquerda
	if(tecla == 'A'|| tecla == 'a' || tecla == '4')
	{
		
		person->xf--;
		matrix[person->yf][person->xf] = 'P';		
	}
	//Diagonal superior esquerda
	if(tecla == 'q'|| tecla == 'Q' || tecla == '7')
	{
		
		person->yf--;
		person->xf--;
		matrix[person->yf][person->xf] = 'P';		
	}
	//Diagonal superior direita
	if(tecla == 'e'|| tecla == 'E' || tecla == '9')
	{
		
		person->yf--;
		person->xf++;
		matrix[person->yf][person->xf] = 'P';		
	}
	//Diagonal inferior esquerda
	if(tecla == 'z'|| tecla == 'Z' || tecla == '1')
	{
		
		person->yf++;
		person->xf--;
		matrix[person->yf][person->xf] = 'P';		
	}
	//Diagonal inferior direita
	if(tecla == 'c'|| tecla == 'C' || tecla == '3')
	{
		
		person->yf++;
		person->xf++;
		matrix[person->yf][person->xf] = 'P';		
	}



}

//analysis(){}
