#ifndef ICT_WPlanner_H__
#define ICT_WPlanner_H__
#include "Good.h"

namespace ict {
  class WPlanner {
  private:
    char filename_[256];
    Good* items_[MAX_NO_RECS];
    std::fstream datafile_;
    int noOfItems_;
    int menu();
    void loadRecs();
    void saveRecs();
    void listItems()const;
    int SearchItems(const char* sku)const;
    void updateQty();
    void addItem(bool isCustomMade);
    void deleteItem();
    void getSku(char* sku);
  public:
    //Copy and assignment prevention goes here:
    WPlanner(const WPlanner& other) = delete;
    WPlanner& operator= (const WPlanner&) = delete;
    WPlanner(const char* filename);
    int run();
  };
}
#endif
