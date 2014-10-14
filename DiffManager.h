#ifndef DIFF_MANAGER_H
#define DIFF_MANAGER_H

#include <map>
#include <memory>

class DiffManager {
public:
  static std::shared_ptr<DiffManager> getInstance() {
    static std::shared_ptr<DiffManager> mgr(new DiffManager());
    return mgr;
  }

  int getDiff(std::string type, std::shared_ptr<Diff> &diff) {
    if (diffMap.find(type) == diffMap.end()) {
      Diff *tmp = NULL;
      if ((tmp = DiffFactory::createDiff(type)) == NULL)
        return -1;

      diffMap[type] = std::shared_ptr<Diff>(tmp);
    }

    diff = diffMap[type];
    return 0;
  }

  int registerDiffType(std::string key, std::shared_ptr<Diff> diff) {
    diffMap[key] = diff; 
    return 0;
  }

private:
  DiffManager() {
    registerDiffType("IntInt", std::shared_ptr<Diff>(new IntDiffInt()));
    registerDiffType("StrStr", std::shared_ptr<Diff>(new StringDiffString()));
  };

  std::map<std::string, std::shared_ptr<Diff>> diffMap;
  
  DiffManager(DiffManager const&);
  void operator=(DiffManager const&);
};

#endif
