#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/keyboard.h>

static int ok_notifier_call(struct notifier_block *blk,
                            unsigned long code, void *_param);

static struct notifier_block ok_notifier_block = {
  .notifier_call = ok_notifier_call,
};

static int ok_notifier_call(struct notifier_block *blk,
                            unsigned long code, void *_param) {
  struct keyboard_notifier_param *param = _param;

  printk(KERN_INFO "Got block: down is %d, shift is %d, value is %u",
         param->down, param->shift, param->value);

  return NOTIFY_OK;
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("liz <web@stillinbeta.com>");
MODULE_DESCRIPTION("wreak havoc");
MODULE_VERSION("0.0.1");

static int __init offkey_init(void) {
  int err;

  printk(KERN_INFO "Hello, kernel!\n");
  err = register_keyboard_notifier(&ok_notifier_block);
  if (err) {
    printk(KERN_INFO "Got error %d", err);
    unregister_keyboard_notifier(&ok_notifier_block);
  }
  return 0;
}

static void __exit offkey_exit(void) {
  unregister_keyboard_notifier(&ok_notifier_block);
  printk(KERN_INFO "Goodbye, kernel\n");
}

module_init(offkey_init);
module_exit(offkey_exit);
