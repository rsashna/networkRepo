/* UDP FILE DOWNLOADER FROM SERVER */

#include <sys/types.h>

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>                                                                            
#include <netinet/in.h>
#include <arpa/inet.h>
                                                                                
#include <netdb.h>

#define	BUFSIZE 64
#define BUFLEN		101	/* buffer length */
#define	MSG		"Any Message \n"


/*------------------------------------------------------------------------
 * main - UDP client for TIME service that prints the resulting time
 *------------------------------------------------------------------------
 */
int
main(int argc, char **argv)
{
	char	*host = "localhost";
	int	port = 3000;
	char	now[100];		/* 32-bit integer to hold time	*/ 
	struct hostent	*phe;	/* pointer to host information entry	*/
	struct sockaddr_in sin;	/* an Internet endpoint address		*/
	int	s, n, type;	/* socket descriptor and socket type	*/
int 	sd;
char	*bp, rbuf[BUFLEN], sbuf[BUFLEN];
FILE *cFile;
	switch (argc) {
	case 1:
		break;
	case 2:
		host = argv[1];
	case 3:
		host = argv[1];
		port = atoi(argv[2]);
		break;
	default:
		fprintf(stderr, "usage: UDPtime [host [port]]\n");
		exit(1);
	}

	memset(&sin, 0, sizeof(sin));
        sin.sin_family = AF_INET;                                                                
        sin.sin_port = htons(port);
                                                                                        
    /* Map host name to IP address, allowing for dotted decimal */
        if ( phe = gethostbyname(host) ){
                memcpy(&sin.sin_addr, phe->h_addr, phe->h_length);
        }
        else if ( (sin.sin_addr.s_addr = inet_addr(host)) == INADDR_NONE )
		fprintf(stderr, "Can't get host entry \n");
                                                                                
    /* Allocate a socket */
        s = socket(AF_INET, SOCK_DGRAM, 0);				/*SOCKET*/
        if (s < 0)
		fprintf(stderr, "Can't create socket \n");
	
                                                                                
    /* Connect the socket */
        if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)	/*BIND*/
		fprintf(stderr, "Can't connect to %s %s \n", host, "Time");

//while(connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0){

printf("------------- UDP FILE DOWNLOAD APPLICATION ------------- \n");
printf("--------------------------------------------------------- \n");
printf("Name the file to download: \n");

while(n=read(0, sbuf, BUFLEN)){	/* get user message */ /*READ*/
char fileToD[30];
//fileToD=sbuf;
memcpy(fileToD, "c" + sbuf, strlen(sbuf));	/*create a file with same name*/
fileToD[strlen(sbuf)]='\0';
//printf("Checking sever for: %s", sbuf);

write(sd, sbuf, BUFLEN);
	  
	  read(sd, sbuf, BUFLEN);
	  fprintf(stdout, "File request %s\n", sbuf); /*prints found or error*/
	  
cFile = fopen(fileToD, "w");

if (cFile == NULL) {
  fprintf(stderr, "Can't open output file %s!\n",
          fileToD);
  exit(1);
}

fprintf(stdout, "\n-----FILE CONTENTS Start-----\n");
read(sd, sbuf, strlen(sbuf));
//while(sbuf[0]=='D' || sbuf[0]=='F'){ /*gets more than 100c until eof*/
while(sbuf[0]=='D' || sbuf[0]=='F'){ /*gets more than 100c until eof*/
fprintf(stdout, "%s", sbuf);/*print to stdout*/
fprintf(cFile, "%s", sbuf);/*print to file*/
}
fprintf(stdout, "\n---------FILE END--------\n\n");
	
	fclose(cFile);
	close(sd);
	return(0);
	}


//}





//	(void) write(s, MSG, strlen(MSG));

	/* Read the time */

//	n = read(s, (char *)&now, sizeof(now));
//	if (n < 0)
//		fprintf(stderr, "Read failed\n");
//	write(1, now, n);
	exit(0);
}
