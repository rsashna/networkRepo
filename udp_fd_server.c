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
/*------------------------------------------------------------------------
 * main - Iterative UDP server for TIME service
 *------------------------------------------------------------------------
 */
int
main(int argc, char *argv[])
{
int 	sd, new_sd, client_len;	
	struct  sockaddr_in fsin;	/* the from address of a client	*/
	char	buf[100];		/* "input" buffer; any size > 0	*/
	char    *pts;
	int	sock;			/* server socket		*/
	time_t	now;			/* current time			*/
	int	alen;			/* from-address length		*/
	struct  sockaddr_in sin; /* an Internet endpoint address         */
        int     s, type;        /* socket descriptor and socket type    */
	int 	port=3000;
                                                                                

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
                                                                                                 
    /* Allocate a socket */
        s = socket(AF_INET, SOCK_DGRAM, 0); 				/*SOCKET*/
        if (s < 0)
		fprintf(stderr, "can't creat socket\n");
                                                                                
    /* Bind the socket */
        if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) 	/*BIND*/
		fprintf(stderr, "can't bind to %d port\n",port);
        listen(s, 5);							/*LISTEN*/
	alen = sizeof(fsin);

	while (1) {
		
		if (recvfrom(s, buf, sizeof(buf), 0,			/*RECVFROM ERROR*/
				(struct sockaddr *)&fsin, &alen) < 0)
			fprintf(stderr, "recvfrom error\n");
		
		
char	*bp, buf[BUFLEN], fbuf[101];
	int 	n, bytes_to_read;
FILE *sFile;
int fileFlag=0;
//	write(sd, "Hello\n" , 6);
	printf("Server up.\n");
	
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
		
		
//		(void) time(&now);
//        	pts = ctime(&now);

//		(void) sendto(s, pts, strlen(pts), 0,
//			(struct sockaddr *)&fsin, sizeof(fsin));





	}
}
