#include "CRC32.h"
#include <stdio.h>

void gen_crc_table(void)
{
  register uint16_t  i, j;
  register uint32_t  crc_accum;

  for (i=0;  i<256;  i++)
  {
    crc_accum = ( (uint32_t ) i << 24 );
    for ( j = 0;  j < 8;  j++ )
    {
      if ( crc_accum & 0x80000000L )
        crc_accum = (crc_accum << 1) ^ POLYNOMIAL;
      else
        crc_accum = (crc_accum << 1);
    }
    crc_table[i] = crc_accum;
  }
}

uint32_t  update_crc(uint32_t crc_accum, uint8_t  *data_blk_ptr, uint32_t  data_blk_size)
{
   register uint32_t  i, j;

   for (j=0; j<data_blk_size; j++)
   {
     i = ((int) (crc_accum >> 24) ^ *data_blk_ptr++) & 0xFF;
     crc_accum = (crc_accum << 8) ^ crc_table[i];
   }
   crc_accum = ~crc_accum;

   return crc_accum;
}

long int filesize( FILE *fp )
  {
    long int save_pos, size_of_file;
 
    save_pos = ftell( fp );
    fseek( fp, 0L, SEEK_END );
    size_of_file = ftell( fp );
    fseek( fp, save_pos, SEEK_SET );
    return( size_of_file );
  }