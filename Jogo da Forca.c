#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strlen mede o tamanho da palavra.
#include <locale.h>
#include "forca.h"	// Declarando as funções
#include <time.h> // Time(0) e Srand

char palavrasecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutes_dados = 0;

int letraexiste(char letra) {
	
	int j;
    for(j = 0; j < strlen(palavrasecreta); j++) {
        if(letra == palavrasecreta[j]) {
            return 1;
        }
    }

    return 0;
}

void abertura(){
	printf("*******************\n");
	printf("*  Jogo da Forca  *\n");
	printf("*******************\n");
}

void chuta(){
	char chute;
	printf("\nQual letra? ");
	scanf(" %c", &chute); 
	if(letraexiste(chute)) {
  		printf("Você acertou a palavra tem a letra %c\n\n", chute);
    } else {
        printf("\nVocê errou a palavra NÃO tem a letra %c\n\n", chute);
    } 

	chutes[chutes_dados] = chute;
	chutes_dados++;
}

int jachutou(char letra){
	int j;
	int achou = 0;
	for (j = 0; j < chutes_dados; j++){
		if (chutes[j] == letra){
			achou = 1;
			break;
		}
	}
	return achou;
}

void desenhaforca(){
		
	int erros = chutes_errados();
 	 
	printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros >= 1 ? '(' : ' '), 
		(erros >=1 ? '_' : ' '), (erros >= 1 ? ')' : ' '));
    printf(" |      %c%c%c  \n", (erros >= 3 ? '\\' : ' '), 
		(erros >= 2 ? '|' : ' '), (erros >= 3 ? '/' : ' '));
    printf(" |       %c     \n", (erros >= 2 ? '|' : ' '));
    printf(" |      %c %c   \n", (erros >= 4 ? '/' : ' '), 
		(erros >= 4 ? '\\' : ' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");
	
		
	int i;
    for(i = 0; i < strlen(palavrasecreta); i++) {
        if(jachutou(palavrasecreta[i])) {
            printf("%c ", palavrasecreta[i]);
        } else {
            printf("_ ");
        }

    }
    printf("\n");

}

void adiciona_palavra(){

	char quer;

	printf("Você deseja adicionar uma nova palavra no jogo? (S/N)");
	scanf (" %c", &quer);

	if(quer == 'S' || 's'){
		char nova_palavra[TAMANHO_PALAVRA];
		
		printf("Qual a nova palavra? ");
		scanf(" %s", nova_palavra);
		
		FILE* f;
		
		f = fopen("palavras.txt", "r+"); // "r+" é leitura e escrita
		if(f == 0){
			printf("Desculpe, banco de dados não disponivel\n\n");
			exit(1);
	   	}
		
		int qtd;
		fscanf(f, "%d", &qtd);
		qtd++;
		
		fseek(f, 0, SEEK_SET);
		fprintf(f, "%d", qtd);
		
		fseek(f, 0, SEEK_END);
	 	fprintf(f, "\n%s", nova_palavra);
	 	
	 	fclose(f);
	} 
}

void escolhepalavra(){
	FILE* f; //Criando arquivo
	
	f = fopen("palavras.txt", "r"); //Abrindo arquivo, "r" = READ fala que quero ler o arquivo
	
	if(f == 0){
		printf("Desculpe, banco de dados não disponivel\n\n");
		exit(1);
	}
	
	int qtd_palavras;
	fscanf(f, "%d", &qtd_palavras);
	
	srand(time(0));
	int randomico = rand() % qtd_palavras;
	
	int i;
	for(i = 0; i <= randomico; i++){
		fscanf(f, "%s", palavrasecreta);
	}
	
	fclose(f);//Fechando arquivo
}	

int acertou(){
	int i;
	
	for(i = 0; i < strlen(palavrasecreta); i++){
		if(!jachutou(palavrasecreta[i])){
			return 0;
		}
	}
	
	return 1;
}

int chutes_errados(){
	int i;
	int erros = 0;
	for (i = 0; i < chutes_dados; i++){

		if(!letraexiste(chutes[i])){
			erros++;
		}
			
	}
	return erros;
}

int enforcou(){

	return chutes_errados() >= 5;
}

int main()
{
	setlocale(LC_ALL, "portuguese");
	
	escolhepalavra();
	abertura();
	
	do{
		desenhaforca();
 	   	chuta();   
		
	} while(!acertou() && !enforcou()); /* '!' antes da variavel se lê como "não",
	exemplo: !acertou se lê como "não acertou", mesma coisa para !enforcou.
	Pode ser chamado de "Negação". */	
	if(acertou()){
	    printf("\nParabéns, você ganhou! A palavra era **%s**\n\n", palavrasecreta);

        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");

	} else {
		 printf("\nPuxa, você foi enforcado!\n");
        printf("A palavra era **%s**\n\n", palavrasecreta);

        printf("    _______________         \n");
        printf("   /               \\       \n"); 
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");
	}
	
	
	adiciona_palavra();
}