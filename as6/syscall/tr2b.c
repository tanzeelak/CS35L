#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#define EOS 0
#define SEP ' '

int main(int arg, char* args[]) {

  //GETTING ARGS
  char* from = args[1];
  char* to = args[2];
  int i = 0;
  int j = 0;

  if (strlen(from) != strlen(to))
    {
      fprintf(stderr, "Error: From and to are not the same length.\n");
      exit(1);
    }
  
  for (i = 0; i < strlen(from); i++)
    {

      for (j = i+1; j < strlen(from); j++)
	{
	  if (from[i] == from[j])
	    {
	      fprintf(stderr, "Error: from does not have unique characters.\n");
	      exit(1);
	    }
	}
    }


  char c = getchar();
  while (c != EOF)
    {
      for (i = 0; i < strlen(from); i++)
	{
	  if (c == from[i])
	    {
	      c = to[i];
	      break;
	    }
	}
      putchar(c);
      c = getchar();
    }

}
