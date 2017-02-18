
#include <cstring>
#include <iostream>
#include "Word.h"

/**********************************************************
********************CONSRACTORS************************
**********************************************************/

Word::Word(const char * s, int K)
{
	str = NULL;
    n = strlen(s);
    k = K;
    if(k > n)
        k = n;
    int i, j;
    bits = new bool[n];
    for (i = 0, j = n -1; i < n; i++, j--)
    {
        if(s[j] == '1')
            bits[i] = true;
        else
            bits[i] = false;
    }
}

Word::Word(const Word & w)
{

	str = NULL;
    n = w.n;
    k = w.k;
    int i;
    bits = new bool[n];
    for (i = 0; i < n; i++)
    {
        bits[i] = w.bits[i];
    }
}

Word::Word(int N, int K)
{
	str = NULL;
    n = N;
    k = K;
    if(k > n)
        k = n;
    bits = new bool[n];
}

Word::Word()
{
	str = NULL;
    n = 0;
    k = 0;
    bits = NULL;
}

Word::~Word()
{
    delete [] bits;
    delete [] str;
}

/**********************************************************
********************OPERATOR    OF    COMPARING************************
**********************************************************/

bool Word::operator>(const Word & w) const
{
    const Word * big, *small;
    bool tmp;
    if (n > w.n)
    {
        big = this;
        small = &w;
        tmp = true;
    }
    else
    {
        small = this;
        big = &w;
        tmp = false;
    }
    int i;

    for ( i = big->n - 1; i > small->n - 1; i--)
    {
        if(big->bits[i])
            return tmp;
    }
    for (; i >= 0; i--)
    {
        if (bits[i] && !w.bits[i])
            return true;
        else if (!bits[i] && w.bits[i])
            return false;
    }
    return false;
}

bool Word::operator>=(const Word & w) const
{
    const Word * big, *small;
    bool tmp;
    if (n > w.n)
    {
        big = this;
        small = &w;
        tmp = true;
    }
    else
    {
        small = this;
        big = &w;
        tmp = false;
    }
    int i;
    for ( i = big->n - 1; i > small->n - 1; i--)
    {
        if(big->bits[i])
            return tmp;
    }

    for (; i >= 0; i--)
    {
        if (bits[i] && !w.bits[i])
            return true;
        else if (!bits[i] && w.bits[i])
            return false;
    }
    return true;
}

bool Word::operator==(const Word & w) const
{
    const Word * big, *small;
    if (n > w.n)
    {
        big = this;
        small = &w;
    }
    else
    {
        small = this;
        big = &w;
    }
    int i;
    for ( i = big->n - 1; i < small->n - 1; i--)
    {
        if(big->bits[i])
            return false;
    }
    for (; i >= 0; i--)
        if(bits[i] != w.bits[i])
            return false;
    return true;
}

bool Word::operator<=(const Word & w) const
{
    return w >= *this;
}

bool Word::operator<(const Word & w) const
{
    return w > *this;
}

/**********************************************************
********************ARITHMETIC AND SHIFT OPERATORS************************
**********************************************************/

Word Word::operator+(const Word & w) const
{
    const Word * big, * small;
    if ( n > w.n)
    {
        big = this;
        small = &w;
    }
    else
    {
        small = this;
        big = &w;
    }

    Word tmp = *big;;

    for (int i = 0; i < small->n; i++)
    {
        tmp.bits[i] = bits[i] ^ w.bits[i];
    }
    return tmp;
}

Word & Word::operator+=(const Word & w)
{
    return (*this = (*this + w));
}

Word & Word::operator=(const Word & w)
{
	delete [] bits;
    n = w.n;
    k = w.k;
    bits = new bool[n];
    for (int i = 0; i < n; i++)
        bits[i] = w.bits[i];
    return *this;
}


Word Word::operator>>(int i) const
{
	 i %= n;
	 Word w(n);
	 for(int j = 0; j < n; j++)
		 w.bits[j] = bits[(j +  i) % n];
	 return w;
}

Word & Word::operator>>=(int i)
{
    return (*this = (*this >> i));
}

Word Word::operator<<(int i) const
{
	i %= n;
	int tmp = n-i;
	Word w(n);
	for(int j = 0; j < n; j++, tmp++)
	    w.bits[j] = bits[tmp % n];
	return w;
}

Word & Word::operator<<=(int i)
{
    return (*this = (*this << i));
}

Word & Word::leftShift(int i)
{
    int j;
    bool * tmp = bits;
    n = n + i;
    bits = new bool[n];
    for (j = 0; j < i; j++)
        bits[j] = false;

    for (; j < n; j++)
        bits[j] = tmp[j - i];
    delete [] tmp;
    return *this;
}

Word & Word::rightShift(int i)
{
    int j;
    bool * tmp = bits;
    n = n - i;
    if (n <= 0)
    {
    	delete [] bits;
    	bits = NULL;
    	n = 0;
    	k = 0;
    	return * this;
    }
    bits = new bool[n];
    for ( j = 0; j < n; j++)
        bits[j] = tmp[j + i];

    delete [] tmp;
    return *this;
}

/************************************************

*********************OTHERS**********************

************************************************/

bool Word::operator[](int i) const
{
    return bits[i];
}

bool & Word::operator[](int i)
{
    return bits[i];
}


int Word::weight() const
{
    int i, cnt = 0;
    for (i = 0; i < n; i++)
        cnt += bits[i];
    return cnt;
}



bool Word::set(int i)
{
    return (bits[i] = true);
}


bool Word::reset(int i)
{
    return !(bits[i] = false);
}



void Word::set()
{
    for ( int i = 0; i < n; i++)
        bits[i] = true;
}



void Word::reset()
{
    for ( int i = 0; i < n; i++)
        bits[i] = false;
}

void Word::print(bool s) const
{
    if (s)
    {
        std::cout << "n = "  << n << "\n";
        std::cout << "k = "  << k << "\n";
    }
    if (n > 0)
    {
    	for (int i = n - 1; i >=0; i--)
    	{
    		std::cout << ( bits[i] ? '1' : '0');
    	}
    }
    std::cout << std::endl;
}

int Word::max() const
{
	int i;
	for ( i = n -1; i >=0; i--)
		if(bits[i])
			return i;
	return -1;
}


char * Word::to_char()
{
	delete [] str;
	char * str = new char[n + 1];
	for (int i = 0; i < n; i++)
	{
		if (bits[i])
			str[n - i -1] = '1';
		else
			str[n - i - 1] = '0';
	}
	str[n] = '\0';
	return str;
}

