#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "aes.c"
#include "CRC32.c"


int main (int argc, char **argv) 
{ 
  gen_crc_table();

    if (argc == 1) {
		  printf("-h help\n");
	  }

 	if (argc < 5 || argc > 6) {
    if (strcmp(argv[1], "-h") == 0) {
		  printf("Порядок параметров: ключ, место входного файла, место выходного файлв, место ключа шифрования");
      printf("-d шифровать");
      printf("-e дешивровать");
	  }
     else {
		  printf("Неверное количество параметров");
     }
	}

  if (strcmp(argv[1], "-h") == 0)
  {
		  printf("Порядок параметров: ключ, место входного файла, место выходного файлв, место ключа шифрования\n");
      printf("-d шифровать\n");
      printf("-e дешивровать");
	}
//--------------------encodind
  else if (strcmp(argv[1], "-e") == 0)
  {
		  f1 = fopen(argv[2], "r");
      f2 = fopen(argv[3], "w");
      f3 = fopen(argv[4], "r");

		  if (f1 == NULL) 
      {
			    printf("Неверный адресс файла %s\n", argv[2]);
      }
      else if (f2 == NULL)
      {
          printf("Неверный адресс файла %s\n", argv[3]);
      }
          else if (f3 == NULL)
      {
          printf("Неверный адресс файла %s\n", argv[3]);
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
    
    for (int i = 0; i < 16; i++)
      out[i] = out[i+2];

    char Word[5] = "BEBEB";
    size = ftell(f1); 

    uint16_t crc32 = update_crc(-1, out, Leg);

    // fputs (Word, f2);  //ввод заголовка в файл
    // fprintf(f2, "%d\t", size);
    // fprintf(f2, "%d\n", crc32);

      for (int i = 0; i < 16; i++)
       fprintf(f2, "0x%x\t", out[i]);

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
			    printf("Неверный адресс файла %s\n", argv[2]);
      }
      else if (f2 == NULL)
      {
          printf("Неверный адресс файла %s\n", argv[3]);
      }
            else if (f3 == NULL)
      {
          printf("Неверный адресс файла %s\n", argv[3]);
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
    for (int i = 0; i < 16; i++)
      out[i] = out[i+1];

for (int i = 0; i < 16; i++)
       fprintf(f2, "0x%x\n", out[i]);  
  }

 
	return 0;
}


