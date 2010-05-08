// Ocelot1.h
#ifndef __OCELOT1_H__
#define __OCELOT1_H__

#include "Counter.h"

#include <cstring>

using namespace std;

#define BYTE unsigned char

class Ocelot1
{
//****************************************************************************
//
// The OCELOT1 stream ciphering method method, Version 1.1.0 (01 May 2010)
// Copyright (C) 2009-2010, George Anescu, www.sc-gen.com
// All right reserved.
//
// This is the C++ implementation of a new stream ciphering method called OCELOT1. It is accepting any practical key size and can
// be set to any practical state size.
//
// COPYRIGHT PROTECTION: The OCELOT1 stream ciphering method is still under development and testing and for this reason the code is
// freely distributed only for TESTING AND RESEARCH PURPOSES. The author is reserving for himself the rights to MODIFY AND MAINTAIN the
// code, but any ideas about improving the code are welcomed and will be recognized if implemented.
//
// If you are interested in testing the code, in research collaborations for possible security holes in the method, or in any
// other information please contact the author at <george.anescu@sc-gen.com>.
//
// Test Samples:
//
// 1)
// statesize=4, key="XXXXXXX"
// hexresult="1DF27C916D3443EA5CB3D1C44EC8F6C3D01C0BDBF3CBD5"...
// hexresult=..."56051B30C8BAE9EB96A5A44178A5254E01419D95D48A13"
//
// 2)
// statesize=4, key="YXXXXXX"
// hexresult="87D9B363BACC5EA792DFE7CF2331F19F44DD3526A2483BCA9851037AFD5D2F66DF6FFA29E39FFABB715C5A0B75E3E5D74ED8"...
//
// 3)
// statesize=8, key="\0\0\0\0"
// hexresult="16CF935B0A0EB611EC0840E578A8521215D9D938D18C5F"...
//
//****************************************************************************
public:
	//Constructors
	Ocelot1() {}

	Ocelot1(int size, BYTE const* key, int keysize)
	{
		Initialize(size, key, keysize);
	}
	
	void Initialize(int size, BYTE const* key, int keysize);

	void Reset()
	{
		memcpy(_data, _data0, _size);
		_val = _data0[_size];
		memcpy(_ss, _ss0, 256);            
		_cnt.Reset();
		_ix = _ix0;
		_ix1 = _ix1_0;
		_incr = _incr0;
	}

	void GetNextByte(BYTE& rnd);

	void GetBytes(BYTE* bytes, int n)
	{
		for (int i = 0; i < n; i++)
		{
			GetNextByte(bytes[i]);
		}
	}

private:
	void Expansion(BYTE const* key, int keysize, BYTE* res, int dim, short iter, bool compl);

	//F1 function - switches even bits
	static BYTE F1(BYTE val)
	{
		return (val & 0x55) | (~val & 0xAA);
	}

	//F2 function - switches odd bits
	static BYTE F2(BYTE val)
	{
		return (val & 0xAA) | (~val & 0x55);
	}

	//G1 function - shift left rotating
	static BYTE G1(BYTE val)
	{
		//take last 3 bits, shift left 3 positions and make last 3 bits first
		return (val << 3) | ((val & 0xE0) >> 5);
	}

	//G2 function - shift right rotating
	static BYTE G2(BYTE val)
	{
		//take first 3 bits, shift right 3 positions and make first 3 bits last
		return (val >> 3) | ((val & 0x07) << 5);
	}

	//Fast swap
	static void Swap(BYTE* kk, BYTE val1, BYTE val2)
	{
		if (val1 != val2)
		{
			kk[val1] ^= (kk[val2] ^= (kk[val1] ^= kk[val2]));
		}
	}

	//Fast modulo
	static int Mod(int a, int b)
	{
		int s = b;
		while (s <= a)
		{
			s <<= 1;
		}
		int r = a;
		while (r >= b)
		{
			s >>= 1;
			if (s <= r)
			{
				r -= s;
			}
		}
		return r;
	}

	const static BYTE _sss[256];
	const static short _sarrprimes[256];

	Counter _cnt;
	BYTE _data0[256];
	BYTE _data[256];
	BYTE _ss0[256];
	BYTE _ss[256];
	BYTE _val;
	int _ssix;
	int _ix;
	int _ix1;
	int _incr;
	int _ix0;
	int _ix1_0;
	int _incr0;
	int _size;
};

#endif // __OCELOT1_H__

