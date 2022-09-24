#include "Order.h"
#include "Product.h"
#include "Waitlist.h"
#include "Warehouse.h"
#include "OrderState.h"
#include "PaperCompany.h"
#include "gtest/gtest.h"

TEST(TestWaitlist, checkAllTest) {
  Waitlist *wl = new Waitlist();
  Warehouse *wh = new Warehouse(wl);
  Order *o = new Order(wh, wl);
  OrderState *ost = new PendingState();
  Product *p = new Product("A4", 3.5);

  wl->addOrder(o);
  EXPECT_EQ(wl->size(), 1);
  o->editContents(p, 50);
  wh->changeQuantity(p, 30);
  wl->checkAll();
  EXPECT_EQ(wl->size(), 1);

  delete wl;
  delete wh;
  delete o;
  delete ost;
  delete p;
}
