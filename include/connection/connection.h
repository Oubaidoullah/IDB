#include <sys/pm.h>
#include <fstream>

using namespace opt::package;
using namespace cli;

string ADB_LOCATION;

int is_connected() {
    auto start = (false);

    if (is_installed("adb")) {
        start = (true);
    } else {
        start = (false);
    }
    string location;
    string name;
    if (start) {
        name = "adb devices";
        location = "adb";
    } else {
        ifstream file("lib64/adb");
        if (file.is_open()) {
            name = "./ib64/adb devices";
            location = "./lib64/adb";
        } else {
            return 2;
        }
    }

    auto process = exec(name, "r");
    {
        string take;
        while (next(process)) {
            take += buffer.data();
            if (take.find("	device") != string::npos) {
                ADB_LOCATION = location;
                return (0);
            }
        }
        return (1);
    }
}
