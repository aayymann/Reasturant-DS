# Restaurant Management Application
## About 
This is a capstone project for "Data structures & Algorithms" course, written in c++ to show skills in object-oriented programming, problem solving & handling big projects. CMUGraphics library was used provided by our educators.

This project is an implementation of queues, priority queues, stacks and linked lists data structurs from scratch where each order logic maps to an approproate DS. 


The interface has three modes, Step by step, Interactive & Silent where is shows

1. The number of active(waiting) orders of each order type sorted where VIP are put first then Frozen and Normal.
2. The number of available motorcycles of each type.
3. Type & ID for ALL motorcycles and orders that were assigned in the last timestep.

All the restaurant information is to be read from a text file.






## Features

- **Menu Management**:
  - Three main order types ( Normal, VIP & Frozen ).
  - Three main Motorcycles types ( Normal, Fast, Frozen ).
  - Four branches. Can be increased easily.
- **Delivery Management**:
   - VIP orders to be delivered first with any of the available motorcycles starting from Fast then Normal then Frozen motorcycles.
   - Frozen orders to be delivered after VIP on Frozen motorcycles only.
   - Normal orders to be delivered lastly using Normal motorcycles and Fast if there are no available Normal ones.
   - For VIP orders, orders with the highest pill or long waiting time are served first. For Normal & Frozen, orders that arrived first are served first.
   - Normal orders can be promoted to VIP orders with extra money.
- **Order Management**:
  - Normal orders can be promoted automatically to VIP orders if it waited for more than a specified limit.
  - Normal Orders can be canceled if it wasn't served.

## Output
After each session an output file will be exported that includes:

1. The number of delivered orders for each type and region sorted by it's finish time and serving time.
2. Each order waiting time, ID, serving time, arrival time and finish time.
3. Average waiting time and Average serving time.
4. Technical restrictions:
It is not allowed to use C++ STL. All data structures used must be implemented in the project.
CMUGraphics library must be used for the interface.

