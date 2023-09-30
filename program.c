#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

void print_usage(char* program_name);

int main(int argc, char** argv) {
    if (argc < 3) {
        print_usage(argv[0]);
        return -1;
    }
    int fd_src = open(argv[1], O_RDONLY);
    if (fd_src == -1) {
        perror("open SOURCE");
        print_usage(argv[0]);
        return -1;
    }
    int fd_dst = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd_dst == -1) {
        perror("open DEST");
        print_usage(argv[0]);
        return -1;
    }

    char buf[2];
    ssize_t nr;
    // max of 10 lines all
    while ((nr = read(fd_src, buf, sizeof(buf))) > 0) {
        char temp = buf[0];
        buf[0] = buf[1];
        buf[1] = temp;
        if (write(fd_dst, buf, sizeof(buf)) == -1) {
            perror("write DEST");
            break;
        }
    }
    if (nr == -1) {
        perror("read SOURCE");
    }
    if (close(fd_src) == -1) {
        perror("close SOURCE");
    }
    if (close(fd_dst) == -1) {
        perror("close DEST");
    }
    return 0;
}

void print_usage(char* program_name) {
    fprintf(stderr, "usage: %s SOURCE DEST\n", program_name);
}