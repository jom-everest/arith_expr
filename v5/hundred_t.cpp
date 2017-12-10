#include "hundr_t.h"
#include <cstring>
#include <stdio.h>

//	++map_d[(int(d*100+0.5))/100];

//------------------------------------------------------
#define RES(a,b) map_str[expr(b)]++;
//------------------------------------------------------
#define subf1(a,b,c) t=b*c; \
	RES(a+t,"+*")\
	RES(a-t,"-*")\
	if (c) {\
		t = b/c;\
		RES(a+t,"+/")\
		RES(a-t,"-/")\
	}
//------------------------------------------------------
#define subf2(a,b,c) t = a*b;\
	RES(t*c, "**")\
	if (c) RES(t/c, "*/")\
	if (b) {\
		t = a/b;\
		RES(t*c, "/*")\
		if (c) RES(t/c, "//")\
	}
//------------------------------------------------------
#define subf3(a,b,c) t = b+c;\
	RES(a*t, "*(+)")\
	if (t) RES(a/t, "/(+)")\
	t = b-c;\
	RES(a*t, "*(-)")\
	RES(a/t, "/(-)")
//------------------------------------------------------
#define subf4(a,b,c) t=a*b;\
	RES(t+c, "*+")\
	RES(t-c, "*-")\
	if (b) {\
		t = a/b;\
		RES(t+c, "/+")\
		RES(t+c, "/-")\
	}
//------------------------------------------------------
#define subf5(a,b,c) t = a+b;\
	RES(t*c, "(+)*")\
	if (c) RES(t/c, "(+)/")\
	t = a-b;\
	RES(t*c, "(-)*")\
	if (c) RES(t/c, "(-)/")
//------------------------------------------------------
#define subf6(a,b,c) \
	RES(a+b+c, "++")\
	RES(a+b-c, "+-")\
	RES(a-b+c, "-+")\
	RES(a-b-c, "--")
//------------------------------------------------------


const char HUNDR_t::oper_sym[] = {' ','+',' ','-','*',' ',' ',' ',' ',' ',' ',' ','/',' ',' ',' ','&'};

//--------------------------------------
char* HUNDR_t::expr(char* sss)
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
    pos = mas[i].pos_brack;
    ch = oper_sym[mas[i+1].numbers[pos].op];
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
inline void HUNDR_t::triple_fa()
{
	register float a, b, c, t;
	char op_b, op_c;

	a = p_str2[0].n;
	b = p_str2[1].n;
	c = p_str2[2].n;
	op_b = p_str2[1].op;
	op_c = p_str2[2].op;

	if (p_mas->pos_brack == 2) {
		if (op_c & 0x01) {
			subf1(a,b,c);
		}
		else if (op_c & 0x04) {
			subf3(a,b,c);
		}
		else {
			subf1(a,b,c);
			subf3(a,b,c);
			if ((op_b & 0x10) && (op_c==0x30)) {
				t = b*10+c;
				RES(a+t, "+&")
				RES(a-t, "-&")
				RES(a*t, "*&")
				if (t) RES(a/t, "/&")
			}
		}
		return;
	}
	
	if (op_b & 0x01) {
		if (op_c & 0x01) {
			subf1(a,b,c);
			subf2(a,b,c);
		}
		else if (op_c & 0x04) {
			subf3(a,b,c);
			subf4(a,b,c);
		}
		else {
			subf1(a,b,c);
			subf2(a,b,c);
			subf3(a,b,c);
			subf4(a,b,c);
		}
	}
	else if (op_b & 0x04) {
		if (op_c & 0x01) {
			subf5(a,b,c);
			subf1(a,b,c);
		}
		else if (op_c & 0x04) {
			subf6(a,b,c);
			subf3(a,b,c);
		}
	  else {
			subf5(a,b,c);
			subf6(a,b,c);
			subf3(a,b,c);
			subf1(a,b,c);
	  }
	}
	else if (op_c & 0x01) {
		subf5(a,b,c);
		subf2(a,b,c);
		subf1(a,b,c);
		if (p_str2[0].op & 0x10 && op_b==0x30) {
			t = a*10+b;
			RES(t*c, "&*")
			if (c) RES(t/c, "&/")
		}
	}
	else if (op_c & 0x04) {
		subf6(a,b,c);
		subf4(a,b,c);
		subf3(a,b,c);
		if ((p_str2[0].op & 0x10) && op_b==0x30) {
			t = a*10+b;
			RES(t+c, "&+")
			RES(t-c, "&-")
		}
	}
	else {
		subf1(a,b,c);
		subf2(a,b,c);
		subf3(a,b,c);
		subf4(a,b,c);
		subf5(a,b,c);
		subf6(a,b,c);
		if (p_str2[0].op & 0x10 && op_b==0x30) {
			t = a*10+b;
			RES(t+c, "&+")
			RES(t-c, "&-")
			RES(t*c, "&*")
			if (c) RES(t/c, "&/")
		}
		if (op_c == 0x30) {
			t = b*10+c;
			RES(a+t, "+&")
			RES(a-t, "-&")
			RES(a*t, "*&")
			if (t) RES(a/t, "/&")
		}
	}
}

//------------------------------------------------------
int HUNDR_t::compose()
{
	register int pos_brack;

	max_ans_c = 1000;
	ans_c = 0;
	mas[0].pos_brack = 0;
	mas[0].ind_oper = 1;
	pos_brack = depth = 0;
	p_mas = &mas[0];
	p_str = mas[0].numbers;
	p_str2 = mas[1].numbers;

	while (true) 
	{
		int c;
		Tnum *p_a = &p_str[pos_brack];
		Tnum *p_b = &p_str2[pos_brack];

		memcpy(p_str2, p_str, sizeof(Tnum)*pos_brack);
		memcpy(&p_b[1], &p_a[2], sizeof(Tnum)*(input_len-depth-2-pos_brack));

		p_mas->ind_oper = 0;

		register float a = p_a->n;
		register float b = p_a[1].n;
		Tnum *p_res = p_mas->res;
		char op_b = p_a[1].op;

		if (op_b & 0x01) 
		{
			p_b->n = a*b;
			p_b->op = 0x04;
			if (b!=0) 
			{
				p_res->n = a/b;
				p_res->op = 0x0C;
				p_mas->res_c = 1;
			} 
			else p_mas->res_c = 0;
		}
		else if (op_b & 0x04) 
		{
			p_b->n = a+b;
			p_b->op = 0x01;
			p_res->n = a-b;
			p_res->op = 0x03;
			p_mas->res_c = 1;
		}
		else 
		{
			p_b->n = a+b;
			p_b->op = 0x01;
			p_res->n = a-b;
			p_res->op = 0x03;
			p_res[1].n = a*b;
			p_res[1].op = 0x04;
			if (b!=0) 
			{
				p_res[2].n = a/b;
				p_res[2].op = 0x0C;
				c = 3;
			} 
			else c = 2;
			if ((p_a->op&0x10) && (op_b==0x30)) 
			{
				p_res[c].n = a*10+b;
				p_res[c].op = 0x10;

				c++;
			}
			p_mas->res_c = c;
		}

		if (input_len-depth == 4) 
		{
_labl1:
			triple_fa();
			if (p_mas->ind_oper == p_mas->res_c) 
			{
_labl2:
				if (++(p_mas->pos_brack) == input_len-1-depth) 
				{
		      if (--depth >= 0) 
					{
						p_mas = &mas[depth];
 	  				pos_brack = p_mas->pos_brack;
						if (p_mas->ind_oper == p_mas->res_c) 
						{
							p_str2 = p_str;
							p_str = p_mas->numbers;
							goto _labl2;
						}
						p_str[p_mas->pos_brack] = p_mas->res[p_mas->ind_oper];
						p_mas->ind_oper++;
						p_mas = &mas[++depth];
						pos_brack = p_mas->pos_brack = pos_brack>1 ? pos_brack-1 : 0;
					}
					else break; // выход из цикла, завершение функции
				}
		  	else 
					pos_brack = p_mas->pos_brack;
			}
			else {
				p_str2[pos_brack] = p_mas->res[p_mas->ind_oper];
				p_mas->ind_oper++;
				goto _labl1;
			}
		}
		else {
			depth++;
			p_str = p_str2;
			p_mas = &mas[depth];
			p_str2 = p_mas[1].numbers;
			pos_brack = p_mas->pos_brack = pos_brack>1 ? pos_brack-1 : 0;
		}

	} // while{...}


	return ans_c;
}

//-----------------------------------------------------
