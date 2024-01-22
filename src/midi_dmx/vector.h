/**
 * @file vector.h
 * @author Christian Neukam
 * @brief Utilities of the mididmxbridge library.
 * @version 1.0
 * @date 2024-01-12
 *
 * @copyright Copyright 2024 Christian Neukam. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef __MIDIDMXBRIDGE_VECTOR_H__
#define __MIDIDMXBRIDGE_VECTOR_H__

#include <stdint.h>

namespace mididmxbridge {
/**
 * @brief This class provides a simple implementation of the std::vector class in case the C++ STL
 * is not available.
 *
 * @warning This class is not standard compliant.
 *
 * @tparam T - The type of the elements.
 */
template <class T>
class vector {
 public:
  /**
   * @brief Construct a new vector object.
   *
   * Default constructor. Constructs an empty container with a default-constructed allocator.
   *
   * @see 1): https://en.cppreference.com/w/cpp/container/vector/vector
   *
   */
  vector() { mData = new T[mCapacity]; }

  /**
   * @brief Construct a new vector object.
   *
   * Constructs the container with count default-inserted instances of T. No copies are made.
   *
   * @see 4): https://en.cppreference.com/w/cpp/container/vector/vector
   *
   * @param count the size of the container
   */
  vector(const uint8_t count) {
    if (count < mMaxCapacity) {
      mSize = count;

      while (mSize > mCapacity) {
        mCapacity *= 2;
      }

    } else {
      mSize = mMaxCapacity;
      mCapacity = mMaxCapacity;
    }

    mData = new T[mCapacity];
  }

  /**
   * @brief Construct a new vector object.
   *
   * Constructs the container with the contents of the initializer array init.
   *
   * @see 10): https://en.cppreference.com/w/cpp/container/vector/vector
   *
   * @param count the size of the container
   * @param values the values to initialize elements of the container with
   */
  vector(const uint8_t count, const T values[]) {
    mData = new T[mCapacity];

    for (uint8_t idx = 0; idx < count; idx++) {
      push_back(values[idx]);
    }
  }

  /**
   * @brief Destroy the vector object.
   *
   */
  ~vector() { delete[] mData; }

  /**
   * @brief Checks if the container has no elements.
   *
   * @see https://en.cppreference.com/w/cpp/container/vector/empty
   *
   * @return true if the container is empty
   * @return false otherwise
   */
  bool empty() const { return (0 == mSize) ? true : false; }

  /**
   * @brief Appends the given element value to the end of the container.
   *
   * @see https://en.cppreference.com/w/cpp/container/vector/push_back
   *
   * @param value 	the value of the element to append
   */
  void push_back(const T& value) {
    if (mSize == mCapacity) {
      resize();
    }

    if (mSize < mCapacity) {
      mData[mSize] = value;
      mSize++;
    }
  }

  /**
   * @brief Removes the last element of the container.
   *
   * @see https://en.cppreference.com/w/cpp/container/vector/pop_back
   *
   */
  void pop_back() {
    if (mSize > 0) {
      mSize--;
      mData[mSize] = T{};
    }
  }

  /**
   * @brief Returns the number of elements in the container.
   *
   * @return uint8_t - the number of elements in the container
   */
  uint8_t size() const { return mSize; }

  /**
   * @brief Returns the maximum number of elements the container is able to hold due to system or
   * library implementation limitations.
   *
   * @return uint8_t - the maximum number of elements.
   */
  uint8_t max_size() const { return mMaxCapacity; }

  /**
   * @brief Returns the number of elements that the container has currently allocated space for.
   *
   * @return uint8_t - the capacity of the currently allocated storage.
   */
  uint8_t capacity() const { return mCapacity; }

  ///@{
  /**
   * @brief Returns a reference to the element at specified location pos.
   *
   * @warning No bounds checking is performed.
   *
   * @param pos the position of the element to return
   * @return T& - the reference to the requested element.
   */
  T& operator[](uint8_t pos) { return mData[pos]; }
  const T& operator[](uint8_t pos) const { return mData[pos]; }
  ///@}

 private:
  /**
   * @brief Increase the capacity if the current capacity is no longer sufficient.
   *
   */
  void resize() {
    const uint8_t newCapacity = (mCapacity < (mMaxCapacity >> 1)) ? mCapacity << 1 : mMaxCapacity;

    if (newCapacity != mCapacity) {
      auto data = new T[newCapacity];

      for (uint8_t idx = 0; idx < mSize; idx++) {
        data[idx] = mData[idx];
      }

      delete mData;
      mData = data;
      mCapacity = newCapacity;
    }
  }

  const uint8_t mMaxCapacity = 128; /**< the maximum capacity, shall be < 256 */
  T* mData;                         /**< the raw data array */
  uint8_t mSize = 0;                /**< the current size of the container */
  uint8_t mCapacity = 16;           /**< the current capacity of the container */
};
}  // namespace mididmxbridge
#endif
