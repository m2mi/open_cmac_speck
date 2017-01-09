/*
 * (C) Copyright ${year} Machine-to-Machine Intelligence (M2Mi) Corporation, all rights reserved.
 *
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
 *     Julien Niset 
 */

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

void print_hex(const unsigned char *s);

#endif
