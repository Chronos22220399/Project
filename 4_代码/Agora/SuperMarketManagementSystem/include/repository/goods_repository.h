#pragma once
#include <string>

class GoodsRepository {
public:
  // just an instance
  static bool insert(const std::string &name, double price);
};
