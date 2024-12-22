#! /usr/bin/make -f

##
# @file
# @brief This is the Makefile for the list.

TARGETS=liblist.so
liblist_so_OBJS=list.o

CC=gcc-14
CFLAGS=-Wall -Wextra -Wpedantic -Werror -fPIC -std=gnu23
LDFLAGS=-shared

.PHONY: all format clean
all: $(TARGETS)
liblist.so: $(liblist_so_OBJS)
	$(CC) $(LDFLAGS) -o liblist.so $(liblist_so_OBJS)
format:
	clang-format -i *.c *.h
clean:
	$(RM) $(TARGETS) $(liblist_so_OBJS)
