#include <stdint.h>
#include <_stdio.h>

#define POLYNOMIAL 0x04c11db7L      
#define BUFFER_LEN       4096L   

uint32_t  crc_table[256]; 

void gen_crc_table(void);

uint32_t  update_crc(uint32_t  crc_accum, uint8_t *data_blk_ptr, uint32_t  data_blk_size);

long int filesize( FILE *fp );
