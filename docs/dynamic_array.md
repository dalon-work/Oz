
# Dynamic Array

Imagine a world without where C++ doesn't have `std::vector`. How would you
handle memory for a dynamically sized array? You would use `new[]` of course!

`std::vector` is the most basic and useful workhorse of C++. It is a wrapper
around a dynamic array, but it is more than that. It automatically expands and
contracts the memory it holds in an logrithmic fashion, allowing the programmer
to not have to think too hard about memory management, while still providing
good performance memory-wise.  It provides convenient interfaces for adding and
removing elements from the array.

What if you don't need all that power? What if you want to create an array to a
certain size, fill it up with values, and leave it until the end of the
program? I often find myself in this situation, and it seems inefficient to have to
pay the price of the extra pointer that `std::vector` must keep around, when
I'm not even going to use it. It turns out there is an even more basic
container than `std::vector`, and that is the dynamic array. Using `new[]` and
`delete[]` directly, of course, is error-prone, so perhaps we can wrap this
most simple usage of a dynamic array into a container to manage the memory
using RAII principles, and provide a convenient interface as well.

`oz::dynamic_array` is an attempt to write this most basic container in a STL-like way.

Some guiding principles:

I imagine this class being a mixture of `std::array` and `std::vector`.
`std::array` is a fixed size container, which is still a Sequence Container,
but doesn't support ALL the sequence operations, because it can't.
So my guiding principles are:

1. Be like std::array
2. Be like std::vector where it can
3. Exception Safety
4. Allocator Aware
5. Be a Sequence Container.

Since this is a new container with its own behavior, there will be places where
implementation/API decisions will have to be made. I will do my best to document
those places and the reasons for the decisions.


