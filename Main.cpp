#include <stdio.h>
#include <iostream>
#include <map>
#include <functional>
#include <sstream>
#include <algorithm>
#include <memory>

#include "DataSource.h"
#include "DataSourceManager.h"
#include "Diff.h"
#include "DiffFactory.h"
#include "DiffManager.h"
#include "Utils.h"

#define MAX_BUF 255
typedef std::function<int(std::string&, std::string&, std::string&)> DiffFuncObj;
std::map <std::string, DiffFuncObj> diffFuncMap;

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

  std::shared_ptr<DataSource> in1, in2, out;
  DataSourceManager::getInstance()->getDataSource("InputFile", in1);
  in1->init(argv[1]);

  DataSourceManager::getInstance()->getDataSource("InputFile", in2);
  in2->init(argv[2]);

  DataSourceManager::getInstance()->getDataSource("OutputFile", out);
  out->init(argv[3]);

  std::shared_ptr<Diff> diffObj;
  std::string h1 = in1->getHeaderType();
  std::string h2 = in2->getHeaderType();
  DiffManager::getInstance()->getDiff(h1 + h2, diffObj);

  Utils::process(in1, in2, out, diffObj);

  in1->close();
  in2->close();
  out->close();
}
