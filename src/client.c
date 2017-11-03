#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define SERVER "hmif.cf"
#define PORT 9999

void recv_until(int sock, char *buf, char *data) {
   bzero((char *) buf, 512);
   int i = 0;
   while (strstr(buf, data) == NULL) {
	   read(sock, buf+i, 1);
	   i++;
   }
}

void getValidSubnet(char *subnet, char *host) {
   bzero((char *) subnet, 512);
   strcat(subnet,"0.0.0.0/0\n");
}

int getMask(char *address) {
   int i = 0;
   while (address[i] != '/') {
      i++;
   }
   i++;
   char c = address[i]; i++;
   if (address[i] == '\0') {
      return (c - '0');
   } else {
      int x = (c - '0');
      int y = (address[i] - '0');
      return (x*10 + y);
   }
}

void countHosts(char *subnet, char *host) {
   bzero((char *) host, 512);

   int y = 32 - getMask(host);
   long long n = 1;

   for (int i=0; i<y; i++){
      n = n*2;
   }
   char temp[10];
   sprintf(temp, "%lld\n", n);
   strcpy(host, temp);
}


int isSubnetValid(char *subnet, char *host) {
   char temphost[32];
   char tempsubnet[32];
   int intSubnet[10];
   int intHost[10];
   int j=0;
   int i =0;
   int temp =0;
   int y = 32 - getMask(subnet);
   int enof = 0;
   while (!enof){
     while (subnet[j]!='.' && subnet[j]!='/' && j<strlen(subnet)) {
       temp = (temp*10) + subnet[j] - '0';
       j++;
     }if (j<strlen(subnet)) {
       intSubnet[i] = temp;
       temp = 0;
       i++;
       j++;
     }else {
       enof = 1;
     }
   }//subnet udh di convert jadi array int//subnet udh di convert jadi array int
   enof = 0;
   j = 0;
   i = 0;
   temp = 0;
   while (!enof){
     while (host[j]!='.' && j <strlen(host)) {
       temp = (temp*10) + host[j] - '0';
       j++;
     }if (j<=strlen(host)) {
       intHost[i] = temp;
       temp = 0;
       i++;
       j++;
     }else {
       enof = 1;
     }
   }//host udh di convert jadi int

   unsigned long result = intSubnet[0] << 24 | intSubnet[1] << 16 | intSubnet[2] << 8 | intSubnet[3];
   unsigned long result2 = intHost[0] << 24 | intHost[1] << 16 | intHost[2] << 8 | intSubnet[3];
   unsigned long result3 = result >> y;
   unsigned long result4 = result2 >> y;
   if (result3 == result4){
     return 1;
   }else {
     return 0;
   }

   //return 1;
}

int main(int argc, char *argv[]) {
   int sockfd, portno, n, i;
   struct sockaddr_in serv_addr;
   struct hostent *server;

   char buffer[512];

   /* Create a socket point */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);

   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }

   server = gethostbyname(SERVER);

   if (server == NULL) {
      fprintf(stderr,"ERROR, no such host\n");
      exit(0);
   }

   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
   serv_addr.sin_port = htons(PORT);

   /* Now connect to the server */
   if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR connecting");
      exit(1);
   }

   recv_until(sockfd, buffer, "NIM: ");
   printf("NIM: ");
   scanf("%s", buffer);
   write(sockfd, buffer, strlen(buffer));

   recv_until(sockfd, buffer, "NIM: ");
   printf("Verify NIM: ");
   scanf("%s", buffer);
   write(sockfd, buffer, strlen(buffer));

   recv_until(sockfd, buffer, "\n");
   printf("%s", buffer);

   char host[512];
   char subnet[512];
   /*char temphost[32];
   char tempsubnet[32];
   int intSubnet[8];
   int intHost[5];
   int j=0;
   i =0;
   int temp =0;
   int y = 32 - getMask(subnet);
   int enof = 0;
   while (!enof){
     while (subnet[j]!='.' || subnet[j]!='\0') {
       temp = (temp*10) + subnet[j] - '0';
       j++;
     }if (subnet[j]=='\0'){
       enof = 1;
     }else {
       intSubnet[i] = temp;
       temp = 0;
       i++;
     }
   }//subnet udh di convert jadi array int
   enof = 0;
   j = 0;
   i = 0;
   temp = 0;
   while (!enof){
     while (host[j]!='.' || host[j]!='\0') {
       temp = (temp*10) + host[j] - '0';
       j++;
     }if (host[j]=='\0'){
       enof = 1;
     }else {
       intHost[i] = temp;
       temp = 0;
       i++;
     }
   }//host udh di convert jadi int

   unsigned long result = intSubnet[0] << 24 | intSubnet[1] << 16 | intSubnet[2] << 8 | intSubnet[3];
   unsigned long result2 = intHost[0] << 24 | intHost[1] << 16 | intHost[2] << 8 | intSubnet[3];
   unsigned long result3 = result >> y;
   unsigned long result4 = result2 >> y;
   if (result3 == result4){
     return 1;
   }else {
     return 0;
   }*/








   // Phase 1
   for (i = 0; i < 100; i++) {
      recv_until(sockfd, buffer, "Host: ");
      recv_until(sockfd, host, "\n");
      host[strlen(host)-1] = '\0';
      recv_until(sockfd, buffer, "Subnet: ");
      getValidSubnet(subnet, host);
      write(sockfd, subnet, strlen(subnet));
   }
   recv_until(sockfd, buffer, "\n");
   printf("%s", buffer);

   // Phase 2
   for (i = 0; i < 100; i++) {
      recv_until(sockfd, buffer, "Subnet: ");
      recv_until(sockfd, subnet, "\n");
      subnet[strlen(subnet)-1] = '\0';
      recv_until(sockfd, buffer, "Number of Hosts: ");
      countHosts(subnet, host);
      write(sockfd, host, strlen(host));
   }
   recv_until(sockfd, buffer, "\n");
   printf("%s", buffer);

   // Phase 3
   for (i = 0; i < 100; i++) {
      recv_until(sockfd, buffer, "Subnet: ");
      recv_until(sockfd, subnet, "\n");
      subnet[strlen(subnet)-1] = '\0';
      recv_until(sockfd, buffer, "Host: ");
      recv_until(sockfd, host, "\n");
      host[strlen(host)-1] = '\0';
      if (isSubnetValid(subnet, host)) {
         write(sockfd, "T\n", 2);
	  } else {
         write(sockfd, "F\n", 2);
	 }
   }
   recv_until(sockfd, buffer, "\n");
   printf("%s", buffer);

   close(sockfd);
   return 0;
}
