#pragma once
#include<iostream>
using namespace std;
#include "Events/Event.h"
#include "Rest\Restaurant.h"

class PromotionEvent :public Event {
private:
	int ExtraMoney;
public:
	PromotionEvent(int Ts, int ID, int Extramoney);
	virtual void Execute(Restaurant* pRest);
};