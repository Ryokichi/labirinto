#include <iostream>
#include <stdlib.h>
#include <graphics.h>
using namespace std;

#define ESC        27

struct Player {
    int x = 18;
    int y = 1;
    int sprite = 0;
};

struct Img {    
    void *a = malloc(imagesize(0,0,63,63));
    void *b = malloc(imagesize(0,0,63,63));    
};

////Variaveis globais
int l1[10][20], l2[10][20], l3[10][20];
Img *tile_pool   = NULL;
Img *img_player = NULL;
Player jogador;

////Funções
void carregaLabirinto();
void desenhaCena(int lab[10][20]);
void trocaCena(int pg, int lab1[10][20], int lab2[10][20]);
void carregaImagens();
int moveJogador(int orientacao, int cena);
int getValorLab(int cena, int i, int j);
////

int main(){    
    printf("Integrantes: \nCAROLINE GONCALVES DE FELIPE \nHEITOR RYOKICHI NAKAMURA \nRENAN ALVES NOWAK \nWILSON RICARDO DA SILVA FABOZI\n\n");
        
    int pg, tecla, cena_atual;
    int dt, dt_ini;
    int *lab_atual;
    bool troca_cena = false;
        
    initwindow(1280, 640, "Labirinto", 0, 0);
    setbkcolor(RGB(25,145,25));        
    
    setactivepage(2);
    carregaLabirinto();
    carregaImagens();    
    
    dt_ini = 5; ////delay para utilizar as setas
    dt = dt_ini;
    
    cena_atual = 1;
    while (tecla != ESC){
        
        if((GetKeyState(VK_UP)&0x80) && dt <= 0){
            dt = moveJogador(0, cena_atual);
        }
        if ((GetKeyState(VK_DOWN)&0x80)&& dt <= 0){
        	dt = moveJogador(1, cena_atual);
        }  
        if ((GetKeyState(VK_LEFT)&0x80) && dt <= 0){
        	dt = moveJogador(2, cena_atual);
        }              
        if((GetKeyState(VK_RIGHT)&0x80)&& dt <= 0){
        	dt = moveJogador(3, cena_atual);
        }
        dt--;
                
        if (jogador.x > 19){
        	switch(cena_atual){
			    case 1:
                    trocaCena(pg, l1, l2);
                    break;
                case 2:
                    trocaCena(pg, l2, l3);
                    break;
                case 3:
                    trocaCena(pg, l3, l1);
                    break;

            }
            cena_atual = (cena_atual < 3) ? (cena_atual+1) : 1;            
        } 
        
        switch(cena_atual){
            case 1: desenhaCena(l1); break;
            case 2: desenhaCena(l2); break;
            case 3: desenhaCena(l3); break;
        }
        
        
        if (kbhit()) tecla = getch();        
        delay(30);
        setvisualpage(pg);
        pg = (pg==0) ? 1 : 0;
        setactivepage(pg);
        cleardevice(); 
    }
    closegraph();
}

int moveJogador(int orientacao, int cena){
    int px = jogador.x;
    int py = jogador.y;
    int prox_bloco;
    int time_delay = 0;    
    
    switch(orientacao){
        ////move para cima
        case 0:                
            prox_bloco = getValorLab(cena, py-1, px);            
            if (prox_bloco != 1){ 
                jogador.y--;
                time_delay = 5;
            }
            if (cena == 1){            	
            	if (py==0){
            		jogador.y=9;
            		jogador.x=10;
				}
            }
            if (cena == 2){            	
            	if (py==0){
            		jogador.y=9;
            		jogador.x=9;
				}
            }
            break;

        ////move para baixo
        case 1:                
            prox_bloco = getValorLab(cena, py+1, px);
            if (prox_bloco != 1){ 
                jogador.y++;
                time_delay = 5;
            }
            if (cena == 1){            	
            	if (py==9){
            		jogador.y=0;
            		jogador.x=15;
				}
            }
            if (cena == 2){            	
            	if (py==9){
            		jogador.y=0;
            		jogador.x=14;
				}
            }
            break;
        ////move para esquerda
        case 2:
            prox_bloco = getValorLab(cena, py, px-1);
            if (prox_bloco != 1){ 
                jogador.x--;
                time_delay = 5;
            }
            break;
        ////move para direita
        case 3:
            prox_bloco = getValorLab(cena, py, px+1);
            if (prox_bloco != 1){ 
                jogador.x++;
                time_delay = 5;
            }
                     	
            if (px==19){            		
            	jogador.x=20;
		    }
        
            break;
    }    	
	return time_delay;
}

int getValorLab(int cena, int i, int j){
    if (cena == 1) return l1[i][j];
    if (cena == 2) return l2[i][j];
    if (cena == 3) return l3[i][j];

}

void desenhaCena(int lab[10][20]){    
    int index;
    for (int i=0; i<10; i++){
        for(int j=0; j<20; j++){
            index = lab[i][j];            
            putimage(64*j, 64*i, tile_pool[index].a, 0);
        }    
    }
    
    jogador.sprite ++;
    if (jogador.sprite > 5) jogador.sprite = 0;
    putimage(jogador.x*64, jogador.y*64, img_player[jogador.sprite].b, 2);
    putimage(jogador.x*64, jogador.y*64, img_player[jogador.sprite].a, 3);
}

void trocaCena(int pg, int lab1[10][20], int lab2[10][20]){    
    int index;    
    desenhaCena(lab1);
    setvisualpage(pg);
	    
    for(int p=0; p < 20; p++){
        pg = (pg==0) ? 1 : 0;
        setactivepage(pg);
        cleardevice();

        for (int i=0; i<10; i++){
            for(int j=0; j<20; j++){
            	
                index = lab1[i][j];
                putimage(64*(j-p), 64*i, tile_pool[index].a, 0);
                
                index = lab2[i][j];
                putimage(64*(jogador.x+j), 64*i, tile_pool[index].a, 0);

                putimage(jogador.x*64, jogador.y*64, img_player[0].b, 2);
                putimage(jogador.x*64, jogador.y*64, img_player[0].a, 3);
           }
        }        
        setvisualpage(pg);
        delay(5);
        jogador.x --;
    }    
     
}

void carregaImagens(){
    char path[4096], c_aux[4096];
    int img_size = imagesize(0,0,63,63);
    
    for(int i=0; i<4; i++){
        Img img;        
        tile_pool = (Img*)realloc(tile_pool, sizeof(Img)*(i+1));        
                
        strcpy(path, "img/tile_");
        sprintf(c_aux, "%d", i);
        strcat(path, c_aux);
        strcat(path, ".bmp");    
        
        setactivepage(2);
        readimagefile(path, 0, 0, 63, 63);
        getimage(0, 0, 63, 63, img.a);
        
        tile_pool[i] = img;        
    }
    
    for(int i=0; i<6; i++){  
        Img img;               
        img_player = (Img*)realloc(img_player, sizeof(Img)*(i+1));
        
                
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
            l3[i][j] = cor;            
        }
    }
}
