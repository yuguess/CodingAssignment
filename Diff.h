#ifndef DIFF_H
#define DIFF_H

class Diff {
public:
  virtual int diff(std::string&, std::string&, std::string&) = 0;
};

#endif
