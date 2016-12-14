OPTIMIZE = -O2

CC = gcc
CFLAGS = $(OPTIMIZE) -g3 -Wall -Wextra -march=native -mtune=native -mrdrnd

randlibhw.so: randlibhw.c
	$(CC) $(CFLAGS) randlibhw.c -shared -fPIC -o randlibhw.so

randlibsw.so: randlibsw.c
	$(CC) $(CFLAGS) randlibsw.c -shared -fPIC -o randlibsw.so

randmain: randmain.c
	$(CC) $(CFLAGS) -g -c randcpuid.c
	$(CC) $(CFLAGS) -g -c randmain.c
	$(CC) $(CFLAGS) randcpuid.o randmain.o -ldl -Wl,-rpath=$(PWD) -o randmain
