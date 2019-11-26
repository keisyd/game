#include<stdlib.h>
#include<stdio.h>
#include "Matrix_creator.h"
#include<math.h>
#include <string.h> //necessário para strcpy

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




Play *initialization(int *size, int *z,char **argv, int *canGo, Play *person) 
{	
	//Lê no arquivo o tamnho da matrix, cria, determina e retorna struct com as posições dos zombies e suas respectivas IDs

	FILE *conf;

	system("clear");
	printf("\n\n\nA string argv%s\n",argv[1]);


		strcat(argv[1],"/config.txt");

	conf = fopen(argv[1],"r");

		if (conf == NULL)
		{
			printf("ERRO! O arquivo 'config.txt' de path:%s nao foi aberto!\n",argv[1]);
			*canGo = 1;
			exit(0);

		}

	Play *zombie = NULL;

	int p1, p2;

	fscanf(conf,"%d\n", size);

	fscanf(conf,"%d\n", z);

	zombie = (Play *)malloc(sizeof(Play)*(*z));

	for(int i=0; i<(*z); i++)
	{
		fscanf(conf,"%d %d\n",&p1, &p2);
		zombie[i].ID = i;
		zombie[i].yi = p1;
		zombie[i].xi = p2;
		zombie[i].yf = p1;
		zombie[i].xf = p2;

	}


	fclose(conf);

	printf("\n\n\nDigite seu nome\n\n\n");


	scanf("%s", person->PlayerName);

	while(getc(stdin)!='\n'){} 

	return zombie;
	
}

char **creator(int size,  Play *zombie, int z, Play *person) 
{
	
	int p1, p2;

	// Alocação da matriz

	char **matrix = (char **)malloc(sizeof(char *)*size);

	for(int i=0; i<size; i++)
	{
		matrix[i] = (char *)malloc(sizeof(char)*size);
	}


	//Matriz toda preenchida por '*'
	for(int i=0; i<size; i++)	
	{
		for(int j=0; j<size; j++)
		{
			matrix[i][j] = '*';
		}
	}


	//inseindo os zumbis na matriz pelas posições na struct
	for(int i=0; i<z; i++)
		matrix[zombie[i].yf][zombie[i].xf] ='Z';


	//Determinar posição na struct e inserir pessoa
	int c_position = size/2;

	(*person).xi = c_position;
	person->yi = c_position;
	(*person).xf = c_position;
	person->yf = c_position;
	
	matrix[c_position][c_position] = 'P';
	
	return matrix;
}

void draw(int size, char **matrix, int *turns) 
{
	//essa função desenha a matriz

	//para os turnos acesos
	if(*turns%3 != 0) 
	{
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

	//para o apagão
	else 
	{	
		
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
					case 'P':
					green();
					printf(" %c ",matrix[i][j]);
					reset();
					break;

					default:
					yellow();
					printf(" * ");
					reset();
					break;
				}
			}
			printf("\n");
		}
	}
}

 void moveZombie(char **matrix, Play *zombie, Play *person, int z)
{	
	//essa função faz os movimentos 

	//primeiro alocando as informações de poisção como 'py e px' prévias posições x e y 
	person->py = person->yf;           
	
	person->px = person->xf;

	

	for(int i =0; i<z; i++)
	{
		zombie[i].px = zombie[i].xf;

		zombie[i].py = zombie[i].yf;
	}

	// limpando a posição da pessoa e dos zombies
	matrix[person->yf][person->xf] = '*';

	for(int i=0; i<z; i++)
		matrix[zombie[i].yf][zombie[i].xf] ='*';
	
	// Para todo zombie
	for(int i=0; i<z; i++)
	{
		//como o movimento é ortogonal, uma forma de garantir uma aproximação orgânica é:
		if(sqrt(pow(person->xf - zombie[i].xf, 2)) > sqrt(pow(person->yf - zombie[i].yf, 2)))
		{//se a distancia em x for maior que a distancia em y haverá 
			if(person->xf <= zombie[i].xf) // se pessoa estiver a esquerda
				zombie[i].xf--; // movimento para esquerda em x
			else if(person->xf>zombie[i].xf)//se tiver a direita
				zombie[i].xf++;// para direita em x

			matrix[zombie[i].yf][zombie[i].xf] ='Z';
		}

		else{// caso contrário
			if(person->yf<=zombie[i].yf)// se estive acima
				zombie[i].yf--;//para acima em y
			
			else if(person->yf>zombie[i].yf)//se estiver abaixo
				zombie[i].yf++;//ou para baixo em Y

			matrix[zombie[i].yf][zombie[i].xf] ='Z';
		}

		matrix[zombie[i].yf][zombie[i].xf] ='Z';//alocação do zombie
	}
}

void movePerson(char **matrix, Play *person, int *canGo)
{
	char tecla; 


	//recebendo, então o que foi digitado,
	scanf("%c",&tecla);
	while(getc(stdin)!='\n'){} //garantido que apenas a primeira letra será utilizada

		//então movendo-o para
	*canGo = 0;
	
	//Cima
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
	else
	{
		*canGo = 1;
	}

}


int verify(Play *zombie, Play person, int size, int z, int *condition){
	// essa função indica se o jogo deve continuar ou não

	//o jogo acaba...
	for(int i=0; i<z; i++ ){//havendo captura ou troca de posição para qualquer dos zombies
		if(zombie[i].xf == person.xf && zombie[i].yf == person.yf || (zombie[i].xf == person.px && zombie[i].yf == person.py && zombie[i].px == person.xf && zombie[i].py == person.yf))
		{
			*condition = 0; //game over
			return 0;
		}
	}

	//no caso de P alnçar a parede,
	if(person.xf == size -1 || person.yf == size -1 || person.xf == 0 || person.yf == 0){
			*condition = 1; //you win
			return 0;
	}

	//caso contrário, o jogo continua
	return 1;

}

void analysis(Play person, Play *zombie, int z, int condition, int turns){
	
	/*o ID do zumbi que mais andou (distância entre a posição inicial e a posição
	no fim do jogo),
	o ID do zumbi que menos andou (distância entre a posição inicial e a posição
	no fim do jogo),
	o ID do zumbi ficou mais distante do jogador,
	o ID do zumbi ficou mais próximo do jogador (caso o jogador ganhe a
	partida),
	a soma total da distância percorrida por todos os zumbis,
	quantos turnos o jogo teve até o seu término,
	quantas posições o jogador percorreu até ganhar ou perder o jogo.
	*/
	
	if(condition == 0){

		system("clear");
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

		printf("                                      %s Voce perdeu :(\n",person.PlayerName);
		printf("\n O Id do(s) Zombie(s) que te alcancaram:\n");
		for(int i=0; i<z; i++)
		{
			if(zombie[i].xf == person.xf && zombie[i].yf == person.yf || (zombie[i].xf == person.px && zombie[i].yf == person.py && zombie[i].px == person.xf && zombie[i].py == person.yf))
				printf("  Zombie %d\n", zombie[i].ID);
		}	


	}
	else{
		

		system("clear");
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

		printf("                                          Parabens %s Voce ganhou :)\n",person.PlayerName);
	}

	printf("\n\n Numero de turns: %d\n\n", (turns -2));
	printf("\n\n Posicoes percorridas: %d\n\n", (turns -2));	
	
}
