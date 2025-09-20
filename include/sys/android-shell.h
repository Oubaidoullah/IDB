//
// Created by mrperfect on 8/12/24.
//

#ifndef ANDROID_MASTER_ANDROID_SHELL_H
#define ANDROID_MASTER_ANDROID_SHELL_H

#define os "android_linux"

#pragma man

#include <fstream>
#include <utility>
#include <sys/reboot.h>
#include <fetch/fetch.h>

void kill(int status) {
    exit(status);
}

using namespace compare;
using namespace printer;

#include "android-master.h"

using namespace default_program;
using namespace read_stream;
using namespace reboot;
using namespace android;

class shell_manager {

    int max_arguments;
    char **default_arguments;
public :
    shell_manager() = default;

    shell_manager(int max, char *args[]) {
        this->max_arguments = max;
        this->default_arguments = args;
        this->program_dir = init_program(max, args).program_dir;
        this->parent_dir = init_program(max,args).parent_dir;
    }

    void start() {

        while (true) {
            print("\033[31mandroid $ \033[0m");
            string command;
            getline(cin, command);

            bool connected = false;
            string program;
            if (is_connected() == DEVICE_CONNECTED) {
                program = ADB_LOCATION;
                connected = (true);
            } else if (is_connected() == DEVICE_NOT_CONNECTED || is_connected() == BINARY_CORRUPTED){
                connected = (false);
            }
            if (start_with(command, "fetch ")) {
                (fetch(command.c_str(),default_program::init_program::split(command , " ")));
            }

            if (start_with(command, "reboot ")) {
                if (! connected) {
                    println("device not connected");
                } else {
                    reboot::reboot(program , init_program::split(command," ")[1].c_str());
                }
            } else if (equals(command.c_str() , "reboot")) {
                if (! connected) {
                    println("device not connected");
                } else {
                    reboot::reboot(program,"");
                }
            }

            if (equals(command.c_str() , "clear") || equals(command.c_str() , "cls")) {
                std::system("clear");
                continue;
            }

            if (equals(command.c_str(),"exit")) {
                tprintln("stopping program android master process 021");
                exit(0);
            }

            if (start_with(command , "app ")) {
                if (connected) {
                    if (app_is_installed(program , init_program::split(command," ")[1].c_str())) {
                        println("this package was installed in the system");
                    } else {
                        println("this package wasn't installed on this system");
                        continue;
                    }
                }
            }

            if (start_with(command , "system ")) {
                println("exec -> ");
                system(init_program::extra_full_command(command).c_str());
            }
        }
    }


    string program_dir;
    string parent_dir;
};

#endif //ANDROID_MASTER_ANDROID_SHELL_H
