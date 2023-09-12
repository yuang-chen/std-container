#include <iostream>

/********************/
/*Double linked list*/
/********************/

template <typename T>
class List
{
  private:
  struct Node
  {
    T     data_;
    Node* next_;
    Node* prev_;

    Node(T data, Node* next, Node* prev) : data_(data), next_(next), prev_(prev) {}
  };
  Node*  head_;
  Node*  tail_;
  size_t size_;

  public:
  List() : head_(nullptr), tail_(nullptr), size_(0) {}

  ~List()
  {
    Node* curr = head_;
    while(curr != nullptr)
    {
      Node* next = curr->next_;
      delete curr;
      curr = next;
    }
  }

  void push_back(T value)
  {
    Node* new_node = new Node(value, nullptr, nullptr);

    if(tail_)
    {
      tail_->next_    = new_node;
      new_node->prev_ = tail_;
      tail_           = new_node;
    }
    else
    {
      head_ = new_node;
      tail_ = new_node;
    }
    size_++;
  }

  void push_front(T value)
  {
    Node* new_node = new Node(value, nullptr, nullptr);

    if(head_)
    {
      head_->prev_    = new_node;
      new_node->next_ = head_;
      head_           = new_node;
    }
    else
    {
      head_ = new_node;
      tail_ = new_node;
    }
    size_++;
  }

  void pop_back()
  {
    if(tail_)
    {
      Node* temp = tail_;
      tail_      = tail_->prev_;
      delete tail_;
      size_--;
    }
  }
  void pop_front()
  {
    if(head_)
    {
      Node* temp = head_;
      head_      = head_->next_;
      delete head_;
      size_--;
    }
  }

  T& back()
  {
    return tail_->data_;
  }

  T& front()
  {
    return head_->data_;
  }
  // the standard library use iterator to index the position
  void insert(size_t pos, T value) {}

  size_t size() const
  {
    return size_;
  }
};

/********************/
/*Single linked list*/
/********************/

template <typename T>
class ForwardList
{
  private:
  struct Node
  {
    T     data_;
    Node* next_;

    Node(T data, Node* next) : data_(data), next_(next) {}
  };
  Node*  head_;
  size_t size_;

  public:
  ForwardList() : head_(nullptr), size_(0) {}

  ~ForwardList()
  {
    Node* curr = head_;
    while(curr != nullptr)
    {
      Node* next = curr->next_;
      delete curr;
      curr = next;
    }
  }

  // stl library uses iterator to index the position
  void insert_after(size_t pos, T value)
  {
    if(pos > size_)
    {
      return;
    }
    Node* new_node = new Node(value, nullptr);
    Node* curr     = head_;
    for(size_t i = 0; i < pos - 1; i++)
    {
      curr = curr->next_;
    }
    Node* temp      = curr->next_;
    curr->next_     = new_node;
    new_node->next_ = temp;
    size_++;
  }

  void push_front(T value)
  {
    Node* new_node = new Node(value, nullptr);

    if(head_)
    {
      new_node->next_ = head_;
      head_           = new_node;
    }
    else
    {
      head_ = new_node;
    }
    size_++;
  }

  void erase_after(size_t pos)
  {
    if(pos > size_)
    {
      return;
    }
    Node* curr = head_;
    for(size_t i = 0; i < pos - 1; i++)
    {
      curr = curr->next_;
    }
    Node* temp  = curr->next_;
    curr->next_ = temp->next_;
    delete temp;
  }

  void pop_front()
  {
    if(head_)
    {
      Node* temp = head_;
      head_      = head_->next_;
      delete temp;
      size_--;
    }
  }

  T& front()
  {
    return head_->data_;
  }
  // the standard library use iterator to index the position
  void insert(size_t pos, T value) {}

  size_t size() const
  {
    return size_;
  }
};

int main()
{
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);

  list.push_front(-1);
  list.push_front(-2);
  list.push_front(-3);
  list.push_front(-4);

  std::cout << "list size_: " << list.size() << std::endl;
  std::cout << "list head_: " << list.front() << std::endl;
  std::cout << "list tail_: " << list.back() << std::endl;

  ForwardList<int> forward_list;
  forward_list.push_front(6);
  forward_list.push_front(3);
  forward_list.push_front(2);
  forward_list.push_front(1);
  forward_list.insert_after(3, 4);
  forward_list.insert_after(4, 5);

  while(forward_list.size() > 0)
  {
    std::cout << forward_list.front() << std::endl;
    forward_list.pop_front();
  }
  return 0;
}