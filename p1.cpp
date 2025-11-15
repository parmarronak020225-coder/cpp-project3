
#include <iostream>
using namespace std;

class Vehicle {
protected:
    int vehicleID;
    string manufacturer;
    string model;
    int year;

public:
    static int totalVehicles;

    // Constructor
    Vehicle() {
        vehicleID = 0;
        manufacturer = "";
        model = "";
        year = 0;
        totalVehicles++;
    }

    Vehicle(int id, string man, string mod, int yr) {
        vehicleID = id;
        manufacturer = man;
        model = mod;
        year = yr;
        totalVehicles++;
    }

    // Getters & Setters
    void setID(int id) { vehicleID = id; }
    void setManufacturer(string man) { manufacturer = man; }
    void setModel(string mod) { model = mod; }
    void setYear(int yr) { year = yr; }

    int getID() { return vehicleID; }

    void display() {
        cout << "ID: " << vehicleID << endl;
        cout << "Manufacturer: " << manufacturer << endl;
        cout << "Model: " << model << endl;
        cout << "Year: " << year << endl;
    }

    // Destructor
    ~Vehicle() {}
};

int Vehicle::totalVehicles = 0;

// ------------------------- DERIVED CLASSES -------------------------

// Single Inheritance
class Car : public Vehicle {
public:
    string fuelType;

    Car() : Vehicle() {}

    Car(int id, string man, string mod, int yr, string fuel)
        : Vehicle(id, man, mod, yr) {
        fuelType = fuel;
    }

    void display() {
        Vehicle::display();
        cout << "Fuel Type: " << fuelType << endl;
    }
};

// Multilevel Inheritance
class ElectricCar : public Car {
public:
    int batteryCapacity;

    ElectricCar() : Car() {}

    ElectricCar(int id, string man, string mod, int yr, string fuel, int battery)
        : Car(id, man, mod, yr, fuel) {
        batteryCapacity = battery;
    }

    void display() {
        Car::display();
        cout << "Battery Capacity: " << batteryCapacity << endl;
    }
};

// Base for multiple inheritance
class Aircraft {
public:
    int flightRange;

    Aircraft() { flightRange = 0; }

    Aircraft(int range) { flightRange = range; }

    void displayAircraft() {
        cout << "Flight Range: " << flightRange << endl;
    }
};

// Multiple Inheritance
class FlyingCar : public Car, public Aircraft {
public:
    FlyingCar() : Car(), Aircraft() {}

    FlyingCar(int id, string man, string mod, int yr, string fuel, int range)
        : Car(id, man, mod, yr, fuel), Aircraft(range) {}

    void display() {
        Car::display();
        Aircraft::displayAircraft();
    }
};

// Hierarchical Inheritance
class Sedan : public Car {
public:
    Sedan(int id, string man, string mod, int yr, string fuel)
        : Car(id, man, mod, yr, fuel) {}
};

class SUV : public Car {
public:
    SUV(int id, string man, string mod, int yr, string fuel)
        : Car(id, man, mod, yr, fuel) {}
};

// Multilevel from ElectricCar
class SportsCar : public ElectricCar {
public:
    int topSpeed;

    SportsCar(int id, string man, string mod, int yr,
              string fuel, int battery, int speed)
        : ElectricCar(id, man, mod, yr, fuel, battery) {
        topSpeed = speed;
    }

    void display() {
        ElectricCar::display();
        cout << "Top Speed: " << topSpeed << endl;
    }
};

// ------------------------- VEHICLE REGISTRY -------------------------

class VehicleRegistry {
public:
    Vehicle* arr[50];
    int count;

    VehicleRegistry() {
        count = 0;
    }

    void add(Vehicle* v) {
        arr[count] = v;
        count++;
        cout << "Vehicle Added Successfully.\n";
    }

    void viewAll() {
        if (count == 0) {
            cout << "No vehicles available.\n";
            return;
        }

        for (int i = 0; i < count; i++) {
            cout << "\n--- Vehicle " << i + 1 << " ---\n";
            arr[i]->display();
        }
    }

    void search(int id) {
        for (int i = 0; i < count; i++) {
            if (arr[i]->getID() == id) {
                cout << "Vehicle Found:\n";
                arr[i]->display();
                return;
            }
        }
        cout << "Vehicle ID not found.\n";
    }
};

// ------------------------- MAIN FUNCTION -------------------------

int main() {
    VehicleRegistry vr;
    int choice;

    while (true) {
        cout << "\n--- Vehicle Registry Menu ---\n";
        cout << "1. Add Vehicle\n";
        cout << "2. View All Vehicles\n";
        cout << "3. Search Vehicle by ID\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int type;
            cout << "\nSelect Vehicle Type:\n";
            cout << "1. Car\n2. Electric Car\n3. Aircraft\n4. Flying Car\n5. Sedan\n6. SUV\n7. Sports Car\n";
            cout << "Enter type: ";
            cin >> type;

            int id, yr, battery, speed, range;
            string man, mod, fuel;

            cout << "Enter ID: ";
            cin >> id;
            cout << "Manufacturer: ";
            cin >> man;
            cout << "Model: ";
            cin >> mod;
            cout << "Year: ";
            cin >> yr;

            if (type == 1) {
                cout << "Fuel Type: ";
                cin >> fuel;
                vr.add(new Car(id, man, mod, yr, fuel));
            }
            else if (type == 2) {
                cout << "Fuel: ";
                cin >> fuel;
                cout << "Battery Capacity: ";
                cin >> battery;
                vr.add(new ElectricCar(id, man, mod, yr, fuel, battery));
            }
            else if (type == 3) {
                cout << "Flight Range: ";
                cin >> range;
                // vr.add(new Aircraft(range));
            }
            else if (type == 4) {
                cout << "Fuel: ";
                cin >> fuel;
                cout << "Flight Range: ";
                cin >> range;
                vr.add(new FlyingCar(id, man, mod, yr, fuel, range));
            }
            else if (type == 5) {
                cout << "Fuel: ";
                cin >> fuel;
                vr.add(new Sedan(id, man, mod, yr, fuel));
            }
            else if (type == 6) {
                cout << "Fuel: ";
                cin >> fuel;
                vr.add(new SUV(id, man, mod, yr, fuel));
            }
            else if (type == 7) {
                cout << "Fuel: ";
                cin >> fuel;
                cout << "Battery: ";
                cin >> battery;
                cout << "Top Speed: ";
                cin >> speed;
                vr.add(new SportsCar(id, man, mod, yr, fuel, battery, speed));
            }
        }

        else if (choice == 2) {
            vr.viewAll();
        }

        else if (choice == 3) {
            int id;
            cout << "Enter ID to search: ";
            cin >> id;
            vr.search(id);
        }

        else if (choice == 4) {
            cout << "Exiting...\n";
            break;
        }
    }

    return 0;
}
