#include "Error.h"
#include <cstring>
namespace ict {
  Error::Error()
  {
    message_ = nullptr;
  }
  Error::Error(const char* Error)
  {
    message_ = nullptr;
    message(Error);
  }
  void Error::message(const char* value)
  {
    int size = strlen(value) + 1;
    message_ = new char[size];
    strcpy(message_, value);
  }
  const char* Error::message()const
  {
    return message_;
  }
  bool Error::isClear()const
  {
    return message_ ? false : true;
  }
  void Error::clear()
  {
    delete[] message_;
    message_ = nullptr;
  }
  Error & Error::operator=(const char * errorMessage)
  {
    clear();
    int size = strlen(errorMessage) + 1;
    message_ = new char[size];
    strcpy(message_, errorMessage);
    return *this;
  }
  std::ostream&operator<<(std::ostream&os, const Error& op)
  {
    if (!op.isClear())
    {
      os << op.message();
    }
    return os;
  }

  Error::~Error()
  {
    delete[] message_;
  }
}
