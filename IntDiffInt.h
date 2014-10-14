#ifndef INT_DIFF_INT_H
#define INT_DIFF_INT_H

#include <iostream>
#include "Diff.h"

class IntDiffInt : public Diff {
  int diff(std::string &l, std::string &r, std::string &res) {
    res = std::to_string(std::stoi(l) - std::stoi(r));
    return 0;
  }
};

#endif
