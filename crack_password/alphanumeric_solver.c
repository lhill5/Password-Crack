#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool crackPassword(char *guess_password, char *password, int depth);
bool foundLowercasePassword(char *guess_password, char *password);
void findCorrectPassword(char *guess_password, char *password);
int *getBinary(unsigned int hex, int limit);
int exponential(int a, int b);

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
    if (strcmp(guess_password, password) != 0) {
      findCorrectPassword(guess_password, password);
    }
    printf("\npassword is %s\n", guess_password);
  } else {
    printf("\ncould not crack password\n");
  }
  free(password);
  free(guess_password);
  return 0;
}

bool crackPassword(char *guess_password, char* password, int depth) {

  // static char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
  // int i, length = strlen(alphabet);
  int i;
  static char alphanumeric[] = "abcdefghijklmnopqrstuvwxyz0123456789";
  static int *length = NULL;
  if (length == NULL) {
    length = (int *)malloc(sizeof(int));
    *length = strlen(alphanumeric);
  }
  if (depth < strlen(password)) {
    for (i = 0; i < *length; i++) {
      guess_password[depth] = alphanumeric[i];
      printf("%s\n", guess_password);
      crackPassword(guess_password, password, depth + 1);
      if (foundLowercasePassword(guess_password, password)) {
        return true;
      }
    }
  }
  return false;
}

bool foundLowercasePassword(char *guess_password, char *password) {
  int i, length = strlen(password);
  static char *lowercase_password = NULL;
  if (lowercase_password == NULL) {
    lowercase_password = malloc(length);
    for (i = 0; i < length; i++) {
      lowercase_password[i] = tolower(password[i]);
    }
  }
  return (strcmp(guess_password, lowercase_password) == 0) ? true : false;
}

void findCorrectPassword(char *guess_password, char *password) {
  int length = strlen(guess_password);
  int iterations = exponential(2, length);
  int **capital = (int **)malloc(iterations * sizeof(int *));
  char temp[length + 1];
  int i, n, limit;
  for (i = 0; i < iterations; i++) {
    capital[i] = (int *)malloc(length * sizeof(int));
  }
  for (i = 0x0; i < iterations; i++) {
    capital[i] = getBinary(i, length);
  }
  for (i = 0; i < iterations; i++) {
    for (n = 0; n < length; n++) {
      if (capital[i][n]) {
        temp[n] = toupper(guess_password[n]);
      } else {
        temp[n] = guess_password[n];
      }
    }
    temp[n] = '\0';
    if (strcmp(temp, password) == 0) {
      strcpy(guess_password, temp);
      return;
    }
  }
}

int *getBinary(unsigned int hex, int limit) {
  int i, n, temp, *binary;
  binary = malloc(limit * sizeof(int));
  for (i = 0, n = limit - 1; i < limit; i++, n--) {
    temp = hex & exponential(2,n);
    binary[i] = (temp >= 1) ? 1 : 0;
  }
  return binary;
}

int exponential(int a, int b) {
if (b == 0) {
  return 1;
}
return a * exponential(a, b-1);
}
