#include "painter.h"

int main() {
  std::cerr<<"Creation"<<std::endl;
  Painter pntr;
  //int res;
  //std::cin>>res;
  std::cerr<<"Initialization"<<"\n";
  pntr.init(701,701);
  std::cerr<<"Start"<<"\n";
  pntr.start();
  return 0;
}
