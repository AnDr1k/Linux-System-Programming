#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int strlength(char * str);

int main(int argc,char * argv[])
{
	int fd;
	ssize_t length;
	if(argc < 3)
	{
		syslog(LOG_ERR,"Insufficient arguments\n");
		exit(1);
	}
	fd = open(argv[1], O_RDWR|O_CREAT|O_TRUNC, S_IRWXU);
	if(fd < 0)
	{
		perror("open");
		syslog(LOG_ERR,"Unable to open file: %s\n",strerror(errno));
		exit(1);
	}
	syslog(LOG_DEBUG,"Writing %s\n in %s\n",argv[2],argv[1]);
	length = write(fd, argv[2], strlength(argv[2]));
	if(length < 0)
	{
		perror("write");
		syslog(LOG_ERR,"Unable to write file: %s\n",strerror(errno));
		exit(1);
	}
	close(fd);
	return 0;
}

int strlength(char * str)
{
	int i;
	for(i=0;str[i]!='\0';i++);
	return i;
}
