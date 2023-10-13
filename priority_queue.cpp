#include <iostream>
#include <vector>

/*

A priority queue is a container adaptor that provides constant time lookup of the largest (by default) element,
at the expense of logarithmic insertion and extraction.

Structure Property:
The std::priority_queue typically uses a binary heap as the underlying data structure
A binary heap is a complete binary tree in which every level, except possibly the last, 
is *completely filled*, and all nodes are as *left* as possible.

Order Property:
for the max heap, std::less(parent->value, child->value) === false


For a given element at index i:
- The left child is at index 2i+1
- The right child is at index 2i+2
- The parent is at index (i−1)/2 (integer division)
*/

template <typename T,
          typename Container = std::vector<T>,
          typename Compare   = std::less<T> >
class PriorityQueue
{
  public:
  PriorityQueue()
  {
    make_heap(0, container.size() - 1, 0);
  }

  T& top()
  {
    return container.front();
  }

  void push(const T& value)
  {
    container.push_back(value);
    push_heap(0, container.size() - 1);
  }

  void pop()
  {
    if(container.empty())
    {
      return;
    }
    pop_heap();
    container.pop_back();
  }

  private:
  Container container;
  Compare   compare;

  //ensures the max heap property is maintained for the subtree rooted at i
  void heapify(size_t first, size_t last, size_t index)
  {
    const auto size    = last - first + 1;
    auto       left    = 2 * index + 1;
    auto       right   = 2 * index + 2;
    auto       largest = index;

    if(left < size && compare(container[largest], container[left]))
    {
      largest = left;
    }
    if(right < size && compare(container[largest], container[right]))
    {
      largest = right;
    }
    if(largest != index)
    {
      std::swap(container[index], container[largest]);
      heapify(first, last, largest);
    }
  }
  //builds a (max) heap from an unsorted range of elements.
  //It starts from the middle of the array and
  //heapifies each subtree in a bottom-up manner.
  void make_heap(size_t first, size_t last, size_t index)
  {
    const auto size = last - first + 1;
    for(int i = size / 2 - 1; i >= 0; i--)    // start from the middle node!
    {
      heapify(first, last, first + i);
    }
  }

  void pop_heap()
  {
    if(container.empty())
    {
      return;
    }
    std::swap(container.front(), container.back());
    heapify(0, container.size() - 2, 0);    // reconstruct the heap, excluding the last element
  }

  void push_heap(size_t first, size_t last)
  {
    auto index  = last;
    auto parent = first + (last - 1) / 2;

    while(index > first && compare(container[parent], container[index]))
    {
      std::swap(container[index], container[parent]);
      index  = parent;
      parent = first + (index - 1) / 2;
    }
  }
};

int main()
{
    PriorityQueue<int> pq;
    pq.push(10);
    pq.push(20);
    pq.push(15);
    std::cout << pq.top() << std::endl;  // Output: 20
    pq.pop();
    std::cout << pq.top() << std::endl;  // Output: 15
    pq.pop();
    std::cout << pq.top() << std::endl;  // Output: 10
  return 0;
}