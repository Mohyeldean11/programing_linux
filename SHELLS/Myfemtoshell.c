#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char **argv[])
{
	while(1)
	{
		char buffer[1000000];
		printf("Myfemto>> ");
		char *gets_ptr	=fgets(buffer,sizeof(buffer),stdin);
		if(gets_ptr != NULL)
		{				
			if(strncmp(buffer,"echo ",5) == 0)
			{
				printf("%s",buffer+5);
			}
			else if(strncmp(buffer ,"exit",4) == 0)
			{
				printf("Good Bye :)\n");
				exit(0);
			}
			else if(buffer[0] == '\n')
			{
				continue;
			}

			else
			{
				printf("Invalid command\n");
			}	
		}
		else
		{
			printf("error in reading input");
			exit(0);
		}
	}
}
