#ifndef FORMAT_HPP
#define FORMAT_HPP

#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace da {
namespace utils {

size_t from_chars(std::string_view::const_iterator first, std::string_view::const_iterator last);

template <typename T>
[[nodiscard]] std::string to_string(T const &);

template <typename T>
std::string to_string(T const &value) {
    return std::to_string(value);
}

namespace {

template <typename... Args>
[[nodiscard]] std::string format_impl(std::string_view format_line, std::vector<std::string> &formatted, Args const &... args);
template <typename T, typename... Args>
[[maybe_unused]] std::string format_impl(std::string_view format_line, std::vector<std::string> &formatted, T const &current,
                                         Args const &... args) {
    formatted.push_back(to_string(current));
    return format_impl(format_line, formatted, args...);
}

template <>
std::string format_impl(std::string_view format_line, std::vector<std::string> &formatted) {
    std::string result{};
    bool is_escaped{false};
    for (auto it = format_line.begin(); it != format_line.end(); ++it) {
        if (is_escaped) {
            is_escaped = false;
            if (*it != '{' && *it != '}' && *it != '%') {
                result += '%';
            }
            result += *it;
        } else if (*it == '%') {
            is_escaped = true;
        } else if (*it == '}') {
            throw std::runtime_error("format:\n\tUnescaped \'}\'");
        } else if (*it == '{') {
            auto finish = std::find(++it, format_line.end(), '}');
            if (finish == format_line.end()) {
                throw std::runtime_error("format:\n\tUnescaped \'{\'");
            }
            result += formatted[from_chars(it, finish)];
            it = finish;
        } else {
            result += *it;
        }
    }
    if (is_escaped) {
        throw std::runtime_error("format:\n\tFormat lines ends with not escaped \'%\'");
    }
    return result;
}
}  // namespace

template <typename... Args>
[[nodiscard]] std::string format(std::string_view format_line, Args const &... args) {
    std::vector<std::string> tmp;
    return format_impl(format_line, tmp, args...);
}

}  // namespace utils
}  // namespace da

#endif  // FORMAT_HPP
