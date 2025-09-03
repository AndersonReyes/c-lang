#ifndef RESULT_HPP
#define RESULT_HPP

#include <expected>

namespace engine {
namespace core {

enum class Error {};

/// signal empty result, no value
class Empty {};
const Empty empty{};

template <typename T>
using Result = std::expected<T, Error>;

template <typename T>
Result<T> failure(Error err) {
  return std::unexpected(err);
}

template <typename T>
Result<T> success(T data) {
  return data;
}

}  // namespace core
}  // namespace engine
#endif
