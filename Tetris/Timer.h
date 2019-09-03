#pragma once

#include <chrono> //C++11

class Timer {
public:
	Timer();
	void clear();                                       //重置计时器

	//可用于设置并判断是否达到给定的时间间隔
	void setDifTime(double t);                          //设置时间差
	bool isTimeOut();                                   //时间到

	//可用于计算时间差
	void start();                                       //开始,记录此刻的时间点
	void stop();                                        //停止,记录此刻的时间点
	double count();                                     //计算时间差
private:
	std::chrono::steady_clock::time_point begin;        //记录开始时间点
	std::chrono::steady_clock::time_point end;          //记录结束时间点
	double dif_time;                                    //记录时间间隔
};