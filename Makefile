CURL_CFLAGS = $(shell curl-config --cflags)
CURL_LIBS = $(shell curl-config --libs)

out/weer: $(wildcard src/*.c src/*.h)
	mkdir -p out
	clang -o out/weer -g -Wall -Werror -Wextra -Wpedantic $(CURL_CFLAGS) $(CURL_LIBS) $(wildcard src/*.c)

all: clean out/weer

clean:
	rm -rf out

fmt:
	clang-format -Werror -i --style=file --sort-includes $(wildcard src/*.c src/*.h)

.PHONY: all clean fmt
