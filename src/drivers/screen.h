void print_char(char character, int col, int row, char attribute_byte);

int get_screen_offset(int col, int row);

void set_cursor(int offset);

int get_cursor();

void print_at(char* message, int col, int row);

void print(char *message);

void clear_screen();