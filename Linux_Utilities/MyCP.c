 #include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFFER	7000

int main(int argc , char *argv[])
{
         int opened_file = open(argv[1], O_RDONLY);
        if(opened_file == -1)
        {
                perror("error,can not open the file");
                return 1;
        }
        else
        {
            int new_file = open(argv[2] ,O_WRONLY | O_CREAT | O_TRUNC,0777);
            if(new_file == -1)
            {
                    perror("error, can not create the destined file");
                    close(opened_file);
                    exit(1);
            }
            char CopyBuffer [BUFFER];
            signed int readed_data, Written_data ;

            while( (readed_data = read(opened_file,CopyBuffer,BUFFER)) > 0 )
            {
                    Written_data = write(new_file,CopyBuffer,readed_data);
                    if(readed_data != Written_data)
                    {
                            perror("error, can not write all data in the new file");
                           close(opened_file);
                           close(new_file);
                    }
            }
            close(opened_file);
            close(new_file);
        }
	return 0;
}


