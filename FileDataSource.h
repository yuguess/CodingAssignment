#ifndef FILE_DATA_SOURCE_H
#define FILE_DATA_SOURCE_H

#include "DataSource.h"

class FileDataSource : public DataSource {

public:
  virtual int init(std::string path) {
    initWithMode(path, "a+");
  }

  int initWithMode(std::string path, std::string mode) {
    if ((m_file = fopen(path.c_str(), mode.c_str())) == NULL) {
      fprintf(stderr, "Error: can not open %s\n", path.c_str());
      return -1;
    }
    return 0;
  }

  virtual inline bool getNext(std::string &res) {
    char buf[MAX_BUF];
    if (fgets(buf, MAX_BUF - 1, m_file) == NULL)
      return false;
    res = std::string(buf);
    return true;
  }

  virtual inline int storeData(std::string &res) {
    fprintf(m_file, "%s\n", res.c_str());
    return 0;
  }

  inline std::string getHeaderType() {
    char buf[MAX_BUF];
    std::string res;

    fgets(buf, MAX_BUF - 1, m_file); 
    std::stringstream ss(buf);
    std::getline(ss, res, '_');

    return res;
  }

  int close() {
    fclose(m_file);
  }

private:
  FILE *m_file;
  const static int MAX_BUF = 255;
};
#endif
