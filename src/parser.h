#ifndef SRC_PARSER_H_
#define SRC_PARSER_H_

#include "type.h"

namespace lhef {
LHEFEvent ParseEvent(std::istream *is);
}

#endif  // SRC_PARSER_H_
