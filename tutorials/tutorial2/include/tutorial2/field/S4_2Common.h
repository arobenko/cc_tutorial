// Generated by commsdsl2comms v3.3.0

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref tutorial2::field::S4_2 field.

#pragma once

#include <type_traits>

namespace tutorial2
{

namespace field
{

/// @brief Common functions for
///     @ref tutorial2::field::S4_2 field.
struct S4_2Common
{
    /// @brief Name of the @ref tutorial2::field::S4_2 field.
    static const char* name()
    {
        return "S4_2";
    }
    
    /// @brief Retrieve name of the bit of
    ///     @ref tutorial2::field::S4_2 field.
    static const char* bitName(std::size_t idx)
    {
        static const char* Map[] = {
            "B0",
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            "B5",
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            "B15"
        };
    
        static const std::size_t MapSize = std::extent<decltype(Map)>::value;
        if (MapSize <= idx) {
            return nullptr;
        }
    
        return Map[idx];
    }
    
};

} // namespace field

} // namespace tutorial2

