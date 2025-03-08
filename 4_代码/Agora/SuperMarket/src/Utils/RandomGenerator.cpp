#include <Utils/RandomGenerator.h>
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
};

std::string RandomGenerator::generate_string(size_t len,
                                             const std::string &charset) {
    return impl->generate_string(len, charset);
}
