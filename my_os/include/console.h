extern char* const VGA_MEMORY;

extern const int VGA_WIDTH;
extern const int VGA_HEIGHT;
extern unsigned int vga_pointer;

void print_character(char);
void print_string(char*);
void print_line(char*);
typedef enum {
	      BLACK = 0, BLUE, GREEN, CYAN, RED, PURPLE, BROWN, GRAY, DARK_GRAY,
	      LIGHT_BLUE, LIGHT_GREEN, LIGHT_CYAN, LIGHT_RED, LIGHT_PURPLE, YELLOW, WHITE
} Color;

extern Color terminal_font_color;
void set_terminal_font_color(Color);
void print_character_with_color(char, Color);
void print_string_with_color(char*, Color);
void print_line_with_color(char*, Color);
void shift_terminal_up();
