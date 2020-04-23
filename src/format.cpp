#include "format.hpp"

size_t da::utils::from_chars(std::string_view::const_iterator first, std::string_view::const_iterator last) {
    if (last == first) {
        throw std::runtime_error("format:\n\tNo pos mentioned in {...}");
    }
    return std::accumulate(first, last, static_cast<size_t>(0), [](size_t lhs, char c) {
        if (c < '0' || c > '9') {
            throw std::runtime_error("format:\n\tNot a digit in {...}");
        }
        auto now = static_cast<size_t>(c - '0');
        if (((std::numeric_limits<size_t>::max() - now) / 10) < lhs) {
            throw std::runtime_error("format:\n\tToo big position in {...}");
        }
        return lhs * 10 + now;
    });
}

template <>
std::string da::utils::to_string<bool>(bool const &value) {
    return value ? "true" : "false";
}

template <>
std::string da::utils::to_string<char>(char const &value) {
    return std::string{value};
}
