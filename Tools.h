/*
 * Tools.h
 *
 *  Created on: 23.04.2013
 *      Author: roma
 */

#ifndef TOOLS_H_
#define TOOLS_H_

#include "Word.h"
#include <cmath>
#include <cstring>

Word div(Word num, Word den, char * ch);
Word * control_mtrx(int len, const Word & Px, char * str);
char * word_codding(Word & w, const Word & Px, char * ch);
void error_correct(const Word * mtrx, Word & w,const Word & Px, char *ch);

char * back_zero(char *ch);
char * front_zero(char *ch);

bool check_poly(char * s);
int find_k(int n);
#endif /* TOOLS_H_ */
