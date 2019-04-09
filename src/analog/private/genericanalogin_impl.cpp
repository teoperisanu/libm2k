/*
 * Copyright 2018 Analog Devices, Inc.
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
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file LICENSE.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#include "../../utils/private/device_impl.cpp"
#include <libm2k/analog/genericanalogin.hpp>
#include <libm2k/m2kexceptions.hpp>

#include "libm2k/utils/utils.hpp"
#include <iio.h>
#include <iostream>
#include <algorithm>

using namespace libm2k::utils;
using namespace libm2k::analog;
using namespace std;

class GenericAnalogIn::GenericAnalogInImpl : public DeviceImpl {
public:
	GenericAnalogInImpl(iio_context *ctx, std::string adc_dev) :
		DeviceImpl(ctx, adc_dev)
	{
	}

	~GenericAnalogInImpl()
	{
		//	m_data.clear();
	}

	static double processSample(int16_t sample, unsigned int ch)
	{
		return (double)sample;
	}

	std::vector<std::vector<double>> getSamples(unsigned int nb_samples,
						bool processed = false)
	{
		return DeviceImpl::getSamples(nb_samples, processSample);
	}

	void openAnalogIn()
	{
		std::cout << "Opened analog in for " << m_dev_name << "\n";
	}

	void closeAnalogIn()
	{
		std::cout << "Closed analog in for " << m_dev_name << "\n";
	}

	double getSampleRate()
	{
		return getDoubleValue("sampling_frequency");
	}

	double getSampleRate(unsigned int chn_idx)
	{
		return getDoubleValue(chn_idx, "sampling_frequency");
	}

	double setSampleRate(double sampleRate)
	{
		return setDoubleValue(sampleRate, "sampling_frequency");
	}

	double setSampleRate(unsigned int chn_idx, double sampleRate)
	{
		return setDoubleValue(chn_idx, sampleRate, "sampling_frequency");
	}

	std::vector<double> getAvailableSamplerates()
	{
		return DeviceImpl::getAvailableSamplerates();
	}

	string getDeviceName()
	{
		return m_dev_name;
	}

	void enableChannel(unsigned int index, bool enable)
	{
		DeviceImpl::enableChannel(index, enable);
	}

private:
	std::string m_dev_name;
	unsigned int m_nb_channels;
	bool m_cyclic;
};
