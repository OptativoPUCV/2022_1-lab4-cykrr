SOURCE=$(wildcard *.c) $(wildcard *.h)
test: $(SOURCE)
	echo n | ./test.sh
push: $(SOURCE)
	echo s  | ./test.sh

all: test
