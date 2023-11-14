#include <ctime>

#include "Application.hpp"
#include "messaging/messaging.hpp"

int main() {
  srand(time(NULL));

  Messenger::instance().start_listening();

  Application app;

  emscripten_set_main_loop_arg(
      [](void *app_ptr) {
        Application *app = static_cast<Application *>(app_ptr);
        app->loop();
      },
      &app, 0, 1);

  return 0;
}