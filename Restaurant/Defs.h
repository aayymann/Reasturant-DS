#ifndef __DEFS_H_
#define __DEFS_H_


//The four regions: A, B, C , and D
enum REGION {	
	A_REG,
	B_REG,
	C_REG,
	D_REG,
	REG_CNT		//Total number of regions
};


enum ORD_TYPE	//types of orders
{
	TYPE_NRM,	//normal order
	TYPE_FROZ,	//frozen
	TYPE_VIP,	//VIP
	TYPE_CNT	//Number of types

};

enum MOTOR_TYPE	//types of Motorcycles
{
	NORMAL,			//normal 
	FROZEN,			//frozen
	FAST,			//fast
	MOTOR_TYPE_CNT	//Number of types
};

enum STATUS	//status of motorcycles
{
	IDLE,	//Waiting to be assigned at order
	SERV,	//Delivering an order but hasn't returned yet.
	REST, //Resting from last delivery 
};


enum PROG_MODE	//mode of the program interface
{
	MODE_INTR,	//interactive mode
	MODE_STEP,	//Step-by-step mode
	MODE_SLNT,	//Silent mode
	MODE_CNT	//number of possible modes
};


constexpr int MaxPossibleOrdCnt = 999; 
constexpr char letters[26] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' }; // Used for regions

#endif