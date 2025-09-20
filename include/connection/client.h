//
// Created by mrperfect on 8/12/24.
//

#ifndef ANDROID_MASTER_CLIENT_H
#define ANDROID_MASTER_CLIENT_H

#include <dlfcn.h>
#include <sys/android-info.h>

using namespace printer;

size_t writefunc(void * ptr , size_t size , size_t memb , void * unused) {
    write(STDOUT_FILENO , ptr , size * memb);
}
void init_client() {

    void * handle = dlopen("./libcurl.so" , RTLD_LAZY);
    println("library opened successful");

    const char * url = "https://google.com";

}
#endif //ANDROID_MASTER_CLIENT_H
