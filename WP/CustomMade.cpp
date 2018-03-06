#include "CustomMade.h"

namespace ict {
  CustomMade::CustomMade() :OnShelf('C')
  {
  }

  CustomMade::CustomMade(char rectag) : OnShelf(rectag) {}

  const Date& CustomMade::delivery()const
  {
    return delivery_;
  }
  void CustomMade::delivery(const Date&value)
  {
    delivery_ = value;
  }
  std::fstream& CustomMade::store(std::fstream& file, bool addNewLine)const
  {
    if (err_.isClear())   // store the data must have not error message
    {
      OnShelf::store(file);   // store the OnShelf data
      file << ",";
      delivery_.read(file);
      if (addNewLine)
      {
        file << std::endl;
      }
    }
    return file;
  }
  std::fstream& CustomMade::load(std::fstream& file)
  {
    int day;
    int year;
    int month;
    OnShelf::load(file);   // load OnShelf data
    file >> year;
    file.ignore(1);
    file >> month;
    file.ignore(1);
    file >> day;
    file.ignore(1, '\n');
    Date temp(year, month, day);  // temp object
    delivery(temp);               // copy all the date to delivery
    return file;
  }
  std::ostream& CustomMade::display(std::ostream& os, bool linear)const
  {
    if (err_.isClear())   // display when no error message
    {

      OnShelf::display(os, linear);
      if (!linear)
      {
        std::cout << std::endl;
        std::cout << "delivery date: ";
      }
      delivery_.read(os);
    }
    else
    {
      os << err_;
    }
    return os;
  }
  std::istream& CustomMade::conInput(std::istream& is)
  {
    OnShelf::conInput(is);  // input OnShelf object
    if (err_.isClear())     // check if there has error message or not
    {
      Date tem;
      std::cout << "delivery date (YYYY/MM/DD) : ";
      tem.write(is);                      // input the data to tempory object
      if (tem.errCode() == CIN_FAILED)    // chck the errors
      {
        err_ = "Invalid Date Entry";
        is.setstate(std::ios::failbit);
      }
      else if (tem.errCode() == YEAR_ERROR)
      {
        err_ = "Invalid Year in Date Entry";
        is.setstate(std::ios::failbit);
      }
      else if (tem.errCode() == MON_ERROR)
      {
        err_ = "Invalid Month in Date Entry";
        is.setstate(std::ios::failbit);
      }
      else if (tem.errCode() == DAY_ERROR)
      {
        err_ = "Invalid Day in Date Entry";
        is.setstate(std::ios::failbit);
      }
      else
      {
        delivery_ = tem;         //no error set the delivery to tempory object
      }
    }
    return is;
  }
  std::ostream& operator<<(std::ostream& os, const CustomMade& cp)
  {
    cp.display(os, true);
    return os;
  }
  std::istream&operator >> (std::istream& is, CustomMade& cp)
  {
    cp.conInput(is);
    return is;
  }
}
