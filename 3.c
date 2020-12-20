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

void get_user_input(int *number_one, int *number_two, int *number_three){

    int size = 0;
    int number;
    while(((number = scanf("%4d-%2d-%2d", number_one, number_two, number_three)) != 3) || (getchar() != '\n')){
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

char* get_day_name(FILE *file_pointer, int year, int month, int day){
    int file_year, file_month, file_day;
    for (int i =0; i < 7; i++){
        fscanf(file_pointer ,"%4d-%2d-%2d", &file_year, &file_month, &file_day);
        //printf("%d-%d-%d\n", file_year, file_month, file_day);
        if(file_year == year && file_month == month && file_day == day){
            char *day_name;
            char character;
            day_name = (char*) calloc(20, (sizeof(char)));
            int size = 0;
            memory_allocation_check(day_name);
            while((character = getc(file_pointer)) != '\n'){
                if(character == EOF){
                    break;
                }
                strcpy((day_name + size), &character);
                ++size;
                if (size % 19 == 0){
                    day_name = realloc(day_name, (sizeof(char) * (size + 20)));
                }
            }
            if (size % 19 == 0){
                day_name = realloc(day_name, (sizeof(char) * size + 1));
                strcpy((day_name + size), "\0");
            } else{
                strcpy((day_name + size), "\0");
            }
            return  day_name;
        } else {
            char character;
            while((character = getc(file_pointer)) != '\n'){
                if(character == EOF){
                    break;
                }
            }
        }

    }
    return "Such date not found in  week.txt file";
}

int main(){
    int year;
    int month;
    int day;

    printf("This program tells you which day it is, based on date.\n Please enter date in YYYY-MM-DD format\n");
    printf("Enter here: ");
    while (1){
        get_user_input(&year, &month, &day);
        if (year >= 0 && month <= 12 && month > 0 && day > 0 && day <= 31){/*Technically years can be any int number,
        and I didn't understand from conditions should year be a four digit number, so I decided to check if year if more than 0,
        if we wanted to see if year int 4 digit format in could easily be done like if(year>=1000 && year<=9999)*/
            break;
        }
        printf("Wrong input please enter again: ");
    }

    FILE *file_pointer;

    if ((file_pointer = fopen("week.txt", "r")) == NULL) {//file_name
        printf("Error! Cannot open week file\n");
        exit(1);
    } else {
        printf("Successfully opened file\n");
    }
    char *day_name = get_day_name(file_pointer, year, month, day);
    printf("Day: %s", day_name);
    fclose(file_pointer);
    return 0;
}
