/**
 * @file
 * @brief Deque header file
 * @authors Pavlov Ilya
 *
 * Contains deque class
 */

#pragma once

#include <memory>
#include <stdexcept>
#include <type_traits>
#include <iostream>

/**
 * @brief Deque class.
 * @tparam T deque elements type
 * @tparam Allocator allocator type
 */
template <typename T, typename Allocator = std::allocator<T>>
class deque {
private:
  /**
   * @brief deque iterator class 
   * @tparam T deque elements type
   * @tparam Allocator allocator type
   */
  template <bool IsConst>
  class common_iterator : public std::iterator<std::random_access_iterator_tag, T> {
    friend class deque;

  private:
    T** data; ///< pointer to array of arrays
    size_t i; ///< index in dynamic array
    size_t j; ///< index in fixed-size array

    /**
     * Constructor from pointer to data and indexes
     * @pram[in] data pointer to array of arrays
     * @pram[in] i index in dynamic array
     * @pram[in] j index in fixed-size array
     */
    common_iterator(T** data, size_t i, size_t j) : data(data), i(i), j(j) {};

  public:
    /**
     * Default constructor
     */
    common_iterator() = default;

    /**
     * Copy constructor
     * @param[in] other iterator to copy
     */
    common_iterator(common_iterator const& other) noexcept {
      data = other.data;
      i = other.i;
      j = other.j;
    }

    /**
     * Copy assignment operator
     * @param[in] other iterator to copy
     * @return reference to this iterator
     */
    common_iterator& operator=(common_iterator const& other) noexcept {
      data = other.data;
      i = other.i;
      j = other.j;
      return *this;
    }

    /**
     * Dereference operator *
     * @return reference (const reference for const iterator) to the pointed-to element 
     */
    std::conditional_t<IsConst, T const&, T&> operator*() const noexcept {
      return data[i][j];
    }

    /**
     * Dereference operator ->
     * @return pointer (const pointer for const iterator) to the pointed-to element
     */
    std::conditional_t<IsConst, T const*, T*> operator->() const noexcept {
      return data[i] + j;
    }

    /**
     * Prefix increment
     * @return reference to this iterator
     */
    common_iterator& operator++() noexcept {
      ++j;
      if (j == FIXED_ARRAY_SIZE) {
        j = 0;
        ++i;
      }
      return *this;
    }

    /**
     * Postfix increment
     * @return previous value of this iterator
     */
    common_iterator operator++(int) noexcept {
      common_iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    /**
     * Prefix decrement
     * @return reference to this iterator
     */
    common_iterator& operator--() noexcept {
      --j;
      if (j == -1) {
        j = FIXED_ARRAY_SIZE - 1;
        --i;
      }
      return *this;
    }

    /**
     * Postfix decrement
     * @return previous value of this iterator
     */
    common_iterator operator--(int) noexcept {
      common_iterator tmp = *this;
      --(*this);
      return tmp;
    }

    /**
     * Equality operator
     * @param[in] other iterator to compare
     * @return true if iterators point to the same element else false
     */
    bool operator==(common_iterator const& other) const noexcept {
      return i == other.i && j == other.j;
    }

    /**
     * Inequality operator
     * @param[in] other iterator to compare
     * @return true if iterators point to the different elements else false
     */
    bool operator!=(common_iterator const& other) const noexcept {
      return !(*this == other);
    }

    /**
     * Equality operator
     * @param[in] other iterator to compare
     * @return true if the first iterator point to element to the left of the second iterator point-to else false
     */
    bool operator<(common_iterator const& other) const noexcept {
      if (i < other.i)
        return true;
      else if (i > other.i)
        return false;
      else
        return j < other.j;
    }

    /**
     * Equality operator
     * @param[in] other iterator to compare
     * @return true if the first iterator point to element to the left of the second iterator point-to or they equal else false
     */
    bool operator<=(common_iterator const& other) const noexcept {
      return *this < other || *this == other;
    }

    /**
     * Equality operator
     * @param[in] other iterator to compare
     * @return true if the first iterator point to element to the right of the second iterator point-to else false
     */
    bool operator>(common_iterator const& other) const noexcept {
      return !(*this <= other);
    }

    /**
     * Equality operator
     * @param[in] other iterator to compare
     * @return true if the first iterator point to element to the right of the second iterator point-to or they equal else false
     */
    bool operator>=(common_iterator const& other) const noexcept {
      return !(*this < other);
    }

    /**
     * Shift this iterator to the right
     * @param[in] n number of positions
     * @return reference to this iterator
     */
    common_iterator& operator+=(difference_type n) noexcept {
      if (n < 0)
        return *this -= n;
      if (n < (difference_type)(FIXED_ARRAY_SIZE - j)) {
        j += n;
      }
      else {
        n -= (difference_type)(FIXED_ARRAY_SIZE - j);
        i += n / FIXED_ARRAY_SIZE + 1;
        j = n % FIXED_ARRAY_SIZE;
      }

      return *this;
    }
    
    /**
     * Shift iterator to the right
     * @param[in] n number of positions
     * @return result iterator
     */
    common_iterator operator+(difference_type n) const noexcept {
      common_iterator tmp = *this;
      tmp += n;
      return tmp;
    }

    /**
     * Shift iterator to the right
     * @param[in] n number of positions
     * @param[in] it iterator to shift
     * @return result iterator
     */
    friend common_iterator operator+(difference_type n, common_iterator const& it) noexcept {
      return it + n;
    }

    /**
     * Shift this iterator to the left
     * @param[in] n number of positions
     * @return reference to this iterator
     */
    common_iterator& operator-=(difference_type n) noexcept {
      if (n < 0)
        return *this += n;
      if (n <= (difference_type)j) {
        j -= n;
      }
      else {
        n -= (difference_type)j;
        i -= n / FIXED_ARRAY_SIZE + 1;
        j = FIXED_ARRAY_SIZE - n % FIXED_ARRAY_SIZE;
        if (j == FIXED_ARRAY_SIZE) {
          j = 0;
          ++i;
        }
      }

      return *this;
    }

    /**
     * Shift iterator to the right
     * @param[in] n number of positions
     * @return result iterator
     */
    common_iterator operator-(difference_type n) const noexcept {
      common_iterator tmp = *this;
      tmp -= n;
      return tmp;
    }

    /**
     * Difference between iterators
     * @param[in] other other iterator 
     * @return number n: other + n == *this
     */
    difference_type operator-(common_iterator const& other) const noexcept {
      return (i * FIXED_ARRAY_SIZE + j) - (other.i * FIXED_ARRAY_SIZE + other.j);
    }
  };

  static constexpr size_t FIXED_ARRAY_SIZE = 4;         ///< size of fixed-size arrays
  static constexpr size_t DYNAMIC_ARRAY_START_SIZE = 3; ///< dynamic array start size

  using alloc_traits = std::allocator_traits<Allocator>;

  template <typename T>
  using PtrAllocator = typename alloc_traits::template rebind_alloc<T*>; ///< type of allocator for dynamic array

  template <typename T>
  using ptr_alloc_traits = typename alloc_traits::template rebind_traits<T*>;

  T** data = nullptr;           ///< dynamic array of fixed-size arrays
  size_t _size = 0;             ///< number of elements in deque
  size_t _max_size = 0;         ///< max number of elements that can be pushed without resizing
  size_t dynamic_arr_size = 0;  ///< size of the dynamic array

  size_t first_i = DYNAMIC_ARRAY_START_SIZE / 2;  ///< index of the first element in dynamic array
  size_t first_j = 0;                             ///< index of the first element in fixed-size array
  size_t last_i = first_i;                        ///< index of last element in dynamic array
  size_t last_j = first_j;                         ///< index of last element in fixed-size array

  Allocator alloc;            ///< allocator for fixed-size arrays of elemetns
  PtrAllocator<T> ptr_alloc;  ///< allocator for dynamic array of pointers

  /*
   * Clear deque and deallocate memory 
   */
  void _clear_with_deallocate() noexcept {
    for (size_t i = 0; i < dynamic_arr_size; ++i) {
      size_t j = 0;
      size_t end = FIXED_ARRAY_SIZE;
      if (i == first_i)
        j = first_j;
      if (i == last_i)
        end = last_j;

      for (; i >= first_i && i <= last_i && j < end; ++j) {
        alloc_traits::destroy(alloc, data[i] + j);
      }
      alloc_traits::deallocate(alloc, data[i], FIXED_ARRAY_SIZE);
    }
    ptr_alloc_traits<T>::deallocate(ptr_alloc, data, dynamic_arr_size);

    _size = 0;
    _max_size = 0;
    dynamic_arr_size = 0;
    data = nullptr;
  }

  /**
   * Copy other deque
   * param[in] otehr deque to copy
   */
  void _copy(deque const& other) {
    alloc = alloc_traits::select_on_container_copy_construction(other.alloc);
    ptr_alloc = ptr_alloc_traits<T>::select_on_container_copy_construction(other.ptr_alloc);

    _size = other._size;
    _max_size = other._max_size;
    dynamic_arr_size = other.dynamic_arr_size;
    first_i = other.first_i;
    first_j = other.first_j;
    last_i = other.last_i;
    last_j = other.last_j;

    try {
      data = ptr_alloc_traits<T>::allocate(ptr_alloc, dynamic_arr_size);
    }
    catch (...) {
      throw;
    }

    for (size_t i = 0; i < dynamic_arr_size; ++i) {
      try {
        data[i] = alloc_traits::allocate(this->alloc, FIXED_ARRAY_SIZE);
      }
      catch (...) {
        for (size_t j = 0; j < i; ++j) {
          alloc_traits::deallocate(this->alloc, data[i], FIXED_ARRAY_SIZE);
        }
        ptr_alloc_traits<T>::deallocate(ptr_alloc, data, dynamic_arr_size);
        dynamic_arr_size = 0;
        throw;
      }
    }

    if (first_i == last_i) {
      for (size_t j = first_j; j < last_j; ++j)
        alloc_traits::construct(alloc, data[first_i] + j, other.data[first_i][j]);
    }
    else {
      for (size_t j = first_j; j < FIXED_ARRAY_SIZE; ++j)
        alloc_traits::construct(alloc, data[first_i] + j, other.data[first_i][j]);

      for (size_t i = first_i + 1; i < last_i; ++i) {
        for (size_t j = 0; j < FIXED_ARRAY_SIZE; ++j)
          alloc_traits::construct(alloc, data[i] + j, other.data[i][j]);
      }

      for (size_t j = 0; j < last_j; ++j)
        alloc_traits::construct(alloc, data[last_i] + j, other.data[last_i][j]);
    }
  }

  /**
   * Move other deque
   * param[in] otehr deque to move
   */
  void _move(deque& other) {
    if (alloc_traits::propagate_on_container_move_assignment::value && alloc != other.alloc) {
      try {
        alloc = std::move(other.alloc);
        ptr_alloc = std::move(other.ptr_alloc);
      }
      catch (...) {
        throw;
      }
    }

    data = other.data;
    _size = other._size;
    _max_size = other._max_size;
    dynamic_arr_size = other.dynamic_arr_size;
    first_i = other.first_i;
    first_j = other.first_j;
    last_i = other.last_i;
    last_j = other.last_j;

    other.data = nullptr;
    other._size = 0;
    other._max_size = 0;
    other.dynamic_arr_size = 0;
    other.first_i = 0;
    other.first_j = 0;
    other.last_i = 0;
    other.last_j = 0;
  }

  /**
   * Increase dynamic array max size
   * param[in] shift false to increase on the right or true to increase to the left
   */
  void _increase_size(bool shift) {
    T** new_dynamic_arr;

    try {
      new_dynamic_arr = ptr_alloc_traits<T>::allocate(ptr_alloc, dynamic_arr_size + 1);
    }
    catch (std::bad_alloc) {
      throw;
    }

    T* new_fixed_arr;
    try {
      new_fixed_arr = alloc_traits::allocate(alloc, FIXED_ARRAY_SIZE);
    }
    catch (std::bad_alloc) {
      throw;
    }

    for (size_t i = 0; i < dynamic_arr_size; ++i)
      new_dynamic_arr[i + shift] = data[i];

    new_dynamic_arr[shift ? 0 : dynamic_arr_size] = new_fixed_arr;

    first_i += shift;
    last_i += shift;

    ptr_alloc_traits<T>::deallocate(ptr_alloc, data, dynamic_arr_size);
    data = new_dynamic_arr;
    ++dynamic_arr_size;
    _max_size += FIXED_ARRAY_SIZE;
  }

  /**
   * Reduce dynamic array max size and deallocate memory
   * param[in] side false to cut on the right or true to cut to the left
   * param[in] new_array_size new dynamic array size
   */
  void _reduce_size(bool side, size_t new_array_size) {
    if (dynamic_arr_size <= new_array_size || !new_array_size)
      return;

    T** new_arr;
    try {
      new_arr = ptr_alloc_traits<T>::allocate(ptr_alloc, new_array_size);
    }
    catch (std::bad_alloc) {
      throw;
    }

    size_t lborder = side ? dynamic_arr_size - new_array_size : 0;
    size_t rborder = side ? dynamic_arr_size : new_array_size;
    size_t j = 0;
    for (size_t i = lborder; i < rborder; ++i, ++j)
      new_arr[j] = data[i];

    lborder = side ? 0 : new_array_size;
    rborder = side ? dynamic_arr_size - new_array_size : dynamic_arr_size;
    for (size_t i = lborder; i < rborder; ++i)
      alloc_traits::deallocate(alloc, data[i], FIXED_ARRAY_SIZE);
   
    ptr_alloc_traits<T>::deallocate(ptr_alloc, data, dynamic_arr_size);
    last_i -= side * (dynamic_arr_size - new_array_size);
    first_i -= side * (dynamic_arr_size - new_array_size);
    data = new_arr;
    dynamic_arr_size = new_array_size;
    _max_size = dynamic_arr_size * FIXED_ARRAY_SIZE;
  }

public:
  using iterator = common_iterator<false>;
  using const_iterator = common_iterator<true>;

  /*
   * Begin of deque 
   * @return iterator pointed to the first element of deque 
   */
  iterator begin() const noexcept{
    return iterator(data, first_i, first_j);
  }

  /*
   * End of deque
   * @return iterator pointed to the next after last element of deque
   * @warning dereferencing can cause undefined behaviour
   */
  iterator end() const noexcept{
    return iterator(data, last_i, last_j);
  }

  /*
   * Begin of deque
   * @return const iterator pointed to the first element of deque
   */
  const_iterator cbegin() const noexcept {
    return const_iterator(data, first_i, first_j);
  }

  /*
   * End of deque
   * @return const iterator pointed to the next after last element of deque
   * @warning dereferencing can cause undefined behaviour
   */
  const_iterator cend() const noexcept {
    return const_iterator(data, last_i, last_j);
  }

  /**
   * Constructor of empty deque
   * param[in] alloc allocator to use in deque
   */
  deque(Allocator const& alloc = Allocator()) : alloc(alloc), ptr_alloc(alloc) {
    this->alloc = alloc;
    try {
      data = ptr_alloc_traits<T>::allocate(ptr_alloc, DYNAMIC_ARRAY_START_SIZE);
    }
    catch (...) {
      throw;
    }
    dynamic_arr_size = DYNAMIC_ARRAY_START_SIZE;
    for (size_t i = 0; i < dynamic_arr_size; ++i) {
      try {
        data[i] = alloc_traits::allocate(this->alloc, FIXED_ARRAY_SIZE);
      }
      catch (...) {
        for (size_t j = 0; j < i; ++j) {
          alloc_traits::deallocate(this->alloc, data[i], FIXED_ARRAY_SIZE);
        }
        ptr_alloc_traits<T>::deallocate(ptr_alloc, data, dynamic_arr_size);
        dynamic_arr_size = 0;
        throw;
      }
    }
    _max_size = DYNAMIC_ARRAY_START_SIZE * FIXED_ARRAY_SIZE;
  };
  
  /**
   * Constructor of deque with the same elements
   * param[in] count number of elements
   * param[in] value value of elemnts
   * param[in] alloc allocator to use in deque
   */
  deque(size_t count, T const& value = T(), Allocator const& alloc = Allocator()) : alloc(alloc), ptr_alloc(alloc) {
    dynamic_arr_size = count / FIXED_ARRAY_SIZE + 1;
    try {
      data = ptr_alloc_traits<T>::allocate(ptr_alloc, dynamic_arr_size);
    }
    catch (std::bad_alloc){
      dynamic_arr_size = 0;
      throw;
    }

    for (size_t i = 0; i < dynamic_arr_size; ++i) {
      try {
        data[i] = alloc_traits::allocate(this->alloc, FIXED_ARRAY_SIZE);
      }
      catch (...) {
        for (size_t j = 0; j < i; ++j) {
          alloc_traits::deallocate(this->alloc, data[i], FIXED_ARRAY_SIZE);
        }
        ptr_alloc_traits<T>::deallocate(ptr_alloc, data, dynamic_arr_size);
        dynamic_arr_size = 0;
        throw;
      }
    }

    _max_size = dynamic_arr_size * FIXED_ARRAY_SIZE;
    first_i = dynamic_arr_size / 2;
    first_j = 0;
    last_i = first_i;
    last_j = first_j;

    for (size_t i = 0; i < count; ++i)
      push_back(value);
  }
  
  /**
   * Copy constructor
   * param[in] other deque to copy
   */
  deque(deque const& other) {
    try {
      _copy(other);
    }
    catch (std::bad_alloc) {
      throw;
    }
  }

  /**
   * Move constructor
   * param[in] other deque to move
   */
  deque(deque&& other) {
    try {
      _move(other);
    }
    catch (...) {
      throw;
    }
  }
  
  /**
   * Copy assigment operator
   * param[in] other deque to copy
   * @return reference to this deque
   */
  deque& operator=(deque const& other) {
    if (this == &other)
      return *this;

    _clear_with_deallocate();

    try {
      _copy(other);
    }
    catch (...) {
      throw;
    }

    return *this;
  }
  
  /**
   * Move assigment operator
   * param[in] other deque to move
   * @return reference to this deque
   */
  deque& operator=(deque&& other) noexcept {
    if (this == &other)
      return *this;

    _clear_with_deallocate();
     _move(other);

    return *this;
  }
  
  /**
   * Get element by number of position
   * param[in] pos number of position
   * @return reference to element at this position
   */
  T& at(size_t pos) const {
    if (pos >= _size)
      throw std::out_of_range("index out of range");

    return (*this)[pos];
  }

  /**
   * Get element by number of position
   * param[in] pos number of position
   * @return reference to element at this position
   * @warning does not throw out of range exception
   */
  T& operator[](size_t pos) const noexcept {
    if (pos < FIXED_ARRAY_SIZE - first_j)
      return data[first_i][first_j + pos];

    size_t i = first_i + 1;
    pos -= FIXED_ARRAY_SIZE - first_j;
    i += pos / FIXED_ARRAY_SIZE;
    size_t j = pos % FIXED_ARRAY_SIZE;

    return data[i][j];
  }
  
  /**
   * Get the first element of deque
   * @return reference to the first element of deque
   */
  T& front() const noexcept {
    return data[first_i][first_j];
  }

  /**
   * Get lst element of deque
   * @return reference to the last element of deque
   */
  T& back() const noexcept {
    return (*this)[_size - 1];
  }
  
  /**
   * Check if deque is empty
   * @return true if deque is empty else false
   */
  bool empty() const noexcept {
    return _size == 0;
  }
  
  /**
   * Get number of elemetn in deque
   * @return number of elemetn in deque
   */
  size_t size() const noexcept {
    return _size;
  }

  /**
   * Get capacity of deque
   * @return capacity of deque
   */
  size_t max_size() const noexcept {
    return _max_size;
  }
  
  /**
   * Add element to the end of deque
   * pram[in] value element to add
   */
  template <typename T> // universal reference
  void push_back(T&& value) {
    if (data == nullptr)
      *this = deque();

    size_t tmp_last_i = last_i;
    size_t tmp_last_j = last_j;
    size_t i = last_i;
    size_t j = last_j++;

    if (last_j == FIXED_ARRAY_SIZE) {
      ++last_i;
      last_j = 0;
    }

    if (i >= dynamic_arr_size) {
      try {
        _increase_size(false);
      }
      catch (std::bad_alloc) {
        last_i = tmp_last_i;
        last_j = tmp_last_j;
        throw;
      }
    }

    alloc_traits::construct(alloc, data[i] + j, std::forward<T>(value));
    ++_size;
  }
  
  /**
   * Construct element in the end of deque
   * pram[in] args constructor parameters
   */
  template <typename... Args>
  void emplace_back(Args&&... args)  {
    if (data == nullptr)
      *this = deque();

    size_t tmp_last_i = last_i;
    size_t tmp_last_j = last_j;
    size_t i = last_i;
    size_t j = last_j++;

    if (last_j == FIXED_ARRAY_SIZE) {
      ++last_i;
      last_j = 0;
    }

    if (i >= dynamic_arr_size) {
      try {
        _increase_size(false);
      }
      catch (std::bad_alloc) {
        last_i = tmp_last_i;
        last_j = tmp_last_j;
        throw;
      }
    }

    alloc_traits::construct(alloc, data[i] + j, std::forward<Args>(args)...);
    ++_size;
  }
  
  /**
   * Add element to the front of deque
   * pram[in] value element to add
   */
  template <typename T> // universal reference
  void push_front(T&& value) {
    if (data == nullptr)
      *this = deque();

    --first_j;

    if (first_j == SIZE_MAX) {
      if (first_i == 0) {
        try {
          _increase_size(true);
        }
        catch (std::bad_alloc) {
          first_j = 0;
          throw;
        }
      }
      --first_i;
      first_j = FIXED_ARRAY_SIZE - 1;
    }

    alloc_traits::construct(alloc, data[first_i] + first_j, std::forward<T>(value));
    ++_size;
  }

  /**
   * Construct element in the front of deque
   * pram[in] args constructor parameters
   */
  template<typename... Args>
  void emplace_front(Args&&... args) {
    if (data == nullptr)
      *this = deque();

    --first_j;

    if (first_j == SIZE_MAX) {
      if (first_i == 0) {
        try {
          _increase_size(true);
        }
        catch (std::bad_alloc) {
          first_j = 0;
          throw;
        }
      }
      --first_i;
      first_j = FIXED_ARRAY_SIZE - 1;
    }

    alloc_traits::construct(alloc, data[first_i] + first_j, std::forward<Args>(args)...);
    ++_size;
  }
  
  /**
   * Remove element from the back of deque
   */
  void pop_back() {
    --last_j;
    if (last_j == SIZE_MAX) {
      --last_i;
      last_j = FIXED_ARRAY_SIZE - 1;
    }

    alloc_traits::destroy(alloc, data[last_i] + last_j);

    if (last_i < dynamic_arr_size / 2)
      _reduce_size(false, dynamic_arr_size / 2 + 1);

    --_size;
  }
  
  /**
   * Remove element from the front of deque
   */
  void pop_front() {
    alloc_traits::destroy(alloc, data[first_i] + first_j);

    ++first_j;
    if (first_j == FIXED_ARRAY_SIZE) {
      ++first_i;
      first_j = 0;
    }

    if (first_i > dynamic_arr_size / 2)
      _reduce_size(true, dynamic_arr_size / 2 + 1);

    --_size;
  }

  /**
   * Remove all elements
   */
  void clear() noexcept{
    if (first_i == last_i) {
      for (size_t j = first_j; j < last_j; ++j)
        alloc_traits::destroy(alloc, data[first_i] + j);
    }
    else {
      for (size_t j = first_j; j < FIXED_ARRAY_SIZE; ++j)
        alloc_traits::destroy(alloc, data[first_i] + j);

      for (size_t i = first_i + 1; i < last_i; ++i) {
        for (size_t j = 0; j < FIXED_ARRAY_SIZE; ++j)
          alloc_traits::destroy(alloc, data[i] + j);
      }

      for (size_t j = 0; j < last_j; ++j)
        alloc_traits::destroy(alloc, data[last_i] + j);
    }
    _reduce_size(false, DYNAMIC_ARRAY_START_SIZE);
    first_i = DYNAMIC_ARRAY_START_SIZE / 2;
    first_j = 0;
    last_i = first_i;
    last_j = first_j;
    _size = 0;
  }

  /**
   * Friend operator<< to print deque elements 
   * @param[in] out output stream
   * @param[in] deque deque to output
   * @return reference to stream
   */
  friend std::ostream& operator<<(std::ostream& out, deque const& deque) {
    for (auto& el : deque) {
      out << el << " ";
    }
    return out;
  }
  
  /**
   * Just destructor 
   */
  ~deque() {
    _clear_with_deallocate();
  }
};
