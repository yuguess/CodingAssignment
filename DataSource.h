#ifndef DATA_SOURCE_H
#define DATA_SOURCE_H

#include <iostream>
class DataSource {
public:
  virtual int init(std::string) = 0;
  virtual bool getNext(std::string &) = 0;
  virtual int storeData(std::string &) = 0; 
  virtual std::string getHeaderType() = 0;
  virtual int close() = 0;
};

#endif
