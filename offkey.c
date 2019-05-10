#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/input-event-codes.h>
#include <linux/keyboard.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("liz <web@stillinbeta.com>");
MODULE_DESCRIPTION("wreak havoc");
MODULE_VERSION("0.0.1");

static void ok_event(struct input_handle *handle,
                     unsigned int type, unsigned int code, int value) {
  struct input_value vals[] = { { type, code, value } };
  ok_events(handle, vals, 1);
}

static void ok_events(struct input_handle *handle,
                      const struct input_value *vals, unsigned int count) {
  printk(KERN_INFO "Got some events");
}

static int ok_connect(struct input_handler *handler, struct input_dev *dev,
                      const struct input_device_id *id);

static void ok_disconnect(struct input_handle *handle);
static void ok_start(struct input_handle *handle);

static struct input_handler ok_input_handler = {
  .event = ok_event,
  .events = ok_events,
  .connect = ok_connect,
  .disconnect = ok_disconnect,
  .start = ok_start,
  .name = "offkey",
};


static int __init offkey_init(void) {
  return input_register_handler(&evdev_handler);
}

static void __exit offkey_exit(void) {
  unregister_keyboard_notifier(&ok_notifier_block);
  printk(KERN_INFO "Goodbye, kernel\n");
}



module_init(offkey_init);
module_exit(offkey_exit);
