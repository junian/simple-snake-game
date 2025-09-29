#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX  500

int main()
{
    int n;
    double x, y;
    FILE *foutput;
    
    srand((unsigned) time(NULL));
    foutput = fopen("salesman_data.txt", "w");
    printf("Masukkan jumlah kota (n): ");
    scanf("%d", &n);
    fprintf(foutput, "%d\n", n);
    
    while(n > 0)
    {
        x = rand()%MAX;
        y = rand()%MAX;
        fprintf(foutput, "%lf %lf\n", x, y);
        n--;
    }
    
    fclose(foutput);
    system("pause");
    return 0;
}
