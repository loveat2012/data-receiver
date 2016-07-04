void receive_callback(char *ptr, size_t size, int client_socket);

typedef void (*ReceiveCallback)(char *ptr, size_t size, int client_socket);

int communication(ReceiveCallback receive_callback);