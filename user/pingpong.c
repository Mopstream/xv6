#include "user.h"

int main() {
    int pipes[2][2];
    if (pipe(pipes[0]) < 0) exit(0);
    if (pipe(pipes[1]) < 0) exit(0);

    int pid = fork();
    if (pid < 0) {
        exit(0);
    } else if (pid == 0) {
        int to_parent_pipe = pipes[1][1];
        int from_parent_pipe = pipes[0][0];
        close(pipes[1][0]);
        close(pipes[0][1]);

        char from_parent[4];
        while (read(from_parent_pipe, from_parent, 4) == 0);
        printf("%d: got %s\n", getpid(), from_parent);

        char* mes = "pong";
        write(to_parent_pipe, mes, sizeof(mes));

        close(to_parent_pipe);
        close(from_parent_pipe);

        exit(0);

    } else {
        int from_child_pipe = pipes[1][0];
        int to_child_pipe = pipes[0][1];
        close(pipes[1][1]);
        close(pipes[0][0]);

        char* mes = "ping";
        write(to_child_pipe, mes, sizeof (mes));
        char from_child[4];
        while (read(from_child_pipe, from_child, 4) == 0);
        printf("%d: got %s\n", getpid(), from_child);

        close(from_child_pipe);
        close(to_child_pipe);

        exit(0);
    }
}
