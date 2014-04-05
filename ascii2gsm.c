
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
	for (int c = getchar(), tmp = 0, bits = 0; c != EOF || bits; c = getchar()) {
		if (c != EOF) {
			tmp |= ascii2gsm(c) << bits;
			bits += 7;
		} else {
			if (bits == 1)
				tmp |= 0x0d << bits;
			bits = 8;
		}
		if (bits >= 8) {
			int lsb = base16(tmp & 15);
			int msb = base16((tmp >> 4) & 15);
			putchar(msb);
			putchar(lsb);
			tmp >>= 8;
			bits -= 8;
		}
	}
	return 0;
}

