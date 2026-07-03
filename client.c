#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) return 1;

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080); 
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); 

    int connection_status = connect(client_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    if (connection_status == -1) return 1;

    printf("Woohoo! We threw the string and connected to the treehouse!\n");

    // --- NEW CODE STARTS HERE ---

    // Step 5: Prepare our message
    char message[] = "Hello Server! This is the Client speaking!";

    // Step 6: Yell the message into the tin can!
    send(client_socket, message, sizeof(message), 0);
    printf("Message sent!\n");

    // Step 7: Hang up the tin can when we are done
    close(client_socket);

    return 0;
}