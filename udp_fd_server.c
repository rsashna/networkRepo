/* UDP FILE DOWNLOADER FROM SERVER */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFLEN		256	/* buffer length */

 /*------------------------------------------------------------------------*/
int
main(int argc, char *argv[])
{
int 	sd, new_sd, client_len;	
	struct  sockaddr_in fsin;	/* the from address of a client	*/
	char	buf[100];		/* "input" buffer; any size > 0	*/
	char    *pts;
	int	sock;			/* server socket			*/
	time_t	now;			/* current time			*/
	int	alen;			/* from-address length			*/
	struct  sockaddr_in sin; 	/* an Internet endpoint address	*/
        int     s, type;        	/* socket descriptor and socket type	*/
	int 	port=3000;
struct  pdu{char type; char data[100];}; 	/* pdu 101 bytes with first byte is type  */
struct pdu rpdu;
	switch(argc){
		case 1:
			break;
		case 2:
			port = atoi(argv[1]);
			break;
		default:
			fprintf(stderr, "Usage: %s [port]\n", argv[0]);
			exit(1);
	}

        memset(&sin, 0, sizeof(sin));
        sin.sin_family = AF_INET;
        sin.sin_addr.s_addr = INADDR_ANY;
        sin.sin_port = htons(port);
                                                                                                 
        s = socket(AF_INET, SOCK_DGRAM, 0); 				/*SOCKET*/
printf("checkSocket\n");        
        if (s < 0)
		fprintf(stderr, "can't create socket\n");

        if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) 	/*BIND*/
		fprintf(stderr, "can't bind to %d port\n",port);
while(1){
        listen(s, 5);							/*LISTEN*/

printf("checkListen\n");
	alen = sizeof(fsin);

	while (1) {
									/*RECVFROM ERROR*/
	if (recvfrom(s, rpdu.data, sizeof(rpdu.data), 0,(struct sockaddr *)&fsin, &alen) <  0)	
	fprintf(stderr, "recvfrom error\n");
		
		
char	*bp, buf[BUFLEN], fbuf[101];
int 	n, bytes_to_read;
FILE *sFile;
int fileFlag=0;
	printf("checkServer\n");
	

char fname[100];
memcpy(fname, rpdu.data+1, strlen(rpdu.data)); 		/*take the data*/

fname[strlen(rpdu.data)-1]='\0';

printf("File download requested for %s\n", fname);	


if(access(fname, F_OK) == 0){ 				/*file exists is flag=1*/
fileFlag=1;
}

if(fileFlag==0){
printf("ERROR: file not found\n\n");				/*file does not exist */
rpdu.type='E';
char *tempchar="this is garble";
memcpy(rpdu.data, tempchar, 1);

	printf("CheckErrorMessage.\n");
sendto(s, &rpdu, strlen(rpdu.data)+1, 0, (struct sockaddr *)&fsin, sizeof(fsin));
	printf("CheckSendError\n");
}else{

printf("File found\n");

sFile = fopen(fname, "r");

if (sFile == NULL)						/*checking if file opens*/
 {  
 printf("ERROR: Could not open file\n");
 exit(-1);
 }
}
 int si=0;
 char temp;

while(fscanf(sFile, "%c", &temp)!=EOF){

if(si<100){
fbuf[si]=temp;
si++;
}else{

rpdu.type='D';
memcpy(rpdu.data, fbuf, strlen(fbuf)+1);
sendto(s, &rpdu, strlen(rpdu.data)+1, 0, (struct sockaddr *)&fsin, sizeof(fsin));
	printf("CheckSendD\n");
si=0;
}
}


while(si<100){/*patch: missingno*/
fbuf[si]=' ';
si++;
}


rpdu.type='F';
memcpy(rpdu.data, fbuf, strlen(fbuf)+1);
//rpdu.data[strlen(fbuf)-1]='\0';
sendto(s, &rpdu, strlen(rpdu.data)+1, 0, (struct sockaddr *)&fsin, sizeof(fsin));
	printf("CheckSendF\n");
}
	close(sd);
	return(0);		

	}
}
