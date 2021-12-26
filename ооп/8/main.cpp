#include <iostream>
#include <memory>
#include <vector>
#include <thread>

#include "factory.h"
#include "figure.h"
#include "subscriber.h"

void help() {
    std::cout << "help - print this menu\n"
                "add <square, rectangle or trapezoid> <vertices> - add a figure\n"
                "exit\n";
}

int main(int argc,char* argv[]) {
    if (argc != 2) {
        std::cout << "2 arguments needed\n";
        return 1;
    }

    int  buffer_size = std::stoi(argv[1]);
    std::shared_ptr<std::vector<std::shared_ptr<figure>>> buffer = std::make_shared<std::vector<std::shared_ptr<figure>>>();
    buffer->reserve(buffer_size);
    factory factory;
    std::string cmd;
    subscriber sub;
    sub.processors.push_back(std::make_shared<stream_processor>());
    sub.processors.push_back(std::make_shared<file_processor>());
    std::thread sub_thread(std::ref(sub));

    while (true) {
        std::unique_lock<std::mutex> locker(sub.mtx);
        std::cin >> cmd;
        if (cmd == "help") {
            help();
        } else if (cmd == "add") {
            try {
                buffer->push_back(factory.new_figure(std::cin));
            } catch (std::logic_error &e) {
                std::cout << e.what() << '\n';
                continue;
            }
            if (buffer->size() == buffer_size) {
                std::cout << "You've reached the limit\n";
                sub.buffer = buffer;
                sub.cond_var.notify_all();
                sub.cond_var.wait(locker, [&](){ return sub.buffer == nullptr;});
                buffer->clear();
            }
        } else if (cmd == "quit")  {
            break;
        } else {
            std::cout << "Wrong command\n";
        }
    }
    sub.stop = true;
    sub.cond_var.notify_all();
    sub_thread.join();
    return 0;
}
