# io-uring Feature Check

This repository contains tools to check for specific features in `io_uring` on Linux systems. It includes programs to determine if certain `io_uring` capabilities such as `IORING_FEAT_FAST_POLL` and `IOSQE_ASYNC` are supported by the kernel.

## Features

- **`check_io_uring_support`**: Determines if `io_uring` is supported.
- **`check_io_uring_features`**: Checks for the support of `IORING_FEAT_FAST_POLL` and `IORING_OP_PROVIDE_BUFFERS`.
- **`check_iosqe_async`**: Checks if `IOSQE_ASYNC` is supported for operations.

## Getting Started

### Prerequisites

Ensure you have a C compiler (such as gcc) and `liburing` installed on your system. If `liburing` is not installed, follow the installation instructions below.

### Installing liburing

`liburing` provides an easy-to-use setup for utilizing the `io_uring` interface in Linux. To compile and install `liburing`, follow these steps:

1. Clone the `liburing` repository:

    ```bash
    git clone https://github.com/axboe/liburing.git
    ```

2. Change to the directory:

    ```bash
    cd liburing
    ```

3. Compile and install:

    ```bash
    make
    sudo make install
    ```

### Compilation of This Project

To compile the programs in this repository, use the included Makefile:

```bash
make all
```

This will compile all the programs (`check_io_uring_support`, `check_io_uring_features`, and `check_iosqe_async`).

### Usage

After compilation, you can run the programs to check `io_uring` support and features:

- **Check `io_uring` support**:

    ```bash
    make test_iouring_support
    ```

- **Check `io_uring` features**:

    ```bash
    make test_iouring_features
    ```

- **Check `IOSQE_ASYNC` support**:

    ```bash
    make test_iosqe_async
    ```

## Cleaning Up

To clean up the compiled binaries and object files, run:

```bash
make clean
```

## Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues to improve the documentation or code.

## License

This project is open source and available under the [MIT License](LICENSE).

## Acknowledgments

- Thanks to the `liburing` community for providing the tools necessary to interact with `io_uring` efficiently.

## More Information

For more details on `io_uring`, visit the official GitHub repository:

[liburing GitHub](https://github.com/axboe/liburing)

---

