#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define EOS 0
#define SEP ' '

int compare(const void *v1, const void *v2) {
  char* s1 = *(char**)v1;
  char* s2 = *(char**)v2;
  return frobcmp(s1, s2);
}

int frobcmp (const char  *s1, const char *s2) {
  int i = 0;

  while (1)
    {
      if (s1[i] == ' ' && s2[i] == ' ')
	return 0;
      else if (s1[i] == ' ' || (s1[i]^42) < (s2[i]^42))
	return -1;
      else if (s2[i] == ' ' || (s1[i]^42) > (s2[i]^42))
	return 1;
      i++;
    }
    
}

int main(int argc, char** argv) {

  //read text from stdin
  char* str;
  char** arr;
  
  str = (char*)malloc(sizeof(char));
  if (errno == ENOMEM)
    {
      fprintf(stderr, "no memory\n");
      exit(1);
    }

  arr = (char**)malloc(sizeof(char*));
    if (errno == ENOMEM)
    {
      fprintf(stderr, "no memory\n");
      exit(1);
    }


  
  int strI = 0;
  int arrI = 0;
  char c = getchar();
  
  while (c != EOF) //while not end of file
    {
      if (c != ' ') //if letter not space
	{
	  str[strI] = c; //add add letter to string
	  strI++;
	  str=realloc(str, (strI+1)*sizeof(char));
	  if (errno == ENOMEM)
	    {
	      fprintf(stderr, "realloc failed: no memory\n");
	      exit(1);
	    }

	}
      else if (c == ' '|| c == '\n' || c==EOF) //if is end of word
	{
	  c=' ';
	  str[strI] = c; //add final space
	  arr[arrI] = str; //add word to array
	  arrI++;
	  strI = 0; //reset string
	  str = (char*)malloc(sizeof(char));
	  arr=realloc(arr, (arrI+1)*sizeof(char*));
	    if (errno == ENOMEM)
	      {
		fprintf(stderr, "realloc failed: no memory\n");
		exit(1);
	      }

	}
      c = getchar();

    }
  //add last word
  if (strI != 0 && c != ' ')  
  {
        c=' ';
	str[strI] = c;
	arr[arrI] = str;
	arrI++;
    }
  
  
  qsort(arr, arrI, sizeof(char*), compare);
  int i = 0;
  for (; i < arrI; i++)
    {
      int j;
      for (j = 0; arr[i][j] != ' ' ; j++)
	{
	  printf("%c", arr[i][j]);
	}
      printf("%c", arr[i][j]);
      
    }


  //freeing everything
  i = 0;
  for (; i < arrI; i++)
    {
      free(arr[i]);
      
    }
  free(arr);

  if (errno != 0)
    {
      fprintf(stderr, "Final errors\n");
      exit(1);
    }

}
