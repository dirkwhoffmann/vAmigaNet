// -----------------------------------------------------------------------------
// This file is part of vAmiga
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#include "config.h"
#include "Amiga.h"
#include "CIA.h"
#include <cmath>

namespace vamiga {

//
// Butterworth filter (DEPRECATED)
//

void
ButterworthFilter::setSampleRate(double sampleRate)
{
    // Compute butterworth filter coefficients based on
    // https://stackoverflow.com/questions/
    //  20924868/calculate-coefficients-of-2nd-order-butterworth-low-pass-filter

    // Cutoff frequency in Hz
    const double f_cutoff = 4500;

    // Frequency ratio
    const double ff = f_cutoff / sampleRate;

    // Compute coefficients
    const double ita = 1.0/ tan(M_PI * ff);
    const double q = sqrt(2.0);

    b0 = 1.0 / (1.0 + q * ita + ita * ita);
    b1 = 2 * b0;
    b2 = b0;
    a1 = 2.0 * (ita * ita - 1.0) * b0;
    a2 = -(1.0 - q * ita + ita * ita) * b0;
}

void
ButterworthFilter::clear()
{
    x1 = x2 = y1 = y2 = 0.0;
}

float
ButterworthFilter::apply(float sample)
{
    // Run pipeline
    double x0 = (double)sample;
    double y0 = (b0 * x0) + (b1 * x1) + (b2 * x2) + (a1 * y1) + (a2 * y2);

    // Shift pipeline
    x2 = x1; x1 = x0;
    y2 = y1; y1 = y0;

    return (float)y0;
}


//
// OnePoleFilter
//

void
OnePoleFilter::setup(double sampleRate, double R, double C)
{
    double cutoff = 1.0 / (2 * AudioFilter::pi * R * C);
    setup(sampleRate, cutoff);
}

void
OnePoleFilter::setup(double sampleRate, double cutoff)
{
    if (cutoff >= sampleRate / 2.0) cutoff = (sampleRate / 2.0) - 1e-4;

    this->cutoff = cutoff;

    const double a = 2.0 - std::cos((2.0 * AudioFilter::pi * cutoff) / sampleRate);
    const double b = a - std::sqrt((a * a) - 1.0);

    a1 = 1.0 - b;
    a2 = b;
}

void
OnePoleFilter::clear()
{
    tmpL = tmpR = 0.0;
}

void
OnePoleFilter::applyLP(double &l, double &r)
{
    tmpL = (a1 * l) + (a2 * tmpL);
    l = tmpL;

    tmpR = (a1 * r) + (a2 * tmpR);
    r = tmpR;
}

void
OnePoleFilter::applyHP(double &l, double &r)
{
    tmpL = (a1 * l) + (a2 * tmpL);
    l = l - tmpL;

    tmpR = (a1 * r) + (a2 * tmpR);
    r = r - tmpR;
}


//
// TwoPoleFilter
//

void
TwoPoleFilter::setup(double sampleRate, double R1, double R2, double C1, double C2)
{
    double cutoff = 1.0 / (2 * AudioFilter::pi * std::sqrt(R1 * R2 * C1 * C2));
    double qFactor = std::sqrt(R1 * R2 * C1 * C2) / (C2 * (R1 + R2));

    setup(sampleRate, cutoff, qFactor);
}

void
TwoPoleFilter::setup(double sampleRate, double cutoff, double qFactor)
{
    if (cutoff >= sampleRate / 2.0) cutoff = (sampleRate / 2.0) - 1e-4;

    this->cutoff = cutoff;
    this->qFactor = qFactor;

    const double a = 1.0 / std::tan((2.0 * AudioFilter::pi * cutoff) / sampleRate);
    const double b = 1.0 / qFactor;

    a1 = 1.0 / (1.0 + b * a + a * a);
    a2 = 2.0 * a1;
    b1 = 2.0 * (1.0 - a*a) * a1;
    b2 = (1.0 - b * a + a * a) * a1;
}

void
TwoPoleFilter::clear()
{
    tmpL[0] = tmpL[1] = tmpL[2] = tmpL[3] = 0.0;
    tmpR[0] = tmpR[1] = tmpR[2] = tmpR[3] = 0.0;
}

void
TwoPoleFilter::applyLP(double &l, double &r)
{
    auto inl = l;
    auto inr = r;

    l = (a1 * inl) + (a2 * tmpL[0]) + (a1 * tmpL[1]) - (b1 * tmpL[2]) - (b2 * tmpL[3]);
    r = (a1 * inr) + (a2 * tmpR[0]) + (a1 * tmpR[1]) - (b1 * tmpR[2]) - (b2 * tmpR[3]);

    tmpL[1] = tmpL[0];
    tmpL[0] = inl;
    tmpL[3] = tmpL[2];
    tmpL[2] = l;

    tmpR[1] = tmpR[0];
    tmpR[0] = inr;
    tmpR[3] = tmpR[2];
    tmpR[2] = r;
}


//
// AudioFilter (filter pipeline)
//


const double AudioFilter::pi = std::atan(1) * 4.0;

void
AudioFilter::_dump(Category category, std::ostream& os) const
{
    using namespace util;

    if (category == Category::Config) {

        os << tab("Filter type");
        os << FilterTypeEnum::key(config.filterType) << std::endl;
    }

    if (category == Category::State) {

        os << tab("Low-pass filter");
        os << bol(loFilterEnabled(), "enabled", "disabled") << std::endl;
        os << tab("Cutoff");
        os << flt(loFilter.cutoff) << " Hz" << std::endl;
        os << tab("a1");
        os << flt(loFilter.a1) << std::endl;
        os << tab("a2");
        os << flt(loFilter.a2) << std::endl;

        os << std::endl;
        os << tab("LED filter");
        os << bol(ledFilterEnabled(), "enabled", "disabled") << std::endl;
        os << tab("Cutoff");
        os << flt(ledFilter.cutoff) << " Hz" << std::endl;
        os << tab("Quality Factor");
        os << flt(ledFilter.qFactor) << std::endl;
        os << tab("a1");
        os << flt(ledFilter.a1) << std::endl;
        os << tab("a2");
        os << flt(ledFilter.a2) << std::endl;
        os << tab("b1");
        os << flt(ledFilter.b1) << std::endl;
        os << tab("b2");
        os << flt(ledFilter.b2) << std::endl;

        os << std::endl;
        os << tab("High-pass filter");
        os << bol(hiFilterEnabled(), "enabled", "disabled") << std::endl;
        os << tab("Cutoff");
        os << flt(hiFilter.cutoff) << " Hz" << std::endl;
        os << tab("a1");
        os << flt(hiFilter.a1) << std::endl;
        os << tab("a2");
        os << flt(hiFilter.a2) << std::endl;

        os << std::endl;
        os << tab("Legacy filter");
        os << bol(legacyFilterEnabled(), "enabled", "disabled") << std::endl;
    }
}

void
AudioFilter::resetConfig()
{
    assert(isPoweredOff());
    auto &defaults = amiga.defaults;

    std::vector <Option> options = {

        OPT_FILTER_TYPE
    };

    for (auto &option : options) {
        setConfigItem(option, defaults.get(option));
    }
}

i64
AudioFilter::getConfigItem(Option option) const
{
    switch (option) {

        case OPT_FILTER_TYPE:       return config.filterType;

        default:
            fatalError;
    }
}

void
AudioFilter::setConfigItem(Option option, i64 value)
{
    switch (option) {

        case OPT_FILTER_TYPE:

            if (!FilterTypeEnum::isValid(value)) {
                throw VAError(ERROR_OPT_INVARG, FilterTypeEnum::keyList());
            }

            config.filterType = (FilterType)value;
            setup(host.getSampleRate());
            return;

        default:
            fatalError;
    }
}

void
AudioFilter::setup(double sampleRate)
{
    trace(AUD_DEBUG, "Setting sample rate to %f Hz\n", sampleRate);

    setupLoFilter(sampleRate);
    setupLedFilter(sampleRate);
    setupHiFilter(sampleRate);

    // Setup the legacy filter (DEPRECATED)
    butterworthL.setSampleRate(sampleRate);
    butterworthR.setSampleRate(sampleRate);
}

void
AudioFilter::setupLoFilter(double sampleRate)
{
    loFilter.clear();
    loFilter.setup(sampleRate, 360.0, 1e-7);
}

void
AudioFilter::setupLedFilter(double sampleRate)
{
    ledFilter.clear();
    ledFilter.setup(sampleRate, 10000.0, 10000.0, 6.8e-9, 3.9e-9);
}
void
AudioFilter::setupHiFilter(double sampleRate)
{
    hiFilter.clear();
    if (config.filterType == FILTER_A1200) {
        hiFilter.setup(sampleRate, 1360.0, 2.2e-5);
    } else {
        hiFilter.setup(sampleRate, 1390.0, 2.233e-5);
    }
}

bool
AudioFilter::loFilterEnabled() const
{
    switch (config.filterType) {

        case FILTER_A500:
        case FILTER_A1000:
        case FILTER_LOW:        return true;
        default:                return false;
    }
}

bool
AudioFilter::ledFilterEnabled() const
{
    switch (config.filterType) {

        case FILTER_A500:
        case FILTER_A1200:      return ciaa.powerLED();
        case FILTER_A1000:
        case FILTER_LED:        return true;
        default:                return false;
    }
}

bool
AudioFilter::hiFilterEnabled() const
{
    switch (config.filterType) {

        case FILTER_A500:
        case FILTER_A1000:
        case FILTER_A1200:
        case FILTER_HIGH:       return true;
        default:                return false;
    }
}

bool
AudioFilter::legacyFilterEnabled() const
{
    switch (config.filterType) {

        case FILTER_VAMIGA:     return ciaa.powerLED();
        default:                return false;
    }
}

void
AudioFilter::clear()
{
    butterworthL.clear();
    butterworthR.clear();
}

}
