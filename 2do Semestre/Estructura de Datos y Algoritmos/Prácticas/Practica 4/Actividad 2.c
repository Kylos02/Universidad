#include <stdio.h>
#include <stdlib.h>
#define NG 15
#define n 10
#define m 13

int **forma_Imagen(int ren,int col);
int *forma_Histograma(int ng);
void llena_Imagen(int **imagen,int ren,int col);
void cal_Histograma(int **imagen, int *histog,int ren,int col);
void histograma_I(void);

int main()
{
    int **imagen, *histog,i;
    imagen=forma_Imagen(n,m);
    if(imagen ==NULL)
    {
        return 1;
    }
    llena_Imagen(imagen,n,m);
    histog=forma_Histograma(NG);
    histograma_I();
}

int **forma_Imagen(int ren, int col)
{
    int **imagen, i;
    imagen=(int **)calloc(ren,sizeof(int *));
    if (imagen != NULL){
    for (i=0; i<ren; i++){
        imagen[i]=(int *)calloc(col,sizeof(int));
    }
    return imagen;
    }
}

int *forma_Histograma(int ng)
{
    int *histog;
    histog=(int *)calloc(ng,sizeof(int));
    return histog;
}

void llena_Imagen(int **imagen,int ren,int col)
{
    
    int i,j;
    for(i=0;i<ren;i++)
    {
        for(j=0;j<col;j++)
        {
            *(*(imagen+i)+j)=rand()%NG;
        }
    }
}

void histograma_I(void)
{ 
    int n1=n,m1=m;
    printf("\n");
    int I[n1][m1],histog[NG],i,j;
    for(i=0;i<n1;i++)
    {
        for(j=0;j<m1;j++)
        {
         I[i][j]=rand()%NG;
        }
    }

    for(i=0;i<NG;i++)
    {
        histog[i]=0;
    }

    for(i=0;i<n1;i++)
    {
        for(j=0;j<m1;j++)
        {
            histog[I[i][j]]+=1;
        }
    }

    for(i=0;i<n1;i++)
    {
        for(j=0;j<m1;j++)
        {
            printf("%d    \n",I[i][j]);
        }
    }
    
printf("\nIndice    Ocurrencia\n");
    for(i=0;i<NG;i++)
    {
        printf("%i         %d\n",i,histog[i]);
    }
}

