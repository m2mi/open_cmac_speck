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

#include <string.h>
#include <stdio.h>
#include "cmac-speck.h"

int main(int argc, const char * argv[]) {

	unsigned char * digest;
	cmac_ctx * ctx;

	/* A 128 bit key */
  	unsigned char *key = (unsigned char *)"01234567890123456789012345678901";
  	/* Message to hash */
  	unsigned char *message = (unsigned char *)"The quick brown fox jumps over the lazy dog";

  	/* Initialize the context */
  	cmac_init(ctx, key, 128);

  	/* Hash the message */
  	digest = cmac_update(ctx, message, strlen ((const char *)message));

  	printf("Digest is: %s", digest);

}
