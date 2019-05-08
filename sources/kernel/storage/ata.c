#include "ata.h"
int wait_ready()
{
    if (port_byte_in(MASTER_PORT + ATA_STATUS_OFFSET) & 1) return 0;
    while (port_byte_in(MASTER_PORT + ATA_STATUS_OFFSET) & (1 << STATUS_BSY_SHIFT));
    return 1;
}

int wait_data()
{
    if (port_byte_in(MASTER_PORT + ATA_STATUS_OFFSET) & 1) return 0;
    while (!(port_byte_in(MASTER_PORT + ATA_STATUS_OFFSET) & (1 << STATUS_DRQ_SHIFT)));
    return 1;
}

int read_lba28(uint64_t start, uint16_t count, void * buffer)
{
    int LBA0 = (start >> 0) & 0xFFFF, LBA1 = (start >> 16) & 0xFFFF;
    port_byte_out(MASTER_PORT + ATA_COUNT_OFFSET, (unsigned char)count);
    port_byte_out(MASTER_PORT + ATA_LBALO_OFFSET, (LBA0 >> 0) & 0xFF);
    port_byte_out(MASTER_PORT + ATA_LBAMI_OFFSET, (LBA0 >> 8) & 0xFF);
    port_byte_out(MASTER_PORT + ATA_LBAHI_OFFSET, (LBA1 >> 0) & 0xFF);
    port_byte_out(MASTER_PORT + ATA_DRIVE_OFFSET, (unsigned char)(DRIVE_REG_INITIAL | DRIVE_LBA_ENABLE | (MASTER_PORT << DRIVE_DRIVE_SHIFT)));
    port_byte_out(MASTER_PORT + ATA_COMMAND_OFFSET, ATA_READ);
    wait_ready();
    wait_data();
    unsigned short * buf = (unsigned short*)buffer;
    for (int i = 0; i < 256 * count; i++)
        buf[i] = port_word_in(MASTER_PORT + ATA_DATA_OFFSET);
    return 1;
}
