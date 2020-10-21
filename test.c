#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "aes.h"
#include "CRC32.h"

FILE *f1, *f2, *f3;

int main (int argc, char **argv) 
{ 
  uint32_t Siz_e = 0;
  uint32_t Siz_d = 0;
  uint32_t Siz_key = 0;

  gen_crc_table();
  if (argc == 1) 
  {
    printf("-h help\n");
    return 0;
  }

  if (argc < 5 || argc > 6) 
  {
    if (strcmp(argv[1], "-h") == 0) 
    {
      printf("Parameter order: key, input file location, output file location, encryption key location\n");
      printf("-d decrypts");
      printf("-e encrypts");
      printf("-ed encrypt data");
      printf("-dd decrypt data");
      printf("-c comparison CRC32");
    }
    else 
    {
      printf("Invalid number of parameters\n");
      return -1;
    }
  }

//--------------------encrypts
  else if (strcmp(argv[1], "-e") == 0)
  {
    f1 = fopen(argv[2], "r");
    f2 = fopen(argv[3], "w");
    f3 = fopen(argv[4], "r");
      
    if( f1 != NULL )
      Siz_e = filesize(f1);
  
    if( f3 != NULL )
      Siz_key = filesize(f3);

    if (f1 == NULL) 
    {
      printf("Invalid file address %s\n", argv[2]);
      return -1;
    }
    else if (f2 == NULL)
    {
      printf("Invalid file address %s\n", argv[3]);
      return -1;
    }
    else if (f3 == NULL)
    {
      printf("Invalid file address %s\n", argv[4]);
      return -1;
    }
      
    uint8_t datae[Siz_e];
    uint8_t key[Siz_key];

    fread(datae, 1 , Siz_e, f1);
    fclose(f1);

    for (int i = 0; i < 32; i++)
      fscanf(f3, "%x", &key[i]);
    fclose(f3);

    struct AES_ctx ctx;

    AES_init_ctx(&ctx, key);
    AES_ECB_encrypt(&ctx, datae);

    char Word[] = "BEBEB";

    uint16_t crc32 = update_crc(-1, datae, Siz_e);

    printf("Encrypt data: String %s\tSize = %d\tCRC32 = %d\n", Word, Siz_e, crc32);
    fwrite(&datae, 1 , Siz_e, f2);
  }


//--------------------descrypts

  else if(strcmp(argv[1], "-d") == 0)
  {
    f1 = fopen(argv[2], "r");
    f2 = fopen(argv[3], "w");
    f3 = fopen(argv[4], "r");

    if (f1 == NULL) 
    {
      printf("Invalid file address %s\n", argv[2]);
      return -1;
    }
    else if (f2 == NULL)
    {
      printf("Invalid file address %s\n", argv[3]);
      return -1;
    }
    else if (f3 == NULL)
    {
      printf("Invalid file address %s\n", argv[4]);
      return -1;
    }

    uint16_t CRC32_after;
    printf("Please, enter encrypt data CRC32:\n");
    scanf("%d", &CRC32_after);
  
    if( f1 != NULL ) 
      Siz_d = filesize(f1);

            
    if( f3 != NULL ) 
      Siz_key = filesize(f3);

    uint8_t datad[Siz_d];
    uint8_t key[Siz_key];

    fread(datad, 1 , Siz_d, f1);
    fclose(f1);

    for (int i = 0; i < 32; i++)
      fscanf(f3, "%x", &key[i]);
    fclose(f3);

    uint16_t CRC32_before = update_crc(-1, datad, Siz_d);
    if (CRC32_after == CRC32_before) 
      printf("SUCCESS CRC32!!!\n");
    else printf("EROR CRC32\n");

    struct AES_ctx ctx;

    AES_init_ctx(&ctx, key);
    AES_ECB_decrypt(&ctx, datad);

    printf("Encrypt data: Size = %d\tCRC32 = %d\n", Siz_d, CRC32_before);
    fwrite(&datad, 1 , Siz_d, f2);

  }

return 0;
}

