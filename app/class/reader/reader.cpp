#include "reader.hpp"

Reader::Reader(const string &filepath): filepath {filepath} {};

Reader::~Reader() {};

const string Reader::getFilePath() const {
  return filepath;
}

/* ===== CSV ===== */

/*
 * Author : Lucas Pauzies
 * Date : 07/03/2018
 * Input : None
 * Output : Body vector to initialize NBody object using data from CSV file named "filepath" (Reader attribute)
 */

vector<Body> Reader::readCSV() const {
  vector<Body> bodies;
  const string filepath = getFilePath();
  ifstream file(filepath);
  if (file) {
      Body body;
      while (!file.eof()) {
          //Using overloaded operator ">>"
          file >> body;
          if (!file.fail())
              bodies.push_back(body);
      }
  } else {
      Error::error("reader.cpp","Open file failed for CSV reading");
  }
  file.close();
  return bodies;
}

/* ===== JSON ===== */

/*
 * Author : Lucas Pauzies
 * Date : 07/03/2018
 * Input : s, string object / delimiter, char that represent the delimiter
 * Output : string vector of parts of string s where they are separated by delimiter
 */

vector<string> split(string &s, const char &delimiter) {
  vector<string> res;
  int cpt = 0;
  for (unsigned int i = 0; i < s.length(); i++) {
    if (s[i] == delimiter || i == s.length()-1) {
      res.push_back(s.substr(cpt,i-cpt));
      cpt = i+1;
    }
  }
  return res;
}

/*
 * Author : Lucas Pauzies
 * Date : 07/03/2018
 * Input : body_string, string which represent body object with JSON style
 * Output : Body object that was represented by body_string
 */

Body toBody(string &body_string) {
  body_string.erase(remove(body_string.begin(), body_string.end(), '\"'), body_string.end());
  body_string.erase(remove(body_string.begin(), body_string.end(), '{'), body_string.end());
  body_string.erase(remove(body_string.begin(), body_string.end(), '}'), body_string.end());
  replace(body_string.begin(), body_string.end(), ':', ',');
  vector<string> body_string_vector = split(body_string,',');
  Body body(stod(body_string_vector[1]),
            stod(body_string_vector[3]),
            stod(body_string_vector[5]),
            stod(body_string_vector[7]),
            stod(body_string_vector[9]),
            stod(body_string_vector[11]),
            stod(body_string_vector[13]));
  return body;
}

/*
 * Author : Lucas Pauzies
 * Date : 07/03/2018
 * Input : json, string that represent N bodies with JSON style
 * Output : Body vector that was represented by json
 */

vector<Body> parseJSON(string &json) {
  vector<Body> bodies;
  /* Format string */
  json.erase(remove(json.begin(), json.end(), '\n'), json.end());
  json.erase(remove(json.begin(), json.end(), '\t'), json.end());
  json.erase(remove(json.begin(), json.end(), ' '), json.end());
  json = json.substr(11,json.length()-13);
  int cpt = 0;
  string body = "";
  for (unsigned int i = 0; i < json.length(); i++) {
    if (json[i] == '}') {
      body = json.substr(cpt,i+1-cpt);
      Body body_ = toBody(body);
      bodies.push_back(body_);
      cpt = i+2;
    }
  }
  return bodies;
}

/*
 * Author : Lucas Pauzies
 * Date : 07/03/2018
 * Input : None
 * Output : Body vector to initialize NBody object using data from JSON file named "filepath" (Reader attribute)
 */

vector<Body> Reader::readJSON() const {
  vector<Body> bodies;
  const string filepath = getFilePath();
  ifstream file(filepath);
  if (file) {
    string json;
    string line;
    //Get data in only one string
    while (getline(file,line)) {
      json += line;
    }
    bodies = parseJSON(json);
  } else {
    Error::error("reader.cpp","Open file failed for JSON reading");
  }
  file.close();
  return bodies;
}

/* ===== Reading without care of file type ===== */

/*
 * Author : Lucas Pauzies
 * Date : 07/03/2018
 * Input : None
 * Output : NBody object read from CSV/JSON file
 */

vector<Body> Reader::readBodies() const{
  const string filepath = getFilePath();
  size_t found_csv = filepath.rfind("csv");
  size_t found_json = filepath.rfind("json");
  vector<Body> bodies;
  if (found_csv != string::npos) {
    bodies = readCSV();
  }
  if (found_json != string::npos) {
    bodies = readJSON();
  }
  return bodies;
}
