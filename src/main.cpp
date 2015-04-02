#include "hidapi/hidapi.h"
#include <cstdio>

int main()
{
    hid_init();

    struct hid_device_info *hid_dev = hid_enumerate(0, 0);
    while (hid_dev) {
        std::printf("HID device: VID=%x PID=%x Path=%s Product string: \"%S\"\n",
                    hid_dev->vendor_id,
                    hid_dev->product_id,
                    hid_dev->path,
                    hid_dev->product_string);
        hid_dev = hid_dev->next;
    }

    hid_exit();
    return 0;
}

