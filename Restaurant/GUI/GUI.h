#ifndef __GUI_H_
#define __GUI_H_

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\Defs.h"

#include "..\Rest\Order.h"

#include <string>
using namespace std;

class GUI
{

private:
	window *pWind;
	color OrdersClrs[TYPE_CNT];


	// Some Static Constant Data Members: ---------------------

	static const int
		WindWidth = 1200, WindHeight = 650,		//Window width and height
		StatusBarHeight = 150,	//Status Bar Height
		MenuBarHeight = 50,		//Menu Bar Height (distance from top of window to bottom line of menu bar)
		MenuItemWidth = 80,		//Width of each item in menu bar menu

		DrawingAreaHeight = WindHeight - MenuBarHeight - StatusBarHeight,
		YHalfDrawingArea = MenuBarHeight + DrawingAreaHeight / 2, //The y coordinate of half the Drawing area

		RestStartX = (int)(WindWidth * 0.4), //The x coordinate of the upper left corner of the Rest
		RestEndX = (int)(WindWidth * 0.6),   //The x coordinate of the lower right corner of the Rest

		RestWidth = RestEndX - RestStartX, //The width of the Rest (Note: the Rest is a Square)		

		RestStartY = YHalfDrawingArea - RestWidth / 2, //The y coordinate of the upper left corner of the Rest
		RestEndY = YHalfDrawingArea + RestWidth / 2,   //The y coordinate of the lower right corner of the Rest


		FontSize = 20,	//font size used to draw orders ID on Interface
		OrderWidth = 2 * FontSize,	//width of the order to be drawn on GUI
		OrderHeight = FontSize,		//height of the order to be drawn on GUI


		MaxHorizOrders = ((WindWidth - RestWidth) / 2) / (OrderWidth + 1),		//The max no. of orders the can be drwan in on Horizontal line in a region
		MaxVerticalOrders = (DrawingAreaHeight / 2) / (OrderHeight + 1),   //The max no. of orders the can be drwan in on Horizontal line in a region


		//Max no of orders that can be drawn in a single region
		MaxRegionOrderCount = MaxHorizOrders * MaxVerticalOrders;

	//////

	int OrderCount;		//the total number of orders to be drawn

	Order * OrdListForDrawing[MaxPossibleOrdCnt]; // This Array of Pointers is used for drawing elements in the GUI
	//NOTES: 
	//Orders are assumed to be sorted by arrival time
	// At every time step, you should update those pointers 
	// to point to the current waiting orders only

	// array = [ VIPorders,,, FrozenOrders,,, NormalOrders,,,]
	// the first frozen order index
	int FrozenIndex;

	// first Normal order Index
	int NormalIndex;

	int priority(Order* ptr);

	//draws ONE order 
	void DrawSingleOrder(Order* pO, int RegionCount) const;

	//drwas ALL orders in OrdListForDrawing
	void DrawOrders() const;

	// prints a message in the passed coordinates
	void DrawString(const int iX, const int iY, const string Text);

	// draws the restaurant area
	void DrawRestArea() const;


	void ClearStatusBar() const;
	void ClearDrawingArea() const;

public:
	GUI();
	~GUI();

	// waits a user click from the user
	void waitForClick() const;

	// reads a string (keyboard input) from the user
	string GetString() const;

	// print given strings on status bar. Each string represent a new line
	void PrintMessage(string msg, string msg1 = "\0", string msg2 = "\0", string msg3 = "\0", string msg4 = "\0", string msg5 = "\0") const; // prints a message in the status bar

	//@return number of orders in the GUI list
	int GetOrderCount();

	void UpdateInterface();

	//Adds a new order to the drawing list
	void AddOrderForDrawing(Order* pOrd);

	//resets drawing list (should be called every timestep after drawing)
	void ResetDrawingList();

	//Remove item for the drawing list
	void Remove(int id);

	//returns the mode of the program
	PROG_MODE getGUIMode() const;

};

#endif