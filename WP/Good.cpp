#include <cstring>
#include "wpgeneral.h"
#include "Good.h"
using namespace std;
namespace ict {
  void Good::setEmpty()
  {
    sku_[0] = 0;
    name_ = nullptr;
    price_ = 0;
    taxed_ = false;
    quantity_ = 0;
    qtyNeeded_ = 0;
  }
  Good::Good()
  {
    setEmpty();
  }
  Good::Good(const char SKU[], const char* name, const double price, const int qtyNeeded, bool taxed)
  {
    strcpy(sku_, SKU);
    name_ = new char[strlen(name) + 1];
    strcpy(name_, name);
    quantity_ = 0;
    price_ = price;
    qtyNeeded_ = qtyNeeded;
    taxed_ = taxed;
  }
  Good::Good(const Good&cp)
  {
    name_ = new char[strlen(cp.name_) + 1];
    strcpy(name_, cp.name_);
    strcpy(sku_, cp.sku_);
    price_ = cp.price_;
    quantity_ = cp.quantity_;
    qtyNeeded_ = cp.qtyNeeded_;
    taxed_ = cp.taxed_;
  }

  Good& Good:: operator=(const Good& cp)
  {
    if (this != &cp)
    {
      delete[] name_;
      name_ = new char[strlen(cp.name_) + 1];
      strcpy(name_, cp.name_);
      strcpy(sku_, cp.sku_);
      price_ = cp.price_;
      quantity_ = cp.quantity_;
      qtyNeeded_ = cp.qtyNeeded_;
      taxed_ = cp.taxed_;
    }
    return *this;
  }
  void Good::sku(const char sku[])
  {
    strcpy(sku_, sku);
  }
  void Good::price(const double price)
  {
    price_ = price;
  }
  void Good::name(const char* name)
  {
    delete[]name_;
    name_ = new char[strlen(name) + 1];
    strcpy(name_, name);
  }
  void Good::taxed(bool taxed)
  {
    taxed_ = taxed;
  }
  void Good::quantity(const int quantity)
  {
    quantity_ = quantity;
  }
  void Good::qtyNeeded(const int qtyNeeded)
  {
    qtyNeeded_ = qtyNeeded;
  }
  const char* Good::sku()const
  {
    return sku_;
  }

  double Good::price()const
  {
    return price_;
  }
  const char* Good::name()const
  {
    return name_;
  }

  bool Good::taxed()const
  {
    return taxed_;
  }

  int Good::quantity()const
  {
    return quantity_;
  }

  int Good::qtyNeeded()const
  {
    return qtyNeeded_;
  }

  double Good::cost()const
  {
    double sum = price_;
    if (taxed_)
    {
      sum = price_*(TAX + 1);
    }
    return sum;
  }
  bool Good::operator==(const char* cp)
  {
    return !(strcmp(sku_, cp));
  }
  int Good::operator+=(int cp)
  {
    return quantity_ += cp;
  }
  double operator+=(double& a, const Good& cp)
  {

    return (a += cp.cost()*cp.quantity());
  }

  Good::~Good()
  {
    delete[] name_;
  }
}