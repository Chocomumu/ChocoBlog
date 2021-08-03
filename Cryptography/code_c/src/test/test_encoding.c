#include"encoding.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
// gcc test_encoding.c ../basic/encoding.c -o ../../bin/test_encoding -I ../include
INT32 main(INT32 argc, SCHAR const *argv[])
{
    SCHAR  ascii_str[] = {0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef};
    INT32  ascii_str_len = strlen(ascii_str);

    SCHAR *hex_str = (SCHAR *)malloc((ascii_str_len * 2 + 1)*sizeof(SCHAR));
    SCHAR *ascii_str_res = (SCHAR *)malloc((ascii_str_len + 1)*sizeof(SCHAR));

    memset(hex_str,       0x00, ascii_str_len * 2 + 1);
    memset(ascii_str_res, 0x00, ascii_str_len + 1);

    ascii2hex(hex_str, ascii_str, strlen(ascii_str));
    printf("hex string is %s\n", hex_str);
    printf("the length of hex string is %d\n", strlen(hex_str));

    hex2ascii(ascii_str_res, hex_str, strlen(hex_str));
    printf("the length of ascii_str_res is %d\n", strlen(ascii_str_res));
    for (INT32 i = 0; i < strlen(ascii_str_res); i++)
    {
        printf("%02x ", (UCHAR)ascii_str_res[i]);
    }
    printf("\n");
    if (0 == strncmp(ascii_str, ascii_str_res, ascii_str_len))
    {
        printf("res after cvted is equivalent to before \n");
    }
    else
    {
        printf("res after cvted is not equivalent to before \n");
    }

    free(ascii_str_res);
    free(hex_str);

    return 0;
}