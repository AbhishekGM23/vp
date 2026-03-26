#include <iostream>
using namespace std;

// enum for account type
enum acc_type { SAVING, CURRENT };

// Base class
class account {
protected:
    string holder;
    double balance;

public:
    account(string h, double b) {
        holder = h;
        balance = b;
    }

    virtual void display() {
        cout << "holder : " << holder << endl;
        cout << "balance : " << balance << endl;
    }

    virtual ~account() {}   // virtual destructor
};

// Saving account
class saving_account : public account {
    double interest_rate;
    double fd_rate;

public:
    saving_account(string h, double b, double ir, double fd)
        : account(h, b) {
        interest_rate = ir;
        fd_rate = fd;
    }

    void display() override {
        account::display();
        cout << "interest rate : " << interest_rate << endl;
        cout << "FD rates : " << fd_rate << endl;
    }

    ~saving_account() {
        cout << "saving account of " << holder << " deleted" << endl;
    }
};

// Current account
class current_account : public account {
public:
    current_account(string h, double b) : account(h, b) {}

    ~current_account() {
        cout << "current account of " << holder << " deleted" << endl;
    }
};

// Main
int main() {
    account* acc1 = new saving_account("John", 899.7, 4.5, 6.5);
    acc1->display();

    account* acc2 = new current_account("Mathew", 500);

    delete acc1;
    delete acc2;

    return 0;
}



































#include <iostream>
using namespace std;

// Overload + operator for ostream
ostream& operator+(ostream& out, int val) {
    out << val;
    return out;
}

ostream& operator+(ostream& out, double val) {
    out << val;
    return out;
}

int main() {
    cout + 5 + 5.5;
    cout << endl;
    cout << "This Works!" << endl;
    return 0;
}
