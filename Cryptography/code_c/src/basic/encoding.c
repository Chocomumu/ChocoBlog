#include "encoding.h"
#define HEX2FOURBITS(x)  ((x) >= 'A' ? (x) - 'A' + 10 :  (x) - '0')
SCHAR * ascii2hex(SCHAR *dest, SCHAR *src, INT32 src_len)
{
    SCHAR temp = 0;
    SCHAR *tmp_dest = dest;
    SCHAR *tmp_src = src;
    INT32 i = 0;
    for(; i < src_len; i++)
    {
        /* 取高位四字节进行转换 */
        temp = (*tmp_src & 0xf0) >> 4;
        if (temp < CHAR10)
        {
            *tmp_dest = '0' + temp;
        }
        else
        {
            *tmp_dest = 'A' + temp - 10;
            // tmp_dest = 'a' + temp - 10;
        }
        tmp_dest ++;
        /* 取低位四字节进行转换 */
        temp = *tmp_src & 0x0f;
        if (temp < CHAR10)
        {
            *tmp_dest = '0' + temp;
        }
        else
        {
            *tmp_dest = 'A' + temp - 10;
            // tmp_dest = 'a' + temp - 10;
        }
        tmp_src  ++;
        tmp_dest ++;
    }
    return dest;
}
SCHAR * hex2ascii(SCHAR *dest, SCHAR *src, INT32 src_len)
{
    SCHAR temp = 0;
    SCHAR *tmp_dest = dest;
    SCHAR *tmp_src = src;
    INT32 i = 0;
    for(; i < src_len; i+=2)
    {
        *tmp_dest = (HEX2FOURBITS(tmp_src[i]) << 4) | HEX2FOURBITS(tmp_src[i+1]);
        /* printf("%02x ", (UCHAR)*(tmp_dest)); */
        tmp_dest ++;
    }
    return dest;
}