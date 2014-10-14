#ifndef DATA_SOURCE_FACTORY_H
#define DIFF_SOURCE_FACTORY_H

#include "FileDataSource.h"
#include "InputFileDataSource.h"
#include "OutputFileDataSource.h"

class DataSourceFactory {

public:
  static DataSource* createDataSource(std::string type) {
    if (type == "InputFile") {
      return new InputFileDataSource(); 
    } else if (type == "OutputFile") {
      return new OutputFileDataSource(); 
    } else {
      fprintf(stderr, "Error: DiffFactory recv invalid diff type %s\n", type.c_str());
      return NULL;
    }
  }
};

#endif
