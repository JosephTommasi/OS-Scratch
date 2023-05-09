#include <console.h>

char* const VGA_MEMORY = (char*) 0xb8000;
const int VGA_WIDTH = 80;
const int VGA_HEIGHT = 25;
unsigned int vga_pointer = 0;
Color terminal_font_color = GRAY;

void shift_terminal_up(){
  //starting at the second line, move everything up to the end of the buffer up one line
  for(int i = VGA_WIDTH*2; i < VGA_WIDTH*VGA_HEIGHT*2; i+=2){
    VGA_MEMORY[i-VGA_WIDTH*2] = VGA_MEMORY[i];
    VGA_MEMORY[(i-VGA_WIDTH*2)+1] = VGA_MEMORY[i+1];

    //if we're on the last line, clear it
    if(i/(VGA_WIDTH*2) == VGA_HEIGHT-1){
      VGA_MEMORY[i] = '\0';
      //also clear out the color setting just in case
      VGA_MEMORY[i+1] = '\0';
    }
  }
}

void set_terminal_font_color(Color color){
  terminal_font_color = color;
}

void print_character_with_color(char ch, Color color){
  //if the pointer overflows, shift the terminal up then set the pointer to the start of the last line
  //being at the beginning here isn't accurate to how a cursor should behave
  //if the very bottom right character is input, the cursor should start a new line
  //but because the assignment sample starts a new line after filling out the bottom line,
  //but the terminal hasn't shifted
  //I'll emulate that behavior here as well
  //this can be put at the end of the function to be "properly" implemented
  if (vga_pointer >= VGA_HEIGHT*VGA_WIDTH*2){
    shift_terminal_up();
    vga_pointer = (VGA_HEIGHT-1)*VGA_WIDTH*2;
  }
  
  if (ch == '\n'){
    //perform integer division to get the line number, then add 1 to start a newline
    //then set the pointer to the start of the new line
    vga_pointer = ((vga_pointer/(VGA_WIDTH*2))+1)*(VGA_WIDTH*2);
  }
  else{
    VGA_MEMORY[vga_pointer] = ch;
    VGA_MEMORY[vga_pointer+1] = color;
    vga_pointer += 2;
  }

}

void print_string_with_color(char* str, Color color){
  unsigned int i = 0;
  
  while(str[i] !='\0'){
    print_character_with_color(str[i], color);
    i++;
  }  
}

void print_line_with_color(char* str, Color color){
  print_string_with_color(str, color);
  print_character('\n');  
}

void print_character(char ch){
  print_character_with_color(ch, terminal_font_color);
}

void print_string(char* str){
  print_string_with_color(str, terminal_font_color);
}

void print_line(char* str){
  print_line_with_color(str, terminal_font_color);
}
