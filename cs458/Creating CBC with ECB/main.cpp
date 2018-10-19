#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "fscrypt.h"

int main()
{
  char s[] = "hello world";
  char *outbuf, *recvbuf, *outbuf2;
  char pass[] = "top secret";
  int len = 0;
  int recvlen = 0;
  int i = 0;
  printf("%s %d\n", "length before encryption = ", (int)strlen(s));
  printf("plaintext = ");
  for (i = 0; i < len; i++)
      printf("%02x", s[i]);
  printf("\n");

  outbuf = (char *) fs_encrypt((void *) s, strlen(s)+1, pass, &len);
  printf("%s %d\n", "length after encryption = ", len);

  printf("ciphertext = ");
  for (i = 0; i < len; i++)
      printf("%02x", outbuf[i]);
  printf("\n");

  recvbuf  = (char *) fs_decrypt((void *) outbuf, len, pass, &recvlen);
  printf("%s %d\n", "length after decryption = ", recvlen);
  printf("plaintext = ");
  for (i = 0; i < len; i++)
      printf("%02x", recvbuf[i]);
  printf("\n");

  assert(memcmp(s, recvbuf, recvlen) == 0);
  assert(recvlen == (strlen(s) + 1));
  printf("plaintext = %s\n", recvbuf);
}