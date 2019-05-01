//public declaration
void print_at(char* message, int col, int row, char attr);
void print(char* message, char attr);
void clear_screen();
int print_char(char c, int col, int row, char attr);

#define WHITE_ON_BLACK 0x0f
#define RED_ON_WHITE 0xf4