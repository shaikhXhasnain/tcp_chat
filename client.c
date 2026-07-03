#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    // 1. Get a tin can
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        printf("Oh no! We couldn't build the client tin can!\n");
        return 1;
    }

    // 2. Write down the Server's address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    // 3. Throw the string!
    int connection_status = connect(client_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    if (connection_status == -1) {
        printf("Oh no! The string missed the window (Connection failed)!\n");
        return 1;
    }

    printf("Woohoo! We threw the string and connected to the treehouse!\n");

    // 4. Get our whiteboard ready
    char notepad[256];

    // 5. Start the endless game of catch
    while (1) {
        // --- MY TURN TO TALK ---
        memset(notepad, 0, sizeof(notepad)); // Erase the whiteboard
        printf("You: ");
        fgets(notepad, sizeof(notepad), stdin); // Read keyboard
        send(client_socket, notepad, strlen(notepad), 0); // Yell into the can

        // Check if I pushed the emergency stop button
        if (strncmp(notepad, "quit", 4) == 0) {
            printf("You chose to leave the chat. Goodbye!\n");
            break; 
        }

        // --- MY TURN TO LISTEN ---
        memset(notepad, 0, sizeof(notepad)); // Erase the whiteboard
        recv(client_socket, notepad, sizeof(notepad), 0); // Listen to the can
        printf("Server says: %s", notepad);

        // Check if the Server pushed the emergency stop button
        if (strncmp(notepad, "quit", 4) == 0) {
            printf("The Server ended the chat.\n");
            break; 
        }
    }

    // 6. Clean up
    close(client_socket);
    printf("Tin can safely put away.\n");
    return 0;
}