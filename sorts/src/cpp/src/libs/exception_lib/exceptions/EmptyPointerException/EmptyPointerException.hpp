#ifndef LAB1_EMPTY_POINTER_EXCEPTION_HPP
#define LAB1_EMPTY_POINTER_EXCEPTION_HPP

#include "../BaseException.hpp"

namespace kogan {

class EmptyPointerException : public BaseException {
    void build_message() const override;
};

}  // namespace kogan

#endif