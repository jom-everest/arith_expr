#ifndef HUNDR_H
#define HUNDR_H

#include <cstring>
#include <ctype.h>

class HUNDR {

  static const char oper_sym[17];
  typedef char str30[30];

  struct Tnum 
  {
    float n;
    unsigned char op;
  };

  struct TMas
  {
    int ind_oper;
    int pos_brack;
    Tnum numbers[10];
  	Tnum res[4];
	int res_c;
  };

  int ans_c, max_ans_c;
  str30 *ans_list;
  int target;
  char depth;
  char input[10];
  int input_len;
  Tnum *p_str, *p_str2;
  TMas *p_mas;
  TMas mas[10];
  char answ[30];
  void double_fa();
  char* expr(char* );
  int compose();
public:
  int total;
  int compose(long n, int t, str30* b = 0);
  int compose(const char* digits, int t, str30* b = 0);
};

//-------------------------------------------
inline int HUNDR::compose(const char* digits, int t, str30* list)
{
  target = t;
  ans_list = list;

  input_len = strlen(digits);
  for (int i=0; i<input_len; i++) 
  {
    if (!isdigit(digits[i])) return 0;
    mas[0].numbers[i].n = input[i] = digits[i]- 0x30;
    mas[0].numbers[i].op = 0x30;
  }
  return compose();
}
//-------------------------------------------
inline int HUNDR::compose(long n, int t, str30* list)
{
  if (n < 1) return 0;

  target = t;
  ans_list = list;

  int a, b;
  int m[10];
  input_len = 0;
  do 
  {
    a = n%10;
    b = n/10;
    m[input_len++] = a;
  }  while (b);
  
  for (int i=0; 0<input_len; i--) 
  {
    mas[0].numbers[i].n = input[i] = m[input_len-i-1];
    mas[0].numbers[i].op = 0x30;
  }
  return compose();
}

//--------------------------------------------


#endif // HUNDR_H
