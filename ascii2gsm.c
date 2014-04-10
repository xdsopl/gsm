
/*
gsm - encode and decode message in GSM 03.38
Written in 2014 by <Ahmet Inan> <xdsopl@googlemail.com>
To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.
You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
*/

#include <stdio.h>
#include <ctype.h>

int base16(int c)
{
	return c <= 9 ? c + '0' : c - 10 + 'A';
}

int ascii2gsm(int c)
{
	switch (c) {
		case '@':
			return 0x00;
		case '$':
			return 0x02;
		case '_':
			return 0x11;
		case '\n':
			return 0x0d;
		default:
			if (c < 0x20
				|| (0x5b <= c && c <= 0x60)
				|| (0x7b <= c && c <= 0x7f))
					return '.';
	}
	return c;
}

int main()
{
	int tmp = 0, bits = 0;
	for (int c = getchar(); c != EOF; c = getchar()) {
		tmp |= ascii2gsm(c) << bits;
		bits += 7;
		if (bits >= 8) {
			putchar(base16((tmp >> 4) & 15));
			putchar(base16(tmp & 15));
			tmp >>= 8;
			bits -= 8;
		}
	}
	if (bits == 1)
		tmp |= 0x0d << 1;
	if (bits) {
		putchar(base16((tmp >> 4) & 15));
		putchar(base16(tmp & 15));
	}
	return 0;
}

