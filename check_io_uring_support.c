#include <stdio.h>
#include <liburing.h>

int main() {
    struct io_uring ring;
    int ret;

    // 尝试初始化 io_uring，这里我们使用一个较小的队列深度，例如 2
    ret = io_uring_queue_init(2, &ring, 0);
    if (ret < 0) {
        // 初始化失败，可能是因为内核不支持 io_uring
        fprintf(stderr, "io_uring is not supported on this system, error: %s\n", strerror(-ret));
        return 1;
    }

    // 如果成功，说明系统支持 io_uring
    printf("io_uring is supported on this system.\n");

    // 清理，关闭 io_uring 实例
    io_uring_queue_exit(&ring);
    return 0;
}
