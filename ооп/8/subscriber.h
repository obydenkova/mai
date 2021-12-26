#ifndef _D_SUBSCTIBER_H_
#define _D_SUBSCTIBER_H_

#include <iostream>
#include <condition_variable>
#include <thread>
#include <vector>
#include <mutex>
#include "factory.h"
#include "figure.h"
#include "processor.h"

struct subscriber {
    void operator()();
    std::vector<std::shared_ptr<processor>> processors;
    std::shared_ptr<std::vector<std::shared_ptr<figure>>> buffer;
    std::mutex mtx;
    std::condition_variable cond_var;
    bool stop = false;
};

#endif // _D_SUBSCTIBER_H_
