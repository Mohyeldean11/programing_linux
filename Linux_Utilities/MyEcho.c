#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main(int argc , char *argv[])
{
	if(argv != NULL)
	{

		for(int i = 1; i< argc ; i++)
		{
			char *PtrChar = argv[i];
			while(*PtrChar !=NULL)
			{
				if(*PtrChar == '\\')
				{
					write(1,"\\",1);
				}
				write(1,PtrChar,1);
				PtrChar++;
			}
			if(i <(argc-1))
			{
				write(1," ",1);
			}
		}
	}
	else
	{
		/*return error*/
		return -1;
	}
	write(1,"\n",1);
	
	return 0;
}
