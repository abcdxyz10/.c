#include <iostream>
using namespace std;

int countOnes(string s) {
    int count = 0;
    for (char c : s) {
        if (c == '1') count++;
    }
    return count;
}

int main() {
    string data;
    int choice;
    cout << "Enter binary string: ";
    cin >> data;

    cout << "Choose Parity Type:\n";
    cout << "1. Even Parity\n";
    cout << "2. Odd Parity\n";
    cin >> choice;

    int ones = countOnes(data);
    char parityBit;

    if (choice == 1) {
        if (ones % 2 == 0)
            parityBit = '0';
        else
            parityBit = '1';
    }
    else if (choice == 2) {
        if (ones % 2 == 0)
            parityBit = '1';
        else
            parityBit = '0';
    }

    string transmitted = data + parityBit;

    cout << "\n--- SENDER SIDE ---\n";
    cout << "Original Data:   " << data << endl;
    cout << "Parity Bit:      " << parityBit << endl;
    cout << "Transmitted Data:" << transmitted << endl;
    string received;
    cout << "\nEnter received binary string: ";
    cin >> received;

    int receivedOnes = countOnes(received);
    bool isCorrect;

    if (choice == 1) {
        isCorrect = (receivedOnes % 2 == 0);
    } else {
        isCorrect = (receivedOnes % 2 == 1);
    }

    cout << "\n--- RECEIVER SIDE ---\n";
    if (isCorrect)
        cout << "Status: No Error (Data is correct)\n";
    else
        cout << "Status: ERROR detected (Data corrupted)\n";

    return 0;
}
