#include <stdio.h>
#include <iostream>
#include <map>
#include <functional>
#include <sstream>
#include <algorithm>

#define MAX_BUF 255
typedef std::function<int(std::string&, std::string&, std::string&)> DiffFuncObj;
std::map <std::string, DiffFuncObj> diffFuncMap;

std::string &ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), 
        std::not1(std::ptr_fun<int, int>(std::isspace))));
  return s;
}

std::string &rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(), 
        std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
  return s;
}

int strDiffStr(std::string &l, std::string &r, std::string &res) {
  res = (l == r ? "T" : "N");
  return 0;
}

int intDiffInt(std::string &l, std::string &r, std::string &res) {
  res = std::to_string(std::stoi(l) - std::stoi(r));
  return 0;
}

int registerDiffType(std::string key, DiffFuncObj func) {
  diffFuncMap[key] = func; 
  return 0;
}

std::string getColType(FILE *in) {
  char buf[MAX_BUF];
  std::string res;

  fgets(buf, MAX_BUF - 1, in); 
  std::stringstream ss(buf);
  std::getline(ss, res, '_');

  return res;
}

int main(int argc, char* argv[]) {
  if (argc != 4) {
    fprintf(stderr, "Error in argument\n");
    fprintf(stderr, "usage: ./colDiff inputFile1 inputFile2 outputFile\n");
    return -1;
  }

  char buf1[MAX_BUF], buf2[MAX_BUF];
  FILE *in1 = NULL, *in2 = NULL, *out = NULL;

  registerDiffType("IntInt", intDiffInt);
  registerDiffType("StrStr", strDiffStr);

  if ((in1 = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "Error: can not open %s\n", argv[1]);
    return -1;
  }

  if ((in2 = fopen(argv[2], "r")) == NULL) {
    fprintf(stderr, "Error: can not open %s\n", argv[2]);
    fclose(in1);
    return -1;
  }

  std::string colType1 = getColType(in1);
  std::string colType2 = getColType(in2);

  if (diffFuncMap.find(colType1 + colType2) == diffFuncMap.end()) {
    fprintf(stderr, "Error: can not find proper diff func for %s and %s \n", 
        colType1.c_str(), colType2.c_str());
    fclose(in1);
    fclose(in2);
    return -1;
  }

  DiffFuncObj diff = diffFuncMap[colType1 + colType2];  

  if ((out = fopen(argv[3], "w")) == NULL) {
    fprintf(stderr, "Error: can not open %s\n", argv[3]);
    fclose(in1);
    fclose(in2);
    return -1;
  }

  fprintf(out, "Diff\n");
  std::string res;
  while (fgets(buf1, MAX_BUF - 1, in1) && fgets(buf2, MAX_BUF - 1, in2)) { 
    std::string s1(buf1);
    std::string s2(buf2);

    s1 = ltrim(rtrim(s1)); 
    s2 = ltrim(rtrim(s2));
    if (s1.size() == 0 || s2.size() == 0)
      continue;
    
    diff(s1, s2, res);
    fprintf(out, "%s\n", res.c_str());
  }

  fclose(in1);
  fclose(in2);
  fclose(out);
}
