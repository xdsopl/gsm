CFLAGS = -std=c99 -O3 -W -Wall

all: gsm2ascii ascii2gsm

test: all
	echo -n "*100#" | ./ascii2gsm | ./gsm2ascii

clean:
	rm -f gsm2ascii ascii2gsm

gsm2ascii: gsm2ascii.c

ascii2gsm: ascii2gsm.c

