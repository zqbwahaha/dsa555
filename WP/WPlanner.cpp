#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iomanip>
#include "WPlanner.h"
#include "Good.h"
#include "OnShelf.h"
#include "CustomMade.h"

using namespace std;
namespace ict {

  WPlanner::WPlanner(const char* filename) {
    strcpy(filename_, filename);
    items_[0] = nullptr;
    noOfItems_ = 0;
    loadRecs();

  }
  void WPlanner::saveRecs() {
    datafile_.open(filename_, ios::out);
    for (int i = 0; i < noOfItems_; i++)
    {
      items_[i]->store(datafile_);
    }
    datafile_.close();

  }
  void WPlanner::loadRecs() {
    char id;
    int i = 0;
    datafile_.open(filename_, ios::in);
    if (datafile_.fail())
    {
      datafile_.clear();
      datafile_.close();
      datafile_.ignore(2);
      datafile_.open(filename_, ios::out);
      datafile_.close();
    }
    else
    {
      datafile_.get(id);
      while (!datafile_.eof())
      {

        items_[i] = nullptr;
        if (id == 'C')
        {
          items_[i] = new CustomMade;
          datafile_.ignore(100, ',');
          items_[i]->load(datafile_);
        }
        else if (id == 'O')
        {
          items_[i] = new OnShelf;
          datafile_.ignore(100, ',');
          items_[i]->load(datafile_);
        }
        datafile_.get(id);
        i++;
      }
      noOfItems_ = i;
      datafile_.close();
    }
  }
  void WPlanner::getSku(char* sku) {
    cout << "Please enter the SKU: ";
    cin.getline(sku, MAX_SKU_LEN + 1, '\n');
    cout << endl;
    if (cin.fail())
    {
      cin.clear();
      cin.ignore(100);
    }
  }
  void WPlanner::deleteItem() {
    char sku[MAX_SKU_LEN];
    getSku(sku);
    char comfirm;
    int index = SearchItems(sku);
    if (index == -1)
    {
      cout  << "Item Not found!" << endl << endl;
    }
    else
    {
      cout << "The following Item will be deleted:" << endl;
      items_[index]->display(cout, false);
      cout << endl << endl << "Type (Y) to confirm or (N) to abort: ";
      cin >> comfirm;
      if (comfirm == 'y' || comfirm == 'Y')
      {
        int t = 0;
        for (int i = 0; i < noOfItems_; i++)
        {
          if (i != index)
          {
            items_[t] = items_[i];
            t++;
          }
        }
        noOfItems_ -= 1;
        cout << endl << "Item deleted!" << endl << endl;
        for (int i = noOfItems_; i < MAX_NO_RECS; i++)
        {
          items_[i] = nullptr;

        }
        saveRecs();
      }
      else if (cin.fail() || comfirm == 'n' || comfirm == 'N')
      {
        cout <<  endl;
        cout << "Aborted!" << endl << endl;
      }
    }

  }
  void WPlanner::updateQty() {
    int qtt;
    char sku[MAX_SKU_LEN];
    getSku(sku);
    int index = SearchItems(sku);
    if (index == -1)
    {
      cout << endl << "Item Not found!" << endl;
    }
    else
    {
      items_[index]->display(cout, false);
      cout << endl << endl;
      cout << "Please enter the number of purchased goods: ";
      cin >> qtt;
      if (cin.fail())
      {
        cout << "Invalid Quantity value!" << endl;
        cin.clear();

      }
      else
      {

        if (qtt <= (items_[index]->qtyNeeded() - items_[index]->quantity()))
        {
          *items_[index] += qtt;
        }
        else
        {
          cout << "Too many purchased, only " << (items_[index]->qtyNeeded() - items_[index]->quantity())
            << " need, please return the extra " << ((qtt + items_[index]->quantity()) - items_[index]->qtyNeeded());
          qtt = items_[index]->qtyNeeded() - items_[index]->quantity();
          *items_[index] += qtt;

        }
        cout << endl << "Updated!" << endl << endl;
      }
      cin.ignore(100, '\n');
    }








  }
  void WPlanner::listItems()const {
    double total = 0;
    cout << " Row | SKU | Good Name          | Cost  |Tax| QTY|Need| Delivery" << endl
      << "-----|-----|--------------------|-------|---|----|----|----------" << endl;
    if (noOfItems_ > 0)
    {
      for (int i = 0; i < noOfItems_; i++)
      {
        total += *items_[i];
        cout << setiosflags(std::ios::right) << setw(MAX_SKU_LEN) << setfill(' ') << i + 1;
        items_[i]->display(cout, true);
        cout << endl;
      }
      cout << "-----+-----+--------------------+-------+---+----+----+----------" << endl;
    }
    cout << "Total cost of the Wedding: $" << total << endl << endl;;



  }
  int WPlanner::SearchItems(const char* sku)const {

    int index = -1;
    for (int i = 0; i < noOfItems_; i++)
    {
      if (*items_[i] == sku)
      {
        index = i;
        break;
      }
    }
    return index;
  }
  void WPlanner::addItem(bool isCustomMade) {

    if (isCustomMade)
    {
      items_[noOfItems_] = new CustomMade;
      while (1)
      {
        items_[noOfItems_]->conInput(cin);
        if (!cin.fail())
        {
          cout << endl << "Good added" << endl << endl;
          break;
        }
        else
        {
          cin.clear();
          cin.ignore(2000, '\n');
        }
      }
    }
    else
    {
      items_[noOfItems_] = new OnShelf;
      while (1)
      {
        items_[noOfItems_]->conInput(cin);
        if (!cin.fail())
        {
          cout << endl << "Good added" << endl << endl;
          break;
        }
        else
        {
          cin.clear();
          cin.ignore(2000, '\n');
        }
      }
    }
    noOfItems_ += 1;
    saveRecs();
  }
  int WPlanner::menu() {
    int selection = -1;
    cout << "Wedding Planner Management Program" << endl
      << "1 - List goods" << endl
      << "2 - Add On Shelf Good" << endl
      << "3 - Add Custom-Made Good" << endl
      << "4 - Update Good quantity" << endl
      << "5 - Delete" << endl
      << "0 - Exit program" << endl << "> " ;
    cin >> selection;
    cout << endl;
    if (cin.fail())
    {
      cin.clear();
      selection = -1;
    }
    cin.ignore(100, '\n');
    return selection;
  }
  int WPlanner::run() {
    bool done = false;
    while (!done) {
      switch (menu()) {
      case 1:
        listItems();
        break;
      case 2:
        addItem(false);
        break;
      case 3:
        addItem(true);
        break;
      case 4:
        updateQty();
        break;
      case 5:
        deleteItem();
        break;
      case 0:
        done = true;
        cout << "Goodbye!!" << endl << endl;
        break;
      case -1:
        cout << "===Invalid Selection, try again.===" << endl << endl;
        break;
      }
    }
    return 0;
  } // WPlanner::run() end
}


/* outputs

Wedding Planner Management Program
1 - List goods
2 - Add On Shelf Good
3 - Add Custom-Made Good
4 - Update Good quantity
5 - Delete
0 - Exit program
>



Not found!

Please enter the number of purchased goods:

Too many purchased, only 5 needed, please return the extra 15.

Updated!

Not implemented!

*/