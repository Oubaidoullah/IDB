//
// Created by mrperfect on 8/9/24.
//

#ifndef ANDROID_MASTER_ANDROID_MASTER_H
#define ANDROID_MASTER_ANDROID_MASTER_H

#include <iostream>
#include <vector>
#include <array>
#include <unistd.h>
#include <cstring>
#include <sys/utsname.h>
#include <regex.h>
#include <regex>
#include <fstream>
#include <sys/android-properties.h>
#include "android-info.h"
#include <fstream>

using namespace std;
using namespace compare;
using namespace printer;

namespace io {

#define SPACE_BAR " "
#define SEPARATE "/"

    bool defined(const char *dir) {
        ifstream file(dir);
        return (file.is_open());
    }

    bool defined(string str) {
        return defined(str.c_str());
    }

    string valueOf(bool b) {
        return b ? "true" : "false";
    }
}
namespace default_program {

    using namespace default_program;

    class command {

    private:
        int max{};
        char **machine_arguments{};

    public:
        command(int max, char *args[]) {
            this->max = (max);
            this->machine_arguments = (args);
        }

        vector<string> get_arguments() {
            vector<string> data;
            bool start = (false);

            for (int index = 0; index < max; index++) {
                if (start) {
                    data.emplace_back(this->machine_arguments[index]);
                } else {
                    start = (true);
                    continue;
                }
            }
            return (data);
        }

        vector<string> get_arguments(int at) {
            vector<string> data;
            bool start = (false);

            for (int index = 0; index < max; index++) {
                if (start) {
                    data.emplace_back(this->machine_arguments[index]);
                } else {
                    if (index == at) {
                        start = (true);
                        continue;
                    }
                }
            }
            return (data);
        }
    };

    class init_program {

    private:
        int max{};
        char **machine_arguments{};

        void init(int init_max, char *args[]) {
            this->max = init_max;
            this->machine_arguments = args;
        }

    public:
        // standard objects
        command *getCommand() {
            return (new command(this->max, this->machine_arguments));
        }

        init_program(int max, char *args[]) {
            this->init(max, args);
            this->program_dir = args[0];
            string _string(program_dir);
            if (start_with(_string, ".")) {
                auto length = _string.length();
                auto target = _string.substr(1, length);
                auto path = remove_last_from_vector(split(target, "/"), "/");
                auto real = '.' + path;
                this->parent_dir = real;
            } else {
                const auto loop = split(_string, "/");
                size_t target = loop.size() - 1;

                if (target != -1) {
                    auto real = (remove_last_from_vector(loop, "/"));
                    this->parent_dir = real;
                }
            }

            this->query = max > 1 ? args[1] : "";
        }

        string parent_dir;
        string program_dir;
        string query;

        static vector<string> split(string s, const char *reg) {
            regex target(reg);
            sregex_token_iterator iterator(s.begin(), s.end(), target, -1);
            sregex_token_iterator end;

            vector<string> data;
            for (; iterator != end; iterator++) {
                data.push_back(*iterator);
            }
            return data;
        }


        static string extra_full_command(string cmd) {
            auto data = init_program::split(std::move(cmd), " ");
            bool start = (false);
            string get_data;

            for (const auto &index: data) {
                if (start) {
                    get_data += index;
                    get_data += " ";
                } else {
                    start = (true);
                    continue;
                }
            }
            return (get_data);
        }


        static string merge(int max, char *args[]) {
            string merging;
            for (int index = 0; index < max; index++) {
                merging += args[index];
            }
            return merging;
        }

        static string merge(int max, char *args[], const char *sign) {
            string merging;
            for (int index = 0; index < max; index++) {
                merging += args[index];
                merging += (sign);
            }
            return merging;
        }

        static string remove_last_from_vector(vector<string> s, const char *sign) {

            size_t stop = s.size() - 1;
            string merge;
            for (int index = 0; index < s.size(); index++) {
                if (index == stop) {
                    break;
                }
                merge += s[index];
                merge += sign;
            }
            return merge;
        }

        static string get_full_vector(vector<string> s, const char *sign) {
            string merge;
            for (const auto &index: s) {
                merge += index;
                merge += sign;
            }
            return merge;
        }
    };

    class get : init_program {
    public:
        get(int max, char **args);
    };
}
#endif //ANDROID_MASTER_ANDROID_MASTER_H
