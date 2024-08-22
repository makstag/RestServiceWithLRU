#include <drogon/drogon.h>
#include "controllers/JsonCtrl.h"
int main(int argc, char **argv)
{
    int num_threads = 1;
    int capacity = 2;
    if (argc == 3)
    {
        capacity = atoi(argv[1]);
        num_threads = atoi(argv[2]);
    }
    std::cout << "capacity = " << capacity << std::endl;
    std::cout << "num_threads = " << num_threads << std::endl;
    // Set HTTP listener address and port
    drogon::app().addListener("127.0.0.1", 8080).setThreadNum(num_threads);
    auto json_ctrl_ptr = std::make_shared<JsonCtrl>(capacity);
    app().registerController(json_ctrl_ptr);
    // Load config file
    // drogon::app().loadConfigFile("../config.json");
    // Run HTTP framework,the method will block in the internal event loop
    drogon::app().run();
    return 0;
}
