#include "subscriber.h"

void subscriber::operator()() {
    for(;;) {
        std::unique_lock<std::mutex>lock(mtx);
        cond_var.wait(lock,[&]{ return (buffer != nullptr || stop);});
        if (stop) {
            break;
        }
        for (auto elem: processors) {
            elem->process(buffer);
        }
        buffer = nullptr;
        cond_var.notify_all();
    }
}