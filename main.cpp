#include <iostream>
#include <graphics.h>
using namespace std;

#define ESC    	27


////Variaveis globais
int l1[10][20], l2[10][20], l3[10][20];

struct Player{
    int x = 0;
	int y = 0;
	int sprite = 0;
};

struct Img{	
	void *a = malloc(imagesize(0,0,63,63));	
};

Img *img_pool = NULL;
//char *img = NULL;

////Funções
void carregaLabirinto();
void desenhaCena(int cena, int lab[10][20]);
void carregaImagens();
////

int main(){
	printf("Integrantes: \nCAROLINE GONCALVES DE FELIPE \nHEITOR RYOKICHI NAKAMURA \nRENAN ALVES NOWAK \nWILSON RICARDO DA SILVA FABOZI\n\n");

	Player jogador;
	int pg, tecla, cena_atual;	
	int img_size;
	char path[4096], c_aux[4096];
	
	initwindow(1300, 660, "Labirinto", 0, 0);
	setbkcolor(RGB(25,145,25));	
	
	img_size = imagesize(0,0,63,63);
		
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
	
	cena_atual = 1;		
	
	while (tecla != ESC){
		if (pg==0) pg=1; else pg=0;
        setactivepage(pg);
        cleardevice();
        carregaLabirinto();	
                
        //desenhaCena(cena_atual, l1);
        
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
	
}
void carregaLabirinto(){
	void *lab;	
	setactivepage(2);
	readimagefile("img/lab_1.bmp", 0, 0, 20, 10);
	getimage(0, 0, 20, 10, lab);
	
	//for (int i=0; i<10; i++){
		//for (int j=0; j<20; j++){
			//printf(" cor = %d \n", getpixel(i,j));
		//}
	//}
}
