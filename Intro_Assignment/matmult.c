#include <stdio.h>
#include <stdlib.h>

double* readMatrixFromFile(char* fileName, int height, int width);
int writeMatrixToFile(char* fileName, double* matrix, int height, int width);
struct Matrix matmult(struct Matrix matA, struct Matrix matB);

struct Matrix {
    double** mat;
    int r;
    int c;
};


int main(int argc, char** argv){
    struct Matrix matA, matB, matC;
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
    printf("\n");

    matC = matmult(matA, matB);
    for(int i = 0; i < matC.r; i++) {
        for(int j = 0; j < matC.c; j++) {
            printf("\t%.4f", matC.mat[i][j]);
        }
        printf("\n");
    }
    
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

struct Matrix matmult(struct Matrix matA, struct Matrix matB) {
    struct Matrix out;
    out.r = matA.r;
    out.c = matB.c;
    out.mat = (double**)malloc( sizeof(double*)*out.r*out.c );
    for(int i = 0; i < out.r; i++) {
        for(int j = 0; j < out.c; j++) {
            out.mat[i] = (double*)malloc( sizeof(double)*out.c );
            out.mat[i][j] = 0;
        }
    }

    //TODO: check compatibility
    for(int i = 0; i < matA.r; i++) {
        for(int j = 0; j < matB.c; j++) {
            for(int k = 0; k < matA.c; k++) out.mat[i][j] += matA.mat[i][k]*matB.mat[k][j];
        }
    }
    return out;
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