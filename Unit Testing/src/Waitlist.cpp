#include "Order.h"
#include "Waitlist.h"
#include "OrderState.h"
#include <iostream>
#include <map>

void Waitlist::checkAll() {
  OrderState *pending = new PendingState();
  for (auto &iter : pendingOrders)
    pending->submit(iter);
  delete pending;
}

void Waitlist::addOrder(Order* order) {
  if (order == nullptr)
    throw invalid_parameter_error("Order pointer is null");
  else
    pendingOrders.push_back(order);
}

void Waitlist::removeOrder(Order* order) {
  if (order == nullptr)
    throw invalid_parameter_error("Order pointer is null");
  else
    pendingOrders.remove(order);
}

int Waitlist::size() {
  return pendingOrders.size();
}
