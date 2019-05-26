#include <math.h>
#include <cmath>
#include <iostream>
#include <random>
using namespace std;

int main(void) {
  // default_random_engine e;
  // uniform_real_distribution<float> u(-100, 100);  //随机数
  float sample_time = 10.0;
  float sample_freq = 1000;
  unsigned int origin_signal_freq = 1;
  float dt = 1 / sample_freq;
  double t = 0;
  unsigned int count = sample_time / dt;
  double output[count], input[count] = {};
  cout << "sample_time = " << sample_time << " seconds " << endl;
  cout << "sample_freq = " << sample_freq << " hz " << endl;
  cout << "dt = " << dt << " seconds " << endl;

  for (int i = 0; i < count; i++) {
    input[i] = 3*sin(2*M_PI*origin_signal_freq*t) + sin(2 * M_PI * 10 * t) + sin(2 * M_PI * 30 * t) +
               sin(2 * M_PI * 50 * t) + sin(2 * M_PI * 100 * t) +
               sin(2 * M_PI * 200 * t) + sin(2 * M_PI * 300 * t) +
               sin(2 * M_PI * 400 * t) + sin(2 * M_PI * 500 * t);
    // input[i] = 3000+u(e);
    t = t + dt;
  }
  double lpf0, lpf1 = {};
  double lpf_factor =
      (1 / (1 + 1 / (2.0 * M_PI * (1 / sample_freq) * origin_signal_freq)));
//   lpf_factor = 0.05;
  cout << "lpf_factor = " << lpf_factor << endl;
  for (int i = 0; i < count; i++) {
    lpf1 = lpf0 + (input[i] - lpf0) * lpf_factor;
    lpf0 = lpf1;
    output[i] = lpf1;
  }

  //记录数据
  FILE *fp;
  if ((fp = fopen("a1.txt", "wb")) == NULL) {
    printf("cant open the file");
    exit(0);
  }
  char inputs[10] = "input";

  fprintf(fp, "%s \n", inputs);
  for (int i = 0; i < count; i++) {
    fprintf(fp, "%f \n", input[i]);
  }
  fclose(fp);

  FILE *fp1;
  if ((fp1 = fopen("a2.txt", "wb")) == NULL) {
    printf("cant open the file");
    exit(0);
  }
  char outputs[10] = "output";
  fprintf(fp1, "%s \n", outputs);
  for (int i = 0; i < count; i++) {
    fprintf(fp1, "%f \n", output[i]);
  }
  fclose(fp);

  system("pause");
  return 0;
}
