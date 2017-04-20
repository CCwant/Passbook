#pragma once

#define PASSWD_VERSION 48
typedef signed char        int8_t;
typedef short              int16_t;
typedef int                int32_t;
typedef long long          int64_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;


typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;
typedef uint64_t u8;



inline int C2I(const char *data)
{
	int result = 0;  

	int a = (data[0] & 0xff) << 24;//หตร๗ถþ  
	int b = (data[1] & 0xff) << 16;  
	int c = (data[2] & 0xff) << 8;  
	int d = (data[3] & 0xff);  
	result = a | b | c | d;  

	return result ;  
}

