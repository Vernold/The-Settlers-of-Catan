#include "Regexp.h"

const std::regex Regexp::I ("-?\\d");
const std::regex Regexp::WORD ("\\b\\w{1,9}\\b");
const std::regex Regexp::COORD ("\\(-?\\d,\\s*-?\\d\\)");