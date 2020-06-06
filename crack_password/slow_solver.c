#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool crackPassword(char *guess_password, char *password, int depth);
bool foundPassword(char *guess_password, char *password);

int main(void) {
  int i, length = 6;
  char *password = malloc(100 * sizeof(password));
  char *guess_password;

  printf("\nEnter your password: ");
  fgets(password, 100, stdin);
  sscanf(password, "%s", password);
  password = realloc(password, strlen(password) + 1);
  guess_password = malloc(strlen(password) + 1);

  bool solved = crackPassword(guess_password, password, 0);
  if (solved) {
    printf("\npassword is %s\n", guess_password);
  } else {
    printf("\ncould not crack password\n");
  }
  free(password);
  free(guess_password);
  return 0;
}

bool crackPassword(char *guess_password, char* password, int depth) {
  char uppercase;
  static char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  int i;
  static int *length = NULL;
  if (length == NULL) {
    length = malloc(sizeof(int));
    *length = strlen(alphabet);
  }
  if (depth < strlen(password)) {
    for (i = 0; i < *length; i++) {
      guess_password[depth] = alphabet[i];
      crackPassword(guess_password, password, depth + 1);
      if (foundPassword(guess_password, password)) {
        return true;
      }
    }
  }
  return false;
}

bool foundPassword(char *guess_password, char *password) {
  return (strcmp(guess_password, password) == 0) ? true : false;
}
