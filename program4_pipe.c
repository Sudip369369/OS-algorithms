#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 100
#define WRITE_END 1
#define READ_END 0

int main() {
    int pipe_fd[2];
    pid_t pid;
    char write_message[] = "Hello from Parent Process! This is IPC using pipes.";
    char read_message[BUFFER_SIZE];

    // Create pipe
    if (pipe(pipe_fd) == -1) {
        printf("Pipe creation failed\n");
        return 1;
    }
    printf("Pipe created successfully\n");
    printf("Parent PID: %d\n", getpid());

    pid = fork();
    if (pid == 0) {
        // Child process
        printf("\n--- CHILD PROCESS ---\n");
        printf("Child PID: %d\n", getpid());

        // Close write end in child
        close(pipe_fd[WRITE_END]);

        // Read message from pipe
        printf("Child: Waiting to receive message from parent...\n");
        ssize_t bytes_read = read(pipe_fd[READ_END], read_message, BUFFER_SIZE - 1);

        if (bytes_read > 0) {
            read_message[bytes_read] = '\0';
            printf("Child: Message received from parent:\n");
            printf("Child: \"%s\"\n", read_message);
            printf("Child: Message length: %ld bytes\n", bytes_read);
        } else {
            printf("Child: Failed to read from pipe\n");
        }

        // Close read end
        close(pipe_fd[READ_END]);
        printf("Child: Pipe closed. Terminating...\n");

    } else if (pid > 0) {
        // Parent process
        printf("\n--- PARENT PROCESS ---\n");
        printf("Parent: Child PID: %d\n", pid);

        // Close read end in parent
        close(pipe_fd[READ_END]);

        // Send message to child
        printf("Parent: Sending message to child...\n");
        printf("Parent: Message: \"%s\"\n", write_message);
        ssize_t bytes_written = write(pipe_fd[WRITE_END], write_message, strlen(write_message));

        if (bytes_written > 0) {
            printf("Parent: Message sent successfully (%ld bytes)\n", bytes_written);
        } else {
            printf("Parent: Failed to write to pipe\n");
        }

        // Close write end
        close(pipe_fd[WRITE_END]);

        // Wait for child to complete
        wait(NULL);
        printf("Parent: Child process completed\n");
        printf("Parent: Terminating...\n");

    } else {
        printf("Fork failed\n");
        return 1;
    }
    return 0;
}
