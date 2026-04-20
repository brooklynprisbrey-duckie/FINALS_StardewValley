#include "Report.h"

Report::Report(Season* getData) {//only a quarter at a time
	dataPtr = getData;
	cout << "Report for year " << dataPtr->year << ", " << dataPtr->seasonName << endl;
	cout << "Crops sold = " << getSum(CQUAN) << endl;
	cout << "Crops Revenue = " << getSum(CREV) << endl;
	cout << "Livestock Revenue = " << getSum(LSREV) << endl;
	cout << "Total Revenue = " << getSum(TTLREV) << endl;
	cout << "Expenses = " << getSum(EXP) << endl;
	cout << "Net Profit = " << getSum(NPROFIT) << endl;
	return;
}

int Report::getMax(DataCode toGet) {
	int max = 0;
	foundDays.clear();
	for (int i = 0; i <= (maxR - minR); i++) {
		if (dataPtr->getter(i, toGet) > max) {
			max = dataPtr->getter(i, toGet);
			foundDays.clear();
			foundDays.push_back(i + 1);
		}
		else if (dataPtr->getter(i, toGet) == max) {
			foundDays.push_back(i + 1);
		}
	}
	return max;
}

int Report::getMin(DataCode toGet) {
	int min = 10000;
	foundDays.clear();
	for (int i = 0; i <= (maxR - minR); i++) {
		if (dataPtr->getter(i, toGet) < min) {
			min = dataPtr->getter(i, toGet);
			foundDays.clear();
			foundDays.push_back(i + 1);
		}
		else if (dataPtr->getter(i, toGet) == min) {
			foundDays.push_back(i + 1);
		}
	}
	return min;
}

int Report::getSum(DataCode toGet) {
	int sum = 0;
	for (int i = 0; i <= (maxR - minR); i++) {
		sum += dataPtr->getter(i, toGet);
	}
	return sum;
}

void Report::getFoundDays() {
	cout << "Days pulled on last report";
	for (int i : foundDays) {
		cout << ", " << i;
	}
	cout << endl;
	return;
}

int Report::greaterCropLive() {
	int cropRev = getSum(CREV);
	int liveRev = getSum(LSREV);
	cout << "For year " << dataPtr->year << ", " << dataPtr->seasonName << ": ";
	if (cropRev > liveRev) {
		cout << "revenue from crops (" << cropRev << ") was greater than revenue from livestock (" << liveRev << ")" << endl;
		cout << "Reccomendation: Focus on crops next " << dataPtr->seasonName << "." << endl;
		return cropRev - liveRev;
	}
	else if (liveRev > cropRev) {
		cout << "revenue from livestock (" << liveRev << ") was greater than revenue from crops (" << cropRev << ")" << endl;
		cout << "Reccomendation: Focus on livestock next " << dataPtr->seasonName << "." << endl;
		return liveRev - cropRev;
	}
	else {
		cout << "the revenue from crops (" << cropRev << ") was the same as the revenue from livestock (" << liveRev << ")" << endl;
		return 0;
	}
}

int Report::ratioRevenueCrop() {
	int ratio = getSum(CREV) / getSum(CQUAN);//ultimately decided against fussing with precision and rounding
	cout << "For year " << dataPtr->year << ", " << dataPtr->seasonName << ": The crops revenue to quantity ratio was " << ratio << endl;
	return ratio;
}