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
