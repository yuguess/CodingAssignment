#ifndef STRING_DIFF_STRING_H
#define STRING_DIFF_STRING_H

#include "Diff.h"

class StringDiffString: public Diff {
  int diff(std::string &l, std::string &r, std::string &res) {
    res = (l == r ? "T" : "N");
    return 0;
  }
};

#endif
