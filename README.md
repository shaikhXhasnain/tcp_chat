# 📞 TCP Chat Application in C

Welcome to my very first network programming project! This is a two-way chat application built entirely from scratch using C and sockets. 

It works like a digital tin-can telephone: a **Server** waits in a treehouse listening for a connection, and a **Client** throws a string to connect. Once connected, they can chat back and forth continuously!

## 🛠️ What I Learned
* How to create, bind, and listen to network sockets.
* How to connect a client to a server using IP (`127.0.0.1`) and Port (`8080`).
* How to send and receive messages using memory buffers (`memset`).
* How to use an endless loop for continuous chatting.
* How to create a graceful exit when a user types `quit`.

## 🚀 How to Run the Chat

You will need to open **two** terminal windows for this to work.

**Step 1: Start the Server**
Open Terminal 1 and type:
```bash
gcc server.c -o server
./server