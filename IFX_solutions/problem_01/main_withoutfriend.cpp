#include <iostream>
#include <string>

using namespace std;

class account {
public:
    enum class TYPE {
        SAVING,
        CURRENT
    };
    virtual ~account() {} 
    virtual double balance() const = 0;
    virtual double interest_rate() const = 0;
    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
    virtual string holder() const = 0;
    virtual account::TYPE type() const = 0; 
};

class saving_account : public account {
private:
    string holder_name;
    double balance_amount;
public:
    saving_account(string holder) : holder_name(holder), balance_amount(0) {}
    double balance() const override { return balance_amount; }
    double interest_rate() const override { return 4.5; } // Assuming a fixed interest rate for a savings account
    void deposit(double amount) override { balance_amount += amount; }
    void withdraw(double amount) override { balance_amount -= amount; }
    string holder() const override { return holder_name; }
    account::TYPE type() const override { return account::TYPE::SAVING; }
};

class current_account : public account {
private:
    string holder_name;
    double balance_amount;
public:
    current_account(string holder) : holder_name(holder), balance_amount(0) {}
    double balance() const override { return balance_amount; }
    double interest_rate() const override { return 4.5; } // Assuming a fixed interest rate for a current account
    void deposit(double amount) override { balance_amount += amount; }
    void withdraw(double amount) override { balance_amount -= amount; }
    string holder() const override { return holder_name; }
    account::TYPE type() const override { return account::TYPE::CURRENT; } // Specify the type of account
};

double fixed_deposit_rate(account *ac){
    return (ac->type()==account::TYPE::SAVING) ?6.5:4.0;
}

void delete_account(account *ac){
    cout<< (ac->type() == account::TYPE::SAVING ? "saving account":"current account")<<" of "<<ac->holder()<<" deleted"<<endl;
    delete ac;}

void print_saving_account(account *ac)
{
    if(ac->type()==account::TYPE::SAVING)
    {
        cout << "holder : "<< ac->holder()<<endl;
        cout << "balance : " << ac->balance()<<endl;
        cout <<"interest rate : "<< ac->interest_rate()<<endl;
        cout<<"FD rates : "<< fixed_deposit_rate(ac)<<endl;
    }
}

saving_account* conver_CA_to_SA(account *ac)
{
    if(ac->type()==account::TYPE::CURRENT)
    {
        if(ac->balance() >= 0)
        {
            account *old=ac;

            saving_account *new_s_ac = new saving_account(ac->holder());
            new_s_ac->deposit(ac->balance());
            delete old;
            cout<<"Converted to Saving Account."<<endl;

            return new_s_ac;
            
        }
        else
        {
            cout<<"Saving Account not possible."<<endl;
        }

    }
    else
    {
        cout<<"Account is already a Saving Account."<<endl;
    }
    return 0;
}

int main ()
{
    saving_account *s_ac = new saving_account("john");
    s_ac->deposit(1000);
    s_ac->withdraw(100.3);
    print_saving_account(s_ac);
    delete_account(s_ac);
    cout<<endl;

    current_account *c_ac = new current_account("Mathew");
    c_ac->deposit(10);
    c_ac->withdraw(100.3);
    print_saving_account(c_ac);
    delete_account(c_ac);
    cout<<endl;

    current_account *c_ac1 = new current_account("Shiv");
    saving_account *s_ac1 ;
    c_ac1->deposit(50000);
    c_ac1->withdraw(1000);
    print_saving_account(c_ac1);
    s_ac1=conver_CA_to_SA(c_ac1);
    print_saving_account(s_ac1);
    cout<<endl;

    return EXIT_SUCCESS;
}