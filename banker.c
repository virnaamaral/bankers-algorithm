#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    int num_cols = 0, num_rows = 1;

    // converting argv to int - available instance
    int available[argc-1];
    for(int i = 1; i < argc; i++){
        available[i-1] = atoi(argv[i]);
    }

    num_cols = argc-1;

    FILE *customerFile;
    FILE *commandsFile;

    // verifies if file exists
    customerFile = fopen("customer.txt", "r");
    if(customerFile == NULL){
        printf("File does not exist.\n");
        exit(1);
    }

    // gets num_rows by reading file and looking for '\n's
    char ch;
    while((ch = fgetc(customerFile)) != EOF){
        if(ch == '\n'){
            num_rows++;
        }
    }
    fseek(customerFile, 0, SEEK_SET);

    // feeds maximum matrix
    int maximum_matrix[num_rows][num_cols];
    int aux;

    // char *token;


    // for(int i = 0; i < num_rows; i++){
    //     for(int j = 0; j < num_cols; j++){
    //         maximum_matrix[i][j] = aux;
    //     }
    // }

    // for(int i = 0; i < num_rows; i++){
    //     for(int j = 0; j < num_cols; j++){
    //         printf("%d ", maximum_matrix[i][j]);
    //     }
    //     printf("\n");
    // }

    int allocation_matrix[num_rows][num_cols];
    int need_matrix[num_rows][num_cols];

    printf("num cols: %d\n", num_cols);
    printf("num rows: %d\n", num_rows);

    return 0;
}