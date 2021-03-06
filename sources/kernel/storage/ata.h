#include "stdint.h"
#include "../peripherals/ports.h"

#define PRIMARY_BASE		0x1F0
#define SECONDARY_BASE		0x170

#define ATA_IDENTIFY		0xEC
#define ATA_READ			0x20
#define ATA_READ_EXT		0x24
#define ATA_WRITE			0x30
#define ATA_WRITE_EXT	    0x34

#define ATA_DATA_OFFSET		0x00
#define ATA_ERROR_OFFSET	0x01
#define ATA_FEATURES_OFFSET 0x01
#define ATA_COUNT_OFFSET 	0x02
#define ATA_LBALO_OFFSET 	0x03
#define ATA_LBAMI_OFFSET 	0x04
#define ATA_LBAHI_OFFSET 	0x05
#define ATA_DRIVE_OFFSET 	0x06
#define ATA_STATUS_OFFSET 	0x07
#define ATA_COMMAND_OFFSET 	0x07

#define DRIVE_DRIVE_SHIFT 	4
#define DRIVE_LBA_ENABLE	(1 << 6)
#define DRIVE_REG_INITIAL	((1 << 7) | (1 << 5))

//Error occurred.
#define STATUS_ERR_SHIFT	0
//Index, zeroed.
#define STATUS_ZERO_SHIFT	1
//Correct data, zeroed
#define STATUS_CORR_SHIFT	2
//Device has data to transfer, or drive is ready to accept data
#define STATUS_DRQ_SHIFT	3
//Overlapped mode service request
#define STATUS_SRV_SHIFT	4
//Drive fault
#define STATUS_DF_SHIFT		5
//Set when isn't spun down
#define STATUS_RDY_SHIFT	6
//Set if device preparing data
#define STATUS_BSY_SHIFT	7

//Address mask not found
#define ERROR_AMNF_SHIFT	0
//Track zero not found
#define ERROR_TKZNF_SHIFT	1
//Command aborted
#define ERROR_ABRT_SHIFT	2
//Media change request
#define ERROR_MCR_SHIFT		3
//ID not found
#define ERROR_IDNF_SHIFT	4
//Media changed
#define ERROR_MC_SHIFT		5
//Uncorrectable data error
#define ERROR_UNC_SHIFT		6
//Bad block detected
#define ERROR_BBK_SHIFT		7

//int read_lba28(uint64_t start, uint16_t count, void * buffer);

int identify(char serial[], char firmware[], char model[]);
