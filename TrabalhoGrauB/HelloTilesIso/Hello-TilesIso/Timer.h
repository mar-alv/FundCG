#pragma once
#include <ctime>
#include <chrono>
#include <thread>
#include <iostream>

class Timer
{
private:
	int timeToWaitInMilliseconds;
	std::chrono::duration<float> elapsedTime;
	std::chrono::time_point<std::chrono::system_clock> end;
	std::chrono::time_point<std::chrono::system_clock> begin;

public:
	Timer();
	Timer(int timeToWaitInMilliseconds);

	void start();
	void delay();
	void finish();
	void resetTimer();
	float getElapsedTime();
	double getElapsedTimeMilliseconds();
	double calculateWaitingTime(int fps, double elapsedTime);
};
