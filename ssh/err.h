/*	$OpenBSD$	*/
/*
 * Copyright (c) 2011 Damien Miller
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _SSH_ERR_ERR_H
#define _SSH_ERR_ERR_H

/* XXX are these too granular? not granular enough? I can't decide - djm */

/* Error codes */
#define SSH_ERR_SUCCESS				0
#define SSH_ERR_INTERNAL_ERROR			-1
#define SSH_ERR_ALLOC_FAIL			-2
#define SSH_ERR_MESSAGE_INCOMPLETE		-3
#define SSH_ERR_INVALID_FORMAT			-4
#define SSH_ERR_BIGNUM_IS_NEGATIVE		-5
#define SSH_ERR_BIGNUM_TOO_LARGE		-6
#define SSH_ERR_ECPOINT_TOO_LARGE		-7
#define SSH_ERR_NO_BUFFER_SPACE			-8
#define SSH_ERR_INVALID_ARGUMENT		-9
#define SSH_ERR_KEY_BITS_MISMATCH		-10
#define SSH_ERR_EC_CURVE_INVALID		-11
#define SSH_ERR_KEY_TYPE_MISMATCH		-12
#define SSH_ERR_KEY_TYPE_UNKNOWN		-13 /* XXX UNSUPPORTED? */
#define SSH_ERR_EC_CURVE_MISMATCH		-14
#define SSH_ERR_EXPECTED_CERT			-15
#define SSH_ERR_KEY_LACKS_CERTBLOB		-16
#define SSH_ERR_KEY_CERT_UNKNOWN_TYPE		-17
#define SSH_ERR_KEY_CERT_INVALID_SIGN_KEY	-18
#define SSH_ERR_KEY_INVALID_EC_VALUE		-19
#define SSH_ERR_SIGNATURE_INVALID		-20
#define SSH_ERR_LIBCRYPTO_ERROR			-21
#define SSH_ERR_UNEXPECTED_TRAILING_DATA	-22
#define SSH_ERR_SYSTEM_ERROR			-23
#define SSH_ERR_KEY_CERT_INVALID		-24
#define SSH_ERR_AGENT_COMMUNICATION		-25
#define SSH_ERR_AGENT_FAILURE			-26
#define SSH_ERR_DH_GEX_OUT_OF_RANGE		-27
#define SSH_ERR_DISCONNECTED			-28
#define SSH_ERR_MAC_INVALID			-29
#define SSH_ERR_NO_CIPHER_ALG_MATCH		-30
#define SSH_ERR_NO_MAC_ALG_MATCH		-31
#define SSH_ERR_NO_COMPRESS_ALG_MATCH		-32
#define SSH_ERR_NO_KEX_ALG_MATCH		-33
#define SSH_ERR_NO_HOSTKEY_ALG_MATCH		-34
#define SSH_ERR_NO_HOSTKEY_LOADED		-35
#define SSH_ERR_PROTOCOL_MISMATCH		-36
#define SSH_ERR_NO_PROTOCOL_VERSION		-37
#define SSH_ERR_NEED_REKEY			-38
#define SSH_ERR_PASSPHRASE_TOO_SHORT		-39
#define SSH_ERR_FILE_CHANGED			-40
#define SSH_ERR_KEY_UNKNOWN_CIPHER		-41
#define SSH_ERR_KEY_WRONG_PASSPHRASE		-42
#define SSH_ERR_KEY_BAD_PERMISSIONS		-43
#define SSH_ERR_KEY_CERT_MISMATCH		-44
#define SSH_ERR_KEY_NOT_FOUND			-45
#define SSH_ERR_AGENT_NOT_PRESENT		-46
#define SSH_ERR_AGENT_NO_IDENTITIES		-47
#define SSH_ERR_BUFFER_READ_ONLY		-48


/* Translate a numeric error code to a human-readable error string */
const char *ssh_err(int n);

#endif /* _SSH_ERR_ERR_H */
