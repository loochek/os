#include "ramfs.h"


void print_dir(dir_node *dir, uint32_t ramfs_offset)
{
    print("Directory: ");
    print(dir->name);
    print("\nContains:\n");
    int files_count = dir->entries_count;
    for (int i = 0; i < files_count; i++)
    {
        file_node *file = (file_node*)(dir->entry_offset[i] + ramfs_offset);
        print(file->name);
        if (strcmp(file->name, "hello.txt") == 0)
            print((char*)(file->data_offset + ramfs_offset));
        print("\n");
    }
}
