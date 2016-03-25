#include <stdio.h>

void binary(int num) {
  char str[9] = {0};
  int i;
  for (i=7; i>=0; i--) {
    str[i] = (num&1)?'1':'0';
    num >>= 1;
  }
  printf("%s",str);
}


int myadd(int a,int b){
        return a+b;
}
