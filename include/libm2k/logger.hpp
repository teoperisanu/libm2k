/*
 * Copyright (c) 2020 Analog Devices Inc.
 *
 * This file is part of libm2k
 * (see http://www.github.com/analogdevicesinc/libm2k).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <vector>

// operations
#define LIBM2K_ATTRIBUTE_WRITE "write"
#define LIBM2K_ATTRIBUTE_READ "read"

namespace libm2k {
    static const char *getMessege(const std::vector<const char *> &info, const char *message);
}
#ifdef LIBM2K_ENABLE_LOG
#include <glog/logging.h>

/**
 * S - severity
 * D - device
 * C - channel
 * A - attribute
 * O - operation
 * M - message
 *
 * Format: [D][C][A][O] M
 */
#define LIBM2K_LOG(S, M) LOG(S) << M
//#define LIBM2K_LOG_3(S, D, M) LOG(S) << ("[" + D + "] " + M)
//#define LIBM2K_LOG_4(S, D, C, M) LOG(S) << ("[" + D + "][" + C + "] " + M)
//#define LIBM2K_LOG_5(S, D, C, A, M) LOG(S) << ("[" + D + "][" + C + "][" + A + "] " + M)
//#define LIBM2K_LOG_6(S, D, C, A, O, M) LOG(S) << ("[" + D + "][" + C + "][" + A + "][" + O + "] " + M)

#define LIBM2K_LOG_IF(S, COND, D, M) LOG_IF(S, COND) << ("[" + D + "] " + M)

#else

#define INFO 0
#define WARNING 1
#define ERROR 2
#define FATAL 3

#define LIBM2K_LOG(S, M)
//#define LIBM2K_LOG_3(S, D, M) S
//#define LIBM2K_LOG_4(S, D, C, M) S
//#define LIBM2K_LOG_5(S, D, C, A, M) S
//#define LIBM2K_LOG_6(S, D, C, A, O, M) S

#define LIBM2K_LOG_IF(S, COND, D, M) S

#endif

//#define LIBM2K_LOG_MACRO(_1, _2, _3, _4, _5, _6, NAME, ...) NAME
//#define LIBM2K_LOG(...) LIBM2K_LOG_MACRO(__VA_ARGS__, LIBM2K_LOG_6, LIBM2K_LOG_5, LIBM2K_LOG_4, LIBM2K_LOG_3, LIBM2K_LOG_2)(__VA_ARGS__)

#endif // LOGGER_HPP
