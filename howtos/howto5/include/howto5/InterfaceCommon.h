// Generated by commsdsl2comms v3.6.2

/// @file
/// @brief Contains common template parameters independent functionality of
///    @ref howto5::Interface interface fields.

#pragma once

#include "howto5/field/InterfaceFlagsCommon.h"
#include "howto5/field/VersionCommon.h"

namespace howto5
{

/// @brief Common types and functions for fields of 
///     @ref howto5::Interface interface.
/// @see howto5::InterfaceFields
struct InterfaceFieldsCommon
{
    /// @brief Common types and functions for
    ///     @ref howto5::InterfaceFields::Version field.
    using VersionCommon = howto5::field::VersionCommon;
    
    /// @brief Common types and functions for
    ///     @ref howto5::InterfaceFields::Flags field.
    struct FlagsCommon : public howto5::field::InterfaceFlagsCommon
    {
        /// @brief Name of the @ref howto5::InterfaceFields::Flags field.
        static const char* name()
        {
            return "Flags";
        }
        
    };
    
};
} // namespace howto5

