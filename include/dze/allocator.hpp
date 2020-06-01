#pragma once

#include <cstddef>
#include <new>
#include <type_traits>

namespace dze {

class allocator
{
public:
    using value_type = std::byte;
    using propagate_on_container_move_assignment = std::true_type;
    using is_always_equal = std::true_type;

    // Terminates the process if global allocator cannot allocate memory.
    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    [[nodiscard]] void* allocate_bytes(
        const size_t n, const size_t alignment = alignof(std::max_align_t)) const noexcept
    {
        return ::operator new(n, std::align_val_t{alignment});
    }

    // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
    void deallocate_bytes(
        void* const p,
        const size_t,
        const size_t alignment = alignof(std::max_align_t)) const noexcept
    {
        ::operator delete(p, std::align_val_t{alignment});
    }

private:
    [[nodiscard]] friend constexpr bool operator==(allocator, allocator) noexcept
    {
        return true;
    }

    [[nodiscard]] friend constexpr bool operator!=(allocator, allocator) noexcept
    {
        return false;
    }
};

} // namespace dze
