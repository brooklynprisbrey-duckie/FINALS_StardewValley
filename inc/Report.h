#include "Season.h"

#pragma once

class Report : public Season {
	int minR = 1;
	int maxR = 28;
	Season* dataPtr;
	vector<int> foundDays;
public:
	Report(Season* getData[]);

	Report(Season* getData);

	int getMax(DataCode toGet);

	int getMin(DataCode toGet);

	int getSum(DataCode toGet);

	/*TODO Add comparision of livestock / crop.Add comparision of c - rev / crop ratio Add comparision of two reports.
	Add reccommendations based on this*/
};