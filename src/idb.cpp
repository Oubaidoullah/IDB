#include <sys/android-master.h>
#include <map>
#include <query.h>
#include <sys/stat.h>

using namespace printer;
using namespace io;
using namespace cli;
using namespace compare;

using namespace jre;
using namespace default_program;

int start(int max, char *arg[]);
int add(string _case, command *cmd,int max);
int get(const char *key);
int create_dir(const char *dir);

int main(int max, char *args[])
{
    int result = start(max, args);
    //  println(getenv("HOME"));
    if (result == 1)
    {
        println("unrecognized query . try set (--set) or get (--get)");
        return result;
    }
    else if (result == 0)
    {
        //println("Your request has been add successful");
    }
    return 0;
}

int start(int max, char *args[])
{
    auto program = new init_program(max, args);

    auto cmd = program->getCommand();

    auto _program = program->program_dir;
    auto parent = program->parent_dir;
    auto query = program->query;

    string list[3] = {_program, parent, query};

    if (equals(list[2], "--set") || equals(list[2], "set"))
    {
        return add("write", cmd,max);
    }
    else if (equals(list[2], "--get") || equals(list[2], "get"))
    {
        return add("read", cmd,max);
    } else if (equals(list[2], "--clear") || equals(list[2], "clear")) {
        println("clearing");
        add("clear",cmd,max);
        /*if (add("clear", cmd) == 0)
        {
            println("database cleared");
            return 0;
        }*/
        /*else
        {
            println("database could not be cleared ");
            return 12;
        }*/
    } else if (equals(list[2], "--list") || equals(list[2], "list")) {
        if (!add("list", cmd,max) == 0)
        {
            println("couldn't get the list of keys");
            return -12;
        }
    }
    return 1;
}

int add(string _case, command *cmd , int unused)
{
    const char *HOME = getenv("HOME");
    auto data = cmd->get_arguments(1);
    println(equals(cmd->get_arguments()[1],""));
    auto target = data[0];
    auto split = split_string(target, '=');

    auto key = split[0];
    auto value = split[1];

    string file = HOME;
   // string cwd;
    {
        file += "/.idb";
        //cwd = file;
        ifstream put(file);
        {
            if (!put.is_open())
            {
                auto create = (string)("mkdir -p ");
                {
                    create += file;
                    create_dir(file.c_str());
                }
            }
        }
        file += SEPARATE;
        file += key;
    }
    if (equals(_case, "write"))
    {
        ofstream of(file.c_str());
        {
            of << value;
            printf("added %s \n", value.c_str());
        }
    }
    else if (equals(_case, "read"))
    {
        string line;
        ifstream read(file.c_str());

        if (read.is_open())
        {
            while (getline(read, line))
            {
                println(line);
            }
        }
        else
        {
            cerr << key << " could not found !" << endl;
            return 21;
        }
    }
    return 0;
}

int get(const char *key)
{
    return 0;
}

int create_dir(const char *dir)
{
    std::string dirPath = dir;
    int status = mkdir(dirPath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    if (status == 0)
    {
        std::cout << "database created successfully." << std::endl;
    }
    else
    {
        std::cerr << "Error creating directory." << std::endl;
    }
    return 0;
}
