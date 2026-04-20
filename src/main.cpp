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
            cout << "Do you want to 0. Quit 1. examine reports 2. compare?" << endl;
            int choice1 = reportFolder[0].validate(0, 2);
            int reportNum = 0;
            do {
                cout << "Which report?" << endl;
                reportNum = reportFolder[0].validate(1, reportFolder.size());
                cout << "Is the report for year " << reportFolder[reportNum].year <<
            } while (!reportNum);
            switch (choice1) {
            case 1: {
                cout << "1. Look at specific day, 2. Search days, 3. Pull days from report" << endl;
                int choice2 = reportFolder[0].validate(1, 3);
                switch (choice2) {
                case 1: 
                }
            }
            }
        }

    } while (reporting);

    delete[] quarters;
    return 0;
}