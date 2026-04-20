#include "Season.h"
#include "Report.h"

ifstream openFile() {
    fs::path pathwayMap = fs::current_path();
    while (pathwayMap.has_parent_path()) {
        if (fs::exists(pathwayMap / "files")) {
            pathwayMap = (pathwayMap / "files").string() + "\\stardew_dataset.csv";
            break;
        }
        else pathwayMap = pathwayMap.parent_path();
    }

    ifstream fSDV(pathwayMap, ios::in);
    fSDV.open("stardew_dataset.csv");
    fSDV.clear();

    return fSDV;
}

int main() {
    std::cout << "Hello JojoFarmer to your JojoSoftware!" << std::endl;
    ifstream dataSet = openFile();
    if (!dataSet.is_open()) {
        cout << "File failed to open." << endl;
        return 0;
    }

    dataSet.seekg(-3, fstream::end);//moves away from EOF newline
    while (dataSet.peek() != '\n') {
        dataSet.seekg(-1, fstream::cur);
    }
    dataSet.get();//move one forward
    string yrTtl;
    getline(dataSet, yrTtl, ',');//get year

    dataSet.seekg(0, fstream::beg);//back to beginning
    while (dataSet.peek() != '\n') {//move past headers
        dataSet.seekg(1, fstream::cur);
    }
    dataSet.get();

    int qrtrTtl = stoi(yrTtl) * 4;
    Season* quarters = new Season[qrtrTtl];
    for (int i = 0; i < qrtrTtl; i++) {
        quarters[i].setter(dataSet);
    }
    dataSet.close();//info retrieved

    vector<Report> reportFolder;
    bool reporting = true;
    cout << qrtrTtl << " quarters have been inputted. Here's your latest quarter!" << endl;
    reportFolder.push_back(Report(&quarters[qrtrTtl - 1]));
    do {
        bool makeReports = true;
        while (makeReports){
            cout << "What other quarters would you like to make a report on?" << endl;
            int choice = reportFolder[0].validate(1, qrtrTtl);
            reportFolder.push_back(Report(&quarters[choice - 1]));
            cout << "You have " << reportFolder.size() << " reports. Do you want another report? 0. No 1. Yes." << endl;
            makeReports = reportFolder[0].validate(0, 1);
        }

        bool studyReports = true;
        while (studyReports) {
            cout << "Do you want to 0. Make more reports, 1. Examine reports, 2. Compare?" << endl;
            int choice1 = reportFolder[0].validate(0, 2);
            int reportNum = 0;
            do {
                cout << "Which report?" << endl;
                reportNum = reportFolder[0].validate(1, reportFolder.size())-1;
                cout << "Is the report for " << reportFolder[reportNum].getDate() << " correct? 0. No 1. Yes" << endl;
                reportNum = reportFolder[reportNum].validate(0,1);
            } while (!reportNum);

            string catEnum = "0. Day, 1. Crops Sold, 2. Crop Revenue, 3. Livestock Revenue, 4. Expenses, 5. Total Revenue, 6. Net Profit";
            switch (choice1) {
            case 1: {
                cout << "1. Look at specific day, 2. Search days, 3. Pull days from report" << endl;
                int choice2 = reportFolder[reportNum].validate(1, 3);
                if (choice2 == 1) {
                    cout << "Pick the day, 1-28" << endl;
                    int day = reportFolder[reportNum].validate(1, 28) - 1;
                    cout << "Which category? " << catEnum << endl;
                    DataCode goGet = static_cast<DataCode>(reportFolder[reportNum].validate(0, 6));
                    cout << "There was " << reportFolder[reportNum].getter(day, goGet) << reportFolder[reportNum].enumString(goGet) << "on " << day << ", " << reportFolder[reportNum].getDate() << endl;
                    continue;
                }
                else if (choice2 == 2) {
                    cout << "1. Maximum, 2. Minimum, or 3. Sum?" << endl;
                    int choice3 = reportFolder[reportNum].validate(1, 3);
                    cout << "Which category? " << catEnum << endl;
                    DataCode goGet = static_cast<DataCode>(reportFolder[reportNum].validate(0, 6));
                    switch (choice3) {
                    case 1:
                        reportFolder[reportNum].getMax(goGet);
                        continue;
                    case 2:
                        reportFolder[reportNum].getMin(goGet);
                        continue;
                    case 3:
                        reportFolder[reportNum].getSum(goGet);
                        continue;
                    }
                    continue;
                }
                else {
                    reportFolder[reportNum].getFoundDays();
                    continue;
                }
            }
            case 2: {
                int reportNumC = 0;
                do {
                    cout << "Compare with which report?" << endl;
                    reportNumC = reportFolder[0].validate(1, reportFolder.size())-1;
                    cout << "Is the report for " << reportFolder[reportNumC].getDate() << " correct? 0. No 1. Yes" << endl;
                    reportNumC = reportFolder[reportNumC].validate(0, 1);
                } while (!reportNum);
                reportFolder[reportNum].reportComparison(&reportFolder[reportNumC]);
                continue;
            }
            default:
                studyReports = false;
            }
        }
        cout << "Are you done? 0. No 1. Yes" << endl;
        reporting = !(reportFolder[0].validate(0, 1));
    } while (reporting);

    delete[] quarters;
    return 0;
}