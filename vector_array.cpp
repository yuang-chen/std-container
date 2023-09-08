#include <iostream>

template <typename T>
class Vector
{
  private:
  T*     data_;
  size_t size_;
  size_t capacity_;

  public:
  Vector() : data_(nullptr), size_(0), capacity_(0) {}

  Vector(size_t n_) : size_(n_), capacity_(n_)
  {
    data_ = new T[n_];
  }

  ~Vector()
  {
    delete[] data_;
  };

  T& operator[](size_t index)
  {
    return data_[index];
  }

  const T& operator[](size_t index) const
  {
    return data_[index];
  }

  size_t size() const
  {
    return size_;
  }

  void push_back(const T& value)
  {
    if(size_ == capacity_)
    {
      capacity_    = size_ == 0 ? 1 : 2 * capacity_;
      T* new_data_ = new T[capacity_];

      for(size_t i = 0; i < size_; i++)
      {
        new_data_[i] = data_[i];
      }
      delete[] data_;
      data_ = new_data_;
    }
    data_[size_] = value;
    size_++;
  }
};

template <typename T, size_t size_>
class Array
{
  private:
  T data_[size_];

  public:
  T& operator[](size_t index)
  {
    return data_[index];
  }

  const T& operator[](size_t index) const
  {
    return data_[index];
  }

  size_t size() const
  {
    return size_;
  }
};

int main()
{
  Vector<int> vec;
  vec.push_back(10);
  vec.push_back(2);
  for(int i = 0; i < vec.size(); i++)
    std::cout << vec[i] << '\n';

  Array<int, 3> arr{};
  arr[1] = 9;
  for(int i = 0; i < arr.size(); i++)
    std::cout << arr[i] << '\n';

  return 0;
}