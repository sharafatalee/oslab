#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int my_fopen(char* filename, int filemode);
int my_fclose(int fd);
int my_fputs(int fd, char* data, int dataSize);
int my_fgets(int fd, char* readBuff, int readSize);
int my_fputc(int fd, char* ch);
char* my_fgetc(int fd);

int main()
{
	int fd;
	char filename[] = "mscs13019.txt";
	char data[]="Hello, This is my assignment. \n";
	char readBuff[100];
	char charBuff[1];
	int readSize = 50;
	// creating/openning file
	fd = my_fopen(filename, O_CREAT | O_RDWR);
	if(fd<0)
	{
		printf("File could not be opened.");
		return 0;
	}
	else
	{
		printf("File has been opened.");
	}
	my_fclose(fd);
	
	//writing string	
	fd = my_fopen(filename, O_RDWR);
	int written =  my_fputs(fd,data, strlen(data));
	if(written<0)
	{
		printf("\n  Error occured. Data could not be written");
    }	
	else
	{
		printf("\n %d Bytes written using my_fputs", written);
	
	}	
	my_fclose(fd);
	//Reading string	
	fd = my_fopen(filename, O_RDWR);
	int readBytes =  my_fgets(fd,readBuff, readSize);
	if(readBytes<0)
	{
		printf("\n  Error occured. Data could not be read");
    }	
	else
	{
		printf("\n %d Bytes read using my_fgets ", readBytes);
		printf("\n Read string is: %s ",readBuff);
	
	}	
	my_fclose(fd);
	
	//writing Character	
	fd = my_fopen(filename, O_RDWR | O_APPEND);
	char* ch = "H";
    written =  my_fputc(fd,ch);
	if(written<1)
	{
		printf("\n  Error occured. Char could not be written ");
    }	
	else
	{
		printf("\n %d Character written using my_fputc ", written);
	
	}	
	my_fclose(fd);
	
	//Reading character	
	fd = my_fopen(filename, O_RDWR);
	char* readChar = 	my_fgetc(fd);
	printf("\n my_fgetc returns single char: %c ", readChar[0]); 	
	my_fclose(fd);	
	return 0;
}	


int my_fopen(char* filename, int filemode )
{
	int fd;
	fd =  open(filename, filemode, S_IWRITE | S_IREAD);
	if(fd<0)
	{		
		printf("\n File open failed. ");
	}
	return fd;
}
int my_fclose(int fd)
{
	return close(fd);
}
int my_fputs(int fd, char* data, int datalen)
{
	 return write(fd, data, datalen);
}
int my_fgets(int fd, char* readBuff, int readSize)
{
	return read(fd, readBuff, readSize);
	
}
int my_fputc(int fd, char* ch)
{
	return write(fd, ch, 1);
}
char* my_fgetc(int fd)
{
	char* ch;
	 int readchar =  read(fd, ch, 1);
	//printf(" \n Read char is %s ", ch);
	return ch;
}

