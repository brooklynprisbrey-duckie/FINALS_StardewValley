#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

#pragma once

enum DataCode {
    DAY,
    CQUAN,
    CREV,
    LSREV,
    EXP,
    TTLREV,
    NPROFIT,
};

struct DayData {
    int day = 0;
    int dCropsSold = 0;
    int dCropsRevenue = 0;
    int dLivestockRevenue = 0;
    int dExpenses = 0;
    int dTotalRevenue = 0;
    int dNetProfit = 0;
};

class Season {
    string seasonName;
    DayData month[28];
public:
    Season() {};
    
    void setter(ifstream& ifile);

    int getter(int day, DataCode toGet);
};