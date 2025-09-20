//
// Created by mrperfect on 8/12/24.
//

#ifndef ANDROID_MASTER_FETCH_H
#define ANDROID_MASTER_FETCH_H

#include <iostream>
#include <system/controller>
#include <sys/pm.h>
#include <sys/android-info.h>
#include <connection/connection.h>

using namespace opt::package;

using namespace compare;
using namespace printer;

namespace read_stream {

    class fetch {

    public:
        fetch() = default;

        explicit fetch(const char * query , vector<string> args) {
            auto adb = (string) "";

            switch (is_connected()) {
                case DEVICE_CONNECTED: {
                    adb = ADB_LOCATION;
                    break;
                }
                case DEVICE_NOT_CONNECTED: {
                    tprintln("device not connected");
                    return;
                }
                case BINARY_CORRUPTED: {
                    tprintln("binary is corrupted");
                    return;
                }
                default: {
                    break;
                }
            }

            if (args[1].c_str() == nullptr) {
                return;
            }

            auto to = args[1].c_str();
            if (equals(to, "info")) {
                println("retrieving information");
                auto target = adb + " shell cat /system/build.prop";
                system(target.c_str());
            }
            if(equals(to , "version")) {

            }
        }
    };
}
#endif //ANDROID_MASTER_FETCH_H
