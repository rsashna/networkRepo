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
printf("\n\n--------------------------------------------------------- \n");
char fileToD[30];
struct pdu spdu;


printf("\n\n--------------------------------------------------------- \n");
printf("--------------------------------------------------------- \n");
printf("------------- UDP FILE DOWNLOAD APPLICATION ------------- \n");
printf("--------------------------------------------------------- \n");
printf("--------------------------------------------------------- \n\n");
printf("Enter Q to quit download application, or \n");
printf("Name the file to download: \n\n");



spdu.type= 'C';		//Set the type to FILENAME PDU
n=read(0, spdu.data, 100); 	//Read the filename entered by the user
spdu.data[n-1] = '\0';		//End file name str

if(spdu.data[0]=='Q'){		//Let user quit application
	exit(1);
}


memcpy(fileToD, spdu.data, strlen(spdu.data));	/*create a file with same name*/

//printf("SD: %d", s);
write(s, &spdu, n+1);					//Send the PDU to the server


//fileToD=sbuf;
//memcpy(fileToD, sbuf, strlen(sbuf));		/*create a file with same name*/
//fileToD[strlen(sbuf)]='\0';
printf("\n\nChecking sever for: %s", spdu.data);

	
cFile = fopen(fileToD, "w");				/*creating and writing to local file copy*/
if (cFile == NULL) {
  fprintf(stderr, "Can't open output file %s!\n", fileToD);
  exit(1);
}

fprintf(stdout, "\n-----FILE CONTENTS Start-----\n");
int alen = sizeof(sin);
//read(s, &spdu, (strlen(spdu.data)+1) );
while(n=(recvfrom(s, &spdu, sizeof(spdu.data)+1, 0,(struct sockaddr *)&sin, &alen ) ) >0){

	switch (spdu.type){

	case 'D':
	
	fprintf(cFile, "%s", spdu.data);				/*print to file*/
	fprintf(stdout, "%s", spdu.data);				/*print to stdout*/
	
	//fclose(cFile);
	break;

	case 'F':
printf("checkF");
	spdu.data[strlen(spdu.data)-2]='\0';
	fprintf(stdout, "%s", spdu.data);			/*print to stdout*/
	
	fprintf(cFile, "%s", spdu.data);
	fclose(cFile);
	break;

	case 'E':
		fclose(cFile);
		fprintf(stderr, "SERVER ERROR\n");
	  	//exit(1);
	break;

	default:
		fprintf(stderr, "UNEXPECTED ERROR OCCURED");
	  	exit(1);
	break;
	}

if(spdu.type=='F' || spdu.type=='E')
break;
}

//while(spdu.type=='D' || spdu.type=='F'){		/*gets more than 100c until eof*/

//}
fprintf(stdout, "\n---------FILE END--------\n\n");
	
	
	
	}
	close(s);
	exit(0);
}
