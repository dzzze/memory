#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <new>
#include <type_traits>

namespace dze {

// A non-polymorphic version of std::pmr::monotonic_buffer_resource.
class monotonic_buffer_resource
{
public:
    using value_type = std::byte;
    using propagate_on_container_move_assignment = std::true_type;
    using propagate_on_container_swap = std::true_type;
    using is_always_equal = std::false_type;

    constexpr monotonic_buffer_resource(void* const buf, const size_t size) noexcept
        : m_buf{static_cast<std::byte*>(buf)}
        , m_size{size} {}

    [[nodiscard]] void* allocate_bytes(
        const size_t n, const size_t alignment = alignof(std::max_align_t))
    {
        const auto mask = alignment - 1;
        const auto offset = (alignment - uintptr_t(m_buf)) & mask;
        const auto total_bytes = offset + n;
        if (total_bytes > m_size)
            throw std::bad_alloc{};

        m_size -= total_bytes;
        m_buf += total_bytes;
        return m_buf - n;
    }

    constexpr void deallocate_bytes(
        void*, size_t, size_t = alignof(std::max_align_t)) const noexcept {}

private:
    std::byte* m_buf;
    size_t m_size;

    [[nodiscard]] friend constexpr bool operator==(
        const monotonic_buffer_resource& lhs, const monotonic_buffer_resource& rhs) noexcept
    {
        return lhs.m_buf == rhs.m_buf && lhs.m_size == rhs.m_size;
    }

    [[nodiscard]] friend constexpr bool operator!=(
        const monotonic_buffer_resource& lhs, const monotonic_buffer_resource& rhs) noexcept
    {
        return !(lhs == rhs);
    }
};

} // namespace dze
