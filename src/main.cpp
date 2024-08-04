#include "App.hpp"
#include <spdlog/spdlog.h>

int main () {
    spdlog::set_level(spdlog::level::info);  // Set specific logger's log level
    
    App app = App();
    
    return app.start();

}
