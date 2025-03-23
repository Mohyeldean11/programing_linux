#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define COUNT 100

int main(int argc , char * argv[])
{
	if(argc !=2)
	{
		printf("usage : filename %s\n",argv[0]);
	}

	char buff[COUNT];

	int fd = open(argv[1],O_RDONLY);
	if(fd <0)
	{
		printf("could'nt open the file\n");
		exit(-2);
	}
	else
	{
		/*do nothing*/
	}
	int numread;
	while((numread = read(fd,buff,COUNT)) > 0)
	{
		if(write(1,buff,numread)<0)
		{
			printf("WRITE FAILED\n");
			exit(-3);
		}
	}
	return 0;
}

