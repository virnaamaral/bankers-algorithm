#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void request(int customer, int rows, int cols, int instances[cols], int available[cols], int allocation_matrix[rows][cols], int need_matrix[rows][cols]){

    for(int j = 0; j < cols; j++){
        allocation_matrix[customer][j] = allocation_matrix[customer][j] + instances[j];
        need_matrix[customer][j] = need_matrix[customer][j] - instances[j];
        available[j] = available[j] - instances[j];
    }
}

void release(int customer, int rows, int cols, int instances[cols], int available[cols], int allocation_matrix[rows][cols], int need_matrix[rows][cols]){

    for(int j = 0; j < cols; j++){
        allocation_matrix[customer][j] = allocation_matrix[customer][j] - instances[j];
        available[j] = available[j] + instances[j];
    }
}

void print_all(int rows, int cols, int available[cols], int allocation_matrix[rows][cols], int need_matrix[rows][cols], int maximum_matrix[rows][cols]){
    printf("MAXIMUM | ALLOCATION | NEED\n");
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            printf("%d ", maximum_matrix[i][j]);
        }
        printf("\t\t");

        for(int j = 0; j < cols; j++){
            printf("%d ", allocation_matrix[i][j]);
        }
        printf("\t\t");
    
        for(int j = 0; j < cols; j++){
            printf("%d ", need_matrix[i][j]);
        }
        printf("\n");
    }
    printf("AVAILABLE ");

    for(int j = 0; j < cols; j++){
        printf("%d ", available[j]);
    }
    printf("\n");

}

int main(int argc, char *argv[]){

    // setting up matrices maximum, need, and allocation

    int num_rows = 1, num_cols = 0; // ele ta vendo a quantidade de linhas pelos \n, e na ultima n tem \n

    // converting argv to int - available instances
    int available[argc-1];
    for(int i = 1; i < argc; i++){
        available[i-1] = atoi(argv[i]);
    }

    num_cols = argc-1;

    FILE *customerFile;

    // verifies if file exists
    customerFile = fopen("customer.txt", "r");
    if(customerFile == NULL){
        printf("Fail to read customer.txt\n");
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

    // if(){ // ainda n tem uma função q vê a quantidade de itens na customer
    //     printf("Incompatibility between customer.txt and command line\n");
    // }

    // feeds maximum and need matrices
    int maximum_matrix[num_rows][num_cols];
    int need_matrix[num_rows][num_cols];
    
    char *line = NULL;
    size_t len = 0;

    int row = 0;
    while ((getline(&line, &len, customerFile)) != -1){
        int col = 0;
        char *token = strtok(line, " ,\n");

        while(token != NULL && col < num_cols){
            maximum_matrix[row][col] = atoi(token);
            need_matrix[row][col] = atoi(token);
            token = strtok(NULL, " ,\n");
            col++;
        }
        row++;
        if(row == num_rows){
            break;
        }
    }
    free(line);
    fclose(customerFile);

    // set allocation values to 0
    int allocation_matrix[num_rows][num_cols];
    for(int i = 0; i < num_rows; i++){
        for(int j = 0; j < num_cols; j++){
            allocation_matrix[i][j] = 0;
        }
    }

    FILE *commandsFile;

    commandsFile = fopen("commands.txt", "r");
    if(commandsFile == NULL){
        printf("Fail to read commands.txt\n");
        exit(1);
    } // se o txt nao existir, nao puder ser aberto ou tiver numa formatacao diferente da que deveria ser, exibe a mensagem acima

    char command[2];
    int customer;
    int instances[num_cols];
    line = NULL;
    len = 0;
    row = 0;

    while ((getline(&line, &len, commandsFile)) != -1){
        int col = 0;
        int instances_count = 0;
        
        char *token = strtok(line, " \n");
        while(token != NULL && col < num_cols + 2){
            if(col == 0){
                strcpy(command, token);
            }else if(col == 1){
                customer = atoi(token);
            }else{
                instances[instances_count] = atoi(token);
                instances_count++;
            }
            token = strtok(NULL, " \n");
            col++;
        }

        if((strcmp(command, "RQ") == 0)){
            printf("\n================= REQUEST =================\n");
            request(customer, num_rows, num_cols, instances, available, allocation_matrix, need_matrix);
        }else if((strcmp(command, "RL") == 0)){
            printf("\n---------------- RELEASE ----------------\n");
            release(customer, num_rows, num_cols, instances, available, allocation_matrix, need_matrix);
        }else if((strcmp(command, "*") == 0)){
            printf("\n****************** ASTERISCO ******************\n");
            print_all(num_rows, num_cols, available, allocation_matrix, need_matrix, maximum_matrix);

        } // fazer tratamento de erro aqui: se n foi nenhum dos tres, printar uma exceção



        row++;
    }
    free(line);
    fclose(commandsFile);

    // for(int i = 0; i < num_rows; i++){
    //     for(int j = 0; j < num_cols; j++){
    //         printf("%d ", maximum_matrix[i][j]);
    //     }
    //     printf("\n");
    // }

    printf("\nnum rows: %d\n", num_rows);
    printf("num cols: %d\n", num_cols);

    return 0;
}