#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    // 1. Get a tin can
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        printf("Oh no! We couldn't build the tin can!\n");
        return 1;
    }

    // 2. Fill out our address form
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // 3. Glue the address to our window
    int bind_status = bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    if (bind_status == -1) {
        printf("Oh no! The address wouldn't stick (Bind failed)!\n");
        return 1;
    }

    // 4. Hang up the OPEN sign
    int listen_status = listen(server_socket, 5);
    if (listen_status == -1) {
        printf("Oh no! Our ear is blocked (Listen failed)!\n");
        return 1;
    }
    
    printf("The treehouse is open! Listening for a friend to connect...\n");

    // 5. Wait for the string to hit the window
    int client_socket = accept(server_socket, NULL, NULL);
    if (client_socket == -1) {
        printf("Oh no! We dropped the string (Accept failed)!\n");
        return 1;
    }

    printf("We caught the string! A friend connected to us!\n");

    // 6. Get our whiteboard ready
    char notepad[256];

    // 7. Start the endless game of catch
    while (1) {
        // --- MY TURN TO LISTEN ---
        memset(notepad, 0, sizeof(notepad)); // Erase the whiteboard
        recv(client_socket, notepad, sizeof(notepad), 0); // Listen to the can
        printf("Client says: %s", notepad);

        // Check if the Client pushed the emergency stop button
        if (strncmp(notepad, "quit", 4) == 0) {
            printf("The Client left the chat.\n");
            break; 
        }

        // --- MY TURN TO TALK ---
        memset(notepad, 0, sizeof(notepad)); // Erase the whiteboard
        printf("You: ");
        fgets(notepad, sizeof(notepad), stdin); // Read keyboard
        send(client_socket, notepad, strlen(notepad), 0); // Yell into the can

        // Check if I pushed the emergency stop button
        if (strncmp(notepad, "quit", 4) == 0) {
            printf("You chose to end the chat. Goodbye!\n");
            break; 
        }
    }

    // 8. Clean up
    close(client_socket);
    close(server_socket);
    printf("Tin cans safely put away.\n");
    return 0;
}