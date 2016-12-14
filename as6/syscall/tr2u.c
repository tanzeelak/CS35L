#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
  
 
  char curr[1];
  int c;

  while (read(0, curr, 1))
    {
      //      c = curr[0];
      
      for (i = 0; i < strlen(from); i++)
	{
	  if (curr[0] == from[i])
	    {
	      curr[0] = to[i];
	      break;
	    }
	}
      
      write(1, curr, 1);
    }

}
