#include "Report.h"

Report::Report(Season* getData[]) {//whole amount passed in for extraction
	string minDay;
	string maxDay;
	cout << "Please enter the " << endl;
	return;
}

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