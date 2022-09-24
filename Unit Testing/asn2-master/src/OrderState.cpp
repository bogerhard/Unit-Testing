#include "Order.h"
#include "OrderState.h"
#include "Warehouse.h"
#include <iostream>
#include <map>
#include <string>
using namespace std;

InCartState::InCartState() : OrderState("In Cart") {}

void InCartState::view(Order *in) {
  cout << "InCartState";
  in->displayContent();
}

bool InCartState::submit(Order *in) {
  Warehouse* wh = in->getWarehouse();
  Waitlist* wl = in->getWaitlist();

  for (auto iter : in->getContents()) {
    int warehouseStock = wh->checkQuantity(iter.first);
    int orderQuantity = iter.second;

    if (warehouseStock < orderQuantity) {
      wl->addOrder(in);
      return false;
    }
  }
  for (auto iter : in->getContents()) {
    wh->changeQuantity(iter.first, -(iter.second));
  }
  return true;
}

void InCartState::cancel(Order *in) {
  in->getWaitlist()->removeOrder(in);
  in->getContents().clear();
}

PendingState::PendingState() : OrderState("Pending") {}

void PendingState::view(Order *in) {
  cout << "PendingState";
  in->displayContent();
}

bool PendingState::submit(Order *in) {
  Warehouse* wh = in->getWarehouse();
  Waitlist* wl = in->getWaitlist();
  for (auto iter : in->getContents()) {
    int warehouseStock = wh->checkQuantity(iter.first);
    int orderQuantity = iter.second;

    if (warehouseStock < orderQuantity) {
      return false;
    }
  }
  for (auto iter : in->getContents()) {
    wh->changeQuantity(iter.first, -(iter.second));
  }
  wl->removeOrder(in);
  return true;
}

void PendingState::cancel(Order *in) {
  in->getWaitlist()->removeOrder(in);
  in->getContents().clear();
}

CompleteState::CompleteState() : OrderState("Complete") {}

void CompleteState::view(Order *in) {
  cout << "CompleteState" << endl;
  cout << "Your order has been shipped" << endl;
}

bool CompleteState::submit(Order *in) {
  cout << "The order is already submitted" << endl;
  return true;
}

void CompleteState::cancel(Order *in) {
  cout << "The order is already submitted. It can't be canceled" << endl;
}
