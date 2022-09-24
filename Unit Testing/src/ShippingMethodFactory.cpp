#include "ShippingMethodFactory.h"

#include <iostream>

ShippingMethod *ShippingMethodFactory::getShippingMethod(const double weight) {
  ShippingMethod* method = nullptr;
  if (weight <= 0)
    throw invalid_parameter_error("Weight can not be negative.");
  else if (weight > 0 && weight <= TRUCK)
    method = new Truck();
  else if (weight > TRUCK && weight <= AIR)
    method = new Air();
  else if (weight > AIR && weight <= TRAIN)
    method = new Train();
  else if (weight > TRAIN)
    method = new Ship();

return method;
}
