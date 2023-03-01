#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int n, m;
int **t;
int culoare = 1;
int nr_sol = 0;


typedef struct {
    int x;
    int y;
}punct;

typedef struct {
    punct punct_referinta;
    punct punct2;
    punct punct3;
    punct punct4;
}forma;


forma S1 = { {0,0}, {0,1}, {-1,1}, {-1,2} }; //0

forma S2 = { {0,0}, {-1,0}, {-1,1}, {-2,1} }; //1

forma S3 = { {0,0}, {0,1}, {-1,0}, {-1,-1} }; //2

forma S4 = { {0,0}, {-1,0}, {-1,-1}, {-2,-1} }; //3

forma L1 = { {0,0}, {-1,0}, {-2,0}, {0,1} }; //4

forma L2 = { {0,0}, {0,1}, {0,2}, {-1,2} }; //5

forma L3 = { {0,0}, {-1,0}, {-2,0}, {-2,-1} }; //6

forma L4 = { {0,0}, {-1,0}, {-1,1}, {-1,2} }; //7

forma T1 = { {0,0}, {0,1}, {-1,1}, {0,2} }; //8

forma T2 = { {0,0}, {-1,0}, {-2,0}, {-1,1} }; //9

forma T3 = { {0,0}, {-1,-1}, {-1,0}, {-1,1} }; //10

forma T4 = { {0,0}, {-1,-1}, {-1,0}, {-2,0} }; //11

forma I1 = { {0,0}, {-1,0}, {-2,0}, {-3,0}}; //12

forma I2 = { {0,0}, {0,1}, {0,2}, {0,3} }; //13

forma patrat = { {0,0}, {-1,0}, {0,1}, {-1,1} }; //14

forma O = {{0,0}, {-100,0}, {0,0}, {0,0} }; //15


void colorare(int x, int piesa, forma** index){
    int i =n - 1 - x/m;
    int j = x%m;
        t[ i + index[piesa]->punct_referinta.x ][ j + index[piesa]->punct_referinta.y ] +=culoare;
        if(index[piesa]->punct2.x != -100){
            t[ i + index[piesa]->punct2.x ][ j + index[piesa]->punct2.y ] +=culoare;
            t[ i + index[piesa]->punct3.x ][ j + index[piesa]->punct3.y ] +=culoare;
            t[ i + index[piesa]->punct4.x ][ j + index[piesa]->punct4.y ] +=culoare;
            }
}

void decolorare(int x, int piesa, forma** index, int culoarea){
    int i =n - 1 - x/m;
    int j = x%m;
        t[ i + index[piesa]->punct_referinta.x ][ j + index[piesa]->punct_referinta.y ] -=culoarea;
        if(index[piesa]->punct2.x != -100){
            t[ i + index[piesa]->punct2.x ][ j + index[piesa]->punct2.y ] -=culoarea;
            t[ i + index[piesa]->punct3.x ][ j + index[piesa]->punct3.y ] -=culoarea;
            t[ i + index[piesa]->punct4.x ][ j + index[piesa]->punct4.y ] -=culoarea;
            }
}

void afisare_tabla(FILE *f){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++)
            fprintf(f,"%d ", t[i][j]);
        fprintf(f,"\n");
    }
    fprintf(f,"\n\n\n");
}

void creere_tabla(FILE *f){

    FILE *g = fopen("date.in","r");

        fscanf(g,"%d", &n);
        fscanf(g,"%d", &m);


    fclose(g);

    t =(int **)calloc(n,sizeof(int*));
    for(int i = 0; i < n; i++)
        t[i] =(int*)calloc(m,sizeof(int));

}

int in_matrice(int x, int piesa, forma** index){
    int i =n - 1 - x/m;
    int j = x%m;
    if(i < 0 || i > n - 1)
        return 0;
    if( j < 0 || j > m - 1)
        return 0;
    if(index[piesa]->punct2.x != -100){
        
        if(i + index[piesa]->punct2.x < 0 || i + index[piesa]->punct2.x > n - 1)
            return 0;
        if(j + index[piesa]->punct2.y < 0 || j + index[piesa]->punct2.y  > m - 1)
            return 0;

        if(i + index[piesa]->punct3.x < 0 || i + index[piesa]->punct3.x > n - 1)
            return 0;
        if(j + index[piesa]->punct3.y < 0 || j + index[piesa]->punct3.y  > m - 1)
            return 0;

        if(i + index[piesa]->punct4.x < 0 || i + index[piesa]->punct4.x > n - 1)
            return 0;
        if(j + index[piesa]->punct4.y < 0 || j + index[piesa]->punct4.y  > m - 1)
            return 0;
    }
  
    
    return 1;
}


int are_loc (int x, int piesa, forma** index){
    int i =n - 1 - x/m;
    int j = x%m;
     if(t[ i ][ j ] != 0) 
        return 0;
    if(index[piesa]->punct2.x != -100){
        if(t[ i + index[piesa]->punct2.x ][ j + index[piesa]->punct2.y ] != 0)
            return 0;
        if(t[ i + index[piesa]->punct3.x ][ j + index[piesa]->punct3.y ] != 0)
            return 0;
        if(t[ i + index[piesa]->punct4.x ][ j + index[piesa]->punct4.y ] != 0)
            return 0;
    }
        return 1;
}


int matrice_umpluta(){
    for(int i =0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(t[i][j] == 0)
                return 0;
    return 1;
}

void bkt(int x, FILE *f, forma** index){

    int i =n - 1 - x/m;
    int j = x%m;
    if(x < n*m){
       if(t[i][j] != 0)
           bkt(x+1,f,index);
        else{
            for(int piesa = 0; piesa <=15; piesa++)
            {
                if(in_matrice(x,piesa,index))
                    if(are_loc(x,piesa,index)){//sol partiala
                        colorare(x,piesa,index);
                        int culoare_locala = culoare;
                        culoare++;
                        if(matrice_umpluta()){// sol finala
                            afisare_tabla(f);
                            nr_sol++;
                        }
                        else
                            bkt(x+1, f, index);
                        decolorare(x,piesa,index, culoare_locala);
                        culoare--;
                    }   
            }
        }
    }
}


int main(){
    FILE * f = fopen("tabla.out", "w");
                //   0    1    2    3    4    5    6    7    8    9   10   11   12    13    14     15
forma* index[16] = {&S1, &S2, &S3, &S4, &L1, &L2, &L3, &L4, &T1, &T2, &T3, &T4, &I1, &I2, &patrat, &O};

    creere_tabla(f);
    bkt(0,f, index);


    fclose(f);
    return 0;
}
