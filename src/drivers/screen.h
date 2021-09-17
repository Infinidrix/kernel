#ifndef SCREEN_DEF
#define SCREEN_DEF

#define WHITE_ON_BLACK 0x0f
#define GREEN_ON_BLACK 0x0a

void print_char(char character, int col, int row, char attribute_byte);

int get_screen_offset(int col, int row);

void set_cursor(int offset);

int get_cursor();

void print_at(char* message, int col, int row);

void print(char *message);

void print_attr(char *message, char attr);

void print_int_attr(int number, char attr);

void print_short_attr(short number, char attr);

void print_at_attr(char* message, int col, int row, char attr);

void clear_screen();

int handle_scrolling(int cursor_offset);
#endif