//
// Created by mrperfect on 8/15/24.
//

#ifndef ANDROID_MASTER_JVM_H
#define ANDROID_MASTER_JVM_H

#include <sys/android-master.h>

#include <string>

#define object_bool "object=bool"
#define object_result "object=result"
#define init_object "object=run"

using namespace default_program;
using namespace printer;
using namespace io;
using namespace compare;
using namespace cli;

init_program * field_program;

vector<string> get_at(int at) {
    return field_program->getCommand()->get_arguments(at);
}

string get_full(vector<string> any , const char * sign) {
    return init_program::get_full_vector(any,sign);
}

int run_bool(string args) {
    auto classes_path = field_program->parent_dir + class_path; {

        auto object = classes_path + package_path_instance + "Bool.class";
        if (defined(object)) {
            auto cmd = field_program->parent_dir + java_bin ; {
                 if (defined(cmd)) {
                     cmd += SPACE_BAR;
                     cmd += "-cp";
                     cmd += SPACE_BAR;
                     cmd += class_path;
                     cmd += SPACE_BAR;
                     cmd += ((string) package_instance + "Bool");
                     cmd += SPACE_BAR;
                     cmd += args;
                     auto result = retrieve_data(cmd); {
                         if (!compare::is_empty(result)) {
                             return return_java_bool(result);
                         } else {
                             return 226;
                         }
                     }
                 }
            }
        } else {
            tprintln("Bool object not found");
            return (EXIT_FAILURE);
        }
    }
    return (0);
}
int start(init_program * program , command * _command , vector<string> arguments , string query , string data) {
    field_program = program;

    if (equals(query , object_bool)) {
        auto bool_args = get_at(2);
        auto start = ! bool_args.empty();

        if (start) {
            auto bool_request = bool_args[0];

            if (equals(bool_request , "is_file")) {
                return run_bool(get_full(bool_args , SPACE_BAR));
            }

            if (equals(bool_request, "is_directory")) {
                return run_bool(get_full(bool_args, SPACE_BAR));
            }

            auto return_result = "invalid bool request " + bool_request; {
                tprintln(return_result.c_str());
                return 223;
            }
        }
    }

    if (equals(query , object_result)) {

    }

    if (equals(query , init_object)) {

    }
    return EXIT_SUCCESS;
}
#endif //ANDROID_MASTER_JVM_H
