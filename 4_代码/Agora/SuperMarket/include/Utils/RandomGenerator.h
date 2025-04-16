#pragma once
#include <memory>
#include <string>
#include <vector>

namespace Utils
{
    class RandomGenerator
    {
    public:
        RandomGenerator();

        ~RandomGenerator();

        std::string
        generate_string(size_t len,
                        const std::string &charset =
                                "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopq"
                                "rstuvwxyz0123456789");

        std::vector<size_t> generate_numbers_from(size_t start, size_t end,
                                                  size_t len);

        int generate_number_from(size_t start, size_t end);

    private:
        struct RGImpl;
        std::unique_ptr<RGImpl> impl;
    };
} // namespace Utils
