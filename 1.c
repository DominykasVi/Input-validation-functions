#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int number_check(char *number){
    number = strrchr(number, ',');
    if( number != NULL ){
        if(strlen(number) <= 4){
            return strlen(number);
        } else {
            return 1;
        }
    }

    return 0;
}

double read_number(FILE *file_pointer, char *number_char) {
    double number;

    fgets(number_char, 8, file_pointer);
    if(fgets(number_char, 8, file_pointer) != NULL){
        return -1;
    }

    number = atoi(number_char);
    if (strchr(number_char, '.') != NULL){
        return -1;
    }
    if (number >= 10 && number <= 1000){
        return number;
    }
    else{
        return -1;
    }

}

void memory_allocation_check(void *pointer){
    if(pointer == NULL){
        printf("Cannot allocate memory\n");
        exit(1);
    }
}

int ends_with_txt( char *file_name)
{
    file_name = strrchr(file_name, '.');

    if( file_name != NULL ){
        if(strcmp(file_name, ".txt ") == 0){
            return 1;
        } else {
            return -1;
        }
    }

    return( -1 );
}

char* get_std_char(){//used for getting filename
    char *name = malloc(260);//MAX_SIZE of filename
    memory_allocation_check(name);
    int ending_value = -1;
    while(ending_value < 0){
        if (fgets(name, 260, stdin)) {
            name[strcspn(name, "\n")] = ' ';
            ending_value = ends_with_txt(name);
            if (ending_value != 1){
                printf("Please enter a valid name:");
                continue;
            }
        }
    }
    return name;
}

int main() {
    char *file_name;
    int file_open = 0;
    FILE *file_pointer;

    while (file_open == 0) {
        printf("Please enter name of the file in which there is a number between 10 and 1000, number must have less than 3 digits after point");
        printf("Filename must be in xxx.txt format(filename cannot be longer than 260 characters): ");
        file_name = get_std_char();
        if ((file_pointer = fopen(file_name, "r")) == NULL) {//file_name
            printf("Error! opening file, please make sure the file exists\n");
        } else {
            printf("Successfully opened file\n");
            file_open = 1;
        }
    }

    char number_char[8];
    double number = -1;
    int digits_after_zero = 1;
    number = read_number(file_pointer, &number_char);
    digits_after_zero = number_check(number_char);
    while (number == -1 || digits_after_zero == 1){
        printf("Wrong input in file, please enter filename with correct input: ");

        number = read_number(file_pointer, &number_char);
        digits_after_zero = number_check(number_char);
        file_name = get_std_char();
        if ((file_pointer = fopen(file_name, "r")) == NULL) {//file_name
            printf("Error! opening file, please make sure the file exists\n");
        } else {
            printf("Successfully opened file\n");
            file_open = 1;
        }
    }
    int length = strlen(number_char);
    if(digits_after_zero > 0){
        printf("%d", length-1);
    } else {
        printf("%d", length);
    }

    fclose(file_pointer);

    return 0;

}
