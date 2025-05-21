// Copyright 2025 GHA Test Team
#include "TimedDoor.h"
#include <thread>
#include <chrono>
#include <stdexcept>

DoorTimerAdapter::DoorTimerAdapter(TimedDoor& d) : door(d) {}

void DoorTimerAdapter::Timeout() {
    if (door.isDoorOpened()) {
        door.throwState();
    }
}

TimedDoor::TimedDoor(int timeout) : iTimeout(timeout), isOpened(false) {
    adapter = new DoorTimerAdapter(*this);
}

bool TimedDoor::isDoorOpened() {
    return isOpened;
}

void TimedDoor::unlock() {
    isOpened = true;
}

void TimedDoor::lock() {
    isOpened = false;
}

int TimedDoor::getTimeOut() const {
    return iTimeout;
}

void TimedDoor::throwState() {
    throw std::runtime_error("Door timeout exception");
}

void Timer::tregister(int timeout, TimerClient* client) {
    this->client = client;
    std::thread([this, timeout]() {
        std::this_thread::sleep_for(std::chrono::seconds(timeout));
        this->client->Timeout();
    }).detach();
}
