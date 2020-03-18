#pragma once
#include "..\Restaurant\Rest\Motorcycle.h"
#include "..\Restaurant\GUI\GUI.h"
#include"..\Restaurant\List.h"
#include"..\Restaurant\VIPPQ.h"
#include "..\Restaurant\Rest\Order.h"
#include "MCPQ.h"
#include"MCSpeedPQ.h"
#include"RestingMotorsPQ.h"
#include"FOPQ.h"

class Region {
private:
	List<Order*> NormalOrders;
	VIPPQ VIPQueue;
	Queue<Order*> FrozenOrders;

	int NormalOrder;
	int VIPOrder;
	int FrozenOrder;
	List <Order*> FinishedOrders;
	MCSpeedPQ NormalMotorCycles;
	MCSpeedPQ FastMotorCycles;
	MCSpeedPQ FrozenMotorCycles;
	RestingMotorsPQ RestingMotors;

	int NumofRestMotors;


	MCPQ InServiceMC;
	int FrozenMotorcycle;
	int FastMotorCycle;
	int NormalMotorCycle;
	int AverageWaitingTime;
	int AverageServiceTime;
	int PromotionLimit;  // Time for Normal Orders to be Promoted Autimatically
	List<Order*> NormalsDone;
	List<Order*> VIPDone;
	List<Order*> FrozensDone;
public:
	Region();
	//Takes order and distributes due to Type, For Each Type
	void HandleOrder(Order* pOrd);  
	void CreateMotorcycle(int Speed,MC_TYPE type,int NumberofMC=1);
	
	void OrdersDone(int &Normal);

	//Prints Orders to the GUI
	void printOrders(GUI * pGUI);

	//Assiging Motors to VIP orders with limitaions
	void AssignVIPToMotorCycles(int ts);  

	//Assiging Motors to NOrmal orders with limitaions
	void AssignNormalToMotorCycles(int ts);  

	//Assiging Motors to Frozen orders with limitaions
	void AssignMotorFrzoenToCycles(int ts);
	
	/* Call the 3 Assign Motors to be called in Reasturant
	TO BE CHECKED IF ALL MOTORCYCLES ARE OUT WHEN WE HANDEL WAITING TIME*/
	void AssignMotorCycles(int ts);   

	//Cancels From Normal List Only according to region
	bool CancelOrderRegion(int id);	

	// Setting Promotion Limit to the Number Read from The Input File sent by the reasturant
	void SetPromotionLimit(int pl);
	int GetPromotionLimit();
	Order* Promote(int id , int extraM=0);
	
	void TazbeetMakan(int ts);

	//Automatically promote order if it's waiting time is bigger than promotion limit
	void AutomaticPromotion();

	//Fill passed srings with Order, MotorCycle and Time info
	void GetInfo(string* Order, string* Motorcycle, string*Time);	


	//Set waiting times of orders each timestep
	void IncrementOrdersWT();

	//Getter for AverageWaiting Time to be called in the Resturant
	int GetAverageWaitingTime();


	//Getter for AverageSerive Time to be called in the Resturant
	int GetAverageServiceTime();
	//to be called in he res  . to be called in every timestep in Interactive mode
	int GetNumberOFFinishedOrders();

	//to be called in Res
	void DistibuteMotors(int ts);
	void WriteFile(ofstream &OutFile);
	void GetFinishedOrders(FOPQ& finishedOrders);
	~Region();
};
