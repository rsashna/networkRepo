/* TCP FILE DOWNLOADER FROM SERVER */
#include <stdio.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>


#define SERVER_TCP_PORT 3000	/* well-known port */
#define BUFLEN		256	/* buffer length */
#define SCNLEN		100	/* scan length */


int echod(int);
void reaper(int);

int main(int argc, char **argv)
{
	int 	sd, new_sd, client_len, port;
	

	struct	sockaddr_in server, client;

	switch(argc){
	case 1:
		port = SERVER_TCP_PORT;
		break;
	case 2:
		port = atoi(argv[1]);
		break;
	default:
		fprintf(stderr, "Usage: %s [port]\n", argv[0]);
		exit(1);
	}

	/* Create a stream socket	*/	
	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) { /*SOCKET*/
		fprintf(stderr, "Can't creat a socket\n");
		exit(1);
	}

	/* Bind an address to the socket	*/
	bzero((char *)&server, sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sd, (struct sockaddr *)&server, sizeof(server)) == -1){/*BIND*/
		fprintf(stderr, "Can't bind name to socket\n");
		exit(1);
	}

	/* queue up to 5 connect requests  */
	listen(sd, 5);/*LISTEN*/

	(void) signal(SIGCHLD, reaper);

	while(1) {
	  client_len = sizeof(client);
	  new_sd = accept(sd, (struct sockaddr *)&client, &client_len);/*ACCEPT*/
	  
	  if(new_sd < 0){
	    fprintf(stderr, "Can't accept client \n");
	    exit(1);
	  }
	  switch (fork()){
	  case 0:		/* child */
		(void) close(sd);
		exit(echod(new_sd));
	  default:		/* parent */
		(void) close(new_sd);
		break;
	  case -1:
		fprintf(stderr, "fork: error\n");
	  }
	  
	}
}

/*	echod program	*/
int echod(int sd)
{
	char	*bp, buf[BUFLEN], fbuf[100];
	int 	n, bytes_to_read;
FILE *sFile;
int fileFlag=0;
//	write(sd, "Hello\n" , 6);
	printf("TCP established\n");
	
read(sd, buf, BUFLEN);
char fname[100];
memcpy(fname, buf, strlen(buf)); /*apparently the \n is captured when entering the name on client side, thus the -1 for str termination*/
fname[strlen(buf)-1]='\0';
printf("File download requested for %s\n", buf);	
printf("File download requested for %s\n", fname);	


if(access(fname, F_OK) == 0){ /*file exists is flag=1*/
fileFlag=1;
}

if(fileFlag==0){
printf("ERROR file not found\n\n");
write(sd, "error", 5);
close(sd);
return(0);
}else{
printf("File found\n");
write(sd, "found", BUFLEN); /*the BUFLEN will flush out the other stuff*/

sFile = fopen(fname, "r");
/*checking if file opens*/
if (sFile == NULL)
 {  
 printf("Error! Could not open file\n");
 exit(-1);
 }
 
 int si=0;
 char temp;

while(fscanf(sFile, "%c", &temp)!=EOF){

if(si<100){
fbuf[si]=temp;
si++;
}else{
write(sd, fbuf, 100);
si=0;
}

}

while(si<100){/*patch: missingno*/
fbuf[si]=' ';
si++;
}
write(sd, fbuf, 100);
 
}
	
fclose (sFile);	
	close(sd);
	return(0);
}

/*	reaper		*/
void	reaper(int sig)
{
	int	status;
	while(wait3(&status, WNOHANG, (struct rusage *)0) >= 0);
}
