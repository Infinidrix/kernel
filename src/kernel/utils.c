#include "utils.h"

void memory_copy(char *source, char *dest, int no_bytes) {
    int i;
    for (i = 0; i < no_bytes; i++){
        *(dest + i) = *(source + i);
    }
}
char *int_to_string(char *result, int number){
    int count = 0;
    while (number > 0){
        result[count++] = (char) ((number % 10) + (int) '0');
        number = number / 10;
    }
    result[count] = '\0';
    reverse_string(result, count);
    return result;
}

void reverse_string(char * string, int size) {
    int count = -1;
    char temp;
    while (++count < --size){
        char temp = string[count];
        string[count] = string[size];
        string[size] = temp;
    }
}