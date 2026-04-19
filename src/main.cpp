#include "Season.h"

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

int main(){
    std::cout << "Hello world" << std::endl;
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

    cout << "test line: 2,Winter,28,50,6850,259,328,7109,6781" << endl;
    cout << quarters[7].getter(28, TTLREV);
    cout << quarters[7].getter(28, NPROFIT);

    delete[] quarters;
    return 0;
}