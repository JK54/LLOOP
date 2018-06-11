#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <utmp.h>
#include <fcntl.h>
#include <time.h>

#define DEFAULT_SIZE 16
#define UTMP_SIZE sizeof(struct utmp)
void show_time(long);
void show_info(struct utmp *);
int utmp_open(const char *filename );
int utmp_read(int fd,char *,int size);
int utmp_close(int);

int main()
{
	char utbuf[DEFAULT_SIZE*UTMP_SIZE];
	int fd,num_rec,i;
	if((fd = utmp_open(UTMP_FILE)) == -1)
	{
		perror(UTMP_FILE);
		exit(1);
	}
	while((num_rec = utmp_read(fd,utbuf,DEFAULT_SIZE)/UTMP_SIZE) != 0)
	{
		i = 0;
		while(i != num_rec)
			show_info((struct utmp*)&utbuf[i++*UTMP_SIZE]);
	}
	utmp_close(fd);
	return 0;
}

void show_info(struct utmp *utbufp)
{
	if(utbufp->ut_type != USER_PROCESS)
		return;
	printf("%-8.8s",utbufp->ut_user);
	printf(" ");
	printf("%-8.8s",utbufp->ut_line);
	show_time(utbufp->ut_tv.tv_sec);
	printf(" ");
	printf("%-s",utbufp->ut_host);
	printf("\n");
}

void show_time(long timeval)
{
	char *cp;
	cp = ctime(&timeval);
	printf("%12.12s",cp);
}

int utmp_open(const char *filename)
{
	int fd = open(filename,O_RDONLY);
	return fd;
}

int utmp_read(int fd,char *utbuf,int size)
{
	int num_read = read(fd,utbuf,size*UTMP_SIZE);
	return num_read;
}

int utmp_close(int fd)
{
	return close(fd);
}
