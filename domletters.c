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

// Reads a given file into a buffer
// Returns number of bytes read
// Returns 0 on empty file or failure
// Which in our use-case is equivalent
size_t read_file(char * filepath, char * buffer)
{
  FILE * fp;
  long size;
  size_t result;

  // open
  fp = fopen(filepath, "rb");
  if (fp == NULL)
  {
    printf("Error opening %s\n", filepath);
    return 0;
  }

  // seek, get size, return to start of stream
  fseek(fp, 0, SEEK_END);
  size = ftell(fp);
  rewind(fp);

  // read into buffer
  result = fread(buffer, 1, size, fp);
  if (result != size)
  {
    printf("Error reading %s\n", filepath);
    return 0;
  }

  // close and return number of bytes read
  fclose(fp);
  return result;
}

// program entrypoint
int main(int argc, char * argv[])
{
  char buffer[BUFFER_SIZE];
  char * token;
  int result = 0;

  // check command line args
  if (argc != 2)
  {
    printf("Invalid arguments.\n\ndomletters <inputfile>\n");
    exit(-1);
  }

  // read file into buffer
  if (read_file(argv[1], buffer) == 0)
    exit(-2);

  // iterate string by whitespace delimiters
  token = strtok(buffer, DELIMITERS);
  while (token != NULL)
  {
    // if is alphabetic word, then count dominant letters
    if (is_word(token))
      result += count_dominant_letters(token);

    // next substring
    token = strtok(NULL, DELIMITERS);
  }
  
  // print result and exit
  printf("%d\n", result);
  exit(0);
}

