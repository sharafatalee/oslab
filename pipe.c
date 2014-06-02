#include <sys/wait.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
void main(int argc, char *argv[])
{
int pfd[2];
pid_t cpid;
char filename[50]="mscs13019.txt";
char rec[100];
char d[40];
char readBuff[50];
char childRead[50];

pipe(pfd);



cpid=fork();


if(cpid==0)
{
//child -  client

write(pfd[1],filename,(strlen(filename)+1));

//wait(NULL);
printf("\n Child reading pipe");
read(pfd[0],childRead,sizeof(childRead));
//printf("\n Child read file from pipe: %s",childRead);
int mf =  open("client.txt",  O_CREAT | O_RDWR, S_IWRITE | S_IREAD);
if(mf>0)
{
	int written = write(mf, childRead, sizeof(childRead));
	if(written>0)
	{
		printf("\n Thanks server, I have written my file.");
		
	}
	else
	{
		printf("\n Sorry I can't write.");
	}
}
else
{
	printf("\n file creation failed");
}


}
else{
	//parent -  server
	//wait(NULL);
	read(pfd[0],d,sizeof(d));
	printf("child sent file name : %s \n",d);
	// open file and read it

	int fd =  open(d, O_RDWR);
	if(fd>0)
	{
	
		int readBytes =  read(fd, readBuff, sizeof(readBuff) );
		if(readBytes<0)
		{
			printf("\n Parent Can not read file.");
		}
		else
		{
			close(fd);
			write(pfd[1],readBuff,(strlen(readBuff)+1));		
		}
	}
	else
	{
		printf("\n File could not be opened. ");
		
	}



}

}
