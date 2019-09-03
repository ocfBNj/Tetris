#include "Timer.h"
//Ĭ�ϳ�ʼ��
Timer::Timer() : begin(), end(), dif_time(0.0) {}

void Timer::clear() {
	begin = end;
}


void Timer::setDifTime(double t) {
	dif_time = t;           //����ʱ���
	clear();                //���ö�ʱ��
	start();                //��ʼ��ʱ
}

bool Timer::isTimeOut() {
	stop(); //��ͣ,�Ա����ʱ���
	if (count() >= dif_time) {
		start(); //���¼�ʱ
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
	//��ʱ���תΪ����
	std::chrono::duration<double, std::ratio<1, 1000>> times = end - begin;

	return times.count();
}
