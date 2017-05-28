/* Copyright (c) 2014-2015, 2017, Chan Beom Park <cbpark@gmail.com> */

#ifndef SRC_PARSER_H_
#define SRC_PARSER_H_

#include "event.h"

namespace lhef {
Event parseEvent(std::istream *is);
}  // namespace lhef

#endif  // SRC_PARSER_H_
