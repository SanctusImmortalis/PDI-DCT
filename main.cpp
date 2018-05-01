#include "include/EigenLab.h"

int main(){
  EigenLab::Parser<Eigen::MatrixXd> parserXd;
  EigenLab::Value<Eigen::MatrixXd> resultXd;
  std::string expr;

  expr = "[[1,2];[3,4]]";
  resultXd = parserXd.eval(expr);
  int i = 0;
  return 0;
}
