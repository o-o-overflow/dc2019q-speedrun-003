#include <sys/mman.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void say_hello()
{
   printf("Think you can drift?\n");
}

char xor(char* buf, unsigned int size)
{
   char cur = 0;
   unsigned int i;

   for (i = 0; i < size; i++)
   {
	  cur ^= buf[i];
   }

   return cur;
}

void shellcode_it(char* buf, unsigned int size)
{
   void *ptr = mmap(0, size, PROT_EXEC | PROT_WRITE | PROT_READ, MAP_ANON | MAP_PRIVATE, -1, 0);
   void (*shell)();
   memcpy(ptr, buf, size);

   shell = (void (*)()) ptr;
   shell();

   return;
}

void get_that_shellcode()
{
   char buf[31];
   int num;
   char first_half;
   char second_half;
   printf("Send me your drift\n");
   num = read(0, buf, 30);
   buf[30] = '\0';

   if (num != 30)
   {
	  printf("You're not ready.\n");
	  return;
   }
   if (strlen(buf) != 30)
   {
	  printf("You're not up to regulation.\n");
	  return;
   }
   if (strchr(buf, 0x90) != NULL)
   {
	  printf("Sleeping on the job, you're not ready.\n");
	  return;
   }

   first_half = xor(buf, 15);
   second_half = xor(buf+15, 15);

   if (first_half != second_half)
   {
	  printf("This is a special race, come back with better.\n");
	  return;
   }

   shellcode_it(buf, 30);
   
}

int main(int argc, char** argv)
{
   setvbuf(stdout, NULL, _IONBF, 0);

   if (getenv("DEBUG") == NULL)
   {
	  alarm(5);
   }
   

   say_hello();
   get_that_shellcode();
}
