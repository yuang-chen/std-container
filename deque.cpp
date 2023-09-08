#include <iostream>
#include <vector>

template <typename T>
class Deque
{
  private:
  T**    blocks;
  size_t block_size;
  size_t num_blocks;
  size_t blocks_used;
  size_t block_front;
  size_t block_back;
  size_t index_front;
  size_t index_back;
  size_t size_;

  public:
  Deque();
  ~Deque();
  void   push_back(T elem);
  void   push_front(T elem);
  void   pop_back();
  void   pop_front();
  T      front();
  T      back();
  bool   empty();
  T&     at(size_t index);
  T&     operator[](size_t index);
  size_t size() const;
};

template <typename T>
Deque<T>::Deque()
{
  num_blocks = 5;
  block_size = 8;
  blocks     = new T*[num_blocks];
  for(int i = 0; i < num_blocks; i++)
  {
    blocks[i] = new T[block_size];    // elements are not initialized
  }
  // the starting block is the middle block
  block_front = num_blocks / 2;
  block_back  = num_blocks / 2;
  // the starting index of element is at the middle of the block
  index_front = block_size / 2;
  index_back  = block_size / 2 - 1;    // ensures start with empty
  blocks_used = 0;
  size_       = 0;
}

template <typename T>
Deque<T>::~Deque()
{
  for(int i = 0; i < num_blocks; i++)
  {
    delete[] blocks[i];
  }
  delete[] blocks;
}
/**
 * case breakdown:
 * 0. deque is empty
 *   * just add the element
 * 1. current block is not full
 *   * just add the element
 * 2. current block is full --> further breakdown:
 * 2.1. there is space in the next block
 *   * store the element in next block
 *   * update the indexes
 * 2.2. there is no space in the next block
 *   * create new blocks
 *   * copy the elements to the new blocks
 *   * delete the old blocks
 *   * update the indexes
 */

template <typename T>
void Deque<T>::push_back(T elem)
{
  //if the deque is empty
  if(size_ == 0)
  {
    blocks_used                      = 1;
    blocks[block_back][++index_back] = elem;
    size_++;
    return;
  }
  // if the block is not full
  if(index_back < block_size - 1)
  {
    blocks[block_back][++index_back] = elem;
    size_++;
    return;
  }
  // *********************
  // if current block is full
  //***********************
  // if the next block is not full, move to it
  if(block_back < num_blocks - 1)
  {
    index_back                       = 0;
    blocks[++block_back][index_back] = elem;
    size_++;
    blocks_used++;
    return;
  }

  // if the next block is full, allocate new blocks
  //  0 1 1 1 -> 0 0 1 1 1 1 0 0  (8-3)/2 = 2
  size_t old_block_front = block_front;
  num_blocks *= 2;
  index_back = 0;
  blocks_used++;
  size_++;
  block_front    = (num_blocks - blocks_used) / 2;
  block_back     = block_front + blocks_used - 1;
  T** new_blocks = new T*[num_blocks];
  for(size_t i = 0; i < block_front; i++)
  {
    new_blocks[i] = new T[block_size];    // allocate new blocks
  }
  for(size_t i = block_front; i < block_back; i++)
  {
    new_blocks[i] = blocks[old_block_front++];    // reuse old blocks
  }
  for(size_t i = block_back; i < num_blocks; i++)
  {
    new_blocks[i] = new T[block_size];    // allocate new blocks
  }
  new_blocks[block_back][0] = elem;
  // only delete the ptrptr**
  T** temp = blocks;
  blocks   = new_blocks;
  delete[] temp;

  // std::cout << "Blocks:      " << num_blocks << std::endl;
  // std::cout << "Blocks used: " << blocks_used << std::endl;
  // std::cout << "Block front: " << block_front << std::endl;
  // std::cout << "Block back:  " << block_back << std::endl;
  // std::cout << "Index front: " << index_front << std::endl;
  // std::cout << "Index back:  " << index_back << std::endl;
  // std::cout << std::endl << std::endl;
}
// reverse the push_back
template <typename T>
void Deque<T>::push_front(T elem)
{
  //if the deque is empty
  if(size_ == 0)
  {
    blocks_used                        = 1;
    blocks[block_front][--index_front] = elem;
    size_++;
    return;
  }
  // if the block is not full
  if(index_front > 0)
  {
    blocks[block_front][--index_front] = elem;
    size_++;
    return;
  }
  // *********************
  // if the block is full
  //***********************
  // if the prior block is not full, move to it
  if(block_front > 0)
  {
    index_front                        = block_size - 1;
    blocks[--block_front][index_front] = elem;
    size_++;
    blocks_used++;
    return;
  }

  // if the next block is full, allocate new blocks
  //   1 1 1 0 -> 0 0 1 1 1 1 0 0  (8-3)/2 = 2
  size_t old_block_front = block_front;
  num_blocks *= 2;
  index_front = block_size - 1;
  blocks_used++;
  size_++;
  block_front    = (num_blocks - blocks_used) / 2;
  block_back     = block_front + blocks_used - 1;
  T** new_blocks = new T*[num_blocks];
  for(size_t i = 0; i < block_front; i++)
  {
    new_blocks[i] = new T[block_size];    // allocate new blocks
  }
  for(size_t i = block_front; i < block_back; i++)
  {
    new_blocks[i] = blocks[old_block_front++];    // reuse old blocks
  }
  for(size_t i = block_back; i < num_blocks; i++)
  {
    new_blocks[i] = new T[block_size];    // allocate new blocks
  }
  new_blocks[block_front][index_front] = elem;
  // only delete the ptrptr**
  T** temp = blocks;
  blocks   = new_blocks;
  delete[] temp;

  // std::cout << "Blocks:      " << num_blocks << std::endl;
  // std::cout << "Blocks used: " << blocks_used << std::endl;
  // std::cout << "Block front: " << block_front << std::endl;
  // std::cout << "Block back:  " << block_back << std::endl;
  // std::cout << "Index front: " << index_front << std::endl;
  // std::cout << "Index back:  " << index_back << std::endl;
  // std::cout << std::endl << std::endl;
}

template <typename T>
void Deque<T>::pop_back()
{
  if(size_ == 0)
    return;
  // if the back index is not 0
  size_--;
  blocks[block_back][index_back] = std::numeric_limits<T>::max();    // register an error signal
  index_back--;
  // if the back index is 0, move to prior block
  if(index_back == std::numeric_limits<size_t>::max())    // if(int(index_back) == -1)
  {
    index_back = block_size - 1;
    block_back--;
  }
}

template <typename T>
void Deque<T>::pop_front()
{
  if(size_ == 0)
  {
    return;
  }
  // if the back index is not 0
  size_--;
  blocks[block_front][index_front] = std::numeric_limits<T>::max();    // register an error signal
  index_front++;
  // if the back index is 0
  if(index_front == block_size)
  {
    block_front++;
    index_front = 0;
  }
}

template <typename T>
T Deque<T>::back()
{
  return blocks[block_back][index_back];
}

template <typename T>
T Deque<T>::front()
{
  return blocks[block_front][index_front];
}
template <typename T>
bool Deque<T>::empty()
{
  return size_ == 0;
}
template <typename T>
T& Deque<T>::operator[](size_t index)    // do not perform boundary checking
{
  const size_t remain = block_size - index_front;
  if(index < remain)
  {
    return blocks[block_front][index_front + index];
  }
  size_t curr_block = block_front + (index + remain) / block_size;
  size_t curr_index = (index + remain) % block_size;
  return blocks[curr_block][curr_index];
}

template <typename T>
T& Deque<T>::at(size_t index)    // perform boundary checking
{
  if(index >= size_)
  {
    throw std::out_of_range("Deque::at() index out of range");
  }
  const size_t remain = block_size - index_front;
  if(index < remain)
  {
    return blocks[block_front][index_front + index];
  }
  const size_t curr_block = block_front + (index + remain) / block_size;
  const size_t curr_index = (index + remain) % block_size;
  return blocks[curr_block][curr_index];
}

template <typename T>
size_t Deque<T>::size() const
{
  return size_;
}

int main()
{
  Deque<int> deq;
  std::cout << "-----push_back test-----" << std::endl;
  for(int i = 0; i < 21; i++)
  {
    deq.push_back(i);
    std::cout << deq.back() << ' ';
  }
  std::cout << "\n-----pop_back test-----" << std::endl;
  for(int i = 0; i < 21; i++)
  {
    std::cout << deq.back() << ' ';
    deq.pop_back();
  }
  std::cout << "\n-----push_front test-----" << std::endl;
  for(int i = 0; i < 21; i++)
  {
    deq.push_front(i);
    std::cout << deq.front() << ' ';
  }
  std::cout << "\n-----pop_front test-----" << std::endl;
  for(int i = 0; i < 21; i++)
  {
    std::cout << deq.front() << ' ';
    deq.pop_front();
  }
  std::cout << "\n-----operator[] test-----" << std::endl;
  for(int i = 0; i < 11; i++)
    deq.push_back(i);
  for(int i = 0; i < 12; i++)
  {
    std::cout << deq[i] << ' ';
  }
  std::cout << "\n-----at() test-----" << std::endl;
  std::cout << deq.size() << std::endl;
  for(int i = 0; i < 12; i++)
  {
    std::cout << deq.at(i) << ' ';
  }
}