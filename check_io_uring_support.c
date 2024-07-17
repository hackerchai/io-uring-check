#include <stdio.h>
#include <liburing.h>

int main() {
    struct io_uring ring;
    int ret;

    // init io_uring queue with 2 entries
    ret = io_uring_queue_init(2, &ring, 0);
    if (ret < 0) {
        // init failed
        fprintf(stderr, "io_uring is not supported on this system, error: %s\n", strerror(-ret));
        return 1;
    }

    // if init success, io_uring is supported
    printf("io_uring is supported on this system.\n");

    // clean up
    io_uring_queue_exit(&ring);
    return 0;
}
