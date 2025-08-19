```bash
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pty.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/wait.h>

#define SOCK_PATH "/tmp/shell.sock"

int main() {
    int server_fd, client_fd;
    struct sockaddr_un addr;
    int pty_master, pty_slave;
    pid_t pid;

    // Setup UNIX domain socket
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCK_PATH);
    unlink(SOCK_PATH);
    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 1);

    printf("Waiting for client...\n");
    client_fd = accept(server_fd, NULL, NULL);
    printf("Client connected!\n");

    // Setup PTY
    if (openpty(&pty_master, &pty_slave, NULL, NULL, NULL) == -1) {
        perror("openpty");
        exit(1);
    }

    // Fork and exec shell
    if ((pid = fork()) == 0) {
        close(pty_master);
        dup2(pty_slave, 0);
        dup2(pty_slave, 1);
        dup2(pty_slave, 2);
        setsid();
        ioctl(pty_slave, TIOCSCTTY, 0);
        execl("/bin/sh", "/bin/sh", NULL);
        perror("execl");
        exit(1);
    }

    close(pty_slave);

    // Forward data using select
    fd_set fds;
    char buf[512];
    while (1) {
        FD_ZERO(&fds);
        FD_SET(client_fd, &fds);
        FD_SET(pty_master, &fds);
        int maxfd = (client_fd > pty_master ? client_fd : pty_master) + 1;

        select(maxfd, &fds, NULL, NULL, NULL);

        if (FD_ISSET(client_fd, &fds)) {
            int n = read(client_fd, buf, sizeof(buf));
            if (n <= 0) break;
            write(pty_master, buf, n);
        }
        if (FD_ISSET(pty_master, &fds)) {
            int n = read(pty_master, buf, sizeof(buf));
            if (n <= 0) break;
            write(client_fd, buf, n);
        }
    }

    close(client_fd);
    close(server_fd);
    kill(pid, SIGKILL);
    unlink(SOCK_PATH);
    return 0;
}

```
