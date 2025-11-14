/*
 * hello2.c - Module that uses print_hello() from hello1
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include "hello1.h"

MODULE_AUTHOR("Andrii Yefremov");
MODULE_DESCRIPTION("Hello2 module - uses print_hello()");
MODULE_LICENSE("Dual BSD/GPL");

/* Parameter definition */
static uint count = 1;
module_param(count, uint, 0444);
MODULE_PARM_DESC(count, "Number of times to call print_hello()");

static int __init hello2_init(void)
{
	uint i;
	int ret;

	pr_info("hello2: module loaded with count=%u\n", count);

	/* Check parameter value */
	if (count == 0) {
		pr_warn("hello2: count=0, no greetings will be printed\n");
	} else if (count >= 5 && count <= 10) {
		pr_warn("hello2: count=%u is in warning range (5-10)\n", count);
	}

	if (count > 10) {
		pr_err("hello2: count=%u is too large (max 10)\n", count);
		return -EINVAL;
	}

	/* Call print_hello() count times */
	for (i = 0; i < count; i++) {
		ret = print_hello();
		if (ret) {
			pr_err("hello2: print_hello() failed on iteration %u\n", i);
			return ret;
		}
	}

	return 0;
}

static void __exit hello2_exit(void)
{
	pr_info("hello2: module unloaded\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
