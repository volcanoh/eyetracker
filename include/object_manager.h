#pragma once

#include <object.h>

class ObjectManager {
 public:
  static ObjectManager instance;
  static ObjectManager* GetInstance() {
    return &instance;
  }

 private:
  std::map<int, Object*> object;
  int AddObject();
};
