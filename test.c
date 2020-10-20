#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "global.h"
#include "aes.h"
#include "CRC32.h"

long int filesize( FILE *fp, long offset );

int main (int argc, char **argv) 
{ 
  uint32_t Siz_d = 0;
  uint32_t Siz_e = 0;
  uint32_t Siz_key = 0;
  uint8_t datad[] = { };
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
    }
    else 
    {
        printf("Invalid number of parameters\n");
        return -1;
    }
  }

//--------------------encodind
  else if (strcmp(argv[1], "-e") == 0)
  {
      f1 = fopen(argv[2], "r");
      f2 = fopen(argv[3], "w");
      f3 = fopen(argv[4], "r");
      
      if( f1 != NULL ) {
      Siz_e = filesize(f1, 0L);
      }

            
      if( f3 != NULL ) {
      Siz_key = filesize(f3, 0L);
      }

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
    uint8_t out[Siz_e];

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

    // fprintf(f2, "%d\n", crc32);
     printf("String %s\nSize = %d\nCRC32 = %d\n", Word, Siz_e, crc32);
     fwrite(&datae, 1 , Siz_e, f2);


  }


//--------------------decodind

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
    fscanf(f1, "%d", &CRC32_after);
  
      if( f1 != NULL ) {
      Siz_d = filesize(f1, 0L);
      printf( "File size=%d\n", Siz_d);
      }

            
      if( f3 != NULL ) {
      Siz_key = filesize(f3, 0L);
      printf( "Key size=%d\n", Siz_key);
      }

   uint8_t datad[Siz_d];
    uint8_t key[Siz_key];

    fread(datad, 1 , Siz_d, f1);
    fclose(f1);
    // for (int i = 0; i < Siz_d; i++)
    // fscanf(f1, "%x", &datad[i]);
    // fclose(f1);

    // fread(key, 1 , Siz_key, f3);
    // fclose(f3);
    for (int i = 0; i < 32; i++)
    fscanf(f3, "%x", &key[i]);
    fclose(f3);

    uint16_t CRC32_before = update_crc(-1, datad, Siz_d);
    printf("%d\n", CRC32_before);
    // if (CRC32_after == CRC32_before) printf("SUCCESS CRC32!!!\n");
    // else printf("EROR CRC32\n");
    // printf("%d\n", CRC32_after);
    // printf("%d\n", CRC32_before);

    struct AES_ctx ctx;

    AES_init_ctx(&ctx, key);
    AES_ECB_decrypt(&ctx, datad);

    fwrite(&datad, 1 , Siz_d, f2);

  }
    return 0;
}

long int filesize( FILE *fp, long offset )
  {
    long int save_pos, size_of_file;
 
    save_pos = ftell( fp );
    fseek( fp, offset, SEEK_END );
    size_of_file = ftell( fp );
    fseek( fp, save_pos, SEEK_SET );
    return( size_of_file );
  }
