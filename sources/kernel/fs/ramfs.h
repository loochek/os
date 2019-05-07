#include "stdint.h"
#include "../peripherals/screen.h"
#include "../libc/string.h"

typedef struct
{
    char name[16];
    uint8_t entries_count;
    uint32_t entry_offset[16];
} __attribute__((packed)) dir_node;

typedef struct
{
    char name[16];
    uint32_t size;
    uint32_t data_offset;
} __attribute__((packed)) file_node;

typedef struct
{
    uint32_t root_offset;
} __attribute__((packed)) fs_header;

void print_dir(dir_node *dir, uint32_t ramfs_offset);
