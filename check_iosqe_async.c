#include <stdio.h>
#include <liburing.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    struct io_uring ring;
    struct io_uring_sqe *sqe;
    struct io_uring_cqe *cqe;
    int ret;

    // init io_uring queue with 4 entries
    ret = io_uring_queue_init(4, &ring, 0);
    if (ret) {
        fprintf(stderr, "io_uring_queue_init failed: %d\n", ret);
        return 1;
    }

    // get a submission queue entry
    sqe = io_uring_get_sqe(&ring);
    if (!sqe) {
        fprintf(stderr, "Failed to get submit queue entry\n");
        io_uring_queue_exit(&ring);
        return 1;
    }

    // set up a NOOP operation, with IOSQE_ASYNC flag
    io_uring_prep_nop(sqe);
    sqe->flags |= IOSQE_ASYNC;

    // submit the operation
    ret = io_uring_submit(&ring);
    if (ret <= 0) {
        fprintf(stderr, "Failed to submit to io_uring: %d\n", ret);
        io_uring_queue_exit(&ring);
        return 1;
    }

    // wait for the completion
    ret = io_uring_wait_cqe(&ring, &cqe);
    if (ret) {
        fprintf(stderr, "Error waiting for completion: %d\n", ret);
        io_uring_queue_exit(&ring);
        return 1;
    }

    // check the result
    if (cqe->res < 0) {
        fprintf(stderr, "IO operation failed: %s\n", strerror(-cqe->res));
    } else {
        printf("IOSQE_ASYNC is supported.\n");
    }

    io_uring_cqe_seen(&ring, cqe);
    io_uring_queue_exit(&ring);
    return 0;
}
