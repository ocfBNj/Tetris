#include "Timer.h"
//默认初始化
Timer::Timer() : begin(), end(), dif_time(0.0) {}

void Timer::clear() {
	begin = end;
}


void Timer::setDifTime(double t) {
	dif_time = t;           //设置时间段
	clear();                //重置定时器
	start();                //开始计时
}

bool Timer::isTimeOut() {
	stop(); //暂停,以便计算时间差
	if (count() >= dif_time) {
		start(); //重新计时
		return true;
	}
	return false;
}


void Timer::start() {
	begin = std::chrono::steady_clock::now();
}



void Timer::stop() {
	end = std::chrono::steady_clock::now();
}

double Timer::count() {
	//将时间段转为毫秒
	std::chrono::duration<double, std::ratio<1, 1000>> times = end - begin;

	return times.count();
}
