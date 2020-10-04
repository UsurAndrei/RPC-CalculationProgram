// Server Program Test

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#define SERVER_PORT 6060

int main(int argc, char **argv)
{
    int lsd, sd;
    struct sockaddr_in sin;
    int sin_size = sizeof(sin);
    char buffer[150];
    int calcNum = 1, N, i;
    double a;
    int array[100];

    lsd = socket(AF_INET, SOCK_STREAM, 0);
    if(lsd == -1)
    {
        printf("Cannot create listening socket, program will exit!\n");
        exit(1);  
    }

    sin.sin_family = AF_INET;
    sin.sin_port = htons(SERVER_PORT);
    sin.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(lsd, (struct sockaddr *)&sin, sin_size) == -1)
    {
        printf("Cannot bind listening socket, program will exit!\n");
        exit(1);
    }

    if(listen(lsd, 5) == -1)
    {
        printf("Listen failed, program will exit!\n");
        exit(1);
    }
    
    sd = accept(lsd, (struct sockaddr *)&sin, &sin_size);
    if (sd == -1)
    {
        printf("Cannot accept connect request from socket!\n");
        exit(1);
    }
    
    while(calcNum != 0) {
        read(sd, buffer, sizeof(buffer));
        sscanf(buffer,"%d %lf %d", &calcNum, &a, &N);
        if(calcNum == 0)
        {
            printf("Client finished calculations.\nProgram will exit!\n");
            exit(0);
        }
        printf("\t\tClient Choice\tNumber a\tArray Size");
        printf("\nReceived data:\t\t%d\t%f\t%d\n", calcNum, a, N);

        read(sd, array, sizeof(array));
        for(i=0; i<N; i++)
        {
            printf("Array[%d]: %d\n",i, array[i]);
        }
    }
}
