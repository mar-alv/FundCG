#include "Timer.h"
#include <iostream>

Timer::Timer() {}

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

double Timer::getElapsedTime() {
	end = std::chrono::system_clock::now();
	begin = std::chrono::system_clock::now();
	typedef std::chrono::milliseconds ms;
	std::chrono::duration<double> elapsed_seconds = end - begin;

	ms d = std::chrono::duration_cast<ms>(elapsed_seconds);

	//std::cout << d.count() << std::endl;

	return elapsed_seconds.count();
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
