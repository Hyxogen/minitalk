# minitalk
minitalk is a 42 curriculum project with the goal to send messages from a client to a server, using only UNIX signals

## Usage

1 - build the executables:
 `make [config=debug|release|distr]`

2 - start the server. It accepts no arguments:
 `./server`

It will print the process id, which is used with the client.

3 - execute a client. It accepts only 2 arguments, the target process id and the string to send.
 `./client process-id string`

The string will be printed out by the server. Please note that depending on the size of the string it might take some time.

It accepts unicode
