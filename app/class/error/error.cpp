#include "error.hpp"

void Error::error(const string &filename, const string &error) {
  ofstream file;
  file.open("log/error.log",ios::app);
  if (file) {
    //getting current_date
    time_t current_date;
    time(&current_date);
    string current = ctime(&current_date);
    //delete last character
    current.pop_back();
    //display in the shell
    cerr << error << endl;
    string output_error = "";
    output_error.append("[");
    output_error.append(current);
    output_error.append("] : ");
    output_error.append(error);
    output_error.append(" (");
    output_error.append(filename);
    output_error.append(")");
    output_error.append("\n");
    //write it in the log file
    file << output_error;
    file.close();
  }
}
