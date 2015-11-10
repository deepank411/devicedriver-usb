#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/usb.h>

//probe function
//called on usb insertion if no other driver has already been activated
static int pen_probe(struct usb_interface *interface, const struct usb_device_id *id){
	printk(KERN_INFO "[*] PenDrive (%04X:%04X) plugged\n", id->idVendor, id->idProduct);
	return 0; //indicates that we will manage this device
}

static void pen_disconnect(struct usb_interface *interface){
	printk(KERN_INFO "[*] Pen Drive Removed\n");
}

//usb device id
static struct usb_device_id pen_table[] = {
	{ USB_DEVICE(0x0951,0x1624) }, //enter vendor and product id of Pen Drive
	{} //to terminate
};
MODULE_DEVICE_TABLE(usb, pen_table);

// usb driver
static struct usb_driver pen_driver =
{
	.name = "USB Stick Driver",
	.id_table = pen_table, //usb device id
	.probe = pen_probe,
	.disconnect = pen_disconnect, //called when device removed
};

static int __init pen_init(void){
	int ret = -1;
	printk(KERN_INFO "[*]Constructor of Driver");
	printk(KERN_INFO "\tRegistering device with kernel");
	ret = usb_register(&pen_driver);
	printk(KERN_INFO "\tRegistration complete");
	return ret;
}

static void __exit pen_exit(void){
	//deregister pen drive
	printk(KERN_INFO "[*]Deconstructor of Driver");
        printk(KERN_INFO "\tUnRegistering device with kernel");
        usb_deregister(&pen_driver);
        printk(KERN_INFO "\tUnRegistration complete");
}

module_init(pen_init);
module_exit(pen_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("OS Project Group");
MODULE_DESCRIPTION("USB Pen Drive Registration Driver");
