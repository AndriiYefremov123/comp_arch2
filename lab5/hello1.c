/*
 * hello1.c - Module that exports print_hello() function
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include "hello1.h"

MODULE_AUTHOR("Andrii Yefremov");
MODULE_DESCRIPTION("Hello1 module - exports print_hello()");
MODULE_LICENSE("Dual BSD/GPL");

/* Structure for list entries */
struct hello_event {
	struct list_head list;
	ktime_t time_before;
	ktime_t time_after;
};

/* List head */
static LIST_HEAD(event_list);

int print_hello(void)
{
	struct hello_event *event;

	/* Allocate memory for event */
	event = kmalloc(sizeof(*event), GFP_KERNEL);
	if (!event) {
		pr_err("hello1: failed to allocate memory\n");
		return -ENOMEM;
	}

	/* Record time before printing */
	event->time_before = ktime_get();

	/* Print greeting */
	pr_info("Hello, world!\n");

	/* Record time after printing */
	event->time_after = ktime_get();

	/* Add to list */
	list_add_tail(&event->list, &event_list);

	return 0;
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void)
{
	pr_info("hello1: module loaded\n");
	return 0;
}

static void __exit hello1_exit(void)
{
	struct hello_event *event, *tmp;
	ktime_t duration;

	pr_info("hello1: module unloading\n");

	/* Iterate through list, print timing info, and free memory */
	list_for_each_entry_safe(event, tmp, &event_list, list) {
		duration = ktime_sub(event->time_after, event->time_before);
		pr_info("hello1: time before: %lld ns, time after: %lld ns, duration: %lld ns\n",
			ktime_to_ns(event->time_before),
			ktime_to_ns(event->time_after),
			ktime_to_ns(duration));
		list_del(&event->list);
		kfree(event);
	}

	pr_info("hello1: module unloaded\n");
}

module_init(hello1_init);
module_exit(hello1_exit);
