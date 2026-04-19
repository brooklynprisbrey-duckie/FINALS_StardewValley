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

class Season {
    ifstream& file;
    string seasonName;
public:
    Season(ifstream& ifile, string seas) :file{ ifile }, seasonName{ seas } {
        DayData month[28];
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

        }
    }
};

struct DayData {
    int day = 0;
    int dCropsSold = 0;
    int dCropRevenue = 0;
    int dLivestockRevenue = 0;
    int dExpenses = 0;
    int dTotalRevenue = 0;
    int dNetProfit = 0;
};

int main(){
    std::cout << "Hello world" << std::endl;
    ifstream dataSet = openFile();
    if (!dataSet.is_open()) {
        cout << "File failed to open." << endl;
        return 0;
    }


    dataSet.close();
    return 0;
}