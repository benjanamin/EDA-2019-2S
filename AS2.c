#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int m=0;
int n=0;
int** leer(char* Nombre){
	FILE *fp;
	fp = fopen(Nombre, "r"); // read mode
 	char ch;
 	int flag=0;
 	int fila=0;
 	int contadorI=0;
 	int contadorJ=0;
    if (fp == NULL)
    {
    	FILE *fptr;
		fprintf(fptr,"ERROR, NO SE ENCUENTRA EL ARCHIVO DE LOS ALIENS");
		fclose(fptr);
    	exit(EXIT_FAILURE);
    }
    fscanf(fp,"%d %d",&m,&n);
    int** matriz=(int **)malloc(m * sizeof(int *)); 
    // a cada columna le asigna otro array
    for (int i = 0; i < m; i++) {
        matriz[i] = (int *)malloc(n * sizeof(int));
    }
    for(int i=0;i<m;i++){
    	for(int j=0;j<n;j++){
    		fscanf(fp,"%d",&matriz[i][j]);
    		
		}

		
	}

    fclose(fp);
    return matriz;
    
}
int getMayor(int**board){
	int aux=board[0][0];
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			if(board[i][j]>aux){
				aux=board[i][j];
			}
		}
	}
	return aux;
}
int getMenor(int**board){
	int aux=board[0][0];
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			if(board[i][j]<aux){
				aux=board[i][j];
			}
		}
	}
	return aux;
}

void printBoard(int **board){//se imprime el tableroBM
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			printf("%d ",board[i][j]);
		}
		printf("\n");
	}
}
int** suma(int** matriz1,int** matriz2){
	int** matriz=(int **)malloc(m * sizeof(int *)); 
    // a cada columna le asigna otro array
    for (int i = 0; i < m; i++) {
        matriz[i] = (int *)malloc(n * sizeof(int));
    }
    for(int i=0;i<m;i++){
    	for(int j=0;j<n;j++){
    		matriz[i][j]=matriz1[i][j]+matriz2[i][j];
		}
	}
	return matriz;
}
int** multiplicacion(int** matriz1,int** matriz2,int n1,int n2,int m1,int m2){
	int** matriz=(int **)malloc(n2 * sizeof(int *)); 
    // a cada columna le asigna otro array
    for (int i = 0; i < n2; i++) {
        matriz[i] = (int *)malloc(m1 * sizeof(int));
    }
    int aux;
    for(int i=0;i<n1;i++){
    	for(int j=0;j<m2;j++){
    		matriz[i][j]=matriz[i][j]
		}
	}
	return matriz;
}
int main(){
	int** board=leer("AS2.txt");
	int** board2=leer("AS2-2.txt");
	int**sumas= suma(board,board2);
	printBoard(sumas);
	printf("Menor: %d, Mayor: %d",getMenor(board),getMayor(board));
	return 0;
}
