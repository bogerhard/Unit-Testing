#include "Warehouse.h"
#include <map>

Warehouse::Warehouse(Waitlist* w) {
  pending = w;
}

bool Warehouse::changeQuantity(Product* type, int quantity) {
  if (type == nullptr) {
      throw invalid_parameter_error("Product pointer is null");
  } else if (checkQuantity(type) + quantity >= 0) {
      inventory[type] += quantity;
      return true;
  } else {
      return false;
  }
}

int Warehouse::checkQuantity(Product* type) {
  if (type == nullptr)
    throw invalid_parameter_error("Product pointer is null");
  else if (inventory.find(type) != inventory.end())
    return inventory[type];
  else
    return 0;
}
