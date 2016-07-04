#include <sys/wait.h>
#include <stdlib.h>
#include <memory.h>
#include <arpa/inet.h>
#include <signal.h>
#include "protocol.h"
#include "daemonize.c"
#include "log.h"

void receive_callback(char *ptr, size_t size, int client_socket)
{
    FILE *fp;

    ptr[size] = '\r';
    ptr[size + 1] = '\n';
    ptr[size + 2] = '\0';

    fp = fopen(queue_file, "a+");
    if (fp == NULL) {
        log_error("Can't open queue file.");
    } else {
        write_file_with_lock(fp, ptr, size + 2);
        if (send(client_socket, "000", 3, 0) < 0) {
            log_error("Can't send feedback message.");
            close(client_socket);
        }
    }
    exit(0);
}

int communication(ReceiveCallback receive_callback)
{
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;

    int server_socket;
    int client_socket;

    int receive_len;
    char buffer[BUFSIZ];

    socklen_t accept_size;

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(atoi(listen_port));

    if ((server_socket = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Can't create a socket");
        return 1;
    }

    if (bind(server_socket, (struct sockaddr *) &server_address, sizeof(struct sockaddr)) < 0) {
        perror("Can't bind a socket");
        return 1;
    }

    if (listen(server_socket, 5) < 0) {
        perror("Can't listen a socket");
        return 1;
    }

    if (do_daemonize == 1) {
        daemonize();
    }

    while (1) {
        accept_size = sizeof(struct sockaddr_in);
        if ((client_socket = accept(server_socket, (struct sockaddr *) &client_address, &accept_size)) < 0) {
            perror("Can't accept client");
            break;
        }

        if (!fork()) {
            if ((receive_len = recv(client_socket, buffer, BUFSIZ, 0)) > 0) {
                receive_callback(buffer, receive_len, client_socket);
            } else {
                char client_ip[32];
                strcpy(client_ip, inet_ntoa(client_address.sin_addr));
                char errmsg[68] = "Can't receive message from client: ";
                log_error(strcat(errmsg, client_ip));
                exit(0);
            }
        } else {
            pid_t pid;
            int status;
            pid = wait(&status);
            if (WIFEXITED(status) == 0) {
                char errmsg[33];
                sprintf(errmsg, "Can't exit child process: %d", pid);
                log_error(errmsg);
                kill(pid, SIGALRM);
            }
        }
        close(client_socket);
    }

    return 0;
}