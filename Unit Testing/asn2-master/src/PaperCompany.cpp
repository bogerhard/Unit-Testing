#include <Exceptions.h>
#include "PaperCompany.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

PaperCompany::PaperCompany() {
  wl = new Waitlist();
  wh = new Warehouse(wl);
}

PaperCompany::~PaperCompany() {
  for (auto o : orders) delete o;
  for (auto p : products) delete p.second;
  delete wh;
  delete wl;
}

Order* PaperCompany::createOrder() {
  if (wh != nullptr || wl != nullptr)
    return new Order(wh, wl);

  return nullptr;
}

void PaperCompany::addToOrders(Order* input) {
  if (input != nullptr)
    orders.push_back(input);
  else
    throw invalid_parameter_error("Order pointer is null");
}

bool PaperCompany::addProduct(string name, double weight) {
  if (name.empty() || weight <= 0)
    throw invalid_parameter_error("illegal parameter");
  if (products.find(name) == products.end()) {
    Product* p = new Product(name, weight);
    products.insert({name, p});
    return true;
  }
  return false;
}

Product* PaperCompany::findProduct(string name) {
  if (products.find(name) != products.end())
    return products[name];
  return nullptr;
}

void PaperCompany::listInventory() {
  for (auto iter = products.begin(); iter != products.end(); ++iter)
    cout << iter->first << " : " << wh->checkQuantity(iter->second) << endl;
}

bool PaperCompany::adjustInventory(string name, int quantity) {
  if ((products.find(name) != products.end()) && (quantity > 0)) {
      return (wh->changeQuantity(products[name], quantity));
  } else if ((products.find(name) != products.end()) && (quantity <= 0)) {
      if (wh->checkQuantity(products[name]) - quantity >= 0)
        return (wh->changeQuantity(products[name], quantity));
  } else {
      return false;
  }
}

void PaperCompany::viewOrders() {
  for (int i = 0; i < orders.size(); i++)
    cout << orders[i] << ", ";
}

vector<Order*> PaperCompany::getOrders() {
  return orders;
}
