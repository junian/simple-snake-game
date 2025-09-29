#include <allegro.h>

//definisi warna hitam dan putih
#define BLACK  makecol(0  , 0  , 0  )
#define WHITE  makecol(255, 255, 255)

void init();
void deinit();

//Fungsi untuk membuat garis lurus dengan
//menyimpan koordinat titik ujungnya
void lineForward(int*, int*, int, int, int);

//untuk membuat kurva hilbert dengan bentukkan sebagai berikut
// -------      |     |      ----------      ----------
// |     |      |     |      |                        |
// |     | atau |     | atau |          atau          |
// |     |      -------      ----------      ----------
void drawHilbert(int*, int*, int, int, int);

int main(){
	init();
	
    char title[22] = "Hilbert Curve Level 1"; //title window
    int x, y, length;
    int lvl = 1; //level mula-mula 1
    
    set_window_title("Hilbert Curve");
    allegro_message("Hilbert Curve\n(C) 2008 by A Ninja @ Junior IT");
    allegro_message("Press UP / DOWN to change level\nPress ESC to Exit");
    
	do{
        //koordinat awal adalah (10, 590) dan mula-mula panjang per garis
        //lurus adalah 512 px
        x = 10, y = 590, length = 512;
        
        //panjang akan dibagi dua sebanyak lvl kali
        //jika lebih dari atau sama dengan 8 px
        for(int i=1; i<=lvl; i++)
            if(length >= 8) length /= 2;
        
        title[20] = lvl+48;
        title[21] = '\0';
        set_window_title(title);
        
        //bersihkan layar menjadi putih
        clear_to_color(screen, WHITE);
        
        drawHilbert(&x, &y, 0, length, lvl);
        do{
		  readkey();
		}while(!key[KEY_UP] && !key[KEY_DOWN] && !key[KEY_ESC]);
		
		//jika tombol UP ditekan, maka level akan bertambah
        if(key[KEY_UP] && lvl<9) lvl++;
        //jika tombol DOWN ditekan, maka level akan berkurang
        else if(key[KEY_DOWN] && lvl>1) lvl--;
	}while(!key[KEY_ESC]);
	
    allegro_message("Thanks and good-bye ^_^");
	deinit();
	return 0;
}
END_OF_MAIN();

void init() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 960, 600, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}
	install_keyboard();
}

void deinit() {
	clear_keybuf();
}

void lineForward(int *x, int *y, int lengthX, int lengthY, int color){
    //cetak garis dari (*x, *y) hingga (*x + lengthX, *y + lengthY)
    line(screen, *x, *y, lengthX + *x, lengthY + *y, color);
    
    //simpan koordinat ujung garis yang telah dibuat
    *x += lengthX;
    *y += lengthY;
}

//fungsi rekursif hilbert dengan pola-pola tertentu
void drawHilbert(int *x, int *y, int lengthX, int lengthY, int lvl){
    if(lvl>0){
        drawHilbert (x, y,  lengthY,  lengthX, lvl-1);
        lineForward (x, y,  lengthX, -lengthY, BLACK);
        drawHilbert (x, y,  lengthX,  lengthY, lvl-1);
        lineForward (x, y,  lengthY, -lengthX, BLACK);
        drawHilbert (x, y,  lengthX,  lengthY, lvl-1);
        lineForward (x, y, -lengthX,  lengthY, BLACK);
        drawHilbert (x, y, -lengthY, -lengthX, lvl-1);
    }
}
