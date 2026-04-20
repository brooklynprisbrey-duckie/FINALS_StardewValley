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

	int greaterCropLive();//

	int ratioRevenueCrop();


	/*Add comparision of two reports.
	Add reccommendations based on this*/
};