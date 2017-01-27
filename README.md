# open-cmac-speck

The IoT Security Suite, commissioned by the Department of Homeland Security (DHS) Science and Technology Directorate (S&T) under the Silicon Valley Innovation Program (SVIP), is developed by Machine-to-Machine Intelligence (M2Mi) Corporation and available as open source under the Apache License. The IoT Security Suite provides an implementation of fast encryption ciphers that use minimal resources capable of operating in small IoT devices and sensors that have limited or constrained capabilities. In order to meet this requirement, the IoT Security Suite uses lightweight block ciphers publicly released by the National Security Agency (NSA) in June 2013 which are part of the SIMON & SPECK family of ciphers designed for both hardware and software implementations.

Speck has been optimized for performance in software implementations, while its sister algorithm, Simon, has been optimized for hardware implementations. Speck is an add-rotate-xor (ARX) cipher. 

In cryptography a HMAC is a specific type of message authentication code (MAC) involving a cryptographic hash function in combination with a secret cryptographic key. Several techniques exists for constructing a message authentication code from a block cipher. In a cipher block chaining message authentication code (CBC-MAC), the message is encrypted with some block cipher algorithm in CBC mode to create a chain of blocks such that each block depends on the proper encryption of the previous block. This interdependence ensures that a change to any of the plaintext bits will cause the final encrypted block to change in a way that cannot be predicted or counteracted without knowing the key to the block cipher. 

However, it is well known that the CBC-MAC is not secure unless the message length is fixed. Therefore, several variants of CBC-MAC have been proposed for variable length messages. One such variant is called one-way CBC-MAC (OMAC). A detailed study of the algorithm can be found here:https://www.iacr.org/archive/fse2003/28870137/28870137.pdf. Officially there are two OMAC algorithms (OMAC1 and OMAC2) which are both essentially the same except for a small tweak. OMAC1 is equivalent to the Cipher-based Message Authentication Code (CMAC) which became a NIST recommendation in May 2005 and is free of all use (no patents). 

This repository contains a C implementation of a keyed-hash message authentication code (HMAC) using the Speck block cipher developed in IoT Security Phase 1 and the OMAC1 algorithm. It is written as a low-level extension on top of the Speck enabled OpenSSL developped by M2Mi as part of the IoT Security Phase 2.

###Usage

    cmac_ctx ctx;
    unsigned char * key = (unsigned char *)"01234567890123456789012345678901";
    unsigned char * message = (unsigned char *)"The quick brown fox jumps over the lazy dog";
    
    /* Initialize the context */
  	cmac_init(&ctx, key, 128);
    
  	/* Hash the message */
  	unsigned char * digest = cmac_update(&ctx, message, strlen ((const char *)message));
