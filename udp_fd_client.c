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
	struct hostent	*phe;		/* pointer to host information entry	*/
	struct sockaddr_in sin;	/* an Internet endpoint address		*/
	int	s, n, type;		/* socket descriptor and socket type	*/
int 	sd;
char	*bp, rbuf[BUFLEN], sbuf[BUFLEN];
struct  pdu{char type; char data[100];}; 	/* pdu 101 bytes with first byte is type  */

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


while(1){	/* get user message */ /*READ*/

char fileToD[30];
struct pdu spdu;


printf("\n\n--------------------------------------------------------- \n");
printf("--------------------------------------------------------- \n");
printf("------------- UDP FILE DOWNLOAD APPLICATION ------------- \n");
printf("--------------------------------------------------------- \n");
printf("--------------------------------------------------------- \n\n");
printf("Enter Q to quit download application, or \n");
printf("Name the file to download: \n\n");

//n=read(0, sbuf, BUFLEN);
//n=read(0, sbuf, BUFLEN);



spdu.type= 'C';		//Set the type to FILENAME PDU
n=read(0, spdu.data, 100); 	//Read the filename entered by the user
spdu.data[n-1] = '\0';		//End file name str

if(spdu.data[0]=='Q'){		//Let user quit application
	//fclose(cFile);
	//close(sd);
	exit(1);
}


memcpy(fileToD, spdu.data, strlen(spdu.data));	/*create a file with same name*/
write(sd, &spdu, n+1);		//Send the PDU to the serv


//fileToD=sbuf;
//memcpy(fileToD, sbuf, strlen(sbuf));	/*create a file with same name*/
//fileToD[strlen(sbuf)]='\0';
printf("Checking sever for: %s", spdu.data);

//write(sd, sbuf, BUFLEN);
	  
////	  read(sd, sbuf, BUFLEN);
////	  fprintf(stdout, "File request %s\n", sbuf); /*prints found or error*/
	  
cFile = fopen(fileToD, "w");

if (cFile == NULL) {
  fprintf(stderr, "Can't open output file %s!\n",
          fileToD);
  exit(1);
}

fprintf(stdout, "\n-----FILE CONTENTS Start-----\n");
//read(sd, sbuf, strlen(sbuf));
//while(sbuf[0]=='D' || sbuf[0]=='F'){ /*gets more than 100c until eof*/
while(read(sd, sbuf, strlen(sbuf))){ /*gets more than 100c until eof*/
fprintf(stdout, "%s", sbuf);/*print to stdout*/
fprintf(cFile, "%s", sbuf);/*print to file*/
}
fprintf(stdout, "\n---------FILE END--------\n\n");
	
	fclose(cFile);
	
	}


//}

	close(sd);
	exit(0);
}
