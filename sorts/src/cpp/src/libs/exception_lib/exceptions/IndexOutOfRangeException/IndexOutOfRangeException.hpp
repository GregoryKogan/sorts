//
// Created by Gregory Kogan on 04.05.2023.
//

#ifndef LAB2_INDEXOUTOFRANGEEXCEPTION_H
#define LAB2_INDEXOUTOFRANGEEXCEPTION_H

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

} // namespace kogan

#endif // LAB2_INDEXOUTOFRANGEEXCEPTION_H
