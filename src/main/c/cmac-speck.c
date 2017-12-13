/*
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Contributors:
 *     William Bathurst
 *     Louis Lamoureux
 *     Geoffrey Barnard
 */

#include <stdio.h>
#include <string.h>
#include <openssl/speck.h>
#include "cmac-speck.h"

void print_hex(const unsigned char *s)
{
  while(*s) 
    printf("%02x", (unsigned int) *s++);
  printf("\n");
}

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

  	ctx->block_size = key_bits / 16;
  	ctx->k1 = (unsigned char *)calloc(ctx->block_size, sizeof(char));
  	ctx->k2 = (unsigned char *)calloc(ctx->block_size, sizeof(char));

  	unsigned char * k0 = (unsigned char *)calloc(ctx->block_size, sizeof(char));
  
  	Speck_set_key(userKey, key_bits, &ctx->speck_key);
  	Speck_encrypt(k0, k0, &ctx->speck_key);
  
  	derive_subkey(ctx->k1, k0, ctx->block_size);
  	derive_subkey(ctx->k2, ctx->k1, ctx->block_size);

  return 1;
  
}

unsigned char * cmac_update(cmac_ctx *ctx, const unsigned char *msg, size_t msg_len) {

	int i, rest, num_block;
	int BLOCK_SIZE = ctx->block_size;

	unsigned char * digest = (unsigned char *)calloc(BLOCK_SIZE, sizeof(char));
	unsigned char * last_block = (unsigned char *)calloc(BLOCK_SIZE, sizeof(char));

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
  		memcpy(last_block, &msg[num_block - 1], BLOCK_SIZE);
  		xor(last_block, ctx->k1, BLOCK_SIZE);
  	}
  	else {
  		memcpy(last_block, &msg[num_block - 1], rest);
  		last_block[rest] = 0x80;
  		xor(last_block, ctx->k2, BLOCK_SIZE);
  	}
  
  	xor(digest, last_block, BLOCK_SIZE);
  	Speck_encrypt(digest, digest, &ctx->speck_key);
  
  	return digest;
  
}
