#include "../include/Utils/RandomGenerator.h"
#include <random>

using namespace Utils;

RandomGenerator::RandomGenerator() = default;

RandomGenerator::~RandomGenerator() = default;

struct RandomGenerator::RGImpl {
    RGImpl() = default;
    ~RGImpl() = default;

    std::string generate_string(size_t len, const std::string &charset) {
        static thread_local std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<size_t> dist(0, charset.length() - 1);

        std::string ret;
        ret.reserve(len);
        for (size_t i = 0; i < len; i++) {
            ret += charset[dist(rng)];
        }
        return ret;
    }

    std::vector<size_t> generate_numbers_from(size_t start, size_t end,
                                              size_t len) {
        static thread_local std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<size_t> dist(start, end);
        std::vector<size_t> ret;
        ret.reserve(len);

        for (size_t i = 0; i < len; ++i) {
            ret.push_back(dist(rng));
        }
        return ret;
    }

    int generate_number_from(int start, int end) {
        static thread_local std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist(start, end);

        return dist(rng);
    }
};

std::string RandomGenerator::generate_string(size_t len,
                                             const std::string &charset) {
    return impl->generate_string(len, charset);
}

std::vector<size_t>
RandomGenerator::generate_numbers_from(size_t start, size_t end, size_t len) {
    return impl->generate_numbers_from(start, end, len);
}

int RandomGenerator::generate_number_from(size_t start, size_t end) {
    return impl->generate_number_from(start, end);
}
