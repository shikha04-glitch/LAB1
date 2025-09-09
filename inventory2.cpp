#include <iostream>
#include <vector>
#include <utility>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;


vector<pair<int,int>> process_sale(vector<pair<int,int>> inventory, int sku, int qty_sold) {
    vector<pair<int,int>> updated_inventory;
    bool sku_found = false;

    for (auto &item : inventory) {
        int current_sku = item.first;
        int current_qty = item.second;

        if (current_sku == sku) {
            sku_found = true;
            if (current_qty >= qty_sold) {
                updated_inventory.push_back({current_sku, current_qty - qty_sold});
                cout << "Sale processed: " << qty_sold << " units of SKU " << sku << ".\n";
            } else {
                updated_inventory.push_back({current_sku, current_qty});
                cout << "Insufficient stock for SKU " << sku
                     << ". Available: " << current_qty << "\n";
            }
        } else {
            updated_inventory.push_back(item);
        }
    }

    if (!sku_found) {
        cout << "SKU " << sku << " not found in inventory.\n";
    }

    return updated_inventory;
}


vector<int> identify_zero_stock(vector<pair<int,int>> inventory) {
    vector<int> zero_stock_list;
    for (auto &item : inventory) {
        if (item.second == 0) {
            zero_stock_list.push_back(item.first);
        }
    }

    if (!zero_stock_list.empty()) {
        cout << "Zero stock SKUs: [";
        for (size_t i = 0; i < zero_stock_list.size(); i++) {
            cout << zero_stock_list[i];
            if (i != zero_stock_list.size() - 1) cout << ", ";
        }
        cout << "]\n";
    } else {
        cout << "No zero stock items found.\n";
    }

    return zero_stock_list;
}


vector<pair<int,int>> parse_inventory(string input) {
    vector<pair<int,int>> inventory;
    input.erase(remove(input.begin(), input.end(), '['), input.end());
    input.erase(remove(input.begin(), input.end(), ']'), input.end());

    stringstream ss(input);
    string token;

    while (getline(ss, token, ')')) {
        if (token.find('(') != string::npos) {
            int sku, qty;
            char ch;
            stringstream item(token);
            item >> ch >> sku >> ch >> qty;
            inventory.push_back({sku, qty});
        }
    }
    return inventory;
}

int main() {
    string inv_input;
    cout << "Enter Inventory: ";
    getline(cin, inv_input);

    vector<pair<int,int>> inventory = parse_inventory(inv_input);

    int choice;
    cout << "\nChoose operation:\n";
    cout << "1. Process Sale\n";
    cout << "2. Identify Zero Stock\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        int sku, qty;
        cout << "Enter SKU: ";
        cin >> sku;
        cout << "Enter Quantity Sold: ";
        cin >> qty;

        inventory = process_sale(inventory, sku, qty);

        cout << "Updated Inventory: [";
        for (size_t i = 0; i < inventory.size(); i++) {
            cout << "(" << inventory[i].first << ", " << inventory[i].second << ")";
            if (i != inventory.size() - 1) cout << ", ";
        }
        cout << "]\n";
    }
    else if (choice == 2) {
        identify_zero_stock(inventory);
    }
    else {
        cout << "Invalid choice.\n";
    }

    return 0;
}