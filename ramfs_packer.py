import struct, os

file_node_size = 24
dir_node_size = 81

def calculate_fat_size(path):
    size = dir_node_size
    files = os.listdir(path)
    for i in files:
        if os.path.isdir(path + '/' + i):
            size += calculate_fat_size(path + '/' + i)
        else:
            size += file_node_size
    return size

current_fat_offset = 4
current_data_offset = 4
data_offset = 0

fat = bytearray()
data = bytearray()

def generate_file_node(path):
    global current_fat_offset
    global current_data_offset
    global data_offset
    global fat
    global data
    f = open(path, 'rb')
    filedata = f.read()
    f.close()
    filename = os.path.basename(path).encode('ascii')
    fat += struct.pack(str(len(filename)) + 's', filename)
    for i in range(16 - len(os.path.basename(path))):
        fat += b'\0'
    fat += struct.pack('I', len(filedata))
    fat += struct.pack('I', current_data_offset + data_offset)
    data += filedata
    current_fat_offset += file_node_size
    current_data_offset += len(filedata)
    
def generate_dir_node(path):
    global current_fat_offset
    global current_data_offset
    global fat
    global data    
    files = os.listdir(path)
    offsets = []
    for i in files:
        if os.path.isdir(path + '/' + i):
            offsets.append(current_fat_offset)
            generate_dir_node(path + '/' + i)
        else:
            offsets.append(current_fat_offset)
            generate_file_node(path + '/' + i)
    filename = os.path.basename(path).encode('ascii')
    fat += struct.pack(str(len(filename)) + 's', filename)
    for i in range(16 - len(os.path.basename(path))):
        fat += b'\0'
    fat += struct.pack('B', len(files))
    for i in offsets:
        fat += struct.pack('I', i)
    for i in range(16 - len(offsets)):
        fat += struct.pack('I', 0)
    current_fat_offset += dir_node_size
     
data_offset = calculate_fat_size('./ramfs_data')
generate_dir_node('./ramfs_data')
res = struct.pack('I', current_fat_offset - dir_node_size) + fat + data
f = open("ramfs.bin", 'wb')
f.write(res)
f.close()