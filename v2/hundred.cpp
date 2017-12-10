#include "hundr.h"
#include <cstring>
#include <stdio.h>

const char HUNDR::oper_sym[] = {'+', '-', '*', '/', '&'};

//--------------------------------------
char* HUNDR::expr(char* sss)
{
char ch;
char left, right;
int pos, i, ind, i1, c_ind;
char ss[4], str[30];
int ss_len;
int answ_len;

  strcpy(answ, sss);
  answ_len = strlen(answ);
  for (i=depth; i>-1; i--) {
    ch = oper_sym[mas[i].ind_oper-2];
    pos = mas[i].pos_brack;
    ind = i1 = -1;
    do {
      ind++;
      c_ind = ind;
	  if (answ[ind] == '(' || (ind && answ[ind-1] == ')'))
        continue;
      else if (answ[ind] == ')') {
        if (answ[ind-1] != ')') i1++;
        ind++;
      }
      else
        i1++;
    } while (i1 != pos);
    left = c_ind ? answ[c_ind-1] : 0;
    right = answ_len!=c_ind ? answ[c_ind] : 0;
    if ((left=='/' && ch!='&') || ((ch=='+' || ch=='-') && (left=='*' || left=='/' || right=='*' || right=='/'))) {
      ss[0] = '(';
      ss[1] = ch;
      ss[2] = ')';
      ss_len = 3;
    }
    else {
      ss[0] = ch;
      ss_len = 1;
    }
    memcpy(str, answ, c_ind);
    memcpy(str+c_ind, ss, ss_len);
    memcpy(str+c_ind+ss_len, answ+c_ind, answ_len-c_ind+1);
    strcpy(answ, str);
    answ_len = strlen(answ);
  }
  ind = i1 = 0;
  for (i=0; i<answ_len+1; i++) {
    if (str[i]!='(' && (!i || str[i-1]!=')')) {
      answ[i1++] = input[ind++]+0x30;
    }
    if (str[i] != '&') answ[i1++] = str[i];
  }
  return answ;
}

//------------------------------------------------------
inline void HUNDR::double_fa()
{
register float a, b;

  a = p_str2[0].n;
  b = p_str2[1].n;

  if (p_str2[1].op == 0x04) {
	total += 2;
    if (a*b == target) {if (ans_c < max_ans_c) strcpy(ans_list[ans_c], expr("*")); ans_c++;}
    if (b!=0 && a/b==target) {if (ans_c < max_ans_c) strcpy(ans_list[ans_c], expr("/")); ans_c++;}
  }
  else if (p_str2[1].op == 0x06) {
    total += 2;
    if (a+b == target) {if (ans_c < max_ans_c) strcpy(ans_list[ans_c], expr("+")); ans_c++;}
    if (a-b == target) {if (ans_c < max_ans_c) strcpy(ans_list[ans_c], expr("-")); ans_c++;}
  }
  else {
    total += 4;
    if (a*b == target) {if (ans_c < max_ans_c) strcpy(ans_list[ans_c], expr("*")); ans_c++;}
    if (b!=0 && a/b==target) {if (ans_c < max_ans_c) strcpy(ans_list[ans_c], expr("/")); ans_c++;}
    if (a+b == target) {if (ans_c < max_ans_c) strcpy(ans_list[ans_c], expr("+")); ans_c++;}
    if (a-b == target) {if (ans_c < max_ans_c) strcpy(ans_list[ans_c], expr("-")); ans_c++;}
  }
}

//------------------------------------------------------
int HUNDR::compose()
{
	int pos_brack;

	total = 0;
	max_ans_c = 1000;
	ans_c = 0;
	mas[0].pos_brack = 0;
	mas[0].ind_oper = 1;
	pos_brack = depth = 0;
	p_mas = &mas[0];
	p_str = mas[0].numbers;
	p_str2 = mas[1].numbers;
	for (int i=1; i<input_len-1; i++) p_str2[i] = p_str[i+1];

	while (true) 
	{
		switch (p_mas->ind_oper)
		{
		case 1:
			memcpy(p_str2, p_str, sizeof(Tnum)*pos_brack);
			memcpy(&p_str2[pos_brack+1], &p_str[pos_brack+2], sizeof(Tnum)*(input_len-depth-2-pos_brack));
			if (p_str[pos_brack+1].op == 0x04) 
			{
				p_mas->ind_oper=3; 
				goto labl1;
			}
			p_str2[pos_brack].n = p_str[pos_brack].n+p_str[pos_brack+1].n;
			p_str2[pos_brack].op = 0x04;
			break;

		case 2:
			p_str2[pos_brack].n = p_str[pos_brack].n-p_str[pos_brack+1].n;
			p_str2[pos_brack].op = 0x04;
			break;

		case 3:
			if (p_str[pos_brack+1].op == 0x06) goto labl2;
labl1:
			p_str2[pos_brack].n = p_str[pos_brack].n*p_str[pos_brack+1].n;
			//        p_str2[pos_brack].op = p_str[pos_brack].op&p_str[pos_brack+1].op&0x09;
			p_str2[pos_brack].op = 0x06;
			break;

		case 4:
			if (p_str[pos_brack+1].n) {
				p_str2[pos_brack].n = p_str[pos_brack].n/p_str[pos_brack+1].n;
				p_str2[pos_brack].op = 0x06;
				break;
			};
			p_mas->ind_oper++;  // сразу переход на case 5


		case 5:
			if ((p_str[pos_brack].op&0x01) && (p_str[pos_brack+1].op==0x01)) {
				p_str2[pos_brack].n = p_str[pos_brack].n*10+p_str[pos_brack+1].n;
				p_str2[pos_brack].op = 0x03;
				break;
			}

labl2:
			p_mas->ind_oper = 6;  // новая строка чмсел не сформирована
		}
		// Операция произведена успешно - Формирование нового ряда чисел
		if (p_mas->ind_oper < 6)
		{
			p_mas->ind_oper++;
			if (input_len-depth == 3) 
			{
				double_fa();
			}
			else 
			{
				depth++;
				p_str = p_str2;
				p_mas = &mas[depth];
				p_str2 = mas[depth+1].numbers;
				p_mas->ind_oper = 1;
				//		pos_brack = p_mas->pos_brack = 0;
				//		for (int i=1; i<input_len-depth-1; i++) p_str2[i] = p_str[i+1];
				pos_brack = p_mas->pos_brack = pos_brack>1 ? pos_brack-1 : 0;
				continue;
			}
		}
		else {
			//    if (p_mas->ind_oper > 5) {
			p_mas->ind_oper = 1;
			if (++(p_mas->pos_brack) == input_len-1-depth) {
				if (--depth >= 0) {
					p_mas = &mas[depth];
					p_str2 = p_str;
					p_str = mas[depth].numbers;
					pos_brack = p_mas->pos_brack;
				}
				else break;
			}
			else 
				pos_brack = p_mas->pos_brack;
		}
	} // while{...}

	return ans_c;
}

//-----------------------------------------------------
