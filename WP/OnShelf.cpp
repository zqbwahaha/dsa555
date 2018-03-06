#include "OnShelf.h"
#include <iomanip>
#include<iostream>
namespace ict {
  OnShelf::OnShelf(char filetag)
  {
    recTag_ = filetag;
  }
  std::fstream& OnShelf::store(std::fstream& file, bool addNewLine)const
  {
    //write the data to the file

    file << recTag_ << "," << sku() << "," << name() << "," << price() << "," << int(taxed()) << "," << quantity() << "," << qtyNeeded();
    if (addNewLine&&recTag_ == 'O')
    {
      file << std::endl;
    }
    return file;
  }
  std::fstream& OnShelf::load(std::fstream& file)
  {
    char sk[200];     // read the data to from txt file
    char nam[200];
    double pric;
    int taxe;
    int qtt;
    int qtn;
    file.getline(sk, MAX_SKU_LEN + 1, ',');
    file.getline(nam, 200, ',');
    file >> pric;
    file.ignore(100, ',');
    file >> taxe;
    file.ignore(100, ',');
    file >> qtt;
    file.ignore(100, ',');
    file >> qtn;
    file.ignore(1, '\n');
    sku(sk);
    name(nam);
    price(pric);
    taxed((bool(taxe)));
    quantity(qtt);
    qtyNeeded(qtn);
    return file;
  }
  std::ostream& OnShelf::display(std::ostream& os, bool linear)const
  {
    char t;
    if (taxed())
    {
      t = 't';
    }
    else
    {
      t = ' ';
    }
    if (err_.isClear())  // must have not error message 
    {

      std::cout << std::fixed << std::setprecision(2);   // set the flot to ".00" form
      if (linear)
      {
        os << " |" << std::setiosflags(std::ios::left) << std::setw(MAX_SKU_LEN) << std::setfill(' ') << sku()
           
          << " |" << std::left << std::setw(20) << name()

          << "|" << std::right << std::setw(7) << cost()

          << "| " << t << " |" << std::right << std::setw(4) << quantity()

          << "|" << std::right << std::setw(4) << qtyNeeded() << "|";
      }
      else
      {
        if (taxed())        //if taxed is true
        {
          os << "Sku: " << sku() << std::endl
            << "Name: " << name() << std::endl
            << "Price: " << price() << std::endl
            << "Price after tax: " << cost() << std::endl
            << "Quantity On Hand: " << quantity() << std::endl
            << "Quantity Needed: " << qtyNeeded();
        }
        else                 // not taxed
        {
          os << "Sku: " << sku() << std::endl
            << "Name: " << name() << std::endl
            << "Price: " << price() << std::endl
            << "Price after tax: N/A" << std::endl
            << "Quantity On Hand: " << quantity() << std::endl
            << "Quantity Need: " << qtyNeeded();
        }
      }

      os << std::resetiosflags(std::ios::left); //reset ths justfied
    }
    else
    {
      os << err_;
    }
    return os;
  }
  std::istream& OnShelf::conInput(std::istream& is)
  {
    char sk[200];   // varibles for read the data
    char nam[200];
    double pric;
    char taxe;
    int qtt;
    int qtn;
    std::cout << "Sku: ";
    is >> sk;
    std::cout << "Name: ";
    is >> nam;
    std::cout << "Price: ";
    is >> pric;
    if (is.fail())    // if price fail set the Good empty and skip all the stepts
    {
      setEmpty();
      is.setstate(std::ios::failbit);
      err_ = "Invalid Price Entry";
    }
    else         //start input Taxed
    {
      std::cout << "Taxed: ";
      is >> taxe;
      if (taxe == 'Y' || taxe == 'y' || taxe == 'n' || taxe == 'N')    // taxed must be " Y y N n " to go to next stepts
      {
        std::cout << "Quantity On hand: ";
        is >> qtt;
        if (is.fail())    // if input quantitiy fail set all empty and give the error message
        {
          setEmpty();
          is.setstate(std::ios::failbit);
          err_ = "Invalid Quantity Entry";
        }
        else
        {

          std::cout << "Quantity Needed: ";
          is >> qtn;
          if (is.fail())                   // if input quantitiy needed fail set all empty and give the error message
          {
            setEmpty();
            is.setstate(std::ios::failbit);
            err_ = "Invalid Quantity Needed Entry";
          }
          else                          // if all the inputs are correct clear the error message and set all the value to Good
          {
            err_.clear();
            sku(sk);
            price(pric);
            quantity(qtt);
            qtyNeeded(qtn);
            name(nam);
            if (taxe == 'Y' || taxe == 'y')  //if taxe Y set true
            {
              taxed(true);
            }
            else                            // eles false
            {
              taxed(false);
            }
          }
        }
      }
      else      // taxed input wrong
      {
        is.setstate(std::ios::failbit);
        err_ = "Only (Y)es or (N)o are acceptable";
        setEmpty();
      }
    }
    return is;
  }
  std::ostream& operator<<(std::ostream& os, const OnShelf& cp)
  {
    cp.display(os, true);
    return os;
  }
  std::istream&operator >> (std::istream& is, OnShelf& cp)
  {
    cp.conInput(is);
    return is;
  }
}