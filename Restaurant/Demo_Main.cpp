//#include "Drawing.h"
#include "List.h"
#include "Rest\Restaurant.h"
#include "GUI\GUI.h"
#include"VIPPQ.h"
#include"Rest/Order.h"

int main()
{
	
	Restaurant* pRest = new Restaurant;
	pRest->RunSimulation();
	
	delete pRest;
	return 0;
	
}


/*Order* norder = new Order(1, TYPE_NRM, A_REG);
norder->SetMoney(15); norder->SetDistance(10);
Order* aorder = new Order(1, TYPE_NRM, A_REG);
aorder->SetMoney(17); aorder->SetDistance(18);
Order* border = new Order(1, TYPE_NRM, A_REG);
border->SetMoney(50); border->SetDistance(20);
Order* corder = new Order(1, TYPE_NRM, A_REG);
corder->SetMoney(15); corder->SetDistance(500);

Order* lorder = new Order(1, TYPE_NRM, A_REG);
lorder->SetMoney(1); lorder->SetDistance(2);

Order* korder = new Order(1, TYPE_NRM, A_REG);
korder->SetMoney(18); korder->SetDistance(22);

Order* dorder = new Order(1, TYPE_NRM, A_REG);
dorder->SetMoney(0); dorder->SetDistance(0);

Order* vorder = new Order(1, TYPE_NRM, A_REG);
vorder->SetMoney(1500); vorder->SetDistance(5000);


VIPPQ* list=new VIPPQ;
list->enqueue(norder);
list->enqueue(aorder);
list->enqueue(border);
list->enqueue(corder);
list->enqueue(lorder);
list->enqueue(korder);
list->enqueue(dorder);
list->enqueue(vorder);

list->PrintQueue();

return 0;*/