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
    int sd, con;
    int calcNum, N, i;
    int array[100];
    char buffer[150];
    int buflen;
    double a = 0.0, resultArray[100];
    struct sockaddr_in server;

    // Create Socket
    sd = socket(AF_INET, SOCK_STREAM, 0);
    if(sd == -1)
    {
        printf("Error creating socket!\n");
        exit(1);
    }
    printf("- Client Socket Created\n");

    // Initialize struct sockaddr_in server values
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    // Connect
    con = connect(sd, (struct sockaddr *)&server, sizeof(server));
    if(con == -1)
    {
        printf("Error connecting to server!\n");
        exit(1);
    }
    printf("- Client Connected\n\n");
    // Client Code
    printf("Program performs the follwing calculations:\n");
    printf("1. Average value of your array\n");
    printf("2. Maximum and minimum values of your array\n");
    printf("3. Multiplication a * array\n");
    printf("0. Exit\n\n");
    
    printf("Choose option: ");
    scanf("%d", &calcNum);

    while(calcNum != 0)
    {   
        if(calcNum == 3)
        {
            printf("Insert real number a: ");
            scanf("%lf", &a);
        }

        printf("Insert array size: ");
        scanf("%d", &N);

        for(i=0; i<N; i++)
        {
            printf("Insert array element %d: ", i+1);
            scanf("%d", &array[i]);
        }
        sprintf(buffer,"%d %lf %d", calcNum, a, N);
        printf("\nSENDING DATA...\n");
        write(sd, buffer, sizeof(buffer));
        write(sd, array, sizeof(array));

        if(calcNum !=3)
        {
            printf("\nRECEIVING DATA...\n");
            bzero(buffer, sizeof(buffer));
            read(sd, buffer, sizeof(buffer));
            printf("%s", buffer);
        }
        else
        {
            printf("\nRECEIVING DATA...\n");
            printf("Result Array:\n");
            read(sd, resultArray, sizeof(resultArray));
            for(i=0; i<N; i++)
            {
                printf("Array[%d] = %f\n", i+1, resultArray[i]);
            }
        }
        
        printf("\nChoose option: ");
        scanf("%d", &calcNum);

        if(calcNum == 0)
        {
            sprintf(buffer,"%d 0 0", calcNum);
            write(sd, buffer, sizeof(buffer));
        }
    }
    printf("Program will now exit!\n");
    return 0;
}