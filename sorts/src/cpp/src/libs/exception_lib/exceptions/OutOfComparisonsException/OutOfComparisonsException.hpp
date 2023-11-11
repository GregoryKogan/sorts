#pragma once

#include "../BaseException.hpp"

namespace kogan {

class OutOfComparisonsException : public BaseException {
    void build_message() const override;

   public:
    explicit OutOfComparisonsException() = default;
};

}  // namespace kogan