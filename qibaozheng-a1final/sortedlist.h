
template <typename T>
class SortedList{
	struct Node{
    T data_;
    Node* next_;
    Node* pre_;
    //Node that contains data, pointer of next node and pointer of previus node.
		Node(const T& data=T{},Node* nx=nullptr,Node* pr=nullptr){
      next_ = nx;
      data_ = data;
      pre_ = pr;
		}
	};
  Node* front_;
  Node* back_;
public:
	class const_iterator{           	//const iterator class
    friend class SortedList;
    Node* curr_;
	public:
		const_iterator(){
      curr_ = nullptr;
    }
    const_iterator(Node* n) {
      curr_ = n;
    }
		const_iterator operator++(){//Increase to next node (Postfix)
      curr_ = curr_->next_;
      return *this;
    }
		const_iterator operator++(int){ //Increase to next node (Prefix)
      const_iterator old = *this;
      curr_ = curr_->next_;
      return old;
    }
		const_iterator operator--(){ //Decrease to previous node (Postfix)
      if (curr_)
        curr_ = curr_ -> pre_;
      return *this;
    }
		const_iterator operator--(int){ //Decrease to previous node (Prefix)
      if (curr_)
        curr_ = curr_ -> pre_;
      return *this;
    }
		bool operator==(const_iterator rhs){
      return curr_ == rhs.curr_;
    }
		bool operator!=(const_iterator rhs){
      return curr_ != rhs.curr_;
    }
		const T& operator*()const{
      return this->curr_->data_;
    
    }
	};
	class iterator:public const_iterator{     	//iterator class
	public:
    friend class SortedList;
		iterator():const_iterator(){}
    iterator(Node* n):const_iterator(n) {
    }
		iterator operator++(){  	//Increase to next node (Postfix)
      if (this->curr_) {
        this->curr_ = this->curr_->next_;
      }
      return *this;
    }
		iterator operator++(int){  //Increase to next node (Prefix)
      iterator old = *this;
      if (this->curr_) {
        this->curr_ = this->curr_->next_;
      }
      return old;
    }
		iterator operator--(){ //Decrease to previous node (Postfix)
      if (this->curr_) {
        this->curr_ = this->curr_->pre_;
      }
      return *this;
    }
		iterator operator--(int){ //Decrease to previous node (Prefix)
      iterator old = *this;
      if (this->curr_) {
        this->curr_ = this->curr_->pre_;
      }
      return old;
    }
		T& operator*(){     // return the data
      return this->curr_->data_;
    }
		const T& operator*()const{      // return data
      return this->curr_->data_;
    }
	};
	SortedList();
	~SortedList();
	SortedList(const SortedList& rhs);
	SortedList& operator=(const SortedList& rhs);
	SortedList(SortedList&& rhs);
	SortedList& operator=(SortedList&& rhs);
	iterator begin(){
    return front_->next_;
  }
	iterator end(){

    return back_;
  }
	const_iterator begin() const{
    return front_->next_;
  }
	const_iterator end() const{

    return back_;
  }
	iterator insert(const T& data);
	iterator search(const T& data);
	const_iterator search(const T& data) const;
	iterator erase(iterator it);
	iterator erase(iterator first, iterator last);
	bool empty() const;
	int size() const;
};
template <typename T>
SortedList<T>::SortedList(){   // default construtor
  Node* f = new Node();
  Node* b = new Node();
  f->next_ = b;
  b->pre_ = f;
  f->pre_ = nullptr;
  b->next_ = nullptr;
  front_ = f;
  back_ = b;
}
template <typename T>
SortedList<T>::~SortedList(){
  if (begin().curr_ != end().curr_)    // if there has not data in link list just delete front
  erase(begin(), end());
  delete front_;
  delete back_;

}
template <typename T>
SortedList<T>::SortedList(const SortedList& rhs){
  Node* f = new Node();
  Node* b = new Node();

  f->next_ = b;
  b->pre_ = f;
  front_ = f;
  back_ = b;
  for (const_iterator i = rhs.begin(); i != rhs.end(); i++) // copy all the data to this link list
  {
    Node* temp = new Node(*i, back_, back_->pre_);
    back_->pre_->next_ = temp;
    back_->pre_ = temp;

  }
}
template <typename T>
SortedList<T>& SortedList<T>::operator=(const SortedList& rhs){
  if(begin().curr_ !=end().curr_)        // if the link list contain not data skip earse
  erase(begin(), end());
  for (const_iterator i = rhs.begin(); i != rhs.end(); i++)   // copy all the data
  {
    Node* temp = new Node(*i, back_, back_->pre_);
    back_->pre_->next_ = temp;
    back_->pre_ = temp;
  }
  return *this;
}
template <typename T>
SortedList<T>::SortedList(SortedList&& rhs){// move all the data to this class make
  Node* f = new Node();                     // this clss front and back point to rhs clss node
  Node* b = new Node();                     // rhs lass node point to this class front and back
  f->next_ = b;                             // rhs class front next point to rhs back and rhs back prev to front
  b->pre_ = f;
  front_ = f;
  back_ = b;
  rhs.front_->next_->pre_ = front_;   
  front_->next_ = rhs.front_->next_;   
  rhs.back_->pre_->next_ = back_;
  back_->pre_ = rhs.back_->pre_;
  rhs.front_->next_ = rhs.back_;
  rhs.back_->pre_ = rhs.front_;

}

template <typename T>
SortedList<T>& SortedList<T>::operator=(SortedList&& rhs){ // copy move construtor
  //Erases exist data at this list because new data will replace to this list.
  if (begin().curr_ != end().curr_) // if there has not data skip earse
  erase(begin(), end());
  rhs.front_->next_->pre_ = front_;
  front_->next_ = rhs.front_->next_;
  rhs.back_->pre_->next_ = back_;
  back_->pre_ = rhs.back_->pre_;
  rhs.front_->next_ = rhs.back_;
  rhs.back_->pre_ = rhs.front_;


  return *this;
}

template <typename T>
typename SortedList<T>::iterator SortedList<T>::insert(const T& data){
   Node *newNode = new Node(data);
  if (front_->next_ == back_)   // if the list is empty do this 
  {
    front_->next_ = newNode;
    newNode->pre_ = front_;
    back_->pre_ = newNode;
    newNode->next_ = back_;
  }
  else
  {
    for (iterator i = begin(); i != end(); i++)  // make sure it is sort
    {
      if (newNode->data_ < i.curr_->data_ )  // if new data samll than curr put the new data at front of curr
      { 
        i.curr_->pre_->next_ = newNode;
        newNode->pre_ = i.curr_->pre_;
        newNode->next_ = i.curr_;
        i.curr_->pre_ = newNode;
        return newNode;
      }
    }   // if the new data greater than all the curr data push back
   back_->pre_->next_ = newNode;
   newNode->pre_ = back_->pre_;
   newNode->next_ = back_;
   back_->pre_ = newNode;

  }
  return newNode;

}

template <typename T>
typename SortedList<T>::iterator SortedList<T>::search(const T& data){ //  search
  for (iterator it = begin(); it != end(); it++) { // if the data has been found return curr
    if (it.curr_->data_ == data)return it.curr_;
  }
  return end(); // else return end
}

template <typename T>
typename SortedList<T>::const_iterator SortedList<T>::search(const T& data) const{//  search
  for (const_iterator it = begin(); it != end(); it++) {// if the data has been found return curr
    if (it.curr_->data_ == data)return it.curr_;
  }
  return end();// else return end

}

template <typename T>
typename SortedList<T>::iterator SortedList<T>::erase(iterator it){// erase the it
  Node* rc;    
  Node* temp = it.curr_;
  rc = temp;   // make 2 new node point to the same node
  if ((temp != front_) && (temp != back_)) // make sure it not front or back
  {
    temp->pre_->next_ = temp->next_;
    temp->next_->pre_ = temp->pre_;
    rc = temp->next_;    // make the node for return to curr next
    delete temp;      // delete curr
  }
  return rc;
}

template <typename T>
typename SortedList<T>::iterator SortedList<T>::erase(iterator first, iterator last){

  iterator rc = last; // rc is value for return
  last--; // make last = last pre_
  first.curr_->pre_->next_ = rc.curr_; // make the first prev next to rc
  rc.curr_->pre_ = first.curr_->pre_;  
  for (iterator it = first; it != last;) { // delete all data first to last
    Node *temp = it.curr_;
    it++;
    delete temp;
  }
  delete last.curr_;
  return rc;
}
template <typename T>
bool SortedList<T>::empty() const{
  		if(size()==0) return true;    // if size if 0 return true
		else return false;
}
template <typename T>
int SortedList<T>::size() const{
  int temp = 0;
  for (const_iterator it = begin(); it != end(); it++) {  
    temp++;
  }
  return temp;
}
