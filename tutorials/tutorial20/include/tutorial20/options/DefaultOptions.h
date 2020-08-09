// Generated by commsdsl2comms v3.5.0

/// @file
/// @brief Contains definition of protocol default options.

#pragma once

#include "comms/options.h"

namespace tutorial20
{

namespace options
{

/// @brief Default (empty) options of the protocol.
struct DefaultOptions
{
    /// @brief Extra options for messages.
    struct message
    {
        /// @brief Extra options for
        ///     @ref tutorial20::message::Connect message.
        using Connect = comms::option::app::EmptyOption;
        
    }; // struct message
    
    /// @brief Extra options for frames.
    struct frame
    {
        /// @brief Extra options for Layers of
        ///     @ref tutorial20::frame::Frame frame.
        struct FrameLayers
        {
            /// @brief Extra options for @ref
            ///     tutorial20::frame::FrameLayers::Data
            ///     layer.
            using Data = comms::option::app::EmptyOption;
            
            /// @brief Extra options for @ref
            ///     tutorial20::frame::FrameLayers::Id
            ///     layer.
            using Id = comms::option::app::EmptyOption;
            
        }; // struct FrameLayers
        
    }; // struct frame
    
    
};

} // namespace options

} // namespace tutorial20

