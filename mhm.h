/* My Hash Map.
 * See licence at the end of the file.                         (._. )
 *
 * Characteristics:
 *
 * - Single header library.
 * - One malloc() call on initialization.
 * - You need to know max number/limit of your keys upfront.
 * - Data storage is responsibility of the user.  Hash Map structure
 *   stores only pointers to key strings and void pointers to values.
 * - No dynamic memory management.
 * - Predefined hash functions but custom can be provided.
 * - Linear probing in case of collisions.  Because of this strategy
 *   performance suffers a lot when you try to check/get/delete key
 *   that was not set.
 * - Asserts in main API functions to help avoid major mistakes.
 *
 * Usage:
 *
 *	#define MHM_IMPLEMENTATION      // Define once in main file
 *	#include "mhm.h"
 *
 *	// Hash Map structure.  Does not require initialization with
 *	// 0 like "Mhm hm = {0}" as the mhm_init() will define all
 *	// structure values anyway.
 *	Mhm hm;
 *
 *	// Initialize Hash Map with 256 slots and djb2 hash function.
 *	if (mhm_init(&hm, 256, mhm_hash_djb2)) {
 *		// Handle errors.  The only possible error is fail in
 *		// malloc() so usually you should be safe but error
 *		// here is rather critical.
 *	}
 *
 *	// Set new value.
 *	if (mhm_set(&hm, "KeyName", "Your value")) {
 *		// Yes, this can fail if there are no more empty slots
 *		// in Hash Map.  If you know upfront that you will not
 *		// set more keys than available slots then maybe you
 *		// can skip this error handling.  But don't go crying
 *		// to me later if you will have hard to debug error
 *		// because of missing error handling.
 *	}
 *	if (mhm_set(&hm, "AnotherKey", "Test value")) return 1;
 *	if (mhm_set(&hm, "LastKey", "Lorem Ipsum")) return 1;
 *
 *	// Get values.
 *	printf("%s\n", mhm_get(&hm, "KeyName"));
 *	printf("%s\n", mhm_get(&hm, "AnotherKey"));
 *	printf("%s\n", mhm_get(&hm, "LastKey"));
 *
 *	// NULL is returned for keys that where never set.
 *	// Note that searching for key that was never defined cost
 *	// a lot as linear probing will be performed in effort to
 *	// try find this key.
 *	printf("%s\n", mhm_get(&hm, "InvalidKey"));
 *
 *	// Check if key was defined.  Note that searching for key
 *	// that was never defined cost performance as linear probing
 *	// will be performed in effort to try find this key.
 *	if (mhm_has(&hm, "AnotherKey")) {
 *		// "AnotherKey" exists in hash map.
 *	}
 *
 *	// Delete key with value.
 *	mhm_del(&hm, "KeyName");
 *	mhm_del(&hm, "AnotherKey");
 *	mhm_del(&hm, "LastKey");
 *
 *	// Removing invalid key will do nothing but costs performance
 *	// as linear probing will be performed in effort to try find
 *	// the key.
 *	mhm_del(&hm, "InvalidKey");
 *
 *	// This is an internal function but useful for debugging.
 *	// It prints whole memory of hash map to stdout.
 *	_mhm_dump(&hm);
 */
#ifndef MHM_H
#define MHM_H

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MHM_NONE SIZE_MAX       /* Used when indexof key was not found */

/* Type of hashing function that takes KEY string and return hash. */
typedef size_t (*Mhm_Hash)(char *key);

typedef struct mhm {            /* Hash Map structure */
	size_t    _used;        /* Number of used keys */
	size_t    _siz;         /* Size of _key and _buf arrays */
	char    **_key;         /* Buffer with pointers to key strings */
	/* TODO(irek): Make it work with any data type so it is
	 * convenient when you like to us ints or strings with
	 * predefined size itp.  It should be possible to just have
	 * and pointer to a memory and knowledge of single item size
	 * to make it work. */
	void    **_buf;         /* Buffer with pointers to values */
	Mhm_Hash  _hash;        /* Hashing function */
} Mhm;

/* Initialize HM hash map with buffer of SIZ number of slots and HASH
 * hashing function.  It's expected to use one of mhm_hash_* hash
 * functions but any custom hashing function can be provided instead.
 * Return non 0 value on error.  As the only possible error is fail in
 * call to malloc() you should not expect any failures. */
int mhm_init(Mhm *hm, size_t siz, Mhm_Hash hash);

/* In HM hash map store VALUE pointer to any value under KEY.  Return
 * non 0 value on success.  Set can fail if there is no more empty
 * slots in hash map.  In that case you should initialize hash map
 * with more slots upfront. */
int mhm_set(Mhm *hm, char *key, void *value);

/* From HM hash map get KEY item value pointer. */
void *mhm_get(Mhm *hm, char *key);

/* From HM hash map delete KET item. */
void mhm_del(Mhm *hm, char *key);

/* Return non 0 value if HM hash map has KEY item. */
int mhm_has(Mhm *hm, char *key);

/* Create hash of STR by adding all STR bytes. */
size_t mhm_hash_add(char *str);

/* Create hash of STR using DJB2 (Daniel J. Bernstein) algorithm. */
size_t mhm_hash_djb2(char *str);

/* Return index to KEY item in HM hash map.  Return MHM_NONE if not
 * found. */
size_t _mhm_indexof(Mhm *hm, char *key);

/* Print whole HM hash map memory buffer to stdout. */
void _mhm_dump(Mhm *hm);

#endif /* MHM_H */
#ifdef MHM_IMPLEMENTATION

int
mhm_init(Mhm *hm, size_t siz, Mhm_Hash hash)
{
	assert(hm);
	assert(siz > 0);
	assert(siz < MHM_NONE);
	assert(hash);
	hm->_used = 0;
	hm->_siz = siz;
	hm->_hash = hash;
	if ((hm->_key = malloc(siz * sizeof(*hm->_key))) == 0) return 1;
	if ((hm->_buf = malloc(siz * sizeof(*hm->_buf))) == 0) return 2;
	memset(hm->_key, 0, siz);
	memset(hm->_buf, 0, siz);
	return 0;
}

int
mhm_set(Mhm *hm, char *key, void *value)
{
	size_t i;
	assert(hm);
	assert(key);
	if (hm->_used >= hm->_siz) return 1;
	i = (hm->_hash)(key) % hm->_siz;
	while (hm->_key[i]) i = (i + 1) % hm->_siz;
	hm->_key[i] = key;
	hm->_buf[i] = value;
	hm->_used++;
	return 0;
}

void *
mhm_get(Mhm *hm, char *key)
{
	size_t i;
	assert(hm);
	assert(key);
	i = _mhm_indexof(hm, key);
	if (i == MHM_NONE) return 0;
	return hm->_buf[i];
}

void
mhm_del(Mhm *hm, char *key)
{
	size_t i;
	assert(hm);
	assert(key);
	i = _mhm_indexof(hm, key);
	if (i == MHM_NONE) return;
	hm->_key[i] = 0;
	hm->_buf[i] = 0;
	hm->_used--;
}

int
mhm_has(Mhm *hm, char *key)
{
	assert(hm);
	assert(key);
	return _mhm_indexof(hm, key) != MHM_NONE;
}

size_t
mhm_hash_add(char *str)
{
	size_t hash = 0;
	while (*str) hash += *str++;
	return hash;
}

/* Modified version of https://theartincode.stanis.me/008-djb2/ */
size_t
mhm_hash_djb2(char *str)
{
	size_t hash = 5381;
	while (*str) hash += (hash << 5) + *str++;
	return hash;
}

size_t
_mhm_indexof(Mhm *hm, char *key)
{
	size_t i, j;
	if (hm->_used == 0) return MHM_NONE;
	i = (hm->_hash)(key) % hm->_siz;
	for (j = 0; 1; j++) {
		if (j >= hm->_siz) return MHM_NONE;
		if (hm->_key[i] && *hm->_key[i] == *key && !strcmp(hm->_key[i], key)) {
			break;
		}
		i = (i + 1) % hm->_siz;
	}
	return i;
}

void
_mhm_dump(Mhm *hm)
{
	size_t i;
	for (i = 0; i < hm->_siz; i++) {
		printf("%s\t%p\n", hm->_key[i], hm->_buf[i]);
	}
	printf("Number of items: %lu\n", hm->_used);
}

#endif /* MHM_IMPLEMENTATION */
/*
This software is available under 2 licenses, choose whichever.
----------------------------------------------------------------------
ALTERNATIVE A - MIT License, Copyright (c) 2023 Irek
Permission is hereby granted, free  of charge, to any person obtaining
a  copy  of this  software  and  associated documentation  files  (the
"Software"), to  deal in  the Software without  restriction, including
without limitation  the rights to  use, copy, modify,  merge, publish,
distribute, sublicense,  and/or sell  copies of  the Software,  and to
permit persons to whom the Software  is furnished to do so, subject to
the  following  conditions:  The   above  copyright  notice  and  this
permission  notice shall  be  included in  all  copies or  substantial
portions of the  Software.  THE SOFTWARE IS PROVIDED  "AS IS", WITHOUT
WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE WARRANTIES  OF MERCHANTABILITY,  FITNESS FOR A  PARTICULAR PURPOSE
AND  NONINFRINGEMENT.  IN  NO  EVENT SHALL  THE  AUTHORS OR  COPYRIGHT
HOLDERS BE LIABLE  FOR ANY CLAIM, DAMAGES OR  OTHER LIABILITY, WHETHER
IN AN ACTION  OF CONTRACT, TORT OR OTHERWISE, ARISING  FROM, OUT OF OR
IN CONNECTION  WITH THE SOFTWARE OR  THE USE OR OTHER  DEALINGS IN THE
SOFTWARE.
----------------------------------------------------------------------
ALTERNATIVE B - Public Domain (www.unlicense.org)
This  is  free and  unencumbered  software  released into  the  public
domain.  Anyone is free to  copy, modify, publish, use, compile, sell,
or  distribute this  software,  either in  source code  form  or as  a
compiled binary, for any purpose, commercial or non-commercial, and by
any means.  In jurisdictions that recognize copyright laws, the author
or authors of this software dedicate any and all copyright interest in
the software  to the public domain.   We make this dedication  for the
benefit of the public  at large and to the detriment  of our heirs and
successors.   We  intend  this  dedication  to  be  an  overt  act  of
relinquishment in perpetuity of all  present and future rights to this
software  under copyright  law.   THE SOFTWARE  IS  PROVIDED "AS  IS",
WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR IMPLIED, INCLUDING  BUT NOT
LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
PURPOSE AND NONINFRINGEMENT.  IN NO  EVENT SHALL THE AUTHORS BE LIABLE
FOR ANY  CLAIM, DAMAGES OR  OTHER LIABILITY,  WHETHER IN AN  ACTION OF
CONTRACT, TORT  OR OTHERWISE,  ARISING FROM, OUT  OF OR  IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
