/*
 * hello1.h - Header file for hello1 module
 */
#ifndef HELLO1_H
#define HELLO1_H

#include <linux/types.h>

/**
 * print_hello() - Print "Hello, world!" and record timing
 *
 * This function prints a greeting message and records the time
 * taken for the operation.
 *
 * Return: 0 on success, negative error code on failure
 */
int print_hello(void);

#endif /* HELLO1_H */
