#include "Season.h"

void Season::setter(ifstream& file) {
    for (int i = 0; i < 28; i++) {
        string insert;
        getline(file, insert, ',');
        if (stoi(insert) != year) { year = stoi(insert); }
        getline(file, insert, ',');
        if (insert != seasonName) { seasonName = insert; }
        getline(file, insert, ',');
        month[i].day = stoi(insert);
        getline(file, insert, ',');
        month[i].dCropsSold = stoi(insert);
        getline(file, insert, ',');
        month[i].dCropsRevenue = stoi(insert);
        getline(file, insert, ',');
        month[i].dLivestockRevenue = stoi(insert);
        getline(file, insert, ',');
        month[i].dExpenses = stoi(insert);
        getline(file, insert, ',');
        month[i].dTotalRevenue = stoi(insert);
        getline(file, insert);
        month[i].dNetProfit = stoi(insert);
    }
    return;
}

int Season::getter(int day, DataCode toGet) {
    switch (toGet) {
    case DAY:
        return month[day].day;
    case CQUAN:
        return month[day].dCropsSold;
    case CREV:
        return month[day].dCropsRevenue;
    case LSREV:
        return month[day].dLivestockRevenue;
    case EXP:
        return month[day].dExpenses;
    case TTLREV:
        return month[day].dTotalRevenue;
    case NPROFIT:
        return month[day].dNetProfit;
    }
}