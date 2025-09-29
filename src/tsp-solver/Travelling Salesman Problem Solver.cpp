#include <allegro.h>
#include <stdio.h>
#include <math.h>

#define MAKS        500
#define RADIUS        3
#define EMPTY        -1

typedef struct
{
    double length;
    int next_city;
}ROUTE; 

typedef struct
{
    double x;
    double y;
    ROUTE *city_route;
}KOORD;

double panjang(KOORD *dot1, KOORD *dot2);
int* generate_shortest_route(KOORD *city, int n, int *start, double *panjang);

void quicksort(ROUTE *data, int left, int right);
void generate_city_connection(KOORD *city, int n);
void draw_line(BITMAP *bmp, KOORD *dot1, KOORD *dot2);
void make_circle(BITMAP *dest, KOORD *city);
void init();
void deinit();

int main() 
{
	init();
    
    double length;
    int n, i, j;
    int start;
    int *shortest_path;
    int g;
    
    FILE *finput;
    BITMAP *city_box;
    KOORD *city;
    
    city_box = create_bitmap(MAKS+4, MAKS+4+16);    
    finput = fopen("salesman_data.txt", "r");
    
    clear_to_color(city_box, makecol(255, 255, 255));
    fscanf(finput, "%d", &n);
    
    city = (KOORD*) malloc(sizeof(KOORD)*n);
    clear_to_color(screen, makecol(255, 255, 255));
    for(i=0; i<n; i++)
    {
        fscanf(finput, "%lf %lf", &(city[i].x), &(city[i].y));
        make_circle(city_box, &(city[i]));
        city[i].city_route = (ROUTE*) malloc(sizeof(ROUTE)*(n-1));
    }
    
    generate_city_connection(city, n);
    shortest_path = generate_shortest_route(city, n, &start, &length);
	
	g = start;
    for(i=0; i<n; i++)
    {
        draw_line(city_box, &city[g], &city[city[g].city_route[shortest_path[i]].next_city]);
        g = city[g].city_route[shortest_path[i]].next_city;
    }
    textprintf_ex(screen, font, 10, 10, makecol( 0, 0, 0), -1, "jalan terpendek: %lf px", length);
    while (!key[KEY_ESC])
    {
        draw_sprite(screen, city_box, (SCREEN_W-city_box->w)/2, (SCREEN_H-city_box->h)/2);    
        readkey();
	}
    
    for(i=0; i<n; i++)
        free(city[i].city_route);
        
    destroy_bitmap(city_box);
    fclose(finput);
	free(city);
	free(shortest_path);
    deinit();
	return 0;
}
END_OF_MAIN()

void make_circle(BITMAP *dest, KOORD *city)
{
    int x, y;
    x = (int) city->x;
    y = (int) city->y;
    circlefill(dest, x+2, y+2, RADIUS, makecol(0, 255, 0));
}

void init()
{
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
	
    if (res != 0)
    {
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard();
	install_mouse();
	
	set_window_title("Travelling Salesman Problem by Junian Triajianto - 5108100038");
}

void deinit()
{
	clear_keybuf();
}

double panjang(KOORD *dot1, KOORD *dot2)
{
    double hasil;
    hasil = sqrt(pow(dot2->x - dot1->x, 2) + pow(dot2->y - dot1->y, 2));
    return hasil;
}

void draw_line(BITMAP *bmp, KOORD *dot1, KOORD *dot2)
{
    line(bmp, (int) dot1->x+2, (int) dot1->y+2, (int) dot2->x, (int) dot2->y, makecol(255, 0, 0));
}

void generate_city_connection(KOORD *city, int n)
{
    int i, j, k;
    for(i=0; i<n; i++)
    {
        k=0;
        for(j=0; j<n; j++)
        {
            if(j!=i)
            {
                city[i].city_route[k].next_city = j;
                city[i].city_route[k].length = panjang(&(city[i]), &(city[j]));
                k++;
            }
        }
        quicksort(city[i].city_route, 0, n-2);
    }
}

void quicksort(ROUTE *data, int left, int right)
{
    if(left >= right) return;
    int pivot = left, pointer = right;
    int pointerMove = -1, temp;
    ROUTE rtemp;
    while(pivot != pointer)
    {
        if((data[pivot].length>data[pointer].length && pointerMove == -1) || (data[pivot].length<data[pointer].length && pointerMove == +1))
        {
               rtemp = data[pivot];
               data[pivot] = data[pointer];
               data[pointer] = rtemp;
               
               temp = pivot;
               pivot = pointer;
               pointer = temp;
               pointerMove *= -1;
        }
        pointer += pointerMove;
    }
    quicksort(data, left, pivot - 1);
    quicksort(data, pivot + 1, right);
}

int* generate_shortest_route(KOORD *city, int n, int *start, double *panjang)
{
    bool *city_list = (bool*) malloc(sizeof(bool)*n);
    int i, j, k;
    int *list = (int*) malloc(sizeof(int)*n);
    int *shortest_path = (int*) malloc(sizeof(int)*n);
    int *temp;
    int go_next_city;
    
    double total_length = EMPTY;
    double last_length;
    
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            city_list[j] = true;
        }
        
        last_length = 0;
        go_next_city = i;
        
        for(j=0; j<n-1; j++)
        {
            k=0;
            city_list[go_next_city] = false;
            while(1)
            {
                if(city_list[city[go_next_city].city_route[k].next_city]) break;
                k++;
            }
                    
            list[j] = k;
            last_length += city[go_next_city].city_route[k].length;
            go_next_city = city[go_next_city].city_route[k].next_city;
            
        }
        
        k=0;
        
        while(1)
        {
            if(city[go_next_city].city_route[k].next_city == i) 
            {
                list[n-1] = k;
                last_length += city[go_next_city].city_route[k].length;
                break;
            }
            k++;
        }
        
        if(last_length<total_length || total_length==EMPTY)
        {
            total_length = last_length;
            *panjang = total_length;
            *start = i;
            temp = list;
            list = shortest_path;
            shortest_path = temp;
        }       
    }
    
    free(list);
    free(city_list);
    return shortest_path;
}
