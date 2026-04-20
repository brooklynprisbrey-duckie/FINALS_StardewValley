#include "Report.h"

Report::Report(Season* getData) {//only a quarter at a time
	dataPtr = getData;
	cout << "Report for year " << dataPtr->year << ", " << dataPtr->seasonName << endl;
	getSum(CQUAN);
	getSum(CREV);
	getSum(LSREV);
	getSum(TTLREV);
	getSum(EXP);
	getSum(NPROFIT);
	return;
}

string Report::getDate() {
	string date = "Year ";
	date.append(to_string(dataPtr->year));
	date.append(", ");
	date.append(dataPtr->seasonName);
	return date;
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
	cout << "For " << getDate() << ": The highest daily " << enumString(toGet) << " was " << max << endl;
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
	cout << "For " << getDate() << ": The lowest daily " << enumString(toGet) << " was " << min << endl;
	return min;
}

int Report::getSum(DataCode toGet) {
	int sum = 0;
	for (int i = 0; i <= (maxR - minR); i++) {
		sum += dataPtr->getter(i, toGet);
	}
	cout << "For " << getDate() << ": The sum of " << enumString(toGet) << " was " << sum << endl;
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
	cout << "For " << getDate() << ": ";
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
	cout << "For " << getDate() << ": The crops revenue to quantity ratio was " << ratio << endl;
	return ratio;
}

int Report::validate(int min, int max) {
	cin.clear();
	int input = 0;
	bool validating = true;
	while (validating) {
		if (cin >> input) {
			if (min < input || input < max) {
				return input;
			}
		}
		else if (input > max) {
			cerr << "Woah! Error be upon you! Too many failed input attempts" << endl;
			return input;
		}
		cout << "Input failed." << endl;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.clear();
		input++;
	}
}

string Report::enumString(DataCode toString) {
	switch (toString) {
	case DAY:
		return "day";
	case CQUAN:
		return "crops sold";
	case CREV:
		return "crops revenue";
	case LSREV:
		return "livestock revenue";
	case EXP:
		return "expenses";
	case TTLREV:
		return "total revenue";
	case NPROFIT:
		return "net profit";
	}
}

void Report::reportComparison(Report* compare) {
	cout << "Comparing " << getDate() << "to " << compare->getDate() << endl;
	cout << "Looking to compare 1. maximum, 2. minimums, 3. sums, or 4. ratios?" << endl;
	string catEnum = "0. Day, 1. Crops Sold, 2. Crop Revenue, 3. Livestock Revenue, 4. Expenses, 5. Total Revenue, 6. Net Profit";
	int choice1 = validate(1, 4);

	string recThis = "Emulate " + getDate();
	string recThat = "Emulate " + compare->getDate();
	switch (choice1) {
	case 1: {
		cout << "Maximum what? " << catEnum << endl;
		DataCode choice2 = static_cast<DataCode> (validate(0, 6));
		int max1 = getMax(choice2);
		int max2 = compare->getMax(choice2);
		if (choice2 == EXP) {
			string hold = recThis;
			recThis = recThat;
			recThat = hold;
		}
		if (max1 > max2) {
			cout << getDate() << " has the higher daily " << enumString(choice2) << " then " << compare->getDate() << ".\n"
				<< recThis << endl;
		}
		else if (max2 > max1) {
			cout << compare->getDate() << " has the higher daily " << enumString(choice2) << " then " << getDate() << ".\n"
				<< recThat << endl;
		}
		return;
	}
	case 2: {
		cout << "Minimum what? " << catEnum << endl;
		DataCode choice2 = static_cast<DataCode> (validate(0, 6));
		int min1 = getMin(choice2);
		int min2 = compare->getMin(choice2);
		if (choice2 == EXP) {
			string hold = recThis;
			recThis = recThat;
			recThat = hold;
		}
		if (min1 < min2) {
			cout << getDate() << " has the lower daily " << enumString(choice2) << " then " << getDate() << ".\n"
				<< recThat << endl;
		}
		else if (min2 < min1) {
			cout << compare->getDate() << " has the lower daily " << enumString(choice2) << " then " << getDate() << ".\n"
				<< recThis << endl;
		}
		return;
	}
	case 3: {
		cout << "Sum of what? " << catEnum << endl;
		DataCode choice2 = static_cast<DataCode>(validate(0, 6));
		int sum1 = getSum(choice2);
		int sum2 = compare->getSum(choice2);
		if (choice2 == EXP) {
			string hold = recThis;
			recThis = recThat;
			recThat = hold;
		}
		if (sum1 > sum2) {
			cout << getDate() << " has the highest overall " << enumString(choice2) << " then " << compare->getDate() << ".\n"
				<< recThis << endl;
		}
		else if (sum2 > sum1) {
			cout << compare->getDate() << " has the highest overall " << enumString(choice2) << " then " << getDate() << ".\n"
				<< recThat << endl;
		}
		return;
	}
	case 4:{
		int ratio1 = ratioRevenueCrop();
		int ratio2 = compare->ratioRevenueCrop();
		if (ratio1 > ratio2) {
			cout << getDate() << " has the higher ratio than " << compare->getDate() << ".\n";
			if (dataPtr->seasonName == compare->dataPtr->seasonName) {
				cout << recThis << endl;
			}
			else {
				cout << "It appears " << dataPtr->seasonName << " is better for growing crops." << endl;
			}
			return;
		}
		else if (ratio2 > ratio1) {
			cout << compare->getDate() << " has the higher ratio than " << getDate() << ".\n";
			if (dataPtr->seasonName == compare->dataPtr->seasonName) {
				cout << recThat << endl;
			}
			else {
				cout << "It appears " << compare->dataPtr->seasonName << " is better for growing crops." << endl;
			}
			return;
		}
		return;
	}
	}
	return;
}