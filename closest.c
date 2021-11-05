/*
    Andrea Alexandra Sánez Oquendo RA:2126524
    Fernanda Rocha Costa Neto RA:2126605
    Patricia Abe Turato RA:2136007
*/
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<time.h>
#include<math.h>

typedef struct coordenada{
    double x; 
    double y;
} Coordenada;

double min(double x, double y);
double menor_distancia(Coordenada a, Coordenada b, Coordenada c, Coordenada d, Coordenada *par);
void merge_sortX(Coordenada* v, int i, int f);
void combinaX(Coordenada* v, int i, int m, int f);
void merge_sortY(Coordenada* v, int i, int f);
void combinaY(Coordenada* v, int ini, int m, int f);
double distancia_euclidiana(Coordenada a, Coordenada b);
double menor_dist_bruta(Coordenada* v, Coordenada* par, int i, int f);
double menor_dist_Y(Coordenada* v, Coordenada* par, int tam, double distX);
double combina_pares(Coordenada* v, Coordenada* par, double dm, int inicio, int m, int fim);
double par_mais_proximo(Coordenada* v, Coordenada *par, int i, int f);
double mais_proximo(Coordenada* v, Coordenada* par, int tam);

double min(double x, double y){
    return (x < y) ? x : y;
}

/* Atribui ao vetor par o par de coordenadas com menor distância entre si e retorna a menor distância */
double menor_distancia(Coordenada a, Coordenada b, Coordenada c, Coordenada d, Coordenada *par){
    
    double dist1 = distancia_euclidiana(a, b);
    double dist2 = distancia_euclidiana(c, d);
    
    if(dist1 == min(dist1, dist2)){
        par[0] = a;
        par[1] = b;
        return dist1;
    } else {
        par[0] = c;
        par[1] = d;
        return dist2;
    }
}

/* Ordenação do vetor em relação à abcissa */
void merge_sortX(Coordenada* v, int i, int f){ 
    if(i < f){ 
        int m = i + (f-i)/2;
        merge_sortX(v, i, m);
        merge_sortX(v, m+1, f);
        combinaX(v, i, m, f);
    }
}

/* Função de Combinação do Merge Sort X*/
void combinaX(Coordenada* v, int ini, int m, int f){

    int t_esq = m - ini + 1;
    int t_dir = f - m;

    Coordenada* esq = (Coordenada*)malloc(t_esq*sizeof(Coordenada));
    Coordenada* dir = (Coordenada*)malloc(t_dir*sizeof(Coordenada));

    for(int i = 0; i < t_esq; i++){
        esq[i] = v[i+ini];
    }
    for(int i = 0; i < t_dir; i++){
        dir[i] = v[m + i +1];
    }

    int i = 0, j = 0, k = ini;
    while (i < t_esq && j < t_dir){
        if(esq[i].x <= dir[j].x){
            v[k] = esq[i];
            i++;
        } else{
            v[k] = dir[j];
            j++;
        }
        k++;
    }

    while(i<t_esq){
        v[k] = esq[i];
        i++;
        k++;
    }

    while(j<t_dir){
        v[k] = dir[j];
        j++;
        k++;
    }

    free(esq);
    free(dir);
}

/* Ordenação do vetor em relação à ordenada */
void merge_sortY(Coordenada* v, int i, int f){ 
    if(i < f){ 
        int m = i + (f-i)/2;
        merge_sortY(v, i, m);
        merge_sortY(v, m+1, f);
        combinaY(v, i, m, f);
    }
}

/* Função de Combinação do Merge Sort Y*/
void combinaY(Coordenada* v, int ini, int m, int f){

    int t_esq = m - ini + 1;
    int t_dir = f - m;

    Coordenada* esq = (Coordenada*)malloc(t_esq*sizeof(Coordenada));
    Coordenada* dir = (Coordenada*)malloc(t_dir*sizeof(Coordenada));

    for(int i = 0; i < t_esq; i++){
        esq[i] = v[i+ini];
    }
    for(int i = 0; i < t_dir; i++){
        dir[i] = v[m + i +1];
    }

    int i = 0, j = 0, k = ini;
    while (i < t_esq && j < t_dir){
        if(esq[i].y <= dir[j].y){
            v[k] = esq[i];
            i++;
        } else{
            v[k] = dir[j];
            j++;
        }
        k++;
    }

    while(i<t_esq){
        v[k] = esq[i];
        i++;
        k++;
    }

    while(j<t_dir){
        v[k] = dir[j];
        j++;
        k++;
    }

    free(esq);
    free(dir);
}

/* Calcula a distância euclidiana entre duas coordenadas */
double distancia_euclidiana(Coordenada a, Coordenada b){
    return sqrt(pow(a.x - b.x, 2)+pow(a.y - b.y, 2));
}

/* Calcula as distâncias entre até 3 coordenadas de forma bruta e retorna a menor delas */
double menor_dist_bruta(Coordenada* v, Coordenada* par, int i, int f){

    if(i == f) return -1;

    Coordenada* aux = (Coordenada*) malloc(2 *sizeof(Coordenada));
    double dmin = distancia_euclidiana(v[i], v[f]);
    par[0] = v[i];
    par[1] = v[f];
    
    if(f == i + 2){  
        dmin = menor_distancia(v[i+1], v[f], v[i], v[i+1], aux);
        dmin = menor_distancia(v[i], v[f], aux[0], aux[1], par);   
    } 

    free(aux);
    return dmin;
}

/* Verifica se há pares com uma distância menor que distX nas fronteiras do ponto mediano utilizado */
double menor_dist_Y(Coordenada* v, Coordenada* par, int tam, double distX){

    double menor = distX;
    double distY;
    
    for(int i = 0; i < tam; i++){ 
        /* o tamanho do vetor percorrido é muito menor do que n, pois está limitado pela menor distância encontrada até o momento no vetor, portanto, é considerado O(1) */
        for(int j = i+1; j < tam && distancia_euclidiana(v[i], v[j]) < distX ; j++){
            distY = distancia_euclidiana(v[i], v[j]); 
            if (distY < menor){ 
                menor = distY;
                par[0] = v[i];
                par[1] = v[j];
            }
        }   
    }
    return menor;
}

/* Etapa de combinação do Algoritmo de Divisão e Conquista par_mais_proximo*/
double combina_pares(Coordenada* v, Coordenada* par, double dm, int inicio, int m, int fim){

    int a = m, b=m;
    
    int i = m - 1;
    while(i > inicio && (v[m].x - v[i].x < dm)){
        a--;
        i--;
    }

    int j = m+1;
    while(j < fim && (v[j].x - v[m].x) < dm){
        b++;
        j++;
    }

    int tam = b - a + 1; 
    if(tam > 1){
        Coordenada* aux = (Coordenada*)malloc(tam*sizeof(Coordenada)); 
        
        j = a;
        for(i = 0; i < tam; i++, j++){
            aux[i] = v[j];
        }

        merge_sortY(aux, 0, tam-1);
        double menor = menor_dist_Y(aux, par, tam, dm);
        
        free(aux);
        return menor;
    }
    
    return dm;
}

/* Algoritmo de Divisão e Conquista para dividir o vetor em partes e calcular suas distâncias em pequenos pedaços. */
double par_mais_proximo(Coordenada* v, Coordenada *par, int i, int f){ 
    
    if (f <= i + 2){
        return menor_dist_bruta(v, par, i, f);
    } else {
            double dist_e, dist_d, dm;
            int m = i + (f-i)/2;

            Coordenada* par_e = (Coordenada*)malloc(2*sizeof(Coordenada));
            Coordenada* par_d = (Coordenada*)malloc(2*sizeof(Coordenada));

            dist_e = par_mais_proximo(v, par_e, i, m);
            dist_d = par_mais_proximo(v, par_d, m+1, f);
            dm = menor_distancia(par_e[0], par_e[1], par_d[0], par_d[1], par);

            free(par_d);
            free(par_e);

            return combina_pares(v, par, dm, i, m, f);
    }
}

/* Para entrar no Algoritmo de Divisão e Conquista o vetor deve estar ordenado pelo eixo x, então mais_proximo chama a ordenação e logo o algoritmo recursivo. */
double mais_proximo(Coordenada* v, Coordenada* par, int tam){
    merge_sortX(v,0,tam -1);
    return par_mais_proximo(v, par, 0, tam - 1);
}

int main(int argc, char* argv[]){
    
    if(argc !=2){
        return 1;
    }

    
    Coordenada* v;
    int tam = 0;
    
    /*--------- ler coordenadas ---------*/
    FILE* file = fopen (argv[1], "r");
    fscanf (file, "%d", &tam);    
    
    int i = 0;
    v = (Coordenada*)malloc(tam*sizeof(Coordenada));
    double x,y;
    
    while (i < tam)
    {  
      fscanf (file, "%le %le", &v[i].x, &v[i].y);
      i++;   
    }
    
    fclose (file); 

    /*--------- termina de ler coordenadas ---------*/

    Coordenada *par = (Coordenada*)malloc(2*sizeof(Coordenada));
    
    clock_t inicio = clock();  
    double menor = mais_proximo(v, par, tam);
    clock_t fim = clock();
    
    printf("%.6f %.6f %.6f %.6f %.6f %.6f\n", 1.0*(fim-inicio)/CLOCKS_PER_SEC, menor, par[0].x, par[0].y, par[1].x, par[1].y);
    free(par);
    free(v);
    return 0;
}