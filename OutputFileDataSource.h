#ifndef OUTPUT_FILE_DATA_SOURCE_H
#define OUTPUT_FILE_DATA_SOURCE_H

class OutputFileDataSource : public FileDataSource {
  int init(std::string path) {
    initWithMode(path, "w"); 
  }
};

#endif
