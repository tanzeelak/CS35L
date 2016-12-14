#include "randcpuid.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h> //dynamic loading

int
main (int argc, char **argv)
{
  /* Check arguments.  */
  bool valid = false;
  long long nbytes;
  if (argc == 2)
    {
      char *endptr;
      errno = 0;
      nbytes = strtoll (argv[1], &endptr, 10);
      if (errno)
	perror (argv[1]);
      else
	valid = !*endptr && 0 <= nbytes;
    }
  if (!valid)
    {
      fprintf (stderr, "%s: usage: %s NBYTES\n", argv[0], argv[0]);
      return 1;
    }

  /* If there's no work to do, don't worry about which library to use.  */
  if (nbytes == 0)
    return 0;

  /* Now that we know we have work to do, arrange to use the
     appropriate library.  */

  //editing

  void (*initialize) (void);
  unsigned long long (*rand64) (void);
  void (*finalize) (void);
  void *lib_handle;
  if (rdrand_supported ())
    {
      lib_handle = dlopen("randlibhw.so", RTLD_NOW);
      if (lib_handle == NULL)
	{
	  printf("Error opening randlibhw.so: %s\n", dlerror());
	  exit(1);
	}

      initialize = dlsym(lib_handle, "hardware_rand64_init");
      if (dlerror())
	{
	  printf("Error finding hardware_rand64_init: %s\n", dlerror());
	  exit(1);
	}
      
      rand64 = dlsym(lib_handle, "hardware_rand64");
      if (dlerror())
	{
	  printf("Error finding hardware_rand64: %s\n", dlerror());
	  exit(1);
	}
      
      finalize = dlsym(lib_handle, "hardware_rand64_fini");
      if (dlerror())
	{
	  printf("Error finding hardware_rand64_fini: %s\n", dlerror());
	  exit(1);
	}
      printf("HW\n");
     
    }
  else
    {
      lib_handle = dlopen("randlibsw.so", RTLD_NOW);
      if (lib_handle == NULL)
	{
	  printf("Error opening randlibsw.so: %s\n", dlerror());
	  exit(1);
	}

      initialize = dlsym(lib_handle, "software_rand64_init");
      if (dlerror())
	{
	  printf("Error finding software_rand64_init: %s\n", dlerror());
	  exit(1);
	}
      rand64 = dlsym(lib_handle, "software_rand64");
      if (dlerror())
	{
	  printf("Error finding software_rand64: %s\n", dlerror());
	  exit(1);
	}
      finalize = dlsym(lib_handle, "software_rand64_fini");
      if (dlerror())
	{
	  printf("Error finding software_rand64_fini: %s\n", dlerror());
	  exit(1);
	}
      printf("SW\n");
    }

  int wordsize = sizeof rand64 ();
  int output_errno = 0;

  do
    {
     unsigned long long x = rand64 ();
      size_t outbytes = nbytes < wordsize ? nbytes : wordsize;
      /*if (fwrite (&x, 1, outbytes, stdout) != outbytes)
	{
	  output_errno = errno;
	  break;
	  }*/
      nbytes -= outbytes;
    }
  while (0 < nbytes);

  if (fclose (stdout) != 0)
    output_errno = errno;

  if (output_errno)
    {
      errno = output_errno;
      perror ("output");
      finalize ();
      return 1;
    }

  //finalize ();
  /*
   if (dlclose(lib_handle) == NULL)
	{
	  printf("Error closing handle: %s\n", dlerror());
	  exit(1);
	}
  */
  return 0;
}
