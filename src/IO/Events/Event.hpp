#pragma once
#include <memory>
#include <string>

namespace sw::io {

struct Event {
    virtual ~Event() = default;
    virtual std::string to_string() const = 0;
};
using EventPtr = std::shared_ptr<Event>;

} // namespace battle
