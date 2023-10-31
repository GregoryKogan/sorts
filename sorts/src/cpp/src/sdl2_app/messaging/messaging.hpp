#ifndef MESSAGING_HPP
#define MESSAGING_HPP

#include <emscripten.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include <iostream>
#include <queue>
#include <string>

class Messenger {
   private:
    Messenger() {}
    Messenger(const Messenger&) = delete;
    Messenger& operator=(const Messenger&) = delete;

    std::queue<std::string> messages_;

   public:
    static Messenger& instance() {
        static Messenger instance;
        return instance;
    }

    void start_listening() const noexcept;
    void send_message(const std::string& message) const noexcept;
    void add_message(const std::string& message) noexcept;

    bool has_message() const noexcept;
    std::string get_message();
};

extern "C" {
EMSCRIPTEN_KEEPALIVE
void handleMessage(const char* message);
}

#endif