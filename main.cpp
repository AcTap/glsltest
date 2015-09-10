#include "painter.h"

int main() {
  std::cerr<<"Creation"<<std::endl;
  Painter pntr;
  std::cerr<<"Initialization"<<"\n";
  pntr.init(600,600);
  std::cerr<<"Start"<<"\n";
  pntr.start();
  return 0;
}
