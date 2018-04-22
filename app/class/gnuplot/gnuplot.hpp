#ifndef GNUPLOT_H_
#define GNUPLOT_H_

#include <string>
#include <iostream>
#include "../error/error.hpp"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

/*
 * Author : Lucas Pauzies
 * Date : 07/03/2018
 * Gnuplot class that represent interface between C++ and gnuplot
 */

class Gnuplot {
  public:
    Gnuplot() ;
    ~Gnuplot();
    void operator ()(const string & command);
  protected:
    FILE *gnuplotpipe;
};

Gnuplot::Gnuplot() {
  //Open the pipe in write mode
  gnuplotpipe = popen("gnuplot","w");
  if (!gnuplotpipe) {
    Error::error("gnuplot.hpp","Gnuplot not found !");
  }
}

Gnuplot::~Gnuplot() {
  pclose(gnuplotpipe);
}

/*
 * Author : Lucas Pauzies
 * Date : 07/03/2018
 * Input : None
 * Output : overloaded operator to write commands for gnuplot 
 */
void Gnuplot::operator()(const string & command) {
  fprintf(gnuplotpipe,"%s\n",command.c_str());
  fflush(gnuplotpipe);
};

#endif
