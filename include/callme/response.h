#pragma once

#ifndef RESPONSE_H_MVRZEKPX
#define RESPONSE_H_MVRZEKPX

#include "msgpack.hpp"
#include "callme/detail/log.h"

namespace callme {

//! \brief Represents a response and creates a msgpack to be sent back
//! as per the msgpack-rpc spec.
class response {
public:
    //! \brief Constructs a msgpack::response with the given values.
    response(uint32_t id, std::string const &error,
             std::unique_ptr<msgpack::object> result);

    //! \brief Constructs a response from msgpack::object (useful when
    //! reading a response from a stream).
    response(msgpack::object const &o);

    //! \brief Writes the response pack to a buffer.
    void write(msgpack::sbuffer *buf) const;

    msgpack::sbuffer get_data() const;

    //! \brief Returns the call id/index used to identify which call
    //! this response corresponds to.
    int get_id() const;

    //! \brief Returns the error message stored in the response. Can
    //! be empty.
    std::string const &get_error() const;

    //! \brief Returns the result stored in the response. Can be empty.
    msgpack::object get_result() const;

    //! \brief The type of a response, according to the msgpack-rpc spec
    using response_type =
        std::tuple<uint32_t, uint32_t, msgpack::object, msgpack::object>;

private:
    uint32_t id_;
    std::string error_;
    // I really wish to avoid shared_ptr here but at this asio does not work with 
    // move-only handlers in post() and I need to capture responses in lambdas.
    std::shared_ptr<msgpack::object> result_;
    CALLME_CREATE_LOG_CHANNEL(response)
};

} /* callme  */

#endif /* end of include guard: RESPONSE_H_MVRZEKPX */
