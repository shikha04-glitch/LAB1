#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct Product {
    string sku;
    string name;
    int quantity;
    double price;
};

int findProductBySKU(Product inventory[], int count, string sku) {
    for (int i = 0; i < count; i++) {
        if (inventory[i].sku == sku) {
            return i;
        }
    }
    return -1;
}

int findProductByName(Product inventory[], int count, string name) {
    for (int i = 0; i < count; i++) {
        if (inventory[i].name == name) {
            return i;
        }
    }
    return -1;
}

void insertProduct(Product inventory[], int &count, int size) {
    if (count >= size) {
        cout << "Error: Inventory capacity exceeded.\n";
        return;
    }

    cin.ignore();
    string sku;
    cout << "Enter Product SKU: ";
    getline(cin, sku);

    int existingIndex = findProductBySKU(inventory, count, sku);
    if (existingIndex != -1) {
        int mode;
        cout << "Duplicate SKU found. Choose an option:\n";
        cout << "1. Reject insertion (TC02)\n";
        cout << "2. Update quantity and price (TC13)\n";
        cout << "Enter choice: ";
        cin >> mode;

        if (mode == 1) {
            cout << "Error: Duplicate SKU. Product already exists.\n";
            return;
        } 
        else if (mode == 2) {
            cout << "Enter new Quantity: ";
            cin >> inventory[existingIndex].quantity;
            cout << "Enter new Price: ";
            cin >> inventory[existingIndex].price;
            cout << "Quantity & price updated for existing product.\n";
            return;
        } 
        else {
            cout << "Invalid choice. No action taken.\n";
            return;
        }
    }

    Product newProduct;
    newProduct.sku = sku;

    cout << "Enter Product Name: ";
    getline(cin, newProduct.name);
    if (newProduct.name.empty()) {
        cout << "Error: Product name cannot be empty.\n";
        return;
    }

    cout << "Enter Quantity: ";
    if (!(cin >> newProduct.quantity) || newProduct.quantity < 0) {
        cout << "Error: Invalid.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << "Enter Price: ";
    cin >> newProduct.price;

    inventory[count] = newProduct;
    count++;
    cout << "Product inserted successfully.\n";
}

void displayInventory(Product inventory[], int count) {
    if (count == 0) {
        cout << "Inventory is empty.\n";
        return;
    }
    cout << "\n--- Inventory List ---\n";
    cout << "SKU\tName\tQuantity\tPrice\n";
    for (int i = 0; i < count; i++) {
        cout << inventory[i].sku << "\t" << inventory[i].name << "\t" 
             << inventory[i].quantity << "\t\t" << inventory[i].price << "\n";
    }
}

void searchBySKU(Product inventory[], int count) {
    cin.ignore();
    string sku;
    cout << "Enter SKU to search: ";
    getline(cin, sku);
    int index = findProductBySKU(inventory, count, sku);
    if (index != -1) {
        cout << "Product Found: " << inventory[index].name 
             << ", Qty: " << inventory[index].quantity 
             << ", Price: " << inventory[index].price << "\n";
    } else {
        cout << "Product not found.\n";
    }
}

void searchByName(Product inventory[], int count) {
    cin.ignore();
    string name;
    cout << "Enter Name to search: ";
    getline(cin, name);
    int index = findProductByName(inventory, count, name);
    if (index != -1) {
        cout << "Product Found: " << inventory[index].sku 
             << ", Qty: " << inventory[index].quantity 
             << ", Price: " << inventory[index].price << "\n";
    } else {
        cout << "Product not found.\n";
    }
}

void deleteProduct(Product inventory[], int &count) {
    cin.ignore();
    string sku;
    cout << "Enter SKU to delete: ";
    getline(cin, sku);
    int index = findProductBySKU(inventory, count, sku);
    if (index != -1) {
        cout << "Product " << inventory[index].name << " removed from inventory.\n";
        for (int i = index; i < count - 1; i++) {
            inventory[i] = inventory[i + 1];
        }
        count--;
    } else {
        cout << "Product not found.\n";
    }
}

int main() {
    const int SIZE = 100;
    Product inventory[SIZE];
    int count = 0;
    int choice;

    do {
        cout << "\nInventory Management System\n";
        cout << "1. Add Product\n";
        cout << "2. Display Inventory\n";
        cout << "3. Search by SKU\n";
        cout << "4. Search by Name\n";
        cout << "5. Delete Product\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: insertProduct(inventory, count, SIZE); break;
            case 2: displayInventory(inventory, count); break;
            case 3: searchBySKU(inventory, count); break;
            case 4: searchByName(inventory, count); break;
            case 5: deleteProduct(inventory, count); break;
            case 6: cout << "Exiting program.\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}