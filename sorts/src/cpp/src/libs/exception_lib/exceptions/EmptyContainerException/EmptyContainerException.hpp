//
// Created by Gregory Kogan on 04.05.2023.
//

#ifndef LAB2_EMPTYCONTAINEREXCEPTION_H
#define LAB2_EMPTYCONTAINEREXCEPTION_H

#include "../BaseException.hpp"

namespace kogan {

class EmptyContainerException : public BaseException {
  void build_message() const override;
};

} // namespace kogan

#endif // LAB2_EMPTYCONTAINEREXCEPTION_H
