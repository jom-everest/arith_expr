#ifndef HUNDR_CL_H
#define HUNDR_CL_H

#include <cstring>
#include <ctype.h>
#include <unordered_map>
#include <string>

class HUNDR_cl {

  static const char oper_sym[];
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
  void SA_v1(const char* str);
  void SA_v2(const double d);
  void double_fa_v1();
  void double_fa_v2();
  int compose_v1();
  int compose_v2();
  char* expr(char* sss);
public:
  int total;
  std::unordered_map<std::string, int> map_v1;
  std::unordered_map<double, int> map_v2;
  int compose(long n, int t, str30* b = 0);
  int compose_v1(const char* digits);
  int compose_v2(const char* digits);
};

//-------------------------------------------
inline int HUNDR_cl::compose_v1(const char* digits)
{
  input_len = strlen(digits);
  for (int i=0; i<input_len; i++) 
  {
    if (!isdigit(digits[i])) return 0;
    mas[0].numbers[i].n = input[i] = digits[i]- 0x30;
    mas[0].numbers[i].op = 0x01;
  }
  return compose_v1();
}
//-------------------------------------------
inline int HUNDR_cl::compose_v2(const char* digits)
{
  input_len = strlen(digits);
  for (int i=0; i<input_len; i++) 
  {
    if (!isdigit(digits[i])) return 0;
    mas[0].numbers[i].n = input[i] = digits[i]- 0x30;
    mas[0].numbers[i].op = 0x01;
  }
  return compose_v2();
}
//-------------------------------------------
inline void HUNDR_cl::SA_v1(const char* str)
{
	++map_v1[str];
}

//--------------------------------------------
inline void HUNDR_cl::SA_v2(const double d)
{
	++map_v2[(int(d*100+0.5))/100];
}

//--------------------------------------------


#endif // HUNDR_V_H
