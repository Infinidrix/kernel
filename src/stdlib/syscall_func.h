#define WHITE_ON_BLACK 0x0f
#define GREEN_ON_BLACK 0x0a
#define BLACK_ON_WHITE 0xf0
#define YELLOW_ON_BLUE 0x1e

typedef char Byte_t;
/**
 * Print the string str using its attribute atrr
 */
void print_syscall(char * str, Byte_t atrr);
/**
 * Print an integer
 */
void print_int_syscall(int num, Byte_t attr);
