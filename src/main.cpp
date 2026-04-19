#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

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

struct DayData {
    int day = 0;
    int dCropsSold = 0;
    int dCropsRevenue = 0;
    int dLivestockRevenue = 0;
    int dExpenses = 0;
    int dTotalRevenue = 0;
    int dNetProfit = 0;
};

class Season {
    ifstream& file;
    string seasonName;
    DayData month[28];
public:
    Season(ifstream& ifile, string seas) :file{ ifile }, seasonName{ seas } {
        cout << "we got here" << endl;
        for (int i = 0; i < 28; i++) {
            string insert;
            getline(file, insert, ',');
            month[i].day = stoi(insert);
            getline(file, insert, ',');
            if (insert != seasonName) {
                //TODO figure out back cursor
                return;
            }
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

    void testPrint() {
        cout << month << endl;
        return;
    }
};

int main(){
    std::cout << "Hello world" << std::endl;
    ifstream dataSet = openFile();
    if (!dataSet.is_open()) {
        cout << "File failed to open." << endl;
        return 0;
    }
    string headers = "";
    getline(dataSet, headers, '\n');

    Season Spring(dataSet, "Spring");

    Spring.testPrint();

    dataSet.close();
    return 0;
}