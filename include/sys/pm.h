//
// Created by mrperfect on 8/12/24.
//

#ifndef ANDROID_MASTER_PM_H
#define ANDROID_MASTER_PM_H

#include <iostream>
#include "android-master.h"
#include <fstream>

using namespace std;
using namespace cli;
using namespace default_program;

namespace opt {

    namespace package {
        bool is_installed(const char *name) {
            auto process = exec("echo $PATH", "r");
            auto path = (string) "";

            while (next(process)) {
                path += buffer.data();
            }

            auto array = init_program::split(path, ":");
            auto array_size = array.size();

            for (int index = 0; index < array_size; index++) {
                auto merge = (string) array[index];
                {
                    merge += "/";
                    merge += name;
                }
                ifstream c(merge.c_str());
                auto cmd = c.is_open();
                {
                    if (cmd) {
                        return (true);
                    }
                }
            }
            return (false);
        }
    }
}

namespace android {

    bool app_is_installed(string program , const char * package_name) {
        auto cmd = program + " shell pm path " + package_name;

        if (equals(retrieve_data(cmd).c_str() , "")) {
            return false;
        } else {
            return (true);
        }
    }
}
#endif //ANDROID_MASTER_PM_H
