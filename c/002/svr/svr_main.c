#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/select.h>
#include <fcntl.h>
#include <pty.h>
#include <termios.h>
#include <signal.h>
#include <errno.h>

#define SOCK_PATH "/tmp/cli_socket"

int main() {
    int server_fd;
    struct sockaddr_un addr;

    // Create UNIX socket
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd < 0) { perror("socket"); exit(1); }

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path) - 1);
    unlink(SOCK_PATH);

    if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind"); exit(1);
    }

    if (listen(server_fd, 5) < 0) {
        perror("listen"); exit(1);
    }

    printf("Waiting for client on %s...\n", SOCK_PATH);

    while (1) {
        fd_set rfds;
        FD_ZERO(&rfds);
        FD_SET(server_fd, &rfds);
        int maxfd = server_fd + 1;

        if (select(maxfd, &rfds, NULL, NULL, NULL) < 0) {
            if (errno == EINTR) continue;
            perror("select"); break;
        }

        if (FD_ISSET(server_fd, &rfds)) {
            int client_fd = accept(server_fd, NULL, NULL);
            if (client_fd < 0) {
                perror("accept"); continue;
            }

            pid_t pid = fork();
            if (pid < 0) {
                perror("fork"); close(client_fd); continue;
            }
            if (pid == 0) {
                // Child process
                close(server_fd);

                int pty_master, pty_slave;
                if (openpty(&pty_master, &pty_slave, NULL, NULL, NULL) < 0) {
                    perror("openpty"); exit(1);
                }

                pid_t shell_pid = fork();
                if (shell_pid == 0) {
                    // Grandchild: exec shell
                    close(pty_master);
                    dup2(pty_slave, 0);
                    dup2(pty_slave, 1);
                    dup2(pty_slave, 2);
                    setsid();
                    ioctl(pty_slave, TIOCSCTTY, 0);
					setenv("TERM", "xterm", 1);
                    // execl("/bin/sh", "/bin/sh", "-i", NULL);
                    execl("/bin/bash", "/bin/bash", "-i", NULL);
                    perror("execl"); exit(1);
                }

                // Child: bridge client_fd <-> pty_master
                close(pty_slave);
                char buf[1024];
                fd_set fds;
                int n;

                while (1) {
                    FD_ZERO(&fds);
                    FD_SET(client_fd, &fds);
                    FD_SET(pty_master, &fds);
                    int mfd = (client_fd > pty_master ? client_fd : pty_master) + 1;

                    if (select(mfd, &fds, NULL, NULL, NULL) < 0) {
                        if (errno == EINTR) continue;
                        perror("select"); break;
                    }

                    if (FD_ISSET(client_fd, &fds)) {
                        n = read(client_fd, buf, sizeof(buf));
                        if (n <= 0) break;
                        write(pty_master, buf, n);
                    }
                    if (FD_ISSET(pty_master, &fds)) {
                        n = read(pty_master, buf, sizeof(buf));
                        if (n <= 0) break;
                        write(client_fd, buf, n);
                    }
                }

                close(client_fd);
                close(pty_master);
                exit(0);
            }

            // Parent
            close(client_fd);
        }
    }

    close(server_fd);
    unlink(SOCK_PATH);
    return 0;
}

