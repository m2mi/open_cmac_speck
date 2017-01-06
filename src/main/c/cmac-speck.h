#ifndef _cmac_speck
#define _cmac_speck

#include <openssl/speck.h>

#define MSB(x) (((x)[0] & 0x80)?1:0)

struct cmac_ctx_st {
	int block_size;
  	unsigned char * k1;
  	unsigned char * k2;
  	SPECK_KEY speck_key;
};
typedef struct cmac_ctx_st cmac_ctx;

int cmac_init(cmac_ctx *ctx, const unsigned char *userKey, int key_bits);

unsigned char * cmac_update(cmac_ctx *ctx, const unsigned char *msg, size_t msg_len);

#endif
