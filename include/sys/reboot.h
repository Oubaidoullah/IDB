//
// Created by mrperfect on 8/13/24.
//

#ifndef ANDROID_MASTER_REBOOT_H
#define ANDROID_MASTER_REBOOT_H

#include <sys/android-info.h>

using namespace compare;
using namespace printer;
using namespace cli;

namespace reboot {

    static int WHERE_TO_REBOOT;

    void reboot(string program, const char *where) {

        if (equals(where, "bootloader")) {
            auto merge = program + " reboot bootloader";

            println("rebooting to bootloader");
            {
                exec(merge, "r");
            }
            return;
        }

        if (equals(where, "recovery")) {
            auto merge = program + " reboot recovery";
            println("rebooting to recovery mode");
            exec(merge, "r");
            return;
        }

        if (equals(where, "sideload")) {
            auto merge = program + " reboot sideload";
            println("rebooting to sideload ");
            exec(merge, "r");
            return;
        }

        if (equals(where, "sideload-auto-reboot")) {
            auto merge = program + " reboot sideload-auto-reboot";
            println("rebooting to sideload auto reboot mode");
            exec(merge, "r");
            return;
        }

        if (equals(where, "")) {
            println("rebooting system");
            auto cmd = program + " reboot";
            exec(cmd, "r");
            return;
        }
    }
}
#endif //ANDROID_MASTER_REBOOT_H
