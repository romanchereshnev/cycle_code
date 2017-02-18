/*
 * Tools.cpp
 *
 *  Created on: 23.04.2013
 *      Author: roma
 */

#include "Tools.h"
#include <iostream>
#include <cstdio>
using namespace std;

Word div(Word num, Word den, char * ch)
{
	if (ch)
	{
		ch[0] = '\0';
		strcat(ch, "Деление:\n");
	}
	char tmp[255];
	int brd = den.max() - 1;
	if(num.max() < den.max())
		return num;
	if(num.max() == den.max())
	{
		if(ch)
		{
			strcat(ch, num.to_char());
			strcat(ch, "\n");

			strcat(ch, den.to_char());
			strcat(ch, "\n");
		}
		num += den;
		if(ch)
		{
			strcat(ch, "Остаток:\n");
			strcat(ch, num.to_char());
		}

		return num ;
	}
	den.leftShift(num.max() - den.max());
	int i;
	for (i = den.max(); i > brd; i--)
	{
		if (num.max() == den.max())
		{
			if (ch)
			{
				sprintf(tmp,"%s\n", num.to_char());
				front_zero(tmp);//обработка num
				strcat(ch, tmp);//копирование в конец

				sprintf(tmp,"%s\n", den.to_char());
				back_zero(tmp);
				front_zero(tmp);
				//обработка den
				strcat(ch, tmp);//копирование в конец
			}
			num += den;
		}
		den >>=1;
	}

	if (ch)
	{
		sprintf(tmp,"%s\n", num.to_char());
		front_zero(tmp);//обработка num
		strcat(ch, tmp);
	}
	return num;
}




Word * control_mtrx(int len, const Word & Px, char * str)
{
	len--;
	Word tmp(len);
	tmp.reset();
	tmp.set(0);
	string stmp;
	Word * mtrx = new Word[len];
	for (int i = 0; i < len; i++)
	{
		mtrx[i] = div(tmp, Px, NULL);
		stmp = stmp + mtrx[i].to_char() + '\n';
		tmp <<= 1;
	}
	strcpy(str, stmp.c_str());
	return mtrx;
}

char * word_codding(Word & w, const Word & Px, char * ch)
{
	w += div(w, Px, ch);
	return ch;
}

void error_correct(const Word * mtrx, Word & w, const Word & Px, char * ch)
{
	//Поиск ошибки

	Word e;
	Word tmp(w.len());
	tmp.reset();
	tmp[0] = true;
	int i = 0;

	e = div(w, Px, ch);

	while (e != mtrx[i++])
	{
		tmp <<= 1;
	}

	strcat(ch, "Вектор ошибок:\n");

	strcat(ch, tmp.to_char());
	strcat(ch, "\n\n");

	strcat(ch, w.to_char());
	strcat(ch, "\n");

	strcat(ch, tmp.to_char());
	strcat(ch, "\n");
	w += tmp;

	strcat(ch, w.to_char());
	strcat(ch, "\n");

	strcat(ch, "\nИсправленное слово:\n");
	strcat(ch, w.to_char());
}

char * front_zero(char * ch)
{
	int i = -1;
	int j = 0;
	char tmp[255];
	tmp[0] = '\0';
	strcpy(tmp, ch);
	while ( tmp[++i] != '\0' && tmp[i] != '1')
	{
		ch[j++] = ' ';
		ch[j++] = ' ';
		ch[j++] = ' ';
	}
	ch[j] = '\0';
	strcat(ch, tmp + i);

	return ch;
}

char * back_zero(char *ch)
{
	int i = strlen(ch) - 1;
	while (--i > 0 && ch[i] == '0')
		ch[i] = ' ';
	return ch;
}

bool check_poly(char * s)
{
	char * tmp = new char[strlen(s)];
	bool flag = false;
	int i = -1;
	int j = 0;
	if(s[0] == '\0')
		return false;
	while (s[++i] != '\0')
	{
		if ( s[i] == '1')
		{
			tmp[j++] = s[i];
			flag = true;
		}
		else if(s[i] == '0')
		{
			if (flag)
				tmp[j++] = s[i];
		}
		else
		{
			delete [] tmp;
			return false;
		}
	}
	tmp[j] = '\0';
	strcpy(s,tmp);
	delete [] tmp;
	return true;
}

int find_k(int n)
{
	int k = 0;

	while(++k < 10)
	{
		if (pow(2.0, k) >= (k + n))
			break;
	}
	if (k == 10)
		k = 0;
	return k;
}

