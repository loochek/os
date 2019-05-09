#include "ata.h"
#include "../peripherals/screen.h"

int wait_ready(uint16_t base)
{
    if (inportb(base + ATA_STATUS_OFFSET) & 1)
        return 0;
    while (inportb(base + ATA_STATUS_OFFSET) & (1 << STATUS_BSY_SHIFT));
    return 1;
}

int wait_data(uint16_t base)
{
    if (inportb(base + ATA_STATUS_OFFSET) & 1)
        return 0;
    while (!(inportb(base + ATA_STATUS_OFFSET) & (1 << STATUS_DRQ_SHIFT)));
    return 1;
}

int identify(char serial[], char firmware[], char model[])
{
    if (!wait_ready(PRIMARY_BASE))
    {
       print("ERR bit is true\n");
       return 0;
    }
    outportb(PRIMARY_BASE + ATA_DRIVE_OFFSET, 0xA0);
    outportb(PRIMARY_BASE + ATA_COUNT_OFFSET, 0);
    outportb(PRIMARY_BASE + ATA_LBALO_OFFSET, 0);
    outportb(PRIMARY_BASE + ATA_LBAMI_OFFSET, 0);
    outportb(PRIMARY_BASE + ATA_LBAHI_OFFSET, 0);
    outportb(PRIMARY_BASE + ATA_COMMAND_OFFSET, ATA_IDENTIFY);
    wait_ready(PRIMARY_BASE);
    if (!inportb(PRIMARY_BASE + ATA_STATUS_OFFSET))
    {
        print("Drive doesn't exist\n");
        return 0;
    }
    wait_data(PRIMARY_BASE);
    unsigned short buf[256];
    for (int i = 0; i < 256; i++)
        buf[i] = inportw(PRIMARY_BASE + ATA_DATA_OFFSET);
    for (int i = 0; i < 20; i++)
        serial[i] = (buf[10 + (i >> 1)] >> ((!(i & 1)) << 3)) & 0xFF;
    serial[20] = 0;
    for (int i = 0; i < 8; i++)
        firmware[i] = (buf[23 + (i >> 1)] >> ((!(i & 1)) << 3)) & 0xFF;
    firmware[8] = 0;
    for (int i = 0; i < 40; i++)
        model[i] = (buf[27 + (i >> 1)] >> ((!(i & 1)) << 3)) & 0xFF;
    model[40] = 0;
    return 1;
}

//int read_lba28(uint64_t start, uint16_t count, void * buffer)
//{
//    int LBA0 = (start >> 0) & 0xFFFF, LBA1 = (start >> 16) & 0xFFFF;
//    outportb(MASTER_PORT + ATA_COUNT_OFFSET, (unsigned char)count);
//    outportb(MASTER_PORT + ATA_LBALO_OFFSET, (LBA0 >> 0) & 0xFF);
//    outportb(MASTER_PORT + ATA_LBAMI_OFFSET, (LBA0 >> 8) & 0xFF);
//    outportb(MASTER_PORT + ATA_LBAHI_OFFSET, (LBA1 >> 0) & 0xFF);
//    outportb(MASTER_PORT + ATA_DRIVE_OFFSET, (unsigned char)(DRIVE_REG_INITIAL | DRIVE_LBA_ENABLE | (MASTER_PORT << DRIVE_DRIVE_SHIFT)));
//    outportb(MASTER_PORT + ATA_COMMAND_OFFSET, ATA_READ);
//    wait_ready();
//    wait_data();
//    unsigned short * buf = (unsigned short*)buffer;
//    for (int i = 0; i < 256 * count; i++)
//        buf[i] = inportw(MASTER_PORT + ATA_DATA_OFFSET);
//    return 1;
//}
