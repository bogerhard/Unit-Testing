#include "Product.h"
#include <string>
#include "Exceptions.h"

Product::Product(string name, double pWeight) : id(name), weight(pWeight) {
  if (pWeight <= 0)
    throw invalid_parameter_error("illegal weight");
}

double Product::getWeight() {
  return weight;
}

string Product::getName() {
  return id;
}
