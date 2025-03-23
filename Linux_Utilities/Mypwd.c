#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	if(argc > 1)
	{
		printf("there is an error in the call\n");
		printf("%d\n",argc);
	}
	else
	{
		char buff[1024]={0};
		if((getcwd(buff,sizeof(buff))) != NULL)
		{
			write(STDOUT_FILENO, buff,sizeof(buff));
			write(STDOUT_FILENO, "\n",1);

		}
		else
		{
			printf("there's an error in writting the buffer\n");
		}
	}
	return 0;

}

