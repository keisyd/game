#include<stdlib.h>
#include<stdio.h>
#include "Matrix_creator.h"
#include<math.h>

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
	printf("  ");
	for(int i=0; i<size; i++)
		printf(" %.2d",i);
		printf("\n");
	for(int i=0; i<size; i++)
	{	

		printf("%.2d",i);
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
	person->py = person->yf;           
	
	person->px = person->xf;

	for(int i =0; i<z; i++)
	{
		zombie[i].px = zombie[i].xf;

		zombie[i].py = zombie[i].yf;
	}

	char tecla;
	matrix[person->yf][person->xf] = '*';

	for(int i=0; i<z; i++)
		matrix[zombie[i].yf][zombie[i].xf] ='*';
	
	for(int i=0; i<z; i++)
	{

		if(sqrt(pow(person->xf - zombie[i].xf, 2)) > sqrt(pow(person->yf - zombie[i].yf, 2)))
		{
			if(person->xf <= zombie[i].xf)
				zombie[i].xf--;
			else if(person->xf>zombie[i].xf)
				zombie[i].xf++;

			matrix[zombie[i].yf][zombie[i].xf] ='Z';
		}

		else{
			if(person->yf<=zombie[i].yf)
				zombie[i].yf--;
			
			else if(person->yf>zombie[i].yf)
				zombie[i].yf++;

			matrix[zombie[i].yf][zombie[i].xf] ='Z';
		}

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
	else if(tecla == 'X'|| tecla == 'x' || tecla == '2')
	{
		
		person->yf++;
		matrix[person->yf][person->xf] = 'P';		
	}
	//Direita
	else if(tecla == 'D'|| tecla == 'd' || tecla == '6')
	{
		
		person->xf++;
		matrix[person->yf][person->xf] = 'P';		
	}
	//Esquerda
	else if(tecla == 'A'|| tecla == 'a' || tecla == '4')
	{
		
		person->xf--;
		matrix[person->yf][person->xf] = 'P';		
	}
	//Diagonal superior esquerda
	else if(tecla == 'q'|| tecla == 'Q' || tecla == '7')
	{
		
		person->yf--;
		person->xf--;
		matrix[person->yf][person->xf] = 'P';		
	}
	//Diagonal superior direita
	else if(tecla == 'e'|| tecla == 'E' || tecla == '9')
	{
		
		person->yf--;
		person->xf++;
		matrix[person->yf][person->xf] = 'P';		
	}
	//Diagonal inferior esquerda
	else if(tecla == 'z'|| tecla == 'Z' || tecla == '1')
	{
		
		person->yf++;
		person->xf--;
		matrix[person->yf][person->xf] = 'P';		
	}
	//Diagonal inferior direita
	else if(tecla == 'c'|| tecla == 'C' || tecla == '3')
	{
		
		person->yf++;
		person->xf++;
		matrix[person->yf][person->xf] = 'P';		
	}



}

int verify(Play *zombie, Play person, int size, int z, int *condition){
	

	for(int i=0; i<z; i++ ){
		if(zombie[i].xf == person.xf && zombie[i].yf == person.yf || (zombie[i].xf == person.px && zombie[i].yf == person.py && zombie[i].px == person.xf && zombie[i].py == person.yf))
		{
			*condition = 0; //game over
			return 0;
		}
	}
	if(person.xf == size -1 || person.yf == size -1 || person.xf == 0 || person.yf == 0){
			*condition = 1; //you win
			return 0;
	}

	return 1;

}

void analysis(Play person, Play *zombie, int z, int condition){

	if(condition == 0){

		system("clear");

		printf("                                      Voce perdeu :(\n");
	}
	else{d
		

		system("clear");

		printf("                                          Voce ganhou :)\n");
	}

	for(int i=0; i<z; i++)
		printf("\nZombie %d :\nZ.xf: %d Z.yf: %d\n",i, zombie[i].xf, zombie[i].yf);
	
		printf("\nP.xf: %d P.yf: %d", person.xf, person.yf);

}
