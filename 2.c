#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void get_user_input(double *number_one, double *number_two, double *number_three){

    int size = 0;
    int number;
    while(((number = scanf("%lf;%lf;%lf", number_one, number_two, number_three)) != 3) || (getchar() != '\n')){
        scanf("%*[^\n]");
        printf("Enter a  valid input: ");
    }

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
            }
        }
    }
    return name;
}

int main(){
    double number_one;
    double number_two;
    double number_three;

    printf("Enter three digits one after another separated by ;, this program finds the middle number\n");
    printf("Enter here: ");
    get_user_input(&number_one, &number_two, &number_three);

    double middle_number;
    if(number_one >= number_two && number_one <= number_three){
        middle_number = number_one;
    } else if (number_one >= number_three && number_one <= number_two){
        middle_number = number_one;
    } else if(number_two >= number_one && number_two <= number_three){
        middle_number = number_two;
    } else if(number_two >= number_three && number_two <= number_one){
        middle_number = number_two;
    } else {
        middle_number = number_three;
    }

    printf("Please enter name of file you want to put the result in.\n ");
    printf("Filename must end with txt and cannot be longer than 260 characters.\n ");
    printf("Filename: ");
    FILE *file_pointer;
    int file_open = 0;
    char *file_name = NULL;
    while (file_open == 0) {
        file_name = get_std_char();
        if ((file_pointer = fopen(file_name, "w")) == NULL) {//file_name
            printf("Error! opening file, please make sure the file exists\n");
        } else {
            int successful_print = fprintf(file_pointer, "%f", middle_number);
            if(successful_print < 0){
                printf("Problem writing to file\n");
            }else {
                printf("Successfully written to file\n");
            }
            file_open = 1;
        }
    }
    fclose(file_pointer);

    return 0;
}
