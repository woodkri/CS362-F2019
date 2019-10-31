#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // returns random character between space (32) and } (125)
    return ((rand() % (125 - 32 + 1)) + 32);
}

char *inputString()
{
    // Gets 5 random lowercase letters
    static char string[6];
    string[0] = (rand() % (122 - 97 + 1)) + 97;
    string[1] = (rand() % (122 - 97 + 1)) + 97;
    string[2] = (rand() % (122 - 97 + 1)) + 97;
    string[3] = (rand() % (122 - 97 + 1)) + 97;
    string[4] = (rand() % (122 - 97 + 1)) + 97;
    string[5] = '\0';
    return string;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
