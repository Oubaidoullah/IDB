#include <unistd.h>
#include <array>

using namespace std;

namespace cli {

    array<char, 128> buffer;

    FILE *exec(const string &cmd, const string &mode) {
        auto file = popen(cmd.c_str(), mode.c_str());
        return file;
    }

    bool next(FILE *e) {
        auto gets = fgets(buffer.data(), sizeof(buffer), e) != nullptr;
        return gets;
    }

    string retrieve_data(string cmd) {
        auto result = (string) "";
        auto process = exec(cmd , "r"); {
            while(next(process)) {
                result += buffer.data();
            }
        } return result;
    }
}
