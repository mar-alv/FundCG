#include "Timer.h"
using namespace std::chrono_literals;

Timer::Timer() {}

Timer::Timer(int timeToWaitInMilliseconds) {
	this->timeToWaitInMilliseconds = timeToWaitInMilliseconds;

	start();

	end = begin + std::chrono::milliseconds(timeToWaitInMilliseconds);
}

void Timer::start() {
	begin = std::chrono::system_clock::now();
}

void Timer::finish() {
	end = std::chrono::system_clock::now();
}

double Timer::getElapsedTimeMilliseconds() {
	std::chrono::duration<double> elapsed_seconds = end - begin;

	return elapsed_seconds.count() * 1000;
}

float Timer::getElapsedTime() {
	begin = std::chrono::system_clock::now();

	this->elapsedTime = end - begin;

	return elapsedTime.count();
}

void Timer::resetTimer() {
	start();

	end = begin + std::chrono::milliseconds(timeToWaitInMilliseconds);
}

double Timer::calculateWaitingTime(int fps, double elapsedTime) {
	double waitingTime = 1000 / (double)fps - elapsedTime;

	return waitingTime;
}

void Timer::delay() {
	double waitingTime = calculateWaitingTime(15, getElapsedTimeMilliseconds());

	if (waitingTime) {
		std::this_thread::sleep_for(std::chrono::milliseconds((int)waitingTime));
	}
}
