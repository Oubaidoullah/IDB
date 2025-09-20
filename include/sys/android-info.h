//
// Created by mrperfect on 8/12/24.
//

#ifndef ANDROID_MASTER_ANDROID_INFO_H
#define ANDROID_MASTER_ANDROID_INFO_H

#include <iostream>
#include <vector>
#include <array>
#include <unistd.h>
#include <cstring>
#include <sys/utsname.h>
#include <system/cli.h>

using namespace std;

string get_os() {
    struct utsname any{};
    uname(&any);
    return (string) any.sysname;
}

string get_machine() {
    struct utsname name{};
    uname(&name);
    return (string) name.machine;
}

string get_version() {
    struct utsname name{};
    uname(&name);
    return (string) name.version;
}

string get_release() {
    struct utsname name{};
    uname(&name);
    return name.release;
}

string get_domain() {
    struct utsname name{};
    uname(&name);
    return (string) name.domainname;
}

string get_node() {
    struct utsname name{};
    uname(&name);
    return (string) name.nodename;
}

int shell_version = static_cast<int>(2.4);

string get_str(const char * s) {
    return (s);
}

const char * get_c(const string& s) {
    return s.c_str();
}

namespace compare {

    bool equals(const char * x , const char * y) {
        return strcmp(x , y) == 0;
    }

    bool equals(string x, string y) {
        return strcmp(x.c_str(), y.c_str()) == 0;
    }

    bool contains(string x, string y) {
        return x.find(y) != std::string::npos;
    }

    bool start_with(string x , string y) {
        return x.find(y) == 0;
    }

    bool is_empty(string str) {
        return (str.empty());
    }
}

static void alloc(int max , char * args[]) {

}

namespace printer {

    void print(const char * s) {
        cout << s;
    }
    void print(string& s) {
        cout << s;
    }

    void print(int i) {
        cout << i;
    }

    void print(bool b) {
        cout << b;
    }

    void tprint(const char * s) {
        cout << "\033[33m" << s << "\033[0m";
    }

    void tprintln(const char * s) {
        cout << "\033[33m" << s << "\033[0m" << endl;
    }

    void println(const char * s) {
        cout << s << endl;
    }

    void println(string s) {
        cout << s << endl;
    }

    void println(int i) {
        cout << i << endl;
    }

    void println(bool b) {
        cout << b << endl;
    }
}
#endif //ANDROID_MASTER_ANDROID_INFO_H
