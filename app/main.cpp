#include "class/body/Body.cpp"
#include "class/nbody/NBody.cpp"
#include "class/error/error.cpp"
#include "class/reader/reader.cpp"
#include "class/gnuplot/gnuplot.hpp"
//#include "class/graphics/graphics.cpp"

#include <getopt.h>
#include <string>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <omp.h>

using namespace std;

inline void wait() {
    string line;
    cout << "Enter to continue..." << endl;
    getline(cin, line);
}

void resetFile(const string &filename) {
  ofstream ofs;
  ofs.open(filename,ios::out | ios::trunc);
  if (ofs) {
    ofs << "";
  }
  ofs.close();
}

/*
 * Author : Lucas Pauzies
 * Date : 14/03/2018
 * Input : None
 * Output : Help for the program
 */
void displayHelp() {
  string help = "";
  help += "\n#========== N-Body Problem Solver Help documentation ==========#\n\n";
  help += "-h or --help : display help of N-Body Problem Solver\n";
  help += "-f or --file : (compulsory) using the program with this dataset path\n";
  help += "-b or --benchmark : Use if you want to execute the benchmark\n";
  help += "-n or --nbit : (optionnal) if given, execute the program with this number of iterations else do 2000 iterations\n";
  help += "-s or --socket : (optionnal) if given, execute the program with socket (cesga: client, serveur extern python:server, pc:client)\n";
  help += "-p or --port : (optionnal) if given, execute the program on the port specified else 15556\n";
  help += "-a or --adresse : (optionnal) if given, execute the program on the adresse specified else localhost";
  help += "\n\n#========== N-Body Problem Solver Help documentation ==========#\n";
  cout << help << endl;
}

/*
 * Author : Lucas Pauzies
 * Date : 14/03/2018
 * Input : path_input : input filename / nb_it : number of iterations
 * Output : Gnuplot represetation of bodies movement
 */
void execProg(string path_input,int nb_it) {
    Reader reader(path_input);
    NBody nbody = NBody(reader.readBodies(), false, "", 0);
    nbody.exportGNUPLOT2D("data/data.gnuplot");
    for (int i = 0; i < nb_it; i++) {
        nbody.updateNBody();
        nbody.exportGNUPLOT2D("data/data.gnuplot");
    }
    Gnuplot plot;
    plot("plot \"data/data.gnuplot\"");
    wait();
    resetFile("data/data.gnuplot");
}

/*
 * Author : Laurine Sorel
 * Data : 26/03/2018
 * Input : path_input : input filename / nb_it : number of iterations
 * Output : None
 */
void execProgSocket(string path_input, int nb_it, string adresse, int port) {
    Reader reader(path_input);
    NBody nbody = NBody(reader.readBodies(), true, adresse, port);
    for(int i = 0; i < nb_it; i++) {
        nbody.updateNBody();
    }
}

void execBenchmark(string path_input,int nb_it) {
    Reader reader(path_input);
    NBody nbody = NBody(reader.readBodies(), false, "", 0);
    for (int i = 0; i < nb_it; i++) {
        nbody.updateNBody();
    }
}


/*
 * Author : Lucas Pauzies
 * Date : 14/03/2018
 * Input : argc : number of arguments / argv : array of arguments
 * Output : decision depending on the command syntax
 */

void decisionMaker(int argc, char* argv[]) {
  //Setup default values
  bool display_help = false;
  bool has_arg_error = false;
  bool launch_socket = false;
  bool launch_prog = false;
  bool bench = false;
  string dataset_path = " ";
  int nb_it = 2000;
  int port = 15556;
  string adresse = "127.0.0.1";
  int arguments = 0;
  //Setup parameters
  const char* const short_opts = "hsf:n:p:a:b";
  const option long_opts[] = {
    {"file",required_argument,nullptr,'f'},
    {"nbit",optional_argument,nullptr,'n'},
    {"socket",no_argument,nullptr,'s'},
    {"help",no_argument,nullptr,'h'},
    {"port",optional_argument,nullptr,'p'},
    {"adresse",optional_argument,nullptr,'a'},
    {"benchmark",no_argument,nullptr,'b'},
    {nullptr,0,nullptr,0}
  };
  while (arguments != -1) {
    //get each arguments
    arguments = getopt_long(argc, argv, short_opts, long_opts, nullptr);

    switch (arguments) {
      case 'h':
        display_help = true;
        break;
      case 'f':
        dataset_path = string(optarg);
        launch_prog = true;
        break;
      case 'n':
        nb_it = stoi(optarg);
        break;
      case 's':
        launch_socket = true;
        break;
      case 'p':
        port = stoi(optarg);
        break;
      case 'a':
        adresse = string(optarg);
        break;
      case 'b':
        bench = true;
        break;
      case '?':
        has_arg_error = true;
        break;
      default:
        break;
    }
  }
  if (display_help && !has_arg_error) {
    displayHelp();
  } else if (has_arg_error) {
    Error::error("main.cpp","Cannot use these options, please retry or use the option '-h'");
  } else if (launch_socket && launch_prog) {
    execProgSocket(dataset_path, nb_it, adresse, port);
  } else if (launch_prog && !bench) {
    execProg(dataset_path,nb_it);
  } else if (bench) {
    execBenchmark(dataset_path,nb_it);
  } else {
    displayHelp();
  }
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    decisionMaker(argc, argv);

    // Partie graphique
    /*Graphics fenetre("Nbody", 800, 600);
    fenetre.initFenetre();
    fenetre.initGL();
    fenetre.fenetreUpDate(nbody);*/
    return 0;
}
