/*
 * hello.c - Kernel module with parameter and linked list
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/ktime.h>

MODULE_AUTHOR("Andrii Yefremov");
MODULE_DESCRIPTION("Hello world module with list");
MODULE_LICENSE("Dual BSD/GPL");

/* Parameter definition */
static uint count = 1;
module_param(count, uint, 0444);
MODULE_PARM_DESC(count, "Number of times to print 'Hello, world!'");

/* Structure for list entries */
struct hello_event {
	struct list_head list;
	ktime_t timestamp;
};

/* List head */
static LIST_HEAD(event_list);

static int __init hello_init(void)
{
	uint i;
	struct hello_event *event;

	pr_info("hello: module loaded with count=%u\n", count);

	/* Check parameter value */
	if (count == 0 || (count >= 5 && count <= 10)) {
		pr_warn("hello: count=%u is in warning range (0 or 5-10)\n", count);
	}

	if (count > 10) {
		pr_err("hello: count=%u is too large (max 10)\n", count);
		return -EINVAL;
	}

	/* Print "Hello, world!" count times and record events */
	for (i = 0; i < count; i++) {
		/* Allocate memory for event */
		event = kmalloc(sizeof(*event), GFP_KERNEL);
		if (!event) {
			pr_err("hello: failed to allocate memory\n");
			goto cleanup;
		}

		/* Record current time */
		event->timestamp = ktime_get();

		/* Add to list */
		list_add_tail(&event->list, &event_list);

		/* Print greeting */
		pr_info("Hello, world!\n");
	}

	return 0;

cleanup:
	/* Clean up already allocated entries on error */
	{
		struct hello_event *tmp;
		struct hello_event *pos;

		list_for_each_entry_safe(pos, tmp, &event_list, list) {
			list_del(&pos->list);
			kfree(pos);
		}
	}
	return -ENOMEM;
}

static void __exit hello_exit(void)
{
	struct hello_event *event, *tmp;

	pr_info("hello: module unloading\n");

	/* Iterate through list, print timestamps, and free memory */
	list_for_each_entry_safe(event, tmp, &event_list, list) {
		pr_info("hello: event time: %lld ns\n", ktime_to_ns(event->timestamp));
		list_del(&event->list);
		kfree(event);
	}

	pr_info("hello: module unloaded\n");
}

module_init(hello_init);
module_exit(hello_exit);
