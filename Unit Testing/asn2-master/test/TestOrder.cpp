#include "Order.h"
#include "Product.h"
#include "Waitlist.h"
#include "Warehouse.h"
#include "gtest/gtest.h"

TEST(TestOrder, editContentsTest) {
  Waitlist* w = new Waitlist();
  Warehouse *h = new Warehouse(w);
  Order *o = new Order(h, w);
  Product* p = new Product("A4", 3.5);

  EXPECT_TRUE(o->editContents(p, 20));
  EXPECT_TRUE(o->editContents(p, -10));
  EXPECT_FALSE(o->editContents(p, -15));

  delete w;
  delete h;
  delete p;
  delete o;
}
