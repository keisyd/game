#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include "Matrix_creator.h"
#include<math.h>
#include <string.h> //necessário para strcpy

void red() { //impressão vermelho
printf("\033[1;31m");
}
void cyan() { //impressão vermelho
printf("\033[0;36m");
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
	system("clear");

	FILE *conf;
	if(argv[1]==NULL){
		printf("\n\n\nERRO: O diretório de arquivos de configuração não foi informado​.\n\n\n");
		exit(0);
	}
	

	strcat(argv[1],"/config.txt");

	conf = fopen(argv[1],"r");

		if (conf == NULL)
		{
			printf("ERRO! O arquivo 'config.txt' de path:%s nao foi aberto!\n",argv[1]);
			*canGo = 1;
			exit(0);

		}

	cyan();
	printf(
	"\n::::::::: ::::::::  ::::    ::::  ::::::::: ::::::::::: :::::::::: ::::::::"  
	"\n     :+: :+:    :+: +:+:+: :+:+:+ :+:    :+:    :+:     :+:       :+:    :+:" 
	"\n    +:+  +:+    +:+ +:+ +:+:+ +:+ +:+    +:+    +:+     +:+       +:+"        
	"\n   +#+   +#+    +:+ +#+  +:+  +#+ +#++:++#+     +#+     +#++:++#  +#++:++#++" 
	"\n  +#+    +#+    +#+ +#+       +#+ +#+    +#+    +#+     +#+              +#+" 
	"\n #+#     #+#    #+# #+#       #+# #+#    #+#    #+#     #+#       #+#    #+#" 
	"\n######### ########  ###       ### ######### ########### ########## ########"  
	);

	printf("\n"
	"     :::        ::::::::  :::    :::  ::::::::   ::::::::   ::::::::\n"  
	"     :+:       :+:    :+: :+:    :+: :+:    :+: :+:    :+: :+:    :+:\n" 
	"     +:+       +:+    +:+ +:+    +:+ +:+        +:+    +:+ +:+\n"        
	"     +#+       +#+    +:+ +#+    +:+ +#+        +#+    +:+ +#++:++#++\n" 
	"     +#+       +#+    +#+ +#+    +#+ +#+        +#+    +#+        +#+\n" 
	"     #+#       #+#    #+# #+#    #+# #+#    #+# #+#    #+# #+#    #+#\n" 
	"     ########## ########   ########   ########   ########   ########\n" 
	"\n\n");                     
	
	reset();

	system("read -p '                     Aperte Enter para entrar no jogo.' var");
	system("clear");
	cyan();
	printf("\n\n\n\nDurante uma excursão às dunas de Itaúnas, você se depara com uma antiga porta\n"
		    "de igreja levemente enterrada na areia e devidamente lacrada. Muito curioso, \n"
		    "você resolve arrombar a porta mas, infelizmente, arrombá-la acaba sendo uma \n"
		    "péssima idéia: ao chegar ao meio da igreja, você se vê cercado de beatos e \n"
		    "beatas zumbis. Diante dessa massa assassina de zumbis loucos, sua única chance\n" 
		    "é fugir e tentar escapar antes que eles o capturem. A questão é: você é sagaz o\n"
		    "suficiente para se esquivar dos zumbis e chegar até a uma das paredes da igreja\n"
		    "sem ser pego? Sua salvação está em tocar uma das paredes da igreja.\n\n\n");
	reset();
	printf(" ");
	system("read -p '                        Aperte Enter para jogar' var");

	//Lê no arquivo o tamnho da matrix, cria, determina e retorna struct com as posições dos zombies e suas respectivas IDs
	system("clear");

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

	system("clear");

	yellow();
	printf("\n\n\n\n   	Digite seu nome\n\n\n    	");

	scanf("%s", person->PlayerName);

	reset();


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
	person->moves=0; 
	
	matrix[c_position][c_position] = 'P';
	
	return matrix;
}


void movePerson(char **matrix, Play *person, int *canGo, Play *zombie, int z)
{
	for(int i =0; i<z; i++)
	{
		zombie[i].px = zombie[i].xf;

		zombie[i].py = zombie[i].yf;
	}

	//primeiro alocando as informações de poisção como 'py e px' prévias posições x e y 
	person->py = person->yf;           
	
	person->px = person->xf;

	for(int i=0; i<z; i++)
		matrix[zombie[i].yf][zombie[i].xf] ='*';
	
	
	char tecla; 


	//recebendo, então o que foi digitado,
	scanf("%c",&tecla);
	while(getc(stdin)!='\n'){} //garantido que apenas a primeira letra será utilizada

		//então movendo-o para
	*canGo = 0;
	matrix[person->yf][person->xf] = '*';
	

	if(tecla == 'S'|| tecla == 's' || tecla == '5')
	{}
		
		
	
	//Cima
	else if(tecla == 'W'|| tecla == 'w' || tecla == '8')
	{
		
		person->yf--;
		person->moves++;

	}
	//Baixo
	else if(tecla == 'X'|| tecla == 'x' || tecla == '2')
	{
		person->yf++;
		person->moves++;
	}
	//Direita
	else if(tecla == 'D'|| tecla == 'd' || tecla == '6')
	{
		
		person->xf++;
		person->moves++;
	}
	//Esquerda
	else if(tecla == 'A'|| tecla == 'a' || tecla == '4')
	{
		
		person->xf--;
		person->moves++;
	}
	//Diagonal superior esquerda
	else if(tecla == 'q'|| tecla == 'Q' || tecla == '7')
	{
		
		person->yf--;
		person->xf--;
		person->moves++;

	}
	//Diagonal superior direita
	else if(tecla == 'e'|| tecla == 'E' || tecla == '9')
	{
		
		person->yf--;
		person->xf++;
		person->moves++;
	}
	//Diagonal inferior esquerda
	else if(tecla == 'z'|| tecla == 'Z' || tecla == '1')
	{
		
		person->yf++;
		person->xf--;
		person->moves++;
	}
	//Diagonal inferior direita
	else if(tecla == 'c'|| tecla == 'C' || tecla == '3')
	{
		
		person->yf++;
		person->xf++;
		person->moves++;
	}
	else
	{
		*canGo = 1;
	}

	
}

void moveZombie(char **matrix, Play *zombie, Play *person, int z)
{	
	//essa função faz os movimentos 
	// Para todo zombie
	for(int i=0; i<z; i++)
	{
		//como o movimento é ortogonal, uma forma de garantir uma aproximação orgânica é:
		if(person->xf==zombie[i].xf && person->yf== zombie[i].yf){}

		else if(sqrt(pow(person->xf - zombie[i].xf, 2)) >= sqrt(pow(person->yf - zombie[i].yf, 2)))
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

	matrix[person->yf][person->xf] = 'P';		
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
	no fim do jogo),*/
	float menor=9999999, maior=-1, distjogador=-1,proximo=999999,soma=0;
	int ZombieMenor, ZombieMaior, maiordist,prox,i;
	
	for(i=0;i<z;i++){
		if (sqrt(pow(zombie[i].xf-zombie[i].xi,2)+pow(zombie[i].yf-zombie[i].yi,2))<menor){
			menor=sqrt(pow(zombie[i].xf-zombie[i].xi,2)+pow(zombie[i].yf-zombie[i].yi,2));
			ZombieMenor=i;
		}
	}	
	for(i=0;i<z;i++){
		if (sqrt(pow(zombie[i].xf-zombie[i].xi,2)+pow(zombie[i].yf-zombie[i].yi,2))>maior){
			maior=sqrt(pow(zombie[i].xf-zombie[i].xi,2)+pow(zombie[i].yf-zombie[i].yi,2));
			ZombieMaior=i;
		}	
	}
	for(i=0;i<z;i++){
		if(sqrt(pow(zombie[i].xf-person.xf,2)+pow(zombie[i].yf-person.yi,2))>distjogador){
			distjogador=sqrt(pow(zombie[i].xf-person.xf,2)+pow(zombie[i].yf-person.yi,2));
			maiordist=i;
		}	
	}
	for(i=0;i<z;i++){
		soma=soma + sqrt(pow(zombie[i].xf-zombie[i].xi,2)+pow(zombie[i].yf-zombie[i].yi,2));
	}
	
	if(condition == 0){

		system("clear");
		
		green();
		
		printf("		       ..::::!?menor:.. \n");
printf("                  .xUHWH!! !!?M88WHX:.\n");
printf("                .X*#M@$!!  !X!M$$$$$$WWx:.\n");
printf("               :!!!!!!?H! :!$!$$$$$$$$$$8X:\n");
printf("              !!~  :!! :~!$!#$$$$$$$$$$8X:\n");
printf("             :!~::!H!<   ~.U$X!?R$$$$$$$$MM!\n");
printf("             !!!!!~~ .:XW$$$U!!?$$$$$$RMM!\n");
printf("               !:~ .:!M*T#$$$$WX??#MRRMMM!\n");
printf("               ~?WuxiW*´   ´*#$$$$8!!!!P?!!!\n");
printf("             :X- M$$$$       ´*T#$T~!8$WUXU~\n");
printf("            :%´  #$$$m:        ~! ?$$$$$$\n");
printf("          :!´.-   ~T$$$$8xx.  .xWW- ~''##*'\n");
printf(".....   -~~:<´ !    ~?T#$$@@W@*?$$      /´\n");
printf("W$@@M!!! .!~ !!     .:XUW$W! ´:~::   :\n");
printf("#´~~'.:x%´!!  !H:   !WM$$$$Ti.: .!WUn+!´\n");
printf("::::!!´:X .: ?H.!u '$$$B$$$!W:U!T$$M~\n");
printf(".~   :X@!.-   ?@WTWo('*$$$W$TH$! ´\n");
printf("Wi.!X$?!-    : ?$$$B$Wu('**$RM!\n");
printf("$R@i.~~ !     :   ~$$$$$B$$en:´´\n");
printf("?MXT@Wx.~    :     '##*$$$$M \n");
		printf("\n\n %s voce MORREU \n\n\n\n",person.PlayerName);
		reset();

		system("read -p 'Aperte Enter para ver as estatisticas' var");
		//scanf("%d",&zombie[1].px);
		system("clear");
		printf("*******************************************************************\n");		
		printf("*###########################ESTATISTICAS##########################*\n");
		printf("* O Id do(s) Zombie(s) que te alcancaram:                         *\n");
		for(i=0; i<z; i++)
		{
			if(zombie[i].xf == person.xf && zombie[i].yf == person.yf || (zombie[i].xf == person.px && zombie[i].yf == person.py && zombie[i].px == person.xf && zombie[i].py == person.yf))
				printf("* Zumbi %d                                                         *\n", zombie[i].ID);
		}	


	}
	else{
		

		system("clear");
		system("\n");
		printf("\n");

		
		yellow_bold();
		printf("\n\n\n\
8b           d8 88                               88  \n\
'8b         d8' 11   ,d                          11   \n\
 '8b       d8'       88                                     \n\
  '8b     d8'   88 MM88MMM ,adPPYba,  8b,dPPYba, 88 ,adPPYYba,\n\
   '8b   d8'    88   88   a8'     '8a 88P'   'Y8 88 11     `Y8 \n\
    '8b d8'     88   88   8b       d8 88         88 ,adPPPPP88 \n\
     `888`      88   88,  '8a,   ,a8' 88         88 88,    ,88 \n\
      'V'       88   'Y888 `'YbbdP''  88         88 `'8bbdP'Y8 \n\
                                                                                         ");
		reset();
		yellow();
		printf("\n\n\n",person.PlayerName);
		system("read -p '                Aperte Enter para ver as estatisticas' var");
		reset();

		system("clear");
		for(i=0; i<z; i++){
			if(sqrt(pow(zombie[i].xf-person.xf,2)+pow(zombie[i].yf-person.yf,2))<proximo)
			prox=i;
		}
		printf("*******************************************************************\n");
		printf("*###########################ESTATISTICAS##########################*\n");
		printf("* O Zumbi %d foi o que chegou mais perto de te matar               *\n*                                                                 *\n", zombie[prox].ID);
	}
	if(ZombieMaior==ZombieMenor){
		printf("*                                                                 *\n* Todos Zombies andaram a mesma distancia                         * \n*                                                                 *\n");}
	else{	
	printf("* O Zumbi %d foi que mais andou.                                   * \n*                                                                 *\n",zombie[ZombieMaior].ID );	
	printf("* O Zumbi %d foi que menos andou.                                  * \n*                                                                 *\n",zombie[ZombieMenor].ID );}	
	printf("* O Zumbi %d foi que ficou mais longe de te matar.                 * \n*                                                                 *\n",zombie[maiordist].ID );	
	printf("* A distancia percorrida por todos zombies somada foi: %.2f      *\n*                                                                 *\n", soma);
	printf("* O numero de turnos foi: %d                                       *\n*                                                                 *\n", (turns -2));
	printf("* O numero de Posicoes percorridas: %d                             *\n*                                                                 *\n", person.moves);	
	printf("*******************************************************************\n");
		
}
	
