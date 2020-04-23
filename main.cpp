#include <iostream>

#include "format.hpp"

int main() {
    std::cout << da::utils::format("This is string with bools: {0} and {1}", true, false) << std::endl;
    std::cout << da::utils::format("This is string with ints and floats: {2} and {1} and {0}", 5.5f, 3.0, 12) << std::endl;
    std::cout << da::utils::format("This is string with char: {0}", 'a') << std::endl;
    std::cout << da::utils::format("This is string with some escapes: %{0%} %%%% %%{0}", 'a') << std::endl;

    try {
        std::cout << da::utils::format("Line finishs with %") << std::endl;
    } catch (std::runtime_error const& error) {
        std::cout << error.what() << std::endl;
    }

    try {
        std::cout << da::utils::format("Too big pos {9999999999999999999999999999999999999999999999999999999999999999999}")
                  << std::endl;
    } catch (std::runtime_error const& error) {
        std::cout << error.what() << std::endl;
    }

    try {
        std::cout << da::utils::format("Not escaped {") << std::endl;
    } catch (std::runtime_error const& error) {
        std::cout << error.what() << std::endl;
    }

    try {
        std::cout << da::utils::format("Not escaped }") << std::endl;
    } catch (std::runtime_error const& error) {
        std::cout << error.what() << std::endl;
    }

    try {
        std::cout << da::utils::format("Smth bad in {%}") << std::endl;
    } catch (std::runtime_error const& error) {
        std::cout << error.what() << std::endl;
    }
}
