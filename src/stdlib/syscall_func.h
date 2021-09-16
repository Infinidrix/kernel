#define WHITE_ON_BLACK 0x0f
#define GREEN_ON_BLACK 0x0a

typedef char Byte_t;
/**
 * Print the string str using its attribute atrr
 */
void print_syscall(char * str, Byte_t atrr);
/**
 * Print an integer
 */
void print_int_syscall(int num, Byte_t attr);
