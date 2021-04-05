#ifndef COUT_CFG_H
#define COUT_CFG_H
// Libraries
#include <iostream>
#include <string>

// Using from other namespaces
using std::string;

// IOSTREAM Customization
// Configs
const string CoutColorReset = "0m";
const string CoutColorBoldOn = "1;";
const string CoutColorUnderLineOn = "4;";
const string CoutColorInverseOn = "7;";
const string CoutColorBoldOff = "21;";
const string CoutColorUnderlineOff = "24;";
const string CoutColorInverseOff = "27;";

// Start-Stop
const string CoutColorStart = "\033[";
const string CoutColorEnd = CoutColorStart + CoutColorReset;

// Colors
const string CoutColorBlack = "30m";
const string CoutColorRed = "31m";
const string CoutColorGreen = "32m";
const string CoutColorYellow = "33m";
const string CoutColorBlue = "34m";
const string CoutColorMagenta = "35m";
const string CoutColorCyan = "36m";
const string CoutColorWhite = "37m";



enum class CoutSettingsExtra
{
    Reset = 0,
    BoldOn = 1,
    UnderlineOn = 4,
    InverseOn = 7,
    BoldOff = 21,
    UnderlineOff = 24,
    InverseOff = 27,
};

#endif