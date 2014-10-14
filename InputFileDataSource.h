#ifndef INPUT_FILE_DATA_SOURCE_H
#define INPUT_FILE_DATA_SOURCE_H

class InputFileDataSource : public FileDataSource {
  int init(std::string path) {
    initWithMode(path, "r"); 
  }
};

#endif
