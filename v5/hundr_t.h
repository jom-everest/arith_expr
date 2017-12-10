#ifndef HUNDR_T_H
#define HUNDR_T_H

#include <cstring>
#include <ctype.h>
#include <unordered_map>
#include <string>

class HUNDR_t {

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
	void triple_fa();
  char* expr(char* );
  int compose();

public:
  std::unordered_map<std::string, int> map_str;
  std::unordered_map<double, int> map_d;
  int compose(const char* digits);
};

//-------------------------------------------
inline int HUNDR_t::compose(const char* digits)
{
  input_len = strlen(digits);
  for (int i=0; i<input_len; i++) 
  {
    if (!isdigit(digits[i])) return 0;
    mas[0].numbers[i].n = input[i] = digits[i]- 0x30;
    mas[0].numbers[i].op = 0x30;
  }
  return compose();
}

//--------------------------------------------




#endif // HUNDR_H
