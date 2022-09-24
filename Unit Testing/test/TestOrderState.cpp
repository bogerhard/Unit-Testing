#include "Order.h"
#include "Product.h"
#include "Waitlist.h"
#include "Warehouse.h"
#include "OrderState.h"
#include "gtest/gtest.h"

TEST(TestPendingState, submitTest) {
  Waitlist *wl = new Waitlist();
  Warehouse *wh = new Warehouse(wl);
  Order *o = new Order(wh, wl);
  OrderState *ost = new PendingState();
  Product *p = new Product("A4", 3.5);

  wl->addOrder(o);
  o->editContents(p, 50);
  wh->changeQuantity(p, 20);
  EXPECT_FALSE(ost->submit(o));
  EXPECT_EQ(wl->size(), 1);

  wh->changeQuantity(p, 30);
  EXPECT_TRUE(ost->submit(o));

  EXPECT_EQ(wl->size(), 0);
  EXPECT_EQ(wh->checkQuantity(p), 0);

  delete wl;
  delete wh;
  delete o;
  delete p;
  delete ost;
}

TEST(TestInCartState, submitTest) {
  OrderState* ost = new InCartState();
  Waitlist* w = new Waitlist();
  Warehouse *h = new Warehouse(w);
  Order* o1 = new Order(h, w);
  Product* p = new Product("A4", 3.5);

  ost->view(o1);
  // Case1 -  All items on the order are in stock.
  h->changeQuantity(p, 40); // Warehouse quantity = 40

  o1->editContents(p, 10); // Order quantity = 10

  EXPECT_TRUE(ost->submit(o1)); // succesfully submitted

  // Items are removed from the warehouse.
  EXPECT_EQ(h->checkQuantity(p), 30); // Warehouse quantity becomes 30

  // Case2 - If one or more item are not in stock -> pending
  Product* q = new Product("B5", 2.7);
  Order* o2 = new Order(h, w);

  h->changeQuantity(q, 20); // Warehouse quantity = 20
  o2->editContents(q, 60);  // Order quantity = 60
  EXPECT_FALSE(ost->submit(o2)); // Order becomes pending

  delete ost;
  delete w;
  delete h;
  delete p;
  delete q;
  delete o1;
  delete o2;
}
