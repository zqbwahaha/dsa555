#include <string>
#include <utility>
#include <functional>

/*
List of Modified and Added Methods of SimpleTable class

int search(const string& key);							//Change to binary search
int search(const string& key, int start, int end);		//Add for binary search
void sort();											//Change to Insertion search
const SimpleTable<TYPE>& operator=(const SimpleTable<TYPE>& other)
//Remove unnecessary statement
~SimpleTable()											//Remove unnecessary statement
*/

using namespace std;

template <class TYPE>
class Table {
public:
	Table() {}
	virtual bool update(const string& key, const TYPE& value) = 0;
	virtual bool remove(const string& key) = 0;
	virtual bool find(const string& key, TYPE& value) = 0;
	virtual ~Table() {}
};

template <class TYPE>
class SimpleTable :public Table<TYPE> {
	struct Record {
		TYPE data_;
		string key_;
		Record(const string& key, const TYPE& data) {
			key_ = key;
			data_ = data;
		}

	};

	Record** records_;   //the table
	int max_;           //capacity of the array
	int size_;          //current number of records held
	int search(const string& key);						//Edited by Soohyun Roh : For binary Search
	int search(const string& key, int start, int end);	//Added by Soohyun Roh : For binary Search
	void sort();										//Edited by Soohyun Roh : For Insertion sort
	void grow();
public:
	SimpleTable(int maxExpected);
	SimpleTable(const SimpleTable& other);
	SimpleTable(SimpleTable&& other);
	virtual bool update(const string& key, const TYPE& value);
	virtual bool remove(const string& key);
	virtual bool find(const string& key, TYPE& value);
	virtual const SimpleTable& operator=(const SimpleTable& other);
	virtual const SimpleTable& operator=(SimpleTable&& other);
	virtual ~SimpleTable();
};


//Returns index of where key is found.
template <class TYPE>
int SimpleTable<TYPE>::search(const string& key) {

	if (size_ == 0) return -1;
	int mid = (size_ - 1) / 2;
	if (records_[mid]->key_ == key) {
		return mid;
	}
	else if (records_[mid]->key_ > key) {
		return search(key, 0, mid - 1);
	}
	else {
		return search(key, mid + 1, size_ - 1);
	}
	/*
	//code before improvement
	int rc = -1;
	for (int i = 0; i<size_; i++) {
	if (records_[i]->key_ == key) {
	rc = i;
	}
	}
	return rc;
	*/
}

template <class TYPE>
int SimpleTable<TYPE>::search(const string& key, int start, int end) {
	if (start > end) return -1;
	int mid = (start + end) / 2;

	if (records_[mid]->key_ == key) {
		return mid;
	}
	else if (records_[mid]->key_ > key) {
		return search(key, start, mid - 1);
	}
	else {
		return search(key, mid + 1, end);
	}
}

//sort the according to key in table
template <class TYPE>
void SimpleTable<TYPE>::sort() {
	if (size_ == 0)return;
	int place = size_ - 1;
	Record* tmp = records_[place];	//Last record is newest inserted record

	for (int i = 0; i < size_ - 1; i++) {
		if (records_[i]->key_ > tmp->key_) {
			place = i;
			break;
		}
	}

	if (place != size_ - 1) {
		for (int i = size_ - 1; i > place; i--) {
			records_[i] = records_[i - 1];
		}
		records_[place] = tmp;
	}
	/*
	//code before improvement
	int minIdx = 0;
	for (int i = 0; i<size_; i++) {
	minIdx = i;
	for (int j = i + 1; j<size_; j++) {
	if (records_[j]->key_ < records_[minIdx]->key_) {
	minIdx = j;
	}
	}
	Record* tmp = records_[i];
	records_[i] = records_[minIdx];
	records_[minIdx] = tmp;
	}
	*/
}

//grow the array by one element
template <class TYPE>
void SimpleTable<TYPE>::grow() {
	Record** newArray = new Record*[max_ * 2];
	max_ = max_ * 2;
	for (int i = 0; i<size_; i++) {
		newArray[i] = records_[i];
	}
	delete[] records_;
	records_ = newArray;
}

/* none of the code in the function definitions below are correct.  You can replace what you need
*/
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(int maxExpected) : Table<TYPE>() {
	records_ = new Record*[maxExpected];
	max_ = maxExpected;
	size_ = 0;
}

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(const SimpleTable<TYPE>& other) {
	records_ = new Record*[other.max_];
	max_ = other.max_;
	size_ = 0;
	for (int i = 0; i<other.size_; i++) {
		update(other.records_[i]->key_, other.records_[i]->data_);
	}
}
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(SimpleTable<TYPE>&& other) {
	size_ = other.size_;
	max_ = other.max_;
	records_ = other.records_;
	other.records_ = nullptr;
	other.size_ = 0;
	other.max_ = 0;
}

template <class TYPE>
bool SimpleTable<TYPE>::update(const string& key, const TYPE& value) {
	int idx = search(key);
	if (idx == -1) {
		if (size_ == max_) {
			grow();
		}
		records_[size_++] = new Record(key, value);
		sort();
	}
	else {
		records_[idx]->data_ = value;
	}
	return true;
}

template <class TYPE>
bool SimpleTable<TYPE>::remove(const string& key) {
	int idx = search(key);
	if (idx != -1) {
		delete records_[idx];
		for (int i = idx; i<size_ - 1; i++) {
			records_[i] = records_[i + 1];
		}
		size_--;
		return true;
	}
	else {
		return false;
	}
}

template <class TYPE>
bool SimpleTable<TYPE>::find(const string& key, TYPE& value) {
	int idx = search(key);
	if (idx == -1)
		return false;
	else {
		value = records_[idx]->data_;
		return true;
	}
}

template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(const SimpleTable<TYPE>& other) {
	if (this != &other) {
		if (records_) {
			int sz = size_;

			for (int i = 0; i < sz; i++) {
				delete records_[i];
			}
			/*
			//code before improvement
			for (int i = 0; i<sz; i++) {
			remove(records_[0]->key_);
			}
			*/
			delete[] records_;
		}
		records_ = new Record*[other.max_];
		max_ = other.max_;
		size_ = 0;
		for (int i = 0; i<other.size_; i++) {
			update(other.records_[i]->key_, other.records_[i]->data_);
		}
	}
	return *this;
}
template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(SimpleTable<TYPE>&& other) {
	swap(records_, other.records_);
	swap(size_, other.size_);
	swap(max_, other.max_);
	return *this;
}
template <class TYPE>
SimpleTable<TYPE>::~SimpleTable() {
	if (records_) {
		int sz = size_;
		for (int i = 0; i<sz; i++) {
			//code before improvement
			//remove(records_[0]->key_);
			delete records_[i];
		}
		delete[] records_;
	}
}

template <class TYPE>
class LPTable :public Table<TYPE> {
  struct Record {
    TYPE data_;
    string key_;
    size_t hash_;
    Record(const string& key, const TYPE& data, size_t hash) {
      key_ = key;
      data_ = data;
      hash_ = hash;
    }

  };

  Record** records_; 
  int max_;           
  int size_;
public:
  LPTable(int maxExpected);
  LPTable(const LPTable& other);
  LPTable(LPTable&& other);
  virtual bool update(const string& key, const TYPE& value);
  virtual bool remove(const string& key);
  virtual bool find(const string& key, TYPE& value);
  virtual int search(const string& key);
  virtual const LPTable& operator=(const LPTable& other);
  virtual const LPTable& operator=(LPTable&& other);
  virtual ~LPTable();
};
/* none of the code in the function definitions below are correct.  You can replace what you need
*/
template <class TYPE>
LPTable<TYPE>::LPTable(int maxExpected) : Table<TYPE>() {
  records_ = new Record*[maxExpected*2];
  max_ = maxExpected*2;
  size_ = 0;
  for (int i = 0; i<max_; i++)
    records_[i] = nullptr;
}

template <class TYPE>
LPTable<TYPE>::LPTable(const LPTable<TYPE>& other) {
  if (this != &other) {
    records_ = new Record*[other.max_];
    size_ = other.size_;
    max_ = other.max_;
    for (int i = 0; i<other.max_; i++) {
      if (other.records_[i] != nullptr) {
        records_[i] = new Record(other.records_[i]->key_, other.records_[i]->data_, other.records_[i]->hash_);
      }
      else {
        records_[i] = nullptr;
      }
    }
  }

}

template <class TYPE>
LPTable<TYPE>::LPTable(LPTable<TYPE>&& other) {
  size_ = other.size_;
  max_ = other.max_;
  records_ = other.records_;
  other.records_ = nullptr;
  other.size_ = 0;
  other.max_ = 0;
}

template <class TYPE>
bool LPTable<TYPE>::update(const string& key, const TYPE& value) {

  size_t hash = std::hash<std::string>()(key) % max_;
  size_t coll = std::hash<std::string>()(key) % max_;

  int idx = search(key);

  if (idx == -1) {
    while (records_[idx] != nullptr) {
      if (records_[coll] == nullptr || records_[coll]->hash_ == -1) {
                                                                     
        records_[coll] = new Record(key, value, hash);
        size_++;
        return true;
      }
      else {
        coll++;
        if (coll == max_)
          coll = 0;
      }
    }
  }
  else {
    records_[idx]->data_ = value;
    return true;
  }
  return false;
}

template <class TYPE>
bool LPTable<TYPE>::remove(const string& key) {
  int hash = std::hash<std::string>()(key) % max_;
  int idx = search(key);

  if (idx != -1) {// if found 
    records_[idx]->hash_ = -1;
    records_[idx]->key_ = string();
    records_[idx]->data_ = TYPE{};
    size_--;
    return true;
  }
  else {
    return false;
  }
}

template <class TYPE>
bool LPTable<TYPE>::find(const string& key, TYPE& value) {
  int idx = std::hash<std::string>()(key) % max_;
  while (records_[idx] != nullptr) {
    if (records_[idx]->key_ == key) {
      value = records_[idx]->data_;
      return true;
    }
    idx++;
    if (max_ == idx)
      idx = 0;
  }
  return false;
}

template <class TYPE>
int LPTable<TYPE>::search(const string& key) {
  int hash = std::hash<std::string>()(key) % max_;
  while (records_[hash] != nullptr) {  // make sure it not null
    if (records_[hash]->key_ == key) {
      return hash;
    }
    else {
      hash++;
      if (hash == max_)
        return -1;
    }
  }
  return -1;
}

template <class TYPE>
const LPTable<TYPE>& LPTable<TYPE>::operator=(const LPTable<TYPE>& other) {
  if (this != &other) {
    if (records_) {
      delete[] records_;
    }
    records_ = new Record*[other.max_];
    max_ = other.max_;
    size_ = 0;
    for (int i = 0; i<other.max_; i++) {
      records_[i] = other.records_[i];
    }
  }
  return *this;

}

template <class TYPE>
const LPTable<TYPE>& LPTable<TYPE>::operator=(LPTable<TYPE>&& other) {
  swap(records_, other.records_);
  swap(size_, other.size_);
  swap(max_, other.max_);
  return *this;
}

template <class TYPE>
LPTable<TYPE>::~LPTable() {
  if (records_) {
    delete[] records_;
  }
}
