#ifndef UTILS_H
#define UTILS_H

class Utils {

public:
  static std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), 
        std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
  }

  static std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), 
        std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
  }

  static int process(std::shared_ptr<DataSource> in1, std::shared_ptr<DataSource> in2, 
      std::shared_ptr<DataSource> out, std::shared_ptr<Diff> diffObj) {
    std::string s1, s2, res("Diff");

    out->storeData(res);
    while (in1->getNext(s1) && in2->getNext(s2)) { 
      s1 = ltrim(rtrim(s1)); 
      s2 = ltrim(rtrim(s2));
      if (s1.size() == 0 || s2.size() == 0)
        continue;

      diffObj->diff(s1, s2, res);
      out->storeData(res);
    }

    return 0;
  }

};

#endif
