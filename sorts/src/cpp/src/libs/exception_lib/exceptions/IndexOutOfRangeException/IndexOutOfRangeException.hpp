#pragma once

#include "../BaseException.hpp"

namespace kogan {

class IndexOutOfRangeException : public BaseException {
    int index;
    int range_min;
    int range_max;

    void build_message() const override;

   public:
    IndexOutOfRangeException(int index, int range_min, int range_max);
};

}  // namespace kogan