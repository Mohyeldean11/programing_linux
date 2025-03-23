#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFFER	7000

int main(int argc , char *argv[])
{
	//opening the source file
        int opened_file = open(argv[1], O_RDONLY);
        //checking if the file wasn't opened successfully
       	if(opened_file == -1)
        {
		//sending errors to the console
                perror("error,can not open the file");
                return 1;
        }
	//if the file was opened successfully
        else
        {
	    //create a new file with a W/R mode '0777' with the appropriate mode
            int new_file = open(argv[2] ,O_WRONLY | O_CREAT | O_TRUNC,0777);
	    //checking if the new file was not opened successfully
            if(new_file == -1)
            {
		    //sending errors to the console
                    perror("error, can not create the destined file");
                    //closing the source file
		    close(opened_file);
                    exit(1);
            }
	    //creating a buffer for the copy
            char CopyBuffer [BUFFER];
	    //creating variables to get the return value of the opened and created files
            signed int readed_data, Written_data ;
            //looping through the opened file to write it in the new created file until it reaches 0 which is the end of the file
            while( (readed_data = read(opened_file,CopyBuffer,BUFFER)) > 0 )
            {
		    //writing what the buffer have 
                    Written_data = write(new_file,CopyBuffer,readed_data);
                    //checking if there's a problem happened with wether the writing or the reading operations so that we can close both of files and print errors to console
		    if(readed_data != Written_data)
                    {
                           perror("error, can not write all data in the new file");
                           close(opened_file);
                           close(new_file);
                    }
            }
	    //closing the opened source file
            close(opened_file);

	    //closing the opened new created file
            close(new_file);

	     // creating a new variable for the return of unlink function
	     int remove_sFile;
	     //checking for errors
	     if(remove_sFile != 0)
	     {
		     perror("error, can not remove the source file");
	     }
	     //removing the source file 
	     else
	     {
	     	remove_sFile = unlink(argv[1]);
	     }

	}
	return 0;
}

