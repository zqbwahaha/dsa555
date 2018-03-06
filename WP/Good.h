#ifndef ICT_GOOD_H__
#define ICT_GOOD_H__
#include "ReadWritable.h"
#include "wpgeneral.h"
#include<iostream>
namespace ict {
  class Good :public ReadWritable
  {
  private:
    char sku_[MAX_SKU_LEN + 1];
    char* name_;
    double price_;
    bool taxed_;
    int quantity_;
    int qtyNeeded_;
  public:
    Good();
    Good(const char SKU[], const char* name, const double price, int qtyNeeded, bool taxed = true);
    void setEmpty();
    virtual ~Good();
    Good(const Good& cp);
    Good& operator=(const Good& cp);
    void sku(const char sku[]);
    void price(const double price);
    void name(const char* name);
    void taxed(bool taxed);
    void quantity(const int quantity);
    void qtyNeeded(const int qtyNeeded);
    const char* sku()const;
    double price()const;
    const char* name()const;
    bool taxed()const;
    int quantity()const;
    int qtyNeeded()const;
    double cost()const;
    bool operator==(const char* cp);
    int  operator+=(int cp);
  };
  double operator+=(double& a, const Good& cp);

}


#endif