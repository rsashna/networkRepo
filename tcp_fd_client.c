/* TCP FILE DOWNLOADER FROM SERVER */
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>



#define SERVER_TCP_PORT 3000	/* well-known port */
#define BUFLEN		256	/* buffer length */

int main(int argc, char **argv)
{
	int 	n, i, bytes_to_read;
	int 	sd, port;
	struct	hostent		*hp;
	struct	sockaddr_in server;
	char	*host, *bp, rbuf[BUFLEN], sbuf[BUFLEN];

FILE *cFile;

	switch(argc){
	case 2:
		host = argv[1];
		port = SERVER_TCP_PORT;
		break;
	case 3:
		host = argv[1];
		port = atoi(argv[2]);
		break;
	default:
		fprintf(stderr, "Usage: %s host [port]\n", argv[0]);
		exit(1);
	}

	/* Create a stream socket	*/	
	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) { /*SOCKET*/
		fprintf(stderr, "Can't create a socket\n");
		exit(1);
	}

	bzero((char *)&server, sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	if (hp = gethostbyname(host)) 
	  bcopy(hp->h_addr, (char *)&server.sin_addr, hp->h_length);
	else if ( inet_aton(host, (struct in_addr *) &server.sin_addr) ){
	  fprintf(stderr, "Can't get server address\n");
	  exit(1);
	}

	/* Connecting to the server */
	if (connect(sd, (struct sockaddr *)&server, sizeof(server)) == -1){ /*CONNECT*/
	  fprintf(stderr, "Can't connect \n");
	  exit(1);
	}

	
printf("Name the file to download: \n");
	
	while(n=read(0, sbuf, BUFLEN)){	/* get user message */ /*READ*/
char fileToD[30];
//fileToD=sbuf;
memcpy(fileToD, sbuf, strlen(sbuf));
fileToD[strlen(sbuf)-1]='\0';
printf("Checking sever for: %s", sbuf);

write(sd, sbuf, BUFLEN);

	  printf("\nTCP Connection Complete. \n\n");
	  
	  read(sd, sbuf, BUFLEN);
	  fprintf(stdout, "File request %s\n", sbuf); /*prints found or error*/
	  
cFile = fopen(fileToD, "w");

if (cFile == NULL) {
  fprintf(stderr, "Can't open output file %s!\n",
          fileToD);
  exit(1);
}

fprintf(stdout, "\n-----FILE CONTENTS Start-----\n");

while(read(sd, sbuf, strlen(sbuf))){ /*gets more than 100c until eof*/
fprintf(stdout, "%s", sbuf);/*print to stdout*/
fprintf(cFile, "%s", sbuf);/*print to file*/
}
fprintf(stdout, "\n---------FILE END--------\n\n");
	
	fclose(cFile);
	close(sd);
	return(0);
	}
	
	
}
