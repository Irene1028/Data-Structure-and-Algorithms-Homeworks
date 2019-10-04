#include <stdio.h>
#include <stdlib.h>

struct retire_info_tag {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct retire_info_tag retire_info_t;

double calculate_balance(int startAge, double initial, retire_info_t s) {
  //double balance = initial;
  for (int i = 0; i < s.months; i++) {
    printf(
        "Age %3d month %2d you have $%.2lf\n", (startAge + i) / 12, (startAge + i) % 12, initial);
    initial = initial + (double)s.contribution + (double)s.rate_of_return * initial;
  }
  return initial;
}
void retirement(int startAge, double initial, retire_info_t working, retire_info_t retired) {
  //double balance = initial;
  //while working
  initial = calculate_balance(startAge, initial, working);
  //after retired
  initial = calculate_balance(startAge + working.months, initial, retired);
}

int main() {
  retire_info_t working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;  //*//
  retire_info_t retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;  //0.01 / 12;  //*//
  int startAge = 327;                  //months(27 years, 3 months)
  double savings = 21345;
  retirement(startAge, savings, working, retired);
  return 0;
}
