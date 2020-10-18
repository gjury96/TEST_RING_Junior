#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "global.h"
#include "aes.h"
#include "CRC32.h"



int main (int argc, char **argv) 
{ 
  uint8_t datae[16];
  uint8_t datad[16];
  gen_crc_table();
  if (argc == 1) 
  {
          printf("-h help\n");
          return 0;
      }

     if (argc < 5 || argc > 6) {
    if (strcmp(argv[1], "-h") == 0) {
      printf("Parameter order: key, input file location, output file location, encryption key location\n");
      printf("-d decrypts");
      printf("-e encrypts");
      }
     else {
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
     int Leg = 16;

    for (int i = 0; i < 16; i++)
    fscanf(f1, "%x", &datae[i]);
    fclose(f1);

    for (int i = 0; i < 32; i++)
    fscanf(f3, "%x", &key[i]);
    fclose(f3);
    
struct AES_ctx ctx;

    AES_init_ctx(&ctx, key);
    AES_ECB_encrypt(&ctx, datae);

    char Word[5] = "BEBEB";
    size = ftell(f1); 

    uint16_t crc32 = update_crc(-1, datae, Leg);

    // // fputs (Word, f2);  //writing header to file
    // // fprintf(f2, "%d\t", size);
    // // fprintf(f2, "%d\n", crc32);

      for (int i = 0; i < 16; i++)
       fprintf(f2, "0x%x\n", datae[i]);
    
    // // for (int i = 0; i < 256; i++) //bit format of output data
    // // {
    // //   for (int j = 0; j < 8; j++) 
    // //   {
    // //     fprintf(f2, "0x%x\t", (out[i] & 0x80) ? '1' : '0'))
    // //     out[i] <<= 1;
    // //   }
    // // }
    printf("%s %d %d\n", Word, size, crc32);


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
    for (int i = 0; i < 16; i++)
    fscanf(f1, "%x", &datad[i]);
    fclose(f1);

    for (int i = 0; i < 32; i++)
    fscanf(f3, "%x", &key[i]);
    fclose(f3);
  
    int Leg = 16;
    uint16_t b = update_crc(-1, datad, Leg);
    printf("%d\n", b);

struct AES_ctx ctx;

    AES_init_ctx(&ctx, key);
    AES_ECB_decrypt(&ctx, datad);

// size = ftell(f2);
    // for (int i = 0; i < 16; i++)
    //   out[i] = out[i+1];

for (int i = 0; i < 16; i++)
       fprintf(f2, "0x%x\n", datad[i]);  
  }

 
    return 0;
}


