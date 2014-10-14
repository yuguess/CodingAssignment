#ifndef DIFF_FACTORY_H
#define DIFF_FACTORY_H

#include "IntDiffInt.h"
#include "StringDiffString.h"

class DiffFactory {
public:
  static Diff* createDiff(std::string diffType) {
    Diff *diff = NULL;
    if (diffType == "IntInt") {
      diff = new IntDiffInt();
      return diff;
    } else if (diffType == "StrStr") {
      diff = new StringDiffString();
      return diff;
    } else {
      fprintf(stderr, "Error: DiffFactory recv invalid diff type %s\n", diffType.c_str());
    }

    return NULL; 
  }
};

#endif
