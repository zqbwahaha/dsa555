#ifndef ICT_ONSHELF_H__
#define ICT_ONSHELF_H__
#include "Good.h"
#include "Error.h"
namespace ict {
  class OnShelf : public Good {
  private:
    char recTag_;
  protected:
    Error err_;
  public:
    OnShelf(char fileyag_ = 'O');
    virtual std::fstream& store(std::fstream& file, bool addNewLine = true)const;
    virtual std::fstream& load(std::fstream& file);
    virtual std::ostream& display(std::ostream& os, bool linear)const;
    virtual std::istream& conInput(std::istream& is);
  };
  std::ostream& operator<<(std::ostream& os, const OnShelf& cp);
  std::istream&operator >> (std::istream& is, OnShelf& cp);
}
#endif