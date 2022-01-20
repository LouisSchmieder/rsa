//
// Created by louis on 20.01.22.
//

#include "big.h"
#include <malloc.h>
#include <string.h>

bool addBytes_(bool out, byte a, byte i, byte *string);
big addBig_(big a, big b);

big fromNumber(void *data, size_t length, bool positive) {
	byte *buffer = malloc(length);
	memcpy(buffer, data, length);
	big result = {buffer,
	              length,
	              positive};
	return result;
}

big addBig(big a, big b) {
	if (a.pos && b.pos) {
		return addBig_(a, b);
	}
	return a;
}

big addBig_(big a_, big b_) {
	bool al = a_.len > b_.len;
	size_t lowLength = al ? b_.len : a_.len;
	size_t totalLength = 0;

	if (a_.len == b_.len) {
		totalLength = a_.len + 1;
	} else {
		totalLength = al ? a_.len : b_.len;
	}

	byte *data = malloc(totalLength);

	bool carryOut = false;
	int i;
	for (i = 0; i < totalLength; i++) {
		byte a;
		byte b;

		if (i < lowLength) {
			a = a_.data[i];
			b = b_.data[i];
		} else {
			a = 0x00;
			if (lowLength == totalLength) {
				b = 0x00;
			} else {
				b = al ? a_.data[i] : b_.data[i];
			}
		}

		byte res = 0x00;
		carryOut = addBytes_(carryOut, a, b, &res);
		data[(totalLength - 1) - i] = res;
	}

	if (data[0] == 0x00) {
		totalLength -= 1;
		byte *tmp = malloc(totalLength);
		for (i = 1; i < totalLength + 1; i++) {
			tmp[i - 1] = data[i];
		}
		free(data);
		data = tmp;
	}

	big result = {
	        data,
	        totalLength,
	        a_.pos};

	return result;
}

bool addBytes_(bool carry, byte a, byte b, byte *res) {
	for (int s = 0; s < 8; s++) {
		byte as = ((a >> s) & 0x01);
		if (carry) {
			as ^= 0x01 << s;
			if (as != 0) {
				carry = false;
			}
		}
		byte bs = (b >> s) & 0x01;

		*res |= (as ^ bs);

		if (as == bs && as == 1) {
			carry = true;
			continue;
		}
	}

	return carry;
}


void freeBig(big d) {
	free(d.data);
}
