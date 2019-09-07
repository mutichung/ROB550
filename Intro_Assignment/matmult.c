#include <stdio.h>
#include <stdlib.h>

double* readMatrixFromFile(char* fileName, int height, int width);
int writeMatrixToFile(char* fileName, double* matrix, int height, int width);



int main(int argc, char** argv){
    int rowA = atoi(argv[1]);
    int colA = atoi(argv[2]);
    int rowB = atoi(argv[3]);
    int colB = atoi(argv[4]);
    
    double* arrA = readMatrixFromFile("A.csv", rowA, colA);
    double* arrB = readMatrixFromFile("B.csv", rowB, colB);
    double** test[rowA][colA];
    printf("%ld\n\n", sizeof(test)/sizeof(test[0][0]));

    for(int i = 0; i < rowA; i++) {
        for(int j = 0; j < colA; j++) {

        }
        printf("%f\n", arrA[i]); 
    }

    printf("%d %d %d %d\n", rowA, colA, rowB, colB);
    
}

/**
 * Allocates a matrix which must be free'd by the calling free()
 */
double* readMatrixFromFile(char* fileName, int height, int width) {
    FILE* fp = fopen(fileName, "r");
    if (fp == NULL) {
        fprintf(stderr, "Can't open %s.\n", fileName);
        return NULL;
    }
    double val;
    double* M = (double*) malloc(height * width * sizeof(double));
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
        if (fscanf(fp, " %lf", &val) != 1) {
            fprintf(stderr, "Couldn't read value.\n");
            return NULL;
        }
        // Discard the comma without checking.
        fgetc(fp);
        M[i * width + j] = val;
        }
    }
    fclose(fp);
    return M;
}
/*
int writeMatrixToFile(char* fileName, double* matrix, int height, int width) {
    FILE* fp = fopen(fileName, "w");
    if (fp == NULL) {
        return 1;
    }
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
        if (j > 0) {
            fputc(',', fp);
        }
        fprintf(fp, "%lf", matrix[i*width +j]);
        }
        fputs("\r\n", fp);
    }
    fclose(fp);
    return 0;
}
double** matmilt(double** matA, double** matB) {
    double** out;
    for(int i = 0; i <= matA.row; i++) {
        for(int j = 0; j <= matB.col; j++) {
            double temp = 0;
            for(int k = 0; k <= matA.col; k++) {
                temp += matA.mat[i][k] * matB.mat[k][j];
            }
        }
    }
}
*/