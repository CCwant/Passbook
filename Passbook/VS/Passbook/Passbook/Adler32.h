#pragma once
#ifndef CRYPTOPP_ADLER32_H
#define CRYPTOPP_ADLER32_H
#include "stdafx.h"


//! ADLER-32 checksum calculations 
class Adler32  
{
public:
	//CRYPTOPP_CONSTANT(DIGESTSIZE = 4)
	Adler32(void);
	~Adler32(void);
	void Update(char *buf,int len);
	long Update(long adler,const char *buf,int off,int len);

	long getValue();
	void reset();

private:

	long adler;
};

#endif

