#include <iostream>
#include <graphics.h>
using namespace std;

#define ESC    	27

struct Player{
    int x = 0;
	int y = 0;
	int sprite = 0;
};

struct Img{	
	void *a = malloc(imagesize(0,0,63,63));	
};

////Variaveis globais
int l1[10][20], l2[10][20], l3[10][20];
Img *img_pool = NULL;


////Funções
void carregaLabirinto();
void desenhaCena(int cena, int lab[10][20]);
void carreImagens();
////

int main(){
	printf("Integrantes: \nCAROLINE GONCALVES DE FELIPE \nHEITOR RYOKICHI NAKAMURA \nRENAN ALVES NOWAK \nWILSON RICARDO DA SILVA FABOZI\n\n");

	Player jogador;
	int pg, tecla, cena_atual;
	
	initwindow(1300, 660, "Labirinto", 0, 0);
	setbkcolor(RGB(25,145,25));		
	
	setactivepage(2);
	carregaLabirinto();
	carreImagens();	
	
	cena_atual = 1;
	while (tecla != ESC){
		if (pg==0) pg=1; else pg=0;
        setactivepage(pg);
        cleardevice();       	
                
        desenhaCena(cena_atual, l1);
        
        setvisualpage(pg);
        if (kbhit()) tecla = getch();
        delay(30);
	}
	closegraph();
}

void desenhaCena(int cena, int lab[10][20]){
	int index;	
	for (int i=0; i<10; i++){
		for(int j=0; j<20; j++){
			index = lab[i][j];			
			putimage(20+63*j, 15+63*i, img_pool[index].a, 0);
		}	
	}	
}

void carreImagens(){
	char path[4096], c_aux[4096];
	int img_size = imagesize(0,0,63,63);
	
	for(int i=1; i<=2; i++){				 
		img_pool = (Img*)realloc(img_pool, sizeof(Img)*i);
		Img img;
				
		strcpy(path, "img/tile_");
		sprintf(c_aux, "%d", i);
		strcat(path, c_aux);
		strcat(path, ".bmp");
		
		setactivepage(2);
		readimagefile(path, 0, 0, 63, 63);
		getimage(0, 0, 63, 63, img.a);
		
		img_pool[i-1] = img;		
	}	
}

void carregaLabirinto(){
	void *lab;
	lab = malloc(imagesize(0,0,20,10));
	int cor;
	
	readimagefile("img/lab_1.bmp", 0, 0, 20, 10);
	getimage(0, 0, 20, 10, lab);
		
	for (int i=0; i<10; i++){
		for (int j=0; j<20; j++){
			cor = getpixel(j,i);
			if (cor==0){
				l1[i][j] = 1;
			}
			else {
				l1[i][j] = 0;
			}			
			printf("i=%d, j=%d | cor = %d | %d\n", i, j, &cor, RGB(0,255,255));
		}
	}
}
