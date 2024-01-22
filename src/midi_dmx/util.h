/**
 * @file util.h
 * @author Christian Neukam
 * @brief Utilities of the mididmxbridge library.
 * @version 1.0
 * @date 2023-12-25
 *
 * @copyright Copyright 2023 Christian Neukam. All rights reserved.
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
#ifndef __MIDIDMXBRIDGE_UTIL_H__
#define __MIDIDMXBRIDGE_UTIL_H__

namespace mididmxbridge::util {
/**
 * @brief constexpr definition of the min operation.
 *
 * @tparam T the type of the input data, e.g. uint8_t
 * @param[in] x the first value
 * @param[in] y the second value
 * @return T - the minimum value of x and y
 */
template <typename T>
constexpr T min_t(const T x, const T y) {
  return (x < y) ? x : y;
}

/**
 * @brief constexpr definition of the max operation.
 *
 * @tparam T the type of the input data, e.g. uint8_t
 * @param[in] x the first value
 * @param[in] y the second value
 * @return T - the maximum value of x and y
 */
template <typename T>
constexpr T max_t(const T x, const T y) {
  return (x > y) ? x : y;
}

/**
 * @brief calculate the absolute difference of two values.
 *
 * @tparam T the type of the input data, e.g. uint8_t
 * @param[in] x the first value
 * @param[in] y the second value
 * @return T - the absolute difference of \p x and \p y
 */
template <typename T>
constexpr T absDiff_t(const T x, const T y) {
  return (x > y) ? (x - y) : (y - x);
}
}  // namespace mididmxbridge::util
#endif
