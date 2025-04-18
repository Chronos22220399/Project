#pragma once
#include <atomic>

template <typename T, std::size_t Capacity> class RingBuffer {
  public:
    // 指定容量为 2 的幂，可以将 next = (curr+1) % Capacity 优化为 next =
    // (curr+1) & (Capacity - 1)，此外，更方便的实现 64B 的内存对齐
    static_assert(Capacity && !(Capacity & (Capacity - 1)),
                  "Capacity must be power of 2");

    RingBuffer() : read_(0), write_(0) {}

    ~RingBuffer() {
        std::size_t r = read_.load(std::memory_order_relaxed);
        std::size_t w = write_.load(std::memory_order_relaxed);
        while (r != w) {
            reinterpret_cast<T *>(&data_[r])->~T();
            r = (r + 1) & (Capacity - 1);
        }
    }

    // U 用于支持非 POD 类型
    template <typename U> bool Push(U &&value) noexcept {
        const std::size_t w = write_.load(std::memory_order_relaxed);
        const std::size_t next_w = (w + 1) & (Capacity - 1);

        // next_w 用于判断 Buffer 是否满了
        // 缓冲区满了
        if (next_w == read_.load(std::memory_order_acquire))
            return false;

        // 在 data_[w] 上构造新值
        new (&data_[w]) T(std::forward<U>(value));
        write_.store(next_w, std::memory_order_release);
        return true;
    }

    bool Pop(T &val) noexcept {
        const std::size_t r = read_.load(std::memory_order_relaxed);

        // Buffer为空
        if (r == write_.load(std::memory_order_acquire))
            return false;

        // 取出元素并销毁
        val = std::move(*reinterpret_cast<T *>(&data_(r)));
        // 调用析构函数，避免内存泄漏
        reinterpret_cast<T *>(&data_[r])->~T();

        // 更新读索引
        read_.store((r + 1) & (Capacity - 1), std::memory_order_release);
        return true;
    }

    std::size_t size() const noexcept {}

  private:
    alignas(64) std::atomic<std::size_t> read_;
    alignas(64) std::atomic<std::size_t> write_;
    alignas(64) std::aligned_storage_t<sizeof(T), alignof(T)> data_[Capacity];
};
