#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ELFCLASS32_CUSTOM 1
#define ELFCLASS64_CUSTOM 2

int hexprint(char* filename) {
    FILE* fp = fopen(filename, "rb");
    if(fp==NULL) {
        printf("File does not exists.\n");
        return -1;
    }
    char hexcode[16];
    int len = fread(&hexcode, sizeof(char), 17, fp);




    printf("|");
    for(int i=0; i<len; i++) {
        printf("0x%02X|", hexcode[i]);
    }
    printf("\n");
    len = fread(&hexcode, sizeof(char), 1, fp);
    if(hexcode[0]==ELFCLASS32_CUSTOM) {
        printf("|32bit");
    } else if(hexcode[0]==ELFCLASS64_CUSTOM) {
        printf("|64bit");
    }
    return 0;
}

struct ELF_hdr {
    char magic[4];
    char arch[1];
    char endian[1];
    char version[1];
    char ABI[1];
    char ABI_extension[1];
    char padding[7];
    char typ[2];
    char inst_set[2];
    char version2[4];
    char entry[8];
    char prog_hdr_offset[8];
    char section_hdr_offset[8];
    char arch_flags[4];
    char ELF_hdrsize[2];
    char prog_entry_size[2];
    char prog_entry_cnt[2];
    char section_entry_size[2];
    char section_entry_cnt[2];
    char section_hdr_tbl_idx[2];
};
struct ELF {
    ELF_hdr hdr;
};

ELF* load_ELF(char* filename) {
    FILE* fp = fopen(filename, "rb");
    if(fp==NULL) {
        printf("File does not exists.\n");
        return NULL;
    }
    char hexcode[64];
    int len;
    ELF* e = (ELF*)malloc(sizeof(ELF));
    len = fread(&hexcode, sizeof(char),64, fp);
    memcpy(&(e->hdr), &hexcode, sizeof(char)*64);   // ELF header dump
}

int main() {
    ELF *elf = load_ELF("libhello.so");
    return 0;
}