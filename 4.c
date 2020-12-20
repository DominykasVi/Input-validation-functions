#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void memory_allocation_check(void *pointer){
    if(pointer == NULL){
        printf("Cannot allocate memory\n");
        exit(1);
    }
}

int check_email(char *email, int size){
    for(int i = 0; i < size; ++i){
        if(email[i] == '@'){
            for(int j = i; j < size; ++j){
                if(email[j] == '.'){
                    if(i != 0 && email[i - 1] != '.' && email[i - 1] != ' '){//symbol before @
                        if(email[i + 1] != '.' && email[i + 1] != '@'){//symbol between @ and .
                            if(email[j + 1] != '.' && email[j + 1] != '@' && email[j + 1] != '\0'){
                                printf("Email entered correctly\n");
                                return 1;
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int main(){

    printf("This program stores all entered email address domains\n");
    printf("Enter here: ");
    int check = 0;
    char *email;
    int size;
    while (check == 0){

        char character;
        email = (char*) calloc(20, (sizeof(char)));
        size = 0;
        memory_allocation_check(email);
        while((character = getchar()) != '\n'){
            strcpy((email + size), &character);
            ++size;
            if (size % 19 == 0){
                email = realloc(email, (sizeof(char) * (size + 20)));
            }
        }
        if (size % 19 == 0){
            email = realloc(email, (sizeof(char) * size + 1));
            strcpy((email + size), "\0");
        } else{
            strcpy((email + size), "\0");
        }
        check = check_email(email, size);
        if(check == 0){
            printf("Wrong email input, please try again: ");
        }
    }
    char *email_domain;
    for(int i = 0; i < size; ++i){
        if(email[i] == '@'){
            email_domain = calloc((size-i), sizeof(char));
            strcpy(email_domain, (email + i +1));
            free(email);
            break;
        }
    }

    FILE *file_pointer;
    if ((file_pointer = fopen("email.txt", "a")) == NULL) {//file_name
        printf("Error! Cannot open email file\n");
        exit(1);
    } else {
        int successful_print = fprintf(file_pointer, "%s\n", email_domain);
        if(successful_print < 0){
            printf("Problem writing to file\n");
        }else {
            printf("Successfully written to file\n");
        }
    }


    fclose(file_pointer);
    free(email_domain);
    return 0;
}
