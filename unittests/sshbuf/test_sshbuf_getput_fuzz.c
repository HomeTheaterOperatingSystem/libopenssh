/* 	$OpenBSD$ */
/*
 * Regress test for sshbuf.h buffer API
 *
 * Placed in the public domain
 */

#include <sys/types.h>
#include <sys/param.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/bn.h>
#include <openssl/ec.h>
#include <openssl/objects.h>

#include "test_helper.h"
#include "ssherr.h"
#include "sshbuf.h"

void sshbuf_getput_fuzz_tests(void);

static void
attempt_parse_blob(u_char *blob, size_t len)
{
	struct sshbuf *p1;
	BIGNUM *bn;
	EC_KEY *eck;
	u_char *s;
	size_t l;
	u_int8_t u8;
	u_int16_t u16;
	u_int32_t u32;
	u_int64_t u64;

	p1 = sshbuf_new();
	ASSERT_PTR_NE(p1, NULL);
	ASSERT_INT_EQ(sshbuf_put(p1, blob, len), 0);
	sshbuf_get_u8(p1, &u8);
	sshbuf_get_u16(p1, &u16);
	sshbuf_get_u32(p1, &u32);
	sshbuf_get_u64(p1, &u64);
	if (sshbuf_get_string(p1, &s, &l) == 0) {
		bzero(s, l);
		free(s);
	}
	bn = BN_new();
	sshbuf_get_bignum1(p1, bn);
	BN_clear_free(bn);
	bn = BN_new();
	sshbuf_get_bignum2(p1, bn);
	BN_clear_free(bn);
	eck = EC_KEY_new_by_curve_name(NID_X9_62_prime256v1);
	ASSERT_PTR_NE(eck, NULL);
	sshbuf_get_eckey(p1, eck);
	EC_KEY_free(eck);
	sshbuf_free(p1);
}

void
sshbuf_getput_fuzz_tests(void)
{
	u_char blob[] = {
		/* u8 */
		0xd0,
		/* u16 */
		0xc0, 0xde,
		/* u32 */
		0xfa, 0xce, 0xde, 0xad,
		/* u64 */
		0xfe, 0xed, 0xac, 0x1d, 0x1f, 0x1c, 0xbe, 0xef,
		/* string */
		0x00, 0x00, 0x00, 0x09,
		'O', ' ', 'G', 'o', 'r', 'g', 'o', 'n', '!',
		/* bignum1 */
		0x79,
		0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
		0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10,
		/* bignum2 */
		0x00, 0x00, 0x00, 0x14,
		0x00,
		0xf0, 0xe0, 0xd0, 0xc0, 0xb0, 0xa0, 0x90, 0x80,
		0x70, 0x60, 0x50, 0x40, 0x30, 0x20, 0x10, 0x00,
		0x7f, 0xff, 0x11,
		/* EC point (NIST-256 curve) */
		0x00, 0x00, 0x00, 0x41,
		0x04,
		0x0c, 0x82, 0x80, 0x04, 0x83, 0x9d, 0x01, 0x06,
		0xaa, 0x59, 0x57, 0x52, 0x16, 0x19, 0x13, 0x57,
		0x34, 0xb4, 0x51, 0x45, 0x9d, 0xad, 0xb5, 0x86,
		0x67, 0x7e, 0xf9, 0xdf, 0x55, 0x78, 0x49, 0x99,
		0x4d, 0x19, 0x6b, 0x50, 0xf0, 0xb4, 0xe9, 0x4b,
		0x3c, 0x73, 0xe3, 0xa9, 0xd4, 0xcd, 0x9d, 0xf2,
		0xc8, 0xf9, 0xa3, 0x5e, 0x42, 0xbd, 0xd0, 0x47,
		0x55, 0x0f, 0x69, 0xd8, 0x0e, 0xc2, 0x3c, 0xd4,
	};
	u_char *blobm;
	u_int i, j;

	TEST_START("flip every byte");
	blobm = malloc(sizeof(blob));
	for (i = 0; i < sizeof(blob); i++) {
		memcpy(blobm, blob, sizeof(blob));
		blobm[i / 8] ^= 0xff;
		attempt_parse_blob(blobm, sizeof(blob));
	}
	free(blobm);
	TEST_DONE();

	TEST_START("flip two bytes");
	blobm = malloc(sizeof(blob));
	for (i = 0; i < sizeof(blob); i++) {
		for (j = 0; i < sizeof(blob); i++) {
			if (i == j)
				continue;
			memcpy(blobm, blob, sizeof(blob));
			blobm[i / 8] ^= 0xff;
			blobm[j / 8] ^= 0xff;
			attempt_parse_blob(blobm, sizeof(blob));
		}
	}
	free(blobm);
	TEST_DONE();
	TEST_START("flip one bit");
	blobm = malloc(sizeof(blob));
	for (i = 0; i < sizeof(blob) * 8; i++) {
		memcpy(blobm, blob, sizeof(blob));
		blobm[i / 8] ^= 1 << (i % 8);
		attempt_parse_blob(blobm, sizeof(blob));
	}
	free(blobm);
	TEST_DONE();

	TEST_START("flip two bits");
	blobm = malloc(sizeof(blob));
	for (i = 0; i < sizeof(blob) * 8; i++) {
		for (j = 0; i < sizeof(blob) * 8; i++) {
			if (i == j)
				continue;
			memcpy(blobm, blob, sizeof(blob));
			blobm[i / 8] ^= 1 << (i % 8);
			blobm[j / 8] ^= 1 << (j % 8);
			attempt_parse_blob(blobm, sizeof(blob));
		}
	}
	free(blobm);
	TEST_DONE();
}


