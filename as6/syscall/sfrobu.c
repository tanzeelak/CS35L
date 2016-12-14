#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>


int cntCmp = 0;
int frobcmp (const char  *s1, const char *s2) {
  int i = 0;

  while (1)
    {
      if (s1[i] == ' ' && s2[i] == ' ')
        {
          return 0;
        }
      else if (s1[i] == ' ' || (s1[i]^42) < (s2[i]^42))
        {
          cntCmp++;
          return -1;
        }
      else if (s2[i] == ' ' || (s1[i]^42) > (s2[i]^42))
        {
          cntCmp++;
          return 1;
	}
      i++;
    }

}

int compare(const void *v1, const void *v2) {
  char* s1 = *(char**)v1;
  char* s2 = *(char**)v2;
  return frobcmp(s1, s2);
}

int main(void)
{
  //fprintf(stderr, "helloooo");
  struct stat path_stat;
  fstat(0, &path_stat);
  int isReg = S_ISREG(path_stat.st_mode);

  char** arr;
  char* str;
  char *fileBuff;
  str = (char*)malloc(sizeof(char));
  if (str == NULL)
    {
      fprintf(stderr, "Memory allocation failure.");
      exit(1);
    }
  int strI = 0;
  int arrI = 0;
  char mu;
  int mstate = 0;
  if(isReg)
    {

      fileBuff = (char*)malloc(path_stat.st_size * sizeof(char));
      if (fileBuff == NULL)
	{
	  fprintf(stderr, "Memory allocation failure.");
	  exit(1);
	}
	

      int wordPtrCnt = 0; //how many words to point to
      int currWordSize = 1;
      int fileSize = path_stat.st_size;
      int fileI = 0;

      if (read(0, fileBuff, path_stat.st_size) > 0)
	{

	  while (fileI < fileSize)
	    {
	      currWordSize = 1;
	      if (fileI == fileSize-1) //end of file
		{
		  fileBuff[fileI] = ' ';
		}
	      if (fileBuff[fileI] == ' ') //increment wordsize until end of word
		{
		  for (int j = fileI; fileBuff[j] != ' '; j++)
		    {
		      currWordSize++;
		    }
		  wordPtrCnt++;
		}
		fileI+=currWordSize;
	    }
	  if (fileSize < path_stat.st_size)
	    {
	      //fprintf(stderr, "too big");
	    }
	arr = (char**)malloc(wordPtrCnt * sizeof(char*));
	if (arr == NULL)
	{
	  fprintf(stderr, "Memory allocation failure.");
	  exit(1);
	}

	}
      else { //mutating or 0?

	
	//fprintf(stderr, "entered else/n");
	mstate = read(0, &mu, 1);
	//fprintf(stderr, "reveal real size: %i\n", mstate);
	if (mstate == 0) //actually 0
	  {
	    fprintf(stderr, "Comparisons: 0\n");
	    return 0;
	  }
	else  //actually mutating!
	  {
	    
	    arr = (char**)malloc(1000000*sizeof(char*));
	    if (arr == NULL)
	      {
		fprintf(stderr, "Memory allocation failure.");
		exit(1);
	      }

	    /*
	    fprintf(stderr, "why read no work: %i\n", read(0,&mu,1));
	    while (read(0, &mu, 1))
	      {
		currWordSize = 1;
		if (mu == ' ')
		  {
		    for (int j = fileI; fileBuff[j] != ' '; j++)
		      {
			currWordSize++;
		      }
		    wordPtrCnt++;
		  }
		fileI+=currWordSize;
	      }
	    */

	  }
	
       }
      
      //adds word pointed to by address to array. 
      int foundFirst = 0;
      for (int i = 0; i < path_stat.st_size; i++)
	{
	  if (fileBuff[i] != ' ' && foundFirst == 0)
	    {
	      arr[arrI] = &fileBuff[i];
	      arrI++;
	      foundFirst = 1;
	    }
	  else if (fileBuff[i] != ' ' && foundFirst == 0) //allready found
	    {  
	      continue;
	    }
	  else if (fileBuff[i] == ' ') //look for nextword again!
	    {
	      foundFirst = 0;
	    }
	}

    }
  else // irregular file
    {
      //fprintf(stderr, "not isreg");
      arr = (char**)malloc(sizeof(char*));
      if (arr == NULL)
      	{
	  fprintf(stderr, "Memory allocation failure.");
	  exit(1);
	}

    }

  char curr;
  int cS = read(0, &curr, 1);
  char next;
  int nS = read(0, &next, 1);
  while(read(0, &curr, 1))
    {
      str[strI] = curr; 
      str=realloc(str, (strI+1)*sizeof(char));

      if(curr == ' ') 
	{
	  arr[arrI] = str; 
	  arr=realloc(arr, (arrI+2)*sizeof(char*));
	  if (arr == NULL)
	{
	  fprintf(stderr, "Memory allocation failure.");
	  exit(1);
	}

	  arrI++;
	  str=(char*)malloc(sizeof(char));
	  if (str == NULL)
	{
	  fprintf(stderr, "Memory allocation failure.");
	  exit(1);
	}

	  strI = -1;
	}


      if (nS == 0)
	{
	  curr = ' ';
	  strI++;
	}
      else if(nS == 0 && curr == ' ')
	{
	  break;
	}
      else if (curr == ' ' && next == ' ') 
	{
	  while(curr == ' ')
	    {
	      cS = read(0, &curr,1);
	    }
	  nS = read(0, &next,1);
	  strI++;
	}
      //increment our letter counter and get the next character
      curr = next;
      nS = read(0, &next, 1);
      strI++;
    }

  qsort(arr, arrI, sizeof(char*), compare);
  int i = 0;
  for (; i < arrI; i++)
    {
      int j;
      for (j = 0; arr[i][j] != ' ' ; j++)
        {
          write(1, &arr[i][j], 1);
        }
      write(1, &arr[i][j], 1);

    }

  fprintf(stderr, "Comparisons: %i\n", cntCmp);
  
 }
