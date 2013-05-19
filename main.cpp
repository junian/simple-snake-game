#include <allegro.h>

#define SIZE_X       40
#define SIZE_Y       30
#define OBJECT_SIZE  20
#define BLACK        0

#define EAT          3
#define HEAD        -2
#define BODY        -3
#define WALL        -1
#define PATH         0


typedef struct stSNAKE
{
    int x;
    int y;
    struct stSNAKE *next;
}SNAKE;

void add_body(SNAKE **snake, int x, int y, int map[SIZE_Y][SIZE_X]);
int  move_snake(SNAKE *snake, int moveX, int moveY, int map[SIZE_Y][SIZE_X]);
void init();
void deinit();

int main()
{
	init();
	set_window_title("Team27, inc - Innocent Snake");
	srand((unsigned)time(NULL));
	
	//kondisi map awal
	int map[SIZE_Y][SIZE_X] = {-1,-1,-1,-1,-1,-1,-1, 0, 0, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 0, 0, 0,-1,-1,-1,-1, 0, 0, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,
                               -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,
                               -1, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,
                               -1, 0, 0, 0,-1,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,
                               -1, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,
                               -1, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,
                               -1, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,
                               -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,-1,-1,-1,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,
                               -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,
                               -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,-1,-1, 0, 0, 0, 0,
                               -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0,-1,
                               -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0,-1,
                               -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0,-1,
                               -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,-1,-1,-1,-1, 0, 0, 0,-1,-1,-1,-1,-1,-1, 0, 0,-1,
                               -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0,-1,
                               -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0,-1,
                               -1, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0,-1,
                               -1, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0,-1,
                               -1, 0, 0, 0, 0, 0, 0,-1,-1,-1,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,
                               -1, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,
                               -1, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,
                               -1, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,
                               -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,
                               -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,
                               -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,
                               -1,-1,-1,-1,-1,-1,-1, 0, 0, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 0, 0, 0,-1,-1,-1,-1, 0, 0, 0,-1,-1,-1,-1,-1,-1,-1,-1,-1};

	int counter = 0;
	int posX, posY;
	int loaded = 0;
	int x_his, y_his;
    int i, j, moveX = 1, moveY = 0;
    
    BITMAP *buffer      = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP *path        = create_bitmap(OBJECT_SIZE, OBJECT_SIZE);
    BITMAP *wall        = load_bitmap("wall.bmp", NULL);
    BITMAP *head        = load_bitmap("head.bmp", NULL);
    BITMAP *snake_body  = load_bitmap("body.bmp", NULL);
    BITMAP *eat         = create_bitmap(OBJECT_SIZE, OBJECT_SIZE);
    BITMAP *bg_map      = create_bitmap(SCREEN_W, SCREEN_H);
    
    SNAKE  *snake       = NULL;
    SNAKE  *pointer     = NULL;
                  
    clear_to_color(path, makecol(255, 255, 255)); //jalan berwarna putih
    clear_to_color(eat,  makecol(255, 255, 255)); //makanan backgroundnya putih
    circlefill(eat, OBJECT_SIZE/2, OBJECT_SIZE/2, OBJECT_SIZE/2 - 4, makecol(255, 0, 0)); //makanan berwarna merah
    
    //membuat map snake di bitmap
    for(i=0; i<SIZE_Y; i++)
    {
        for(j=0; j<SIZE_X; j++)
        {
            switch(map[i][j])
            {
                case PATH : draw_sprite(bg_map, path, j*OBJECT_SIZE, i*OBJECT_SIZE);
                                break;
                case WALL : draw_sprite(bg_map, wall, j*OBJECT_SIZE, i*OBJECT_SIZE);
                                break;
            }
        }
    }
    
    //inisialisasi awal posisi snake    
    add_body(&snake, 3, 1, map);
    map[snake->y][snake->x] = HEAD;
    add_body(&snake, 2, 1, map);
    add_body(&snake, 1, 1, map);

    set_keyboard_rate(10, 10);
	
    while (!key[KEY_ESC])
    {
        //deteksi apakah sudah ada makanan di map
        if(loaded==0){
            do{
                posX = rand()%(SIZE_X-1) + 1;
                posY = rand()%(SIZE_Y-1) + 1;
            }while(map[posY][posX] != PATH);
            map[posY][posX] = EAT;
            loaded = 1;
        }
        
        //deteksi keyboard yang ditekan dan mengubah arah gerak snake
        if(counter==5){  
            if(key[KEY_UP] && moveY==0)
            {
                moveX=0;
                moveY=-1;
                clear_keybuf();
            }
            else if(key[KEY_DOWN] && moveY==0)
            {
                moveX=0;
                moveY=1;
                clear_keybuf();
            }
            else if(key[KEY_LEFT] && moveX==0)
            {
                moveX=-1;
                moveY=0;
                clear_keybuf();
            }
            else if(key[KEY_RIGHT] && moveX==0)
            {
                moveX=1;
                moveY=0;
                clear_keybuf();
            }
            x_his = snake->x;
            y_his = snake->y;
		  
		  //kalau menabrak sesuatu maka keluar
          if(!move_snake(snake, moveX, moveY, map)) break;
		  
		  //jika bertemu makanan maka tambah badan
          if(map[posY][posX] != EAT)
          {
                add_body(&snake, x_his, y_his, map);
                loaded = 0;
          }
		  counter=0;
        }
        counter++;
		
		//tempelkan semua obyek ke buffer
		draw_sprite(buffer, bg_map, 0, 0);
		draw_sprite(buffer, eat, posX*OBJECT_SIZE, posY*OBJECT_SIZE);
		for(pointer = snake; pointer != NULL; pointer = pointer->next)
        { 
            switch(map[pointer->y][pointer->x])
            {
                case BODY : draw_sprite(buffer, snake_body, pointer->x*OBJECT_SIZE, pointer->y*OBJECT_SIZE);
                            break;
                case HEAD : draw_sprite(buffer, head, pointer->x*OBJECT_SIZE, pointer->y*OBJECT_SIZE);
                            break; 
            }
        }
        
        //tampilkan buffer ke screen
        draw_sprite(screen, buffer, 0, 0);
		clear_bitmap(buffer);
		rest(10);
	}
    
    //destroy semua bitmap
    destroy_bitmap(head);
    destroy_bitmap(buffer);
    destroy_bitmap(path);
    destroy_bitmap(wall);
    destroy_bitmap(snake_body);
    destroy_bitmap(eat);
    
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
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard();
	/* add other initializations here */
}

void deinit() {
	clear_keybuf();
	/* add other deinitializations here */
}

//fungsi untuk menambah badan
void add_body(SNAKE **snake, int x, int y, int map[SIZE_Y][SIZE_X])
{
    SNAKE *new_body = (SNAKE*) malloc(sizeof(SNAKE));
    if(new_body == NULL) return;
    new_body->next = *snake;
    *snake = new_body;
    new_body->x = x;
    new_body->y = y;
    map[y][x] = BODY;
}

//fungsi untuk menggerakkan snake
int move_snake(SNAKE *snake, int moveX, int moveY, int map[SIZE_Y][SIZE_X])
{
    map[snake->y][snake->x] = PATH;
    while(true)
    {
        if(snake->next == NULL)
        {
            snake->x += moveX;
            if(snake->x >= SIZE_X) snake->x = 0;
            else if(snake->x < 0) snake->x = SIZE_X - 1;
            
            snake->y += moveY;
            if(snake->y >= SIZE_Y) snake->y = 0;
            else if(snake->y < 0) snake->y = SIZE_Y - 1;
            
            if(map[snake->y][snake->x] < 0){
                allegro_message("nabrak...");
                return 0;
            }
            map[snake->y][snake->x] = HEAD;
            return 1;
        }
        snake->x = snake->next->x;
        snake->y = snake->next->y;
        map[snake->y][snake->x] = BODY;
        snake = snake->next;
    }
}
