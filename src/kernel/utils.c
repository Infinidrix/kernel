#include "utils.h"

void memory_copy(char *source, char *dest, int no_bytes) {
    int i;
    for (i = 0; i < no_bytes; i++){
        *(dest + i) = *(source + i);
    }
    return;
}

void memset(char *loc, char set_bit, int no_bytes){
    for (int i = 0; i < no_bytes; i++){
        *(loc + i) = set_bit;
    }
    return;
}

char *int_to_string(char *result, unsigned int number){
    if (number == 0){
        result[0] = '0';
        result[1] = '\0';
        return result;
    }
    int count = 0;
    while (number > 0){
        result[count++] = (char) ((number % 10) + (int) '0');
        number = number / 10;
    }
    result[count] = '\0';
    reverse_string(result, count);
    return result;
}

char *short_to_string(char *result, unsigned short number){
    return int_to_string(result, ((int) number) && 0xffff);
}

int strcmp(char * str1, char *str2){
    while(*str1 != '\0' && *str2 != '\0' && *str1==*str2){
        str1++;
        str2++;
    };
    return !(*str1 == *str2 == '\0');
}

int strlen(char *str){
    int count = 0;
    for(; *str != '\0'; count++, str++);
    return count;
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