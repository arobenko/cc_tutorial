// Generated by commsdsl2comms v3.6.1

/// @file
/// @brief Contains definition of protocol default options for a client.

#pragma once

#include "DefaultOptions.h"

namespace howto5
{

namespace options
{

/// @brief Default options of the protocol for a client.
/// @tparam TBase Options to use as a basis.
template <typename TBase = howto5::options::DefaultOptions>
struct ClientDefaultOptionsT : public TBase
{
};

/// @brief Alias to @ref ClientDefaultOptionsT with default template parameter.
using ClientDefaultOptions = ClientDefaultOptionsT<>;

} // namespace options

} // namespace howto5


