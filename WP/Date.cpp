// header files go here

#include "Date.h"
#include "wpgeneral.h"
#include <iomanip>
namespace ict {
  // returns a unique value representing the date
  // this value is used to compare two dates
  int Date::value()const {
    return year_ * 372 + mon_ * 31 + day_;
  }
  // bool validate(), this is an optional private function
  // for validation logic and setting the _readErrorCode.
  // see the read() function description for more details





  // mdays():
  // returns the day of the month.
  // _mon value must be set for this function to work
  // if _mon is invalid, this function returns -1
  // leap years are considered in this logic
  int Date::mdays()const {
    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
    int mon = mon_ >= 1 && mon_ <= 12 ? mon_ : 13;
    mon--;
    return days[mon] + int((mon == 1)*((year_ % 4 == 0) && (year_ % 100 != 0)) || (year_ % 400 == 0));
  }

  // constructors

  Date::Date(int year, int mon, int day)
  {
    year_ = year;
    mon_ = mon;
    day_ = day;
    readErrorCode_ = NO_ERROR;
  }

  Date::Date()
  {
    year_ = 0;
    mon_ = 0;
    day_ = 0;
    readErrorCode_ = -1;
  }

  // member functions
  void Date::errCode(int errorCode)
  {
    readErrorCode_ = errorCode;
  }
  int Date::errCode()const
  {
    return readErrorCode_;
  }
  bool Date::bad()const
  {
    bool n;
    if (readErrorCode_ != 0)
      n = true;
    else
      n = false;
    return n;
  }

  // operators
  bool Date:: operator==(const Date& D)const
  {
    bool n;
    if (this->value() == D.value())
    {
      n = true;
    }
    else {
      n = false;
    }
    return n;
  }
  bool Date::operator!=(const Date& D)const
  {
    bool n;
    if (this->value() != D.value())
    {
      n = true;
    }
    else
      n = false;
    return n;
  }
  bool Date::operator<(const Date& D)const
  {
    bool n;
    if (this->value() < D.value())
      n = true;
    else
      n = false;
    return n;
  }
  bool Date::operator>(const Date& D)const
  {
    bool n;
    if (this->value() > D.value())
      n = true;
    else
      n = false;
    return n;
  }
  bool Date::operator <=(const Date& D)const
  {
    bool n;
    if (this->value() <= D.value())
      n = true;
    else
      n = false;
    return n;
  }
  bool Date::operator>=(const Date& D)const
  {
    bool n;
    if (this->value() >= D.value())
      n = true;
    else
      n = false;
    return n;
  }
  // IO functions
  std::istream& Date::write(std::istream& is)
  {
    is >> year_;
    std::cin.ignore(1, '/');
    is >> mon_;
    std::cin.ignore(1, '/');
    is >> day_;
    if (is.fail())
    {
      errCode(CIN_FAILED);
    }
    else if (year_ > MAX_YEAR || year_ < MIN_YEAR)
    {
      errCode(YEAR_ERROR);
    }
    else if (mon_ > 12 || mon_ < 1)
    {
      errCode(MON_ERROR);
    }
    else if (day_<1 || day_> mdays())
    {
      errCode(DAY_ERROR);
    }
    else
    {
      errCode(NO_ERROR);
    }
    return is;
  }
  std::ostream& Date::read(std::ostream& os)const
  {
    os << year_ << "/" << std::setfill('0') << std::right << std::setw(2) << mon_ << "/" << std::right << std::setw(2) << day_;
    return os;
  }


  // non-memeber operator overloads
  std::istream& operator >> (std::istream& is, Date& D)
  {
    return D.write(is);
  }
  std::ostream& operator << (std::ostream& os, Date& D)
  {

    return D.read(os);;
  }

}
