#include <stdio.h>

int sum_matrix(int matrix[3][3], int matrix2[3][3]){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            matrix[i][j] = matrix[i][j] + matrix2[i][j];
        }
    }
    return 0;
}

int sub_matrix(int matrix[3][3], int matrix2[3][3]){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            matrix[i][j] = matrix[i][j] - matrix2[i][j];
        }
    }
    return 0;
}

int main(int argc, char *argv[]){

    // converting argv to int - available instance
    int available[argc-1];
    for(int i = 1; i < argc; i++){
        available[i-1] = atoi(argv[i]);
    }

    int num_col = argc-1;
    int num_rows;

    FILE *customerFile;
    FILE *commandsFile;

    

    // int matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // int matrix2[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    // for(int i = 0; i < 3; i++){
    //     for(int j = 0; j < 3; j++){
    //         printf("%d ", matrix[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("sum: \n");
    // sum_matrix(matrix, matrix2);
    // for(int i = 0; i < 3; i++){
    //     for(int j = 0; j < 3; j++){
    //         printf("%d ", matrix[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("sub: \n");
    // sub_matrix(matrix, matrix2);
    // for(int i = 0; i < 3; i++){
    //     for(int j = 0; j < 3; j++){
    //         printf("%d ", matrix[i][j]);
    //     }
    //     printf("\n");
    // }
    // return 0;
}