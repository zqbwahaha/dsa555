#ifndef ICT_CUSTOMMADE_H__
#define ICT_CUSTOMMADE_H__
#include "OnShelf.h"
#include "Date.h"
#include "Error.h"
namespace ict {
  class CustomMade :public OnShelf {
  private:
    Date delivery_;
  public:
    CustomMade();
    CustomMade(char rectag);
    void delivery(const Date &value);
    const Date& delivery()const;
    std::fstream& store(std::fstream& file, bool addNewLine = true)const;
    std::fstream& load(std::fstream& file);
    std::ostream& display(std::ostream& os, bool linear)const;
    std::istream& conInput(std::istream& is);
  };
  std::ostream& operator<<(std::ostream& os, const CustomMade& cp);
  std::istream&operator >> (std::istream& is, CustomMade& cp);
}


#endif
