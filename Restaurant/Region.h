#ifndef _REGION_H_
#define _REGION_H_

#include"Generic_DS/Queue.h"
#include"PriorityQueue.h"
#include"List.h"
#include"Rest/Order.h"
#include"GUI/GUI.h"

#include"VIPOrdersComp.h"
#include"MotorCyclesComp.h"
#include"RestingMotorsComp.h"
#include"InServiceMotorsComp.h"
#include"FinishedOrdersComp.h"

class Region
{
private:
	int PromotionLimit;  // Time at which Normal Orders are Promoted to VIP orders
	int AvgWaitingTime, AvgServiceTime; 

	///Orders related data members
	List<Order*> NormalOrders;
	Queue<Order*> FrozenOrders;
	PriorityQueue<Order*, VIPOrdersComp> VipOrders;
	List<Order*> FinishedOrders[3]; //FinishedOrders[TYPE_NRM],	FinishedOrders[TYPE_FROZ],	FinishedOrders[TYPE_VIP]
	int NumNormal, NumVIP, NumFrozen; // Number of Normal, VIP, Frozen orders
	
	///Motorcycles related data members
	PriorityQueue<Motorcycle*, MotorCyclesComp> NormalMotors, FastMotors, FrozenMotors;
	PriorityQueue<Motorcycle*, RestingMotorsComp> RestingMotors;
	int NumNormalMotors, NumFrozenMotors, NumFastMotors, NumRestingMotors;
	PriorityQueue<Motorcycle*, InServiceMotorsComp> InServiceMC; // In service Motorcycles

public:
	Region();
	~Region();

	void SetPromotionLimit(int ts);
	int GetPromotionLimits() const;

	/// Orders related methods
	void AddOrder(Order* pOrd); //Adds passed order object to it's container according to it's type
	bool CancelOrder(int ID); //Cancel normal order if it's not assigned to a motor
	bool PromoteOrder(int ID, double Extramny=0); //promote normal order to VIP order
	void AutomaticPromotion(); // Automatically promote orders if their waiting time exceeds promotion limit
	void IncrementOrdersWT();
	void printOrders(GUI * pGUI);

	/// Motorcycles related methods
	void CheckInServiceMC(int ts);
	void CheckRestMC(int ts);
	void CreateMotorCycles(ifstream &InputFile); // Create motorcycle objects from a file 

	/// Writing information methods
	void FillInfo(string* Order, string* Motorcycle);	//Fill passed srings with Order and MotorCycle info
	void WriteInfo(ofstream & Output);
	int GetAvgWT() const;
	int GetAvgServT() const;
	int GetFinishedOrdersCount() const;

	/// Assign orders to motors methods 
	void AssignMotorCycles(int ts);
	void AssignMotorsToFrozen(int ts);
	void AssignMotorsToNormal(int ts);
	void AssignMotorsToVip(int ts);
};

#endif 
