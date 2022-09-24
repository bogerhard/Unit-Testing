#include "Order.h"
#include <iostream>
#include <map>
#include <utility>

Order::Order(Warehouse *w, Waitlist *wl) {
  if ((w == nullptr) || (wl == nullptr))
    throw invalid_parameter_error("either parameter is null");

  from = w;
  in = wl;
  status = new InCartState();
  shipType = nullptr;
}

Order::~Order() {
  if (status) delete status;
  if (shipType) delete shipType;
}

bool Order::editContents(Product *item, int quantity) {
  if (item == nullptr)
    throw invalid_parameter_error("Product pointer is null");

  if (quantity >= 0) {
    if (contents.find(item) != contents.end()) {
      contents[item] += quantity;
      return true;
    } else {
      contents[item] = quantity;
      return true;
    }
  } else {
    if (contents[item] + quantity >= 0) {
      if (contents.find(item) != contents.end()) {
        contents[item] += quantity;
        return true;
      }
    } else {
        return false;
      }
  }
}

bool Order::submit() {
  if (status->submit(this)) {
      delete status;
      status = new CompleteState();
      int totalWeight = 0;
      for (auto iter : getContents()) {
        totalWeight += iter.first->getWeight() * iter.second;
      }
      setShipping(totalWeight);
      return true;
  } else {
      delete status;
      status = new PendingState();
      int totalWeight = 0;
      for (auto iter : getContents()) {
        totalWeight += iter.first->getWeight() * iter.second;
      }
      setShipping(totalWeight);
      return false;
  }
}

bool Order::isEmpty() {
  return contents.empty();
}

map<Product *, int> &Order::getContents() {
  return contents;
}

Warehouse *Order::getWarehouse() {
  return from;
}

void Order::cancel() {
  getStatus()->cancel(this);
}

void Order::view() {
  getStatus()->view(this);
}

void Order::displayContent() {
  int i = 1;
  for (auto iter = contents.begin(); iter != contents.end(); ++iter) {
    cout << i << ". " << iter->first << ": " << iter->second << endl;
    i++;
  }
}

Waitlist *Order::getWaitlist() {
  return in;
}

OrderState *Order::getStatus() {
  return status;
}

void Order::setShipping(double weight) {
    ShippingMethodFactory* f = nullptr;
    delete getShipping();
    shipType = f->getShippingMethod(weight);
}

ShippingMethod *Order::getShipping() {
    return shipType;
}
