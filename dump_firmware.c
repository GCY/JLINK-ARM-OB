//gcc usb.c `pkg-config libusb-1.0 --libs --cflags` -o usb
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>

#include <libusb.h>

#define EP_DATA_IN        (0x3|LIBUSB_ENDPOINT_IN)
#define EP_DATA_OUT       (0x3|LIBUSB_ENDPOINT_OUT)

static struct libusb_device_handle *devh = NULL;
static struct libusb_transfer *recv_bulk_transfer = NULL;

bool jlinkSendCommand(  void const* commandBuffer, uint32_t commandLength, void* resultBuffer, uint32_t resultHeaderLength)
{
    int transferred, r;
    r = libusb_bulk_transfer(devh, EP_DATA_OUT, commandBuffer, commandLength, &transferred, 200);
     // if(!WriteFile( commandBuffer, commandLength, nullptr, nullptr))
     //    return false;

    if(!resultHeaderLength)
        return true;

    // return !!ReadFile( resultBuffer, resultHeaderLength, nullptr, nullptr);
    return 0==libusb_bulk_transfer(devh, EP_DATA_IN, resultBuffer, resultHeaderLength, &transferred, 200);
}

bool jlinkContinueReadResult(void* resultBuffer, uint32_t resultLength)
{
    int transferred, r;
    // return !!ReadFile( resultBuffer, resultLength, nullptr, nullptr);
    return 0==libusb_bulk_transfer(devh, EP_DATA_IN, resultBuffer, resultLength, &transferred, 200);
}
bool jlinkCommandReadFirmwareVersion(void* dataBuffer)
{
    uint8_t commandBuffer[1] = {0x01};
    uint16_t leftLength = 0;
    if(!jlinkSendCommand(  commandBuffer, sizeof(commandBuffer), &leftLength, sizeof(leftLength)))
                return false;

    return jlinkContinueReadResult( dataBuffer, leftLength);
}
bool jlinkCommandReadEmulatorMemory(uint32_t address, uint32_t length, void* dataBuffer)
{
    uint8_t commandBuffer[9] =
    {
         0xfe,
         (uint8_t)(address), (uint8_t)(address >> 8), (uint8_t)(address >> 16), (uint8_t)(address >> 24),
         (uint8_t)(length), (uint8_t)(length >> 8), (uint8_t)(length >> 16), (uint8_t)(length >> 24),
    };

    return jlinkSendCommand(  commandBuffer, sizeof(commandBuffer), dataBuffer, length);
}
int main(int argc, char **argv)
{
    int r = 1;

    r = libusb_init(NULL);
    if (r < 0) {
        fprintf(stderr, "failed to initialise libusb\n");
        exit(1);
    }

    devh = libusb_open_device_with_vid_pid(NULL, 0x1366, 0x0105);
    if (devh == NULL) {
        fprintf(stderr, "Could not find/open device\n");
        goto out;
    }

    r = libusb_claim_interface(devh, 2);
    if (r < 0) {
        fprintf(stderr, "usb_claim_interface error %d\n", r);
        goto out;
    }
    printf("claimed interface\n");

    char version[128];
    bool ret = jlinkCommandReadFirmwareVersion(version);
    printf("ver[%d] %s\n", ret, version);

    uint8_t bootloader[0xb700] = {0};
    ret = jlinkCommandReadEmulatorMemory( 0x08000000, sizeof(bootloader), bootloader);
    printf("read[%d]\n", ret);

    FILE* fBld = fopen("bootloader.bin", "wb");
    fwrite(bootloader, 1, sizeof(bootloader), fBld);
    fclose(fBld);

out_release:
    libusb_release_interface(devh, 2);
out:
    libusb_close(devh);
    libusb_exit(NULL);
    return r >= 0 ? r : -r;
}

