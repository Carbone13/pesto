#ifndef PESTO_UTIL_HPP
#define PESTO_UTIL_HPP

#include <sstream>
#include <iomanip>

#define DEBUG_MILLISECONDS(title, time, nb) \
(bgfx::dbgTextPrintf(0, nb, ((0x2 + nb) << 4) | 0xF, \
(std::stringstream() << title \
<< std::fixed << std::setprecision(3) \
<< time << " ms").str().c_str()))

#define DEBUG_NUMBER(title, number, nb) \
(bgfx::dbgTextPrintf(0, nb, ((0x2 + nb) << 4) | 0xF, \
(std::stringstream() << title \
<< number).str().c_str()))

#endif // PESTO_UTIL_HPP
