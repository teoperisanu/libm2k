/*
 * Copyright 2019 Analog Devices, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef LIBM2K_SPI_H
#define LIBM2K_SPI_H

#include <tools/m2kcli/commands/command.h>
#include <libm2k/tools/spi.hpp>

namespace libm2k {
namespace cli {

class Spi : public Command {
public:
	Spi(int argc, char **argv);

	~Spi();

	bool parseArguments(std::vector<std::pair<std::string, std::string>> &output) override;

private:
	spi_desc *spiDesc;
	bool writeOnly;

	static const struct option options[];

	void handleInit();

	void handleWrite();

	static const char *const helpMessage;
};
}
}

#endif //LIBM2K_SPI_H
