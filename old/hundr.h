#ifndef HUNDR_H
#define HUNDR_H

#include <cstring>
#include <ctype.h>

class HUNDR {

  static const char oper_sym[];
  typedef char str30[30];

  struct Tnum 
  {
    float n;
    unsigned char op;
	unsigned char rk;
  };

  struct TMas
  {
    int ind_oper;
    int pos_brack;
    int n;
    Tnum numbers[10];
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
  bool SC(double t, const char* s);
  bool triple();
  bool triple_new();
  void double_fa();
  void triple_fa();
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
    mas[0].numbers[i].op = 0x01;
	mas[0].numbers[i].rk = 0;
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
    mas[0].numbers[i].op = 0x01;
	mas[0].numbers[i].rk = 0;
  }
  return compose();
}

//-------------------------------------------
inline bool HUNDR::SC(double t, const char* s)
{
//  strcpy(answ, s);
//  exprn();

//fprintf(stderr, "%s = %f\n", answ, t);
  return false;
}

//--------------------------------------------


#endif // HUNDR_H
