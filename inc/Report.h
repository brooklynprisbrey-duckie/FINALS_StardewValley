#include "Season.h"

#pragma once

class Report : public Season {
	int minR = 1;
	int maxR = 28;
	Season* dataPtr;
	vector<int> foundDays;
public:
	Report(Season* getData);

	int getMax(DataCode toGet);

	int getMin(DataCode toGet);

	int getSum(DataCode toGet);

	void getFoundDays();

	int greaterCropLive();

	int ratioRevenueCrop();

	int validate(int min, int max);

	string enumString(DataCode toString);

	void reportComparison(Report* compare);
	/*Add comparision of two reports.
	Add reccommendations based on this*/
};