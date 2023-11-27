#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void request(int customer, int num_rows, int num_cols, int instances[num_cols], int available[num_cols], int allocation_matrix[num_rows][num_cols], int need_matrix[num_rows][num_cols]){

    for(int j = 0; j < num_cols; j++){
        allocation_matrix[customer][j] = allocation_matrix[customer][j] + instances[j];
        need_matrix[customer][j] = need_matrix[customer][j] - instances[j];
        available[j] = available[j] - instances[j];
    }
}

void release(int customer, int num_rows, int num_cols, int instances[num_cols], int available[num_cols], int allocation_matrix[num_rows][num_cols], int need_matrix[num_rows][num_cols]){

    for(int j = 0; j < num_cols; j++){
        allocation_matrix[customer][j] = allocation_matrix[customer][j] - instances[j];
        available[j] = available[j] + instances[j];
        need_matrix[customer][j] = need_matrix[customer][j] + instances[j];

    }
}

void print_all(int num_rows, int num_cols, int available[num_cols], int allocation_matrix[num_rows][num_cols], int need_matrix[num_rows][num_cols], int maximum_matrix[num_rows][num_cols]){
    printf("MAXIMUM | ALLOCATION | NEED\n");
    for(int i = 0; i < num_rows; i++){
        for(int j = 0; j < num_cols; j++){
            printf("%d ", maximum_matrix[i][j]);
        }
        printf("\t | ");

        for(int j = 0; j < num_cols; j++){
            printf("%d ", allocation_matrix[i][j]);
        }
        printf("\t | ");
    
        for(int j = 0; j < num_cols; j++){
            printf("%d ", need_matrix[i][j]);
        }
        printf("\n");
    }
    printf("AVAILABLE ");

    for(int j = 0; j < num_cols; j++){
        printf("%d ", available[j]);
    }
    printf("\n");
}

void printfarray(int length, int array[length]){
    for(int i = 0; i < length; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}

int compare(int customer, int num_cols, int copy_need_matrix[num_cols], int copy_available[num_cols]){
    int result = 0;
    
    for(int i = 0; i < num_cols; i++){
        if(copy_need_matrix[i] < copy_available[i]){
            result = -1;
        }else if(copy_need_matrix[i] > copy_available[i]){
            result = 1;
            break;
        }
    }
    return result;
}

void sum_array(int num_cols, int array1[num_cols], int array2[num_cols]){
    for(int i = 0; i < num_cols; i++){
        array1[i] = array1[i] + array2[i];
    }
}

int finished_check(int num_rows, int finished[num_rows]){
    for(int i = 0; i < num_rows; i++){
        if(finished[i] == 0){
            return 0;
        }
    }
    return 1;
}

int safe_state(int customer, int num_rows, int num_cols, int instances[num_cols], int available[num_cols], int allocation_matrix[num_rows][num_cols], int need_matrix[num_rows][num_cols], int maximum_matrix[num_rows][num_cols]){

    int finished[num_rows];
    for(int i = 0; i < num_rows; i++){
        finished[i] = 0; // array that represents if a job did finish or deadlocked - if 1 = finished, if 0 = not finished
    }

    int copy_available[num_cols];
    for(int i = 0; i <num_cols; i++){
        copy_available[i] = available[i];
    }

    int copy_maximum_matrix[num_rows][num_cols], copy_allocation_matrix[num_rows][num_cols], copy_need_matrix[num_rows][num_cols];
    for(int i = 0; i < num_rows; i++){
        for(int j = 0; j < num_cols; j++){
            copy_maximum_matrix[i][j] = maximum_matrix[i][j];
            copy_allocation_matrix[i][j] = allocation_matrix[i][j];
            copy_need_matrix[i][j] = need_matrix[i][j];
        }
    }
    
    request(customer, num_rows, num_cols, instances, copy_available, copy_allocation_matrix, copy_need_matrix);

    int finished_flag = 1;
    while(finished_flag == 1 && finished_check(num_rows, finished) == 0){
        finished_flag = 0;
        for(int i = 0; i < num_rows; i++){
            if(finished[i] == 0){
                
                if(compare(i, num_cols, copy_need_matrix[i], copy_available) != 1){
                    sum_array(num_cols, copy_available, copy_maximum_matrix[i]); 
                   
                    finished[i] = 1;
                    finished_flag = 1;
                }
            }
        }
    }
    
    if(finished_check(num_rows, finished) == 0){
        return 0;
    }

    return 1;
}

int request_verification(int customer, int num_rows, int num_cols, int instances[num_cols], int available[num_cols], int allocation_matrix[num_rows][num_cols], int need_matrix[num_rows][num_cols], int maximum_matrix[num_rows][num_cols]){
    
    for(int i = 0; i < num_cols; i++){
        if(maximum_matrix[customer][i] - instances[i] < 0 || need_matrix[customer][i] - instances[i] < 0){
            printf("The customer %d request ", customer);
            for(int j = 0; j < num_cols; j++){
                printf("%d ", instances[j]);
            }
            printf("was denied because exceed its maximum need\n");
            return 1;
        }else if(available[i] - instances[i] < 0){
            printf("The resources ");
            for(int j = 0; j < num_cols; j++){
                printf("%d ", available[j]);
            }
            printf("are not enough to costumer %d request ", customer);
            for(int j = 0; j < num_cols; j++){
                printf("%d ", instances[j]);
            }
            printf("\n");
            return 1;
        }else if(safe_state(customer, num_rows, num_cols, instances, available, allocation_matrix, need_matrix, maximum_matrix) == 0){
            printf("The customer %d request ", customer);
            for(int j = 0; j < num_cols; j++){
                printf("%d ", instances[j]);
            }
            printf("was denied because result in an unsafe state\n");
            return 1;
        }
    }

    printf("Allocate to customer %d the resources ", customer);
    for(int j = 0; j < num_cols; j++){
        printf("%d ", instances[j]);
    }
    printf("\n");
    
    return 0;
}

int release_verification(int customer, int num_rows, int num_cols, int instances[num_cols], int allocation_matrix[num_rows][num_cols]){
    
    for(int i = 0; i < num_cols; i++){
        if(allocation_matrix[customer][i] - instances[i] < 0){
            printf("The customer %d released ", customer);
            for(int j = 0; j < num_cols; j++){
                printf("%d ", instances[j]);
            }
            printf("was denied because exceed its maximum allocation\n");
            return 1;
        }
    }

    printf("Release from customer %d the resources ", customer);
    for(int j = 0; j < num_cols; j++){
        printf("%d ", instances[j]);
    }
    printf("\n");
    
    return 0;
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
    } //tem q arrumar pq se tiver 50 \n no arquivo vai dar como se tivesse 50 cliente sem ter
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
            int flag_request = 0;
            flag_request = request_verification(customer, num_rows, num_cols, instances, available, allocation_matrix, need_matrix, maximum_matrix);
           if(flag_request == 0){
                request(customer, num_rows, num_cols, instances, available, allocation_matrix, need_matrix);
            }
        }else if((strcmp(command, "RL") == 0)){
            int flag_release = 0;
            flag_release = release_verification(customer, num_rows, num_cols, instances, allocation_matrix);
            if(flag_release == 0){
                release(customer, num_rows, num_cols, instances, available, allocation_matrix, need_matrix);
            }
        }else if((strcmp(command, "*") == 0)){
            print_all(num_rows, num_cols, available, allocation_matrix, need_matrix, maximum_matrix);

        }else{
            printf("Invalid command.\n");
        } // fazer tratamento de erro aqui: se n foi nenhum dos tres, printar uma exceção

        row++;
    }
    free(line);
    fclose(commandsFile);

    return 0;
}