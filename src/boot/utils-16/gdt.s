
GDT_START:
.4byte 0x00000000
.4byte 0x00000000
GDT_DATA:
.4byte 0x0000FFFF # Data segment descriptor
.4byte 0x00CF9200 # read/write
GDT_CODE:
.4byte 0x0000FFFF # Code segment descriptor
.4byte 0x00CF9800 # execute/read
GDT_END:

GDT_DESCRIPTOR:
    .2byte GDT_END - GDT_START - 1
    .4byte GDT_START

CODE_SEG:
    .4byte CODE_SEG - GDT_START
DATA_SEG:
    .4byte DATA_SEG - GDT_START
