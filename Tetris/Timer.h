#pragma once

#include <chrono> //C++11

class Timer {
public:
	Timer();
	void clear();                                       //���ü�ʱ��

	//���������ò��ж��Ƿ�ﵽ������ʱ����
	void setDifTime(double t);                          //����ʱ���
	bool isTimeOut();                                   //ʱ�䵽

	//�����ڼ���ʱ���
	void start();                                       //��ʼ,��¼�˿̵�ʱ���
	void stop();                                        //ֹͣ,��¼�˿̵�ʱ���
	double count();                                     //����ʱ���
private:
	std::chrono::steady_clock::time_point begin;        //��¼��ʼʱ���
	std::chrono::steady_clock::time_point end;          //��¼����ʱ���
	double dif_time;                                    //��¼ʱ����
};