#include <stdio.h>
#include <string.h>
#include <openssl/speck.h>
#include "cmac-speck.h"

static void xor(unsigned char *out, const unsigned char *in, const int block_size) {
  
  	int i;
  
  	for (i = 0; i < block_size; i++) {
  		out[i] ^= in[i];
  	}
  
}

static void derive_subkey(unsigned char *out, unsigned char *in, int block_size) {
  
	int i; 
  	unsigned char overflow = 0x00;

  	for (i = block_size - 1; i >= 0; i--) {
    	out[i] = (in[i] << 1) | overflow;
    	overflow = MSB(&in[i]);
  	}
    
  	if (overflow) {
    	out[block_size-1] ^= 0x87;
  	}
  
}

int cmac_init(cmac_ctx *ctx, const unsigned char *userKey, int key_bits)
{
  
	if(key_bits != 128 && key_bits != 256) {
		return -1;
	}
  
  	ctx = (cmac_ctx *)malloc(sizeof(cmac_ctx));
  	ctx->block_size = key_bits / 16;
  	ctx->k1 = (unsigned char *)calloc(ctx->block_size);
  	ctx->k2 = (unsigned char *)calloc(ctx->block_size);

  	unsigned char k0[ctx->block_size] = {0x00};
  
  	Speck_set_key(userKey, bits, &ctx->speck_key);
  	Speck_encrypt(k0, k0, &ctx->speck_key);
  
  	derive_subkey(ctx->k1, k0, ctx->block_size);
  	derive_subkey(ctx->k2, ctx->k1, ctx->block_size);
  
  return 1;
  
}

unsigned char * cmac_update(cmac_ctx *ctx, const unsigned char *msg, size_t msg_len) {
  
	int i, rest, num_block;
	int BLOCK_SIZE = ctx->block_size;

	unsigned char digest[BLOCK_SIZE] = {0x00};
	unsigned char last_block[BLOCK_SIZE] = {0x00};

  	rest = (msg_len % BLOCK_SIZE);
  	num_block = (msg_len - rest) / BLOCK_SIZE;
	if(rest != 0) {
		num_block++;
	}

	for (i = 1; i < num_block - 1; i++) {
    	xor(digest, msg, BLOCK_SIZE);
    	Speck_encrypt(digest, digest, &ctx->speck_key);
    	msg += BLOCK_SIZE;
  	}

  	if (rest == 0) { 
  		//msg[num_block - 1] is a complete block
  		memcpy(last_block, msg[num_block - 1], BLOCK_SIZE);
  		xor(&last_block, ctx->k1, BLOCK_SIZE);
  	}
  	else {
  		memcpy(last_block, msg[num_block - 1], rest);
  		last_block[rest] = 0x80;
  		xor(&last_block, ctx->k2, BLOCK_SIZE);
  	}
  
  	xor(digest, &last_block, BLOCK_SIZE);
  	Speck_encrypt(digest, digest, &ctx->speck_key);
  
  	return digest;
  
}