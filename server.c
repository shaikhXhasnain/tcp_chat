#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) return 1; 

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int bind_status = bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    if (bind_status == -1) return 1; 
    
    int listen_status = listen(server_socket, 5);
    if (listen_status == -1) return 1;
    
    printf("The treehouse is open! Listening for a friend...\n");

    int client_socket = accept(server_socket, NULL, NULL);
    if (client_socket == -1) return 1;

    printf("We caught the string! A friend connected to us!\n");

    // --- NEW CODE STARTS HERE ---

    // Step 11: Get a blank notepad (buffer) big enough to hold 256 letters
    char server_notepad[256];

    // Step 12: Listen to the new tin can (client_socket) and write it on the notepad
    recv(client_socket, &server_notepad, sizeof(server_notepad), 0);

    // Step 13: Read the notepad out loud!
    printf("The Client says: %s\n", server_notepad);

    // Step 14: Hang up both tin cans
    close(client_socket);
    close(server_socket);

    return 0; 
}