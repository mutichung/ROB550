#include <stdio.h>
#include <stdlib.h>

double* readMatrixFromFile(char* fileName, int height, int width);
int writeMatrixToFile(char* fileName, double* matrix, int height, int width);
double** readCsv2Mat(char* fileName, int height, int width);

struct Matrix {
    double** mat;
    int r;
    int c;
};


int main(int argc, char** argv){
    struct Matrix matA, matB;
    matA.r = atoi(argv[1]);
    matA.c = atoi(argv[2]);
    matB.r = atoi(argv[3]);
    matB.c = atoi(argv[4]);
    
    double* arrA = readMatrixFromFile("A.csv", matA.r, matA.c);
    matA.mat = (double **)malloc( sizeof(double *)*matA.r*matA.c );
    for(int i = 0; i < matA.r; i++) {
        matA.mat[i] = (double *)malloc( sizeof(double)*matA.c );
        for(int j = 0; j < matA.c; j++) {
            matA.mat[i][j] = arrA[i*matA.c + j];
            printf("\t%.4f", matA.mat[i][j]);
        }
        printf("\n");
    }
    free(arrA);
    printf("\n");

    double* arrB = readMatrixFromFile("B.csv", matB.r, matB.c);
    matB.mat = (double**)malloc( sizeof(double*)*matB.r*matB.c );
    for(int i = 0; i < matB.r; i++) {
        for(int j = 0; j < matB.c; j++) {
            matB.mat[i] = (double*)malloc( sizeof(double)*matB.c);
            matB.mat[i][j] = arrB[ i*matB.c + j];
            printf("\t%.4f", matB.mat[i][j]);
        }
        printf("\n");
    }
    free(arrB);
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

double** readCsv2Mat(char* fileName, int height, int width) {
    double* arr = readMatrixFromFile(fileName, height, width);

    double **mat = (double **)malloc( sizeof(double *)*height*width );
    for(int i = 0; i < height; i++) {
        mat[i] = (double *)malloc( sizeof(double)*width );
        for (int j = 0; j < width; j++) {
            mat[i][j] = arr[i*width + j];
            //printf("\t%.4f", mat[i][j]);
        }
        //printf("\n");
    }
    free(arr);
}

/*
double** matmult(double** matA, double** matB) {
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