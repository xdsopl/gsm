
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
	return c <= '9' ? c - '0' : tolower(c) - 'a' + 10;
}

int gsm2ascii(int c)
{
	switch (c) {
		case 0x00:
			return '@';
		case 0x02:
			return '$';
		case 0x11:
			return '_';
		case 0x0d:
			return '\n';
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
	for (int msb = getchar(), lsb = getchar(), tmp = 0, bits = 0; msb != EOF && lsb != EOF; msb = getchar(), lsb = getchar()) {
		tmp |= (base16(msb) << 4 | base16(lsb)) << bits;
		bits += 8;
		while (bits >= 7) {
			putchar(gsm2ascii(tmp & 127));
			bits -= 7;
			tmp >>= 7;
		}
	}
	return 0;
}

