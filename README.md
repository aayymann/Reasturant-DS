# Restaurant Management Application

This is a database management application for a restaurant written in C++. It provides functionalities to manage various aspects of the restaurant including menu items, orders, reservations, and customer information.
This project is an implementation of queues, priority queues, stacks and linked lists data structurs from scratch where each order logic maps to an approproate DS. 

## Features

- **Menu Management**: Add, update, and delete menu items with details such as name, price, and category.
- **Order Management**: Take and manage orders, including adding/removing items, calculating total amount, and marking orders as completed.
- **Reservation Management**: Reserve tables for customers, with options to specify date, time, and number of guests.
- **Customer Management**: Maintain customer information, including contact details and order history.

## Prerequisites

- C++ compiler (supporting C++11 or later)
- Standard Template Library (STL)

## Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/aayymann/Datastrucrues-of-C-plus-plus.git
    ```

2. Compile the source code:

    ```bash
    g++ -o restaurant_app main.cpp menu.cpp order.cpp reservation.cpp customer.cpp -lsqlite3
    ```

3. Run the application:

    ```bash
    ./restaurant_app
    ```

## Usage

1. **Main Menu**: Upon running the application, you will be presented with a main menu with options to manage menu items, orders, reservations, and customers.
2. **Menu Management**: Choose option to manage menu items to add, update, or delete items.
3. **Order Management**: Select option to manage orders to take and process orders.
4. **Reservation Management**: Choose option to manage reservations to make or cancel reservations.
5. **Customer Management**: Select option to manage customers to view or update customer information.
6. **Exit**: Choose option to exit the application.

