#include <rte_eal.h>
#include <rte_lcore.h>
#include <rte_log.h>
#include <rte_debug.h>
#include <vector>
#include <string>

// Define your own log type
#define RTE_LOGTYPE_APP RTE_LOGTYPE_USER1

// Function prototype for lcore_hello
static int lcore_hello(__rte_unused void *arg);

int main(int argc, char **argv)
{
    std::vector<std::string> args;

    // If no arguments are passed, use default ones
    if (argc == 1) {
        args.push_back("-l");
        args.push_back("0-3");
        args.push_back("-n");
        args.push_back("4");
    } 
    else 
    {
        for (int i = 1; i < argc; ++i) 
        {
            args.push_back(argv[i]);
        }
    }

    std::vector<char*> cstrArgs;
    for (const auto& arg : args) {
        cstrArgs.push_back(const_cast<char*>(arg.c_str()));
    }


    int ret = rte_eal_init(cstrArgs.size(), cstrArgs.data());
    if (ret < 0)
         rte_panic("Cannot init EAL\n");

    RTE_LOG(INFO, APP, "Hello World!\n");

    // Use RTE_CALL_MASTER instead of CALL_MASTER
    rte_eal_mp_remote_launch(lcore_hello, NULL, CALL_MAIN);
    rte_eal_mp_wait_lcore();

    return 0;
}

// Function definition for lcore_hello
static int lcore_hello(__rte_unused void *arg) {
    unsigned id = rte_lcore_id();
    RTE_LOG(INFO, APP, "Hello from lcore %u\n", id);
    return 0;
}

/*

sudo code --user-data-dir="~/.vscode-root"


*/



