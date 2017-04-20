#include "stdafx.h"
#include "Adler32.h"

#define BASE 65521L /* largest prime smaller than 65536 */
#define NMAX 5552

#define DO1(buf,i)  {s1 += buf[i]; s2 += s1;}
#define DO2(buf,i)  DO1(buf,i); DO1(buf,i+1);
#define DO4(buf,i)  DO2(buf,i); DO2(buf,i+2);
#define DO8(buf,i)  DO4(buf,i); DO4(buf,i+4);
#define DO16(buf)   DO8(buf,0); DO8(buf,8);


Adler32::Adler32(void)
{
	reset();
}
Adler32::~Adler32(void)
{

}

void Adler32::Update(char *buf,int len)
{
	adler = Update(adler,buf,0,len);
}
long Adler32::Update(long adler,const char *buf,int off,int len)
{
	// (By Per Bothner)
	unsigned long s1 = adler & 0xffff;
	unsigned long s2 = (adler >> 16) & 0xffff;
	
	while (len > 0) {
		// We can defer the modulo operation:
		// s1 maximally grows from 65521 to 65521 + 255 * 3800
		// s2 maximally grows by 3800 * median(s1) = 2090079800 < 2^31
		int n = 3800;
		if (n > len)
			n = len;
		len -= n;
		while (--n >= 0) {
			s1 = s1 + (buf[off++] & 0xFF);
			s2 = s2 + s1;
		}
		s1 %= BASE;
		s2 %= BASE;
	}

	assert(s1 < BASE);
	assert(s2 < BASE);

	/*
	* Old implementation, borrowed from somewhere: int n;
	* 
	* while (len-- > 0) {
	* 
	* s1 = (s1 + (bs[offset++] & 0xff)) % BASE; s2 = (s2 + s1) % BASE; }
	*/
	return (s2 << 16) | s1;
}
long Adler32::getValue()
{
	return adler & 0xffffffffL;
}
void Adler32::reset()
{
	adler = 1;
}


