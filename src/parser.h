/* Copyright (c) 2014-2015, 2017, Chan Beom Park <cbpark@gmail.com> */

#ifndef CLHEF_SRC_PARSER_H_
#define CLHEF_SRC_PARSER_H_

#include <istream>
#include <memory>
#include <utility>
#include "event.h"

namespace lhef {
Event parseEvent(std::istream *is);

std::pair<bool, Event> parseOrFail(std::shared_ptr<std::istream> is);
}  // namespace lhef

#endif  // CLHEF_SRC_PARSER_H_
