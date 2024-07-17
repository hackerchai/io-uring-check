#include <stdio.h>
#include <liburing.h>

int main() {
    struct io_uring ring;
    struct io_uring_params params = {0};
    int ret;

    // Initialize io_uring with a small queue depth of 4 and parameters
    ret = io_uring_queue_init_params(4, &ring, &params);
    if (ret) {
        fprintf(stderr, "io_uring_queue_init_params failed: %d\n", ret);
        return 1;
    }

    // Check for IORING_FEAT_FAST_POLL support
    if (params.features & IORING_FEAT_FAST_POLL) {
        printf("IORING_FEAT_FAST_POLL is supported.\n");
    } else {
        printf("IORING_FEAT_FAST_POLL is not supported.\n");
    }

    // Check for IORING_OP_PROVIDE_BUFFERS support
    if (params.features & IORING_FEAT_RW_CUR_POS) {
        printf("IORING_OP_PROVIDE_BUFFERS is supported.\n");
    } else {
        printf("IORING_OP_PROVIDE_BUFFERS is not supported.\n");
    }

    // Clean up
    io_uring_queue_exit(&ring);
    return 0;
}
