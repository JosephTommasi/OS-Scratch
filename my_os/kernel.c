#include <console.h>
#include <io.h>

void kernel_early(void) {
}

int main(void) {
  unsigned char byte;
  while (1) {
    while (byte = scan()) {

      print_character(charmap[byte]);
    }
  }
}
