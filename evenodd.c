#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int even_ones(unsigned x)
{
  x ^= x>>16;
  x ^= x>>8;
  x ^= x>>4;
  x ^= x>>2;
  x ^= x>>1;

  return !(x & 1);
}
int main(int argc, char **argv) {
  unsigned int x = 10;  
printf("%d",even_ones(x));
  return 1;
}
