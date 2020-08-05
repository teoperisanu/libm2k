/*
 * Copyright (c) 2019 Analog Devices Inc.
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

#ifndef M2KEXCEPTIONS_H
#define M2KEXCEPTIONS_H

#include <libm2k/m2kglobal.hpp>
#include <libm2k/logger.hpp>
#include <libm2k/enums.hpp>
#include <stdexcept>
#include <string>
#include <iostream>

#if _EXCEPTIONS || defined(__cpp_exceptions)
	#define exception_type std::exception
	#if defined(_MSC_VER) || (__APPLE__)
		#define __try      try
		#define __catch(X) catch(X)
	#endif
#else
	#define exception_type
	#if defined(_MSC_VER)
		#define __try      if (true)
		#define __catch(X) if (false)
	#endif
#endif

namespace libm2k {

class m2k_exception_builder;

class LIBM2K_API m2k_exception : public std::runtime_error {
public:
	friend class m2k_exception_builder;

	static m2k_exception_builder make(std::string what);

	~m2k_exception() override = default;

	int iioCode() const noexcept;

	libm2k::M2K_EXCEPTION type() const noexcept;

	const char *what() const noexcept override;

private:
	m2k_exception() : runtime_error("")
	{
	}

	explicit m2k_exception(const std::string &what) :
		runtime_error(what)
	{
	}

	explicit m2k_exception(const char *what) :
		runtime_error(what)
	{
	}

	int m_iio_code = 0;
	libm2k::M2K_EXCEPTION m_type = libm2k::EXC_RUNTIME_ERROR;
	std::string m_message = "ERR: Runtime - ";
	std::string m_error;
};


class LIBM2K_API m2k_exception_builder {
public:
	m2k_exception_builder() = default;

	explicit m2k_exception_builder(std::string &what);

	explicit m2k_exception_builder(const char *what);

	m2k_exception_builder &iioCode(int code);

	m2k_exception_builder &type(libm2k::M2K_EXCEPTION type);

	explicit operator m2k_exception &&();

	m2k_exception build();

private:
	m2k_exception m2KException;
};

static void throw_exception(const m2k_exception &exception)
{
#if _EXCEPTIONS || defined(__cpp_exceptions)
	throw exception;
#else
	LOG("exception");

	std::cout << "Exception: " << exception.what() << std::endl;
#endif
}
}

#endif // M2KEXCEPTIONS_H
