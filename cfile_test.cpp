#include <iostream>
int main() {
  FILE *fp = NULL;
  fp = fopen("./input_file.txt", "a");
  fprintf(fp, "%d", 10);
  fclose(fp);
  fp = fopen("./input_file.txt", "r");
  char s[10];
  while (!feof(fp)) {
    fscanf(fp, "%s", s);
    std::cout << s << "\n";
  }
  fclose(fp);
  return 0;
}
