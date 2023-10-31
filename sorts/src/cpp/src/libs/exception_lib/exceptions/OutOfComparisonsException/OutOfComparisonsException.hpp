#ifndef OUT_OF_COMPARISONS_EXCEPTION_HPP
#define OUT_OF_COMPARISONS_EXCEPTION_HPP

#include "../BaseException.hpp"

namespace kogan {

class OutOfComparisonsException : public BaseException {
    void build_message() const override;

   public:
    explicit OutOfComparisonsException() = default;
};

}  // namespace kogan

#endif