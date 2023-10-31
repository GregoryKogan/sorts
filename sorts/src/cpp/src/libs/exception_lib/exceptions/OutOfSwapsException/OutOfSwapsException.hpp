#ifndef OUT_OF_SWAPS_EXCEPTION_HPP
#define OUT_OF_SWAPS_EXCEPTION_HPP

#include "../BaseException.hpp"

namespace kogan {

class OutOfSwapsException : public BaseException {
    void build_message() const override;

   public:
    explicit OutOfSwapsException() = default;
};

}  // namespace kogan

#endif