# Makefile for building io_uring related programs

CC=gcc
CFLAGS=-Wall -g
LDFLAGS=-luring

# Program names
IO_URING_SUPPORT=check_io_uring_support
IO_URING_FEATURES=check_io_uring_features
IOSQE_ASYNC=check_iosqe_async

# Source and object files
SUPPORT_SRC=$(IO_URING_SUPPORT).c
FEATURES_SRC=$(IO_URING_FEATURES).c
ASYNC_SRC=$(IOSQE_ASYNC).c

SUPPORT_OBJ=$(SUPPORT_SRC:.c=.o)
FEATURES_OBJ=$(FEATURES_SRC:.c=.o)
ASYNC_OBJ=$(ASYNC_SRC:.c=.o)

# Default target
all: $(IO_URING_SUPPORT) $(IO_URING_FEATURES) $(IOSQE_ASYNC)

# Link the programs
$(IO_URING_SUPPORT): $(SUPPORT_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(IO_URING_FEATURES): $(FEATURES_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(IOSQE_ASYNC): $(ASYNC_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compile the source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up the build
clean:
	rm -f $(SUPPORT_OBJ) $(FEATURES_OBJ) $(ASYNC_OBJ) $(IO_URING_SUPPORT) $(IO_URING_FEATURES) $(IOSQE_ASYNC)

# To run the programs
test_iouring_support: $(IO_URING_SUPPORT)
	./$(IO_URING_SUPPORT)

test_iouring_features: $(IO_URING_FEATURES)
	./$(IO_URING_FEATURES)

test_iosqe_async: $(IOSQE_ASYNC)
	./$(IOSQE_ASYNC)

# To check dependencies automatically
.PHONY: all clean run_support run_features run_async
