#include <iostream>
#include <vector>

using namespace std;

class Order;
class Customer;
class Driver;

class Dish
{
public:
    string name;
    double price;

    Dish(const string &itemName, double itemPrice) : name(itemName), price(itemPrice) {}
};

class Restaurant
{
public:
    vector<Dish> menu;

    void updateMenu(const vector<Dish> &newMenu)
    {
        menu = newMenu;
    }

    void prepareOrder(const Order &order)
    {
        // logic for preparing the order
    }

    bool sendOrder(const Order &order, const Driver &driver) const
    {
        // Logic for the restaurant to be the order to driver
        // return true if the driver accept the delivery, false if not
        return true;
    }

    // Other restaurant functionalities
};

class Order
{
public:
    vector<Dish> dishes;
    double totalPrice;

    void addDish(const Dish &dish)
    {
        dishes.push_back(dish);
        totalPrice += dish.price;
    }

    // Other order functionalities
};

class Customer
{
public:
    string name;
    string address;

    Order getOrder() const
    {
        Order order;
        // Logic for customer to get order details
        order.addDish(Dish("Pizza", 10.0));
        order.addDish(Dish("Burger", 5.0));
        return order;
    } 

    // Other customer functionalities
};

class Driver
{
public:
    string name;

    void deliverOrder(const Order &order, const Customer &customer) const
    {
        // Logic for delivering the order
        cout << "Order delivered to " << customer.name << " at " << customer.address << "." << endl;
    }

    static Driver findSuitableDriver()
    {
        Driver driver;
        // Logic to find a suitable driver based on certain criteria
        return driver;
    }

    // Other driver functionalities
};

// Facade class
class FoodDeliveryFacade
{
public:
    Restaurant restaurant;
    Customer customer;
    Order order;
    Driver driver;

    FoodDeliveryFacade(Restaurant r, Customer c)
    {
        restaurant = r;
        customer = c;
        order = customer.getOrder();
        driver = Driver::findSuitableDriver();
    }

    void placeOrder()
    {
        Order order = customer.getOrder();
        if (order.dishes.empty())
        {
            cout << "No dishes in the order." << endl;
            cout << "The order is canceled!" << endl;
        }
        else
        {
            Driver driver = Driver::findSuitableDriver();
            if (driver.name == "")
            {
                cout << "No suitable driver found." << endl;
                cout << "The order is canceled!" << endl;
            }
            else
            {
                restaurant.prepareOrder(order);
                if (restaurant.sendOrder(order, driver))
                {
                    driver.deliverOrder(order, customer);

                    cout << "Order placed successfully!" << endl;
                    // perform transactions for the customer, driver and restaurant...
                    cout << "Here is your receipt:" << endl;
                    // Show the receipt
                }
                else
                {
                    cout << "The order is canceled!" << endl;
                    
                }
            }
        }
    }
};

int main()
{
    // Example usage
    Restaurant restaurant;
    Customer customer;
    FoodDeliveryFacade deliveryFacade(restaurant, customer);
    deliveryFacade.placeOrder();

    return 0;
}
