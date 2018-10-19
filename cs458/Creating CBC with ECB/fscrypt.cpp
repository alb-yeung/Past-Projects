#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fscrypt.h"
#include "openssl/blowfish.h"

void *fs_encrypt(void *plaintext, int bufsize, char *keystr, int *resultlen){
	unsigned char* out = (unsigned char*) malloc (100 * sizeof(char));
	int paddedsize = bufsize;
	unsigned char* ptext = (unsigned char*)plaintext;
	if (bufsize%BLOCKSIZE != 0){
		paddedsize = bufsize + (BLOCKSIZE-(bufsize%BLOCKSIZE));
		ptext = new unsigned char[paddedsize];
		strcpy((char*)ptext,(const char*)plaintext);
		for(int i = bufsize; i < paddedsize; i++){
			ptext[i] = BLOCKSIZE - (bufsize%BLOCKSIZE);
		}
	}

	unsigned char* iv = new unsigned char[BLOCKSIZE];
	for (int i = 0; i < BLOCKSIZE; i++){
		iv[i] = 0;
	}
	BF_KEY key;
	BF_set_key(&key, 16, (const unsigned char *)keystr);
	
	unsigned char* Pblock = new unsigned char[BLOCKSIZE];
	for (int i = 0; i < BLOCKSIZE; i++){
		Pblock[i] = ptext[i] ^ iv[i];
	}
	BF_ecb_encrypt(Pblock, out, &key, BF_ENCRYPT);

	for(int i = BLOCKSIZE; i < paddedsize; i += BLOCKSIZE){
		for(int j = 0; j < BLOCKSIZE; j++){
			Pblock[j] = ptext[i+j] ^ out[i+j-BLOCKSIZE];
		}
		BF_ecb_encrypt(Pblock, out+i, &key, BF_ENCRYPT);
	}

	*resultlen = strlen((const char *)out);
	return (void *)out;
	
}

void *fs_decrypt(void *ciphertext, int bufsize, char *keystr, int *resultlen){
	unsigned char* out = (unsigned char*) malloc(bufsize * sizeof(char));
	unsigned char* ctext = (unsigned char*)ciphertext;
	unsigned char* iv = new unsigned char[BLOCKSIZE];
	for (int i = 0; i < BLOCKSIZE; i++){
		iv[i] = 0;
	}
	BF_KEY key;
	BF_set_key(&key, 16, (const unsigned char*)keystr);

	unsigned char* Cblock = new unsigned char[BLOCKSIZE];
	for (int i = 0; i < BLOCKSIZE; i++){
		Cblock[i] = ctext[i];
	}
	BF_ecb_encrypt(Cblock, out, &key, BF_DECRYPT);
	for (int i = 0; i < BLOCKSIZE; i++){
		out[i] ^= iv[i];
	}

	for(int i = BLOCKSIZE; i < bufsize; i+= BLOCKSIZE){
		for(int j = 0; j < BLOCKSIZE; j++){
			Cblock[j] = ctext[i+j];
		}
		BF_ecb_encrypt(Cblock, out+i, &key, BF_DECRYPT);
		for (int j = 0; j < BLOCKSIZE; j++){
			out[i+j] ^= ctext[i+j-BLOCKSIZE];
		}
	}

	*resultlen = strlen((const char*) out) + 1;
	return (void*)out;
}