#include "Season.h"

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

int main(){
    std::cout << "Hello world" << std::endl;
    ifstream dataSet = openFile();
    if (!dataSet.is_open()) {
        cout << "File failed to open." << endl;
        return 0;
    }
    string headers = "";
    getline(dataSet, headers, '\n');//TODO figure out better way of moving cursor

    Season Spring(dataSet, "Spring");
    Season Summer(dataSet, "Summer");

    cout << "Data set test: 1,Spring,1,16,3056,225,464,3281,2817" << endl;
    for (int i = 0; i < 8; i++) {
        cout << Spring.getter(1, static_cast<DataCode>(i)) << ',';
    }

    dataSet.close();
    return 0;
}