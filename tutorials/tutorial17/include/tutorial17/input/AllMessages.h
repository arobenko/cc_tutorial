// Generated by commsdsl2comms v3.4.2

/// @file
/// @brief Contains definition of all messages bundle.

#pragma once

#include <tuple>
#include "tutorial17/message/Msg1.h"
#include "tutorial17/message/Msg2.h"
#include "tutorial17/options/DefaultOptions.h"

namespace tutorial17
{

namespace input
{

/// @brief Messages of the protocol in ascending order.
/// @tparam TBase Base class of all the messages.
/// @tparam TOpt Protocol definition options.
template <typename TBase, typename TOpt = tutorial17::options::DefaultOptions>
using AllMessages =
    std::tuple<
        tutorial17::message::Msg1<TBase, TOpt>,
        tutorial17::message::Msg2<TBase, TOpt>
    >;

} // namespace input

} // namespace tutorial17


