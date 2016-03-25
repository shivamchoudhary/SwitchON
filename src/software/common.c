char* binary(int num) {
  char str[9] = {0};
  int i;
  printf("testing");
  for (i=7; i>=0; i--) {
    str[i] = (num&1)?'1':'0';
    num >>= 1;
  }
  char *pointer = &str[0];
  return pointer;
}
