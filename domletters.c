// Daniel Gerendasy
// CS461P - HW1
// domeletters.c
// 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFFER_SIZE     (1024*4)
#define FALSE           (0)
#define TRUE            (1)
#define DELIMITERS      (" \n\r\t")

// Returns the number of dominant letters in the given string
int count_dominant_letters(char * str)
{
  int count[256];
  int i, max = 0;

  // get string length
  int len = strlen(str);
  if (len == 0)
    return 0;
  
  // initialize count buffer to 0
  for (i = 0; i < 256; ++i)
    count[i] = 0;

  // iterate string
  for (i = 0; i < len; ++i)
  {
    // get char, ignore case by casting to lower
    int c = (int)tolower(str[i]);

    // increment counter
    ++count[c];

    // if new count is greater than largest count, update
    if (count[c] > max)
      max = count[c];
  }
 
  // return largest number of reoccuring characters
  return max;
}

// Determines if a given string is an alphabetic word
// Returns TRUE if true or FALSE if false
int is_word(char * str)
{
  int i;

  // return false if str is empty
  int len = strlen(str);
  if (len == 0)
    return FALSE;

  // check if string contains non-alphabetic character
  for (i = 0; i < len; ++i)
  {
    char c = str[i];
    if (!isalpha(c))
      return FALSE;
  }
  
  // return true if passed
  return TRUE;
}

// program entrypoint
int main(int argc, char * argv[])
{
  char buffer[BUFFER_SIZE];
  char * token;
  int result = 0;
  

  // read stdin into buffer
  if (fread(buffer, 1, BUFFER_SIZE-1, stdin) > 0)
  {
    // break up input string by whitespace
    // iterate each piece
    token = strtok(buffer, DELIMITERS);
    while (token != NULL)
    {
      // if word only contains alphabetic characters, count dominant letters
      if (is_word(token))
        result += count_dominant_letters(token);

      // get next word
      token = strtok(NULL, DELIMITERS);
    }
  }

  // print result and exit
  printf("%d\n", result);
  exit(0);
}

