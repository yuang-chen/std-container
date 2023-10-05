#include <deque>
#include <iostream>

template <typename T, typename Container = std::deque<T>>
class Queue
{
  public:
  using container_type  = Container;
  using value_type      = typename Container::value_type;
  using size_type       = typename Container::size_type;
  using reference       = typename Container::reference;
  using const_reference = typename Container::const_reference;

  T& front()
  {
    return container.front();
  }

  T& back()
  {
    return container.back();
  }

  bool empty()
  {
    return container.empty();
  }

  size_type size()
  {
    return container.size();
  }

  void push(const T& value)
  {
    container.push_back(value);
  }

  void push(const T&& value)
  {
    container.push_back(std::move(value));
  }

  void pop()
  {
    container.pop_front();
  }

  private:
  Container container;
};

template <typename T, typename Container = std::deque<T>>
class Stack
{
  public:
  using container_type  = Container;
  using value_type      = typename Container::value_type;
  using size_type       = typename Container::size_type;
  using reference       = typename Container::reference;
  using const_reference = typename Container::const_reference;

  T& top()
  {
    return container.back();
  }

  bool empty()
  {
    return container.empty();
  }

  size_type size()
  {
    return container.size();
  }

  void push(const T& value)
  {
    container.push_back(value);
  }

  void push(const T&& value)
  {
    container.push_back(std::move(value));
  }

  void pop()
  {
    container.pop_back();
  }

  private:
  Container container;
};

int main()
{
  // Declare an empty queue of integers
  Queue<int> que;

  // Check if the queue is empty
  if(que.empty())
  {
    std::cout << "Queue is empty\n";
  }

  // Push elements onto the queue
  for(int i = 1; i <= 5; ++i)
  {
    std::cout << "Pushing " << i << " onto the queue\n";
    que.push(i);
  }

  // Display size of the queue
  std::cout << "Queue size: " << que.size() << "\n";

  // Access front and back elements
  std::cout << "Front element: " << que.front() << "\n";
  std::cout << "Back element: " << que.back() << "\n";

  // Pop elements from the queue
  while(!que.empty())
  {
    std::cout << "Popping " << que.front() << " from the queue\n";
    que.pop();
  }

  // Check if the queue is empty again
  if(que.empty())
  {
    std::cout << "Queue is now empty\n";
  }

  // Declare an empty stack of integers
  Stack<int> stack;

  // Check if the stack is empty
  if(stack.empty())
  {
    std::cout << "Stack is empty\n";
  }

  // Push elements onto the stack
  for(int i = 1; i <= 5; ++i)
  {
    std::cout << "Pushing " << i << " onto the stack\n";
    stack.push(i);
  }

  // Display size of the stack
  std::cout << "Stack size: " << stack.size() << "\n";

  // Access top element
  std::cout << "Top element: " << stack.top() << "\n";

  // Pop elements from the stack
  while(!stack.empty())
  {
    std::cout << "Popping " << stack.top() << " from the stack\n";
    stack.pop();
  }

  // Check if the stack is empty again
  if(stack.empty())
  {
    std::cout << "Stack is now empty\n";
  }
  return 0;
}
