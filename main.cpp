#include <iostream>
#include <stdlib.h>
#include <graphics.h>
using namespace std;

#define ESC    	27

struct Player {
    int x = 0;
	int y = 0;
	int sprite = 0;
};

struct Img {	
	void *a = malloc(imagesize(0,0,63,63));
	void *b = malloc(imagesize(0,0,63,63));	
};

////Variaveis globais
int l1[10][20], l2[10][20], l3[10][20];
Img *img_pool = NULL;
Img *img_player = NULL;
Player jogador;


////Funções
void carregaLabirinto();
void desenhaCena(int cena, int lab[10][20]);
void carreImagens();
void trocaCena(int cena);
////

int main(){	
	printf("Integrantes: \nCAROLINE GONCALVES DE FELIPE \nHEITOR RYOKICHI NAKAMURA \nRENAN ALVES NOWAK \nWILSON RICARDO DA SILVA FABOZI\n\n");
		
	int pg, tecla, cena_atual;
	int dt, dt_ini;
	
	initwindow(1280, 640, "Labirinto", 0, 0);
	setbkcolor(RGB(25,145,25));		
	
	setactivepage(2);
	carregaLabirinto();
	carreImagens();	
	
	dt_ini = 5;
	dt = dt_ini;
	
	cena_atual = 1;
	while (tecla != ESC){
		if (pg==0) pg=1; else pg=0;
        setactivepage(pg);
        cleardevice();       	
        
        if((GetKeyState(VK_UP)&0x80) && dt <= 0){
        	jogador.y -= 64;
        	dt = dt_ini;
		}
		if((GetKeyState(VK_DOWN)&0x80)&& dt <= 0){
        	jogador.y += 64;
        	dt = dt_ini;
		}
		if((GetKeyState(VK_LEFT)&0x80) && dt <= 0){			
        	jogador.x -= 64;
        	dt = dt_ini;
		}
        if((GetKeyState(VK_RIGHT)&0x80)&& dt <= 0){
        	jogador.x += 64;
        	dt = dt_ini;
		}
		dt--;		
		desenhaCena(cena_atual, l1); 
		
		///troca cena ainda não funciona      
        if (jogador.x > (20*64)){
        	///trocaCena(cena_atual);
		}
        
        if (kbhit()) tecla = getch();        
        delay(30);
        setvisualpage(pg);
	}
	closegraph();
}

void desenhaCena(int cena, int lab[10][20]){
	int index;	
	for (int i=0; i<10; i++){
		for(int j=0; j<20; j++){
			index = lab[i][j];			
			putimage(64*j, 64*i, img_pool[index].a, 0);
		}	
	}
	
	jogador.sprite ++;
	if (jogador.sprite > 5) jogador.sprite = 0;
	putimage(jogador.x, jogador.y, img_player[jogador.sprite].b, 2);
	putimage(jogador.x, jogador.y, img_player[jogador.sprite].a, 3);		
}

void trocaCena(int cena){
	setactivepage(0);
	int index;
	if (cena == 1){
		for(int p=0; p<(20*64); p++){
			cleardevice();
					
	        for (int i=0; i<10; i++){
		        for(int j=0; j<20; j++){
			        index = l1[i][j];			
			        putimage(64*j-p, 64*i, img_pool[index].a, 0);
		       }	
	        }
			
			
			jogador.x -= p;			
			for (int i=0; i<10; i++){
		        for(int j=0; j<20; j++){
			        index = l2[i][j];			
			        putimage(jogador.x, 64*i, img_pool[index].a, 0);
		       }	
	        }		
			
			putimage(jogador.x, jogador.y, img_player[jogador.sprite].b, 2);
	        putimage(jogador.x, jogador.y, img_player[jogador.sprite].a, 3);
	        
	        setvisualpage(0);
		}
	}
	
}

void carreImagens(){
	char path[4096], c_aux[4096];
	int img_size = imagesize(0,0,63,63);
	
	for(int i=0; i<2; i++){				 
		img_pool = (Img*)realloc(img_pool, sizeof(Img)*(i+1));
		Img img;
				
		strcpy(path, "img/tile_");
		sprintf(c_aux, "%d", i);
		strcat(path, c_aux);
		strcat(path, ".bmp");	
		
		setactivepage(2);
		readimagefile(path, 0, 0, 63, 63);
		getimage(0, 0, 63, 63, img.a);
		
		img_pool[i] = img;		
	}
	
	for(int i=0; i<6; i++){				 
		img_player = (Img*)realloc(img_player, sizeof(Img)*(i+1));
		Img img;
				
		strcpy(path, "img/player_");
		sprintf(c_aux, "%d", i);
		strcat(path, c_aux);
		strcat(path, ".bmp");
		
		setactivepage(2);
		readimagefile(path, 0, 0, 63, 63);
		getimage(0, 0, 63, 63, img.a);
		
		strcpy(path, "img/player_b");
		sprintf(c_aux, "%d", i);
		strcat(path, c_aux);
		strcat(path, ".bmp");		
		
		readimagefile(path, 0, 0, 63, 63);
		getimage(0, 0, 63, 63, img.b);
		
		img_player[i] = img;		
	}
		
}

void carregaLabirinto(){
	/*
	**0  = RGB(0  ,  0,  0) - Preto
	**1  = RGB(0  ,  0,128) - Azul
	**2  = RGB(0  ,128,  0) - Verde
	**3  = RGB(0  ,128,128) - Azul claro
	**4  = RGB(128,  0,  0) - Vermelho
	**5  = RGB(128,  0,128) - Roxo
	**6  = RGB(128,128,  0) - Verde/Marrom
	**7  = RGB(192,192,192) - Cinza claro
	**8  = RGB(128,128,128) - Cinza
	**9  = RGB(128,128,255) - Azul médio
	**10 = RGB(128,255,128) - Verde claro
	**11 = RGB(128,255,255) - Azul/Verde Claro
	**12 = RGB(255,128,128) - Rosa
	**13 = RGB(255,128,255) - Rosa claro
	**14 = RGB(255,255,  0) - Amarelo
	**15 = RGB(255,255,255) - Branco
	*/
	
	int cor;
		
	readimagefile("img/lab_1.bmp", 0, 0, 20, 10);		
	for (int i=0; i<10; i++){
		for (int j=0; j<20; j++){
			cor = getpixel(j,i);			
			cor = (cor < 15) ? (cor+1) : 0;
			l1[i][j] = cor;			
		}
	}
	
	readimagefile("img/lab_2.bmp", 0, 0, 20, 10);		
	for (int i=0; i<10; i++){
		for (int j=0; j<20; j++){
			cor = getpixel(j,i);			
			cor = (cor < 15) ? (cor+1) : 0;
			l2[i][j] = cor;			
		}
	}
	
	readimagefile("img/lab_3.bmp", 0, 0, 20, 10);		
	for (int i=0; i<10; i++){
		for (int j=0; j<20; j++){
			cor = getpixel(j,i);			
			cor = (cor < 15) ? (cor+1) : 0;
			l2[i][j] = cor;			
		}
	}
}
