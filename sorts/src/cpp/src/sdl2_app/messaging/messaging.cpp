#include "messaging.hpp"

void Messenger::start_listening() const noexcept {
    emscripten_run_script(
        "window.addEventListener('message', function(event) { Module.ccall('handleMessage', 'void', "
        "['string'], [event.data]); });");
}

void Messenger::send_message(const std::string& message) const noexcept {
    EM_ASM({ window.postMessage(JSON.stringify(Module.UTF8ToString($0)), '*'); }, message.c_str());
}

void Messenger::add_message(const std::string& message) noexcept { Messenger::instance().messages_.push(message); }

bool Messenger::has_message() const noexcept { return Messenger::instance().messages_.size() > 0; }

std::string Messenger::get_message() {
    if (!Messenger::instance().messages_.size()) throw std::runtime_error("no messages to get");

    std::string message = Messenger::instance().messages_.front();
    Messenger::instance().messages_.pop();
    return message;
}

void handleMessage(const char* message) {
    rapidjson::Document document;
    document.Parse(message);

    if (document.HasParseError() || !document.IsObject() || !document.HasMember("to") || !document["to"].IsString() ||
        document["to"].GetString() != std::string("cpp") || !document.HasMember("message") ||
        !document["message"].IsObject())
        return;

    rapidjson::Value& message_val = document["message"];

    // convert message to string
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    message_val.Accept(writer);

    std::string json_string = buffer.GetString();
    Messenger::instance().add_message(json_string);
}