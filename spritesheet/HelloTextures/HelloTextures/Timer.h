#pragma once
#include <ctime>
#include <chrono>
#include <thread>

class Timer
{
protected:
	std::chrono::time_point<std::chrono::system_clock> end;
	std::chrono::time_point<std::chrono::system_clock> begin;

public:
	Timer();

	void start();
	void delay();
	void finish();

	double getElapsedTime();
	double getElapsedTimeMilliseconds();
	double calculateWaitingTime(int fps, double elapsedTime);
};
