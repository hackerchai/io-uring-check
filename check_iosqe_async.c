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

    // 初始化 io_uring
    ret = io_uring_queue_init(4, &ring, 0);
    if (ret) {
        fprintf(stderr, "io_uring_queue_init failed: %d\n", ret);
        return 1;
    }

    // 获取一个提交队列条目
    sqe = io_uring_get_sqe(&ring);
    if (!sqe) {
        fprintf(stderr, "Failed to get submit queue entry\n");
        io_uring_queue_exit(&ring);
        return 1;
    }

    // 设置一个 NOP 操作，使用 IOSQE_ASYNC 标志
    io_uring_prep_nop(sqe);
    sqe->flags |= IOSQE_ASYNC;

    // 提交操作
    ret = io_uring_submit(&ring);
    if (ret <= 0) {
        fprintf(stderr, "Failed to submit to io_uring: %d\n", ret);
        io_uring_queue_exit(&ring);
        return 1;
    }

    // 等待完成
    ret = io_uring_wait_cqe(&ring, &cqe);
    if (ret) {
        fprintf(stderr, "Error waiting for completion: %d\n", ret);
        io_uring_queue_exit(&ring);
        return 1;
    }

    // 检查结果
    if (cqe->res < 0) {
        fprintf(stderr, "IO operation failed: %s\n", strerror(-cqe->res));
    } else {
        printf("IOSQE_ASYNC is supported.\n");
    }

    io_uring_cqe_seen(&ring, cqe);
    io_uring_queue_exit(&ring);
    return 0;
}
