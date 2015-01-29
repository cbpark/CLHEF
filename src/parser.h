#ifndef SRC_PARSER_H_
#define SRC_PARSER_H_

#include "event.h"

namespace lhef {
Event ParseEvent(std::istream *is);
}

#endif  // SRC_PARSER_H_
