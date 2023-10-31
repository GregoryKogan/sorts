#include <ctime>

#include "Application.hpp"
#include "messaging/messaging.hpp"

int main() {
    srand(time(NULL));

    Messenger::instance().start_listening();

    Application app;

    app.loop();

    return 0;
}