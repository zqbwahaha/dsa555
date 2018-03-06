#ifndef ICT_DATE_H__
#define ICT_DATE_H__
#include "wpgeneral.h"
#include<iostream>
#define NO_ERROR 0
#define CIN_FAILED 1
#define YEAR_ERROR 2
#define MON_ERROR 3
#define DAY_ERROR 4

namespace ict {
  // Error code values go here
  class Date {
  private:
    // private member variables
    int year_;
    int mon_;
    int day_;
    int readErrorCode_;
    // private member functions and setters
    void errCode(int errorCode);
    int value()const;

  public:
    // constructors
    Date(int year, int mon, int day);
    Date();
    // operator overloads
    bool operator==(const Date& D)const;
    bool operator!=(const Date& D)const;
    bool operator<(const Date& D)const;
    bool operator>(const Date& D)const;
    bool operator<=(const Date& D)const;
    bool operator>=(const Date& D)const;


    // IO member functions
    std::istream& write(std::istream & is);
    std::ostream& read(std::ostream& os)const;
    // public member functions and getters
    int mdays()const;
    int errCode()const;
    bool bad()const;
  };
  std::istream& operator >> (std::istream& is, Date& D);
  std::ostream& operator<<(std::ostream& os, Date& D);
  // operator << and >> overloads prototypes for ostream and istream go here
}
#endif
