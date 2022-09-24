#include "Exceptions.h"
#include "PaperCompany.h"
#include "gtest/gtest.h"

TEST(TestPaperCompany, succeed) {
  SUCCEED();
}

TEST(TestPaperCompany, defaultConstructorTest) {
  PaperCompany* pc = new PaperCompany();
  EXPECT_NE(pc, nullptr);
  delete pc;
}

TEST(TestPaperCompany, addProductTest) {
  PaperCompany pc;

  EXPECT_TRUE(pc.addProduct("A1", 6.8));

  EXPECT_THROW(pc.addProduct("", 0), invalid_parameter_error);
  EXPECT_FALSE(pc.addProduct("A1", 6.8));
}

TEST(TestPaperCompany, findProductTest) {
  PaperCompany pc;
  pc.addProduct("A4", 6.8);
  Product* p1 = pc.findProduct("A4");

  EXPECT_EQ(p1->getName(), "A4");
  EXPECT_EQ(p1->getWeight(), 6.8);

  EXPECT_EQ(pc.findProduct("A1"), nullptr);
}

TEST(TestPaperCompany, adjustInventoryTest) {
  PaperCompany pc;
  pc.addProduct("A4", 6.8);

  EXPECT_TRUE(pc.adjustInventory("A4", 27));
  EXPECT_TRUE(pc.adjustInventory("A4", -10));

  pc.listInventory();
  EXPECT_FALSE(pc.adjustInventory("A4", -50));

  EXPECT_FALSE(pc.adjustInventory("B5", 50));
}

TEST(TestPaperCompany, addToOrdersTest) {
  PaperCompany pc;
  Order* o = pc.createOrder();

  pc.addToOrders(o);
  EXPECT_EQ((pc.getOrders()).size(), 1);
  pc.viewOrders();

  EXPECT_THROW(pc.addToOrders(nullptr), invalid_parameter_error);
}
