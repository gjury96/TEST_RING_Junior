#include "global.h"

void gen_crc_table(void);

uint32_t  update_crc(uint32_t  crc_accum, uint8_t *data_blk_ptr, uint32_t  data_blk_size);
