#ifndef DATA_SOURCE_MANAGER_H
#define DATA_SOURCE_MANAGER_H

#include <iostream>
#include <memory>
#include "DataSourceFactory.h"

class DataSourceManager {
public:
  static std::shared_ptr<DataSourceManager> getInstance() {
    static std::shared_ptr<DataSourceManager> mgr(new DataSourceManager());
    return mgr;
  }

  int getDataSource(std::string type, std::shared_ptr<DataSource> &ds) {
    DataSource *tmp = NULL;

    if ((tmp = DataSourceFactory::createDataSource(type)) == NULL)
      return -1; 

    ds = std::shared_ptr<DataSource>(tmp);
    return  0;
  }

private:
  DataSourceManager() {};
  DataSourceManager(DataSourceManager const&);
  void operator=(DataSourceManager const&);
};

#endif
