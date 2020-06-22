# Memory management facilities

This library introduces a simplified extension to the C++17 allocator API inline with polymorphic memory resources.

All allocators are not templated on a type and provide `allocate_bytes(size, align)` and `deallocate_bytes(ptr, size, align)` methods.

 - `dze::allocator` is a stateless allocator based on global new allocator. Its `allocate_bytes` method is `noexcept`.
 - `dze::monotonic_memory_resource` is based on `std::pmr::monotonic_memory_resource` without the virtual calls and upstream memory resource and is intented to provide highest throughput when provided with a buffer of adequate size.
 - `dze::pmr::polymorphic_allocator` is a wrapper around `std::polymorphic_allocator<std::byte>` that provides the `allocate_bytes` and `deallocate_bytes` methods in C++17.
