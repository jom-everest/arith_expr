#ifndef HUNDR_V2_H
#define HUNDR_V2_H

#include <cstring>
#include <ctype.h>
#include <unordered_map>
#include <string>

class HUNDR_v2 {

  static const char oper_sym[];
  typedef char str30[30];

  struct Tnum 
  {
    double n;
    unsigned char op;
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
  void SA(const double d);
  void double_fa_v1();
  void double_fa_v2();
  int compose_v1();
  int compose_v2();
  char* expr(char* sss);
public:
  int total;
  std::unordered_map<double, int> map;
  int compose(long n, int t, str30* b = 0);
  int compose(const char* digits, int v);
};

//-------------------------------------------
inline int HUNDR_v2::compose(const char* digits, int v)
{
  input_len = strlen(digits);
  for (int i=0; i<input_len; i++) 
  {
    if (!isdigit(digits[i])) return 0;
    mas[0].numbers[i].n = input[i] = digits[i]- 0x30;
    mas[0].numbers[i].op = 0x01;
  }
  if (v == 1)  return compose_v1();
  
  return compose_v2();
}
//-------------------------------------------
inline int HUNDR_v2::compose(long n, int t, str30* list)
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
  }
//  return compose();
}


inline void HUNDR_v2::SA(const double d)
{
	++map[(int(d*10000+0.5))/10000];
}

//--------------------------------------------


#endif // HUNDR_V_H
