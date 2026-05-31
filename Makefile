NAME := novarys
ARG := binary.nova
RELEASE_MODE := 0

ifeq ($(RELEASE_MODE), 1)
$(info release mode enable)
RELEASE := --release
endif

all: build run

build:
	cargo build $(RELEASE)


ifeq ($(RELEASE_MODE), 1)
run: target/release/$(NAME)
	./target/release/$(NAME) $(ARG)
else
run: target/debug/$(NAME)
	./target/debug/$(NAME) $(ARG)
endif

clean:
	rm -rf target/debug

fclean: clean
	rm -rf target/release

re: fclean all

.PHONY: all clean fclean run re
