
#include <iostream>
#include "atmcontroller.h"
#include "fakebankAPI.h"
using namespace std;

struct card
{
    string pin_number = "";
    bool status = true;
    vector<string> linked_account{ "000", "123", "321" };
    vector<long> account_balance{1, 12, 13};
};

int main()
{
    card fake_card;
    fake_card.pin_number = "SN123";
    fake_card.status = true;

    ATMController atmc;
    atmc.set_atm(1000, "SN2000", true, true); 
    // residual dollors, Serial number, cash_bin_work_status, card_reader_status 

    FakeBankAPI bank;

    for (int i = 1; i <= 10; i++) {
        cout << "Insert your card" << endl;
        cout << "Checking your card" << " try num = " << to_string(i) << "/10" << endl;

        while (atmc.card_reader_working && atmc.cash_bin_working) {
            bool available_card = false;

            if (fake_card.status == false) {
                cout << "Check your card status (magnet tape or IC ...)" << endl;
                break;
            }
            else {
                cout << "Checking your card Pin Number ..." << endl;
                available_card = bank.check_pin_number(fake_card.pin_number);

                if (available_card) {
                    cout << "Your cad Pin Number is available" << endl;

                    if (fake_card.linked_account.size() > 0) {
                        cout << "Choose your linked Account with Account Index" << endl;
                        for (int i = 0; i < fake_card.linked_account.size(); i++) {
                            cout << to_string(i) << " id account : " << fake_card.linked_account[i] << endl;
                        }

                        string acc = "";
                        int acc_id = -1;
                        while (1) {
                            cin >> acc_id;
                            if ((acc_id > fake_card.linked_account.size()) || (acc_id < 0)) {
                                cout << "Choose corrent Account index" << endl;
                            }
                            else {
                                cout << "You choose available account, Index : " << to_string(acc_id) << endl;
                                break;
                            }
                        }

                        while (1) {
                            cout << "What do you want to do with your account?" << endl;
                            cout << "Choose the job index" << endl;
                            cout << "1. See Balace" << endl;
                            cout << "2. Deposit" << endl;
                            cout << "3. Withdraw" << endl;
                            cout << "4. Exit" << endl;

                            int job_id = 0;
                            while (1) {
                                cin >> job_id;
                                if ((job_id < 1) && (job_id > 4)) {
                                    cout << "Choose corrent Job index" << endl;
                                }
                                else break;
                            }

                            switch (job_id) {
                                case 1:
                                {
                                    cout << "See balace" << endl;
                                    cout << to_string(fake_card.account_balance[acc_id]) << endl;
                                    break;
                                }
                                case 2:
                                {
                                    cout << "Deposit" << endl;
                                    cout << "How much do you deposit?" << endl;
                                    int deposit_cash = 0;
                                    while (1) {
                                        cin >> deposit_cash;
                                        if (deposit_cash < 0) {
                                            cout << "Positive number available" << endl;
                                        }
                                        else {
                                            fake_card.account_balance[acc_id] += deposit_cash;
                                            atmc.residual_cash += deposit_cash;
                                            break;
                                        }
                                    }
                                    break;
                                }
                                case 3:
                                {
                                    cout << "Withdraw" << endl;
                                    cout << "How much do you withdraw?" << endl;
                                    int withdraw_cash = 0;
                                    while (1) {
                                        cin >> withdraw_cash;
                                        if (withdraw_cash < 0) {
                                            cout << "Positive number available" << endl;
                                        }
                                        else if (fake_card.account_balance[acc_id] < withdraw_cash){
                                            cout << "Not available because withdraw money is bigger than your account balace" << endl;
                                            cout << "Retype corrent withdraw money" << endl;
                                        }
                                        else if (atmc.residual_cash < withdraw_cash) {
                                            cout << "Sorry, not enough money in ATM" << endl;
                                            cout << "Max available money is " << to_string(atmc.residual_cash) << endl;
                                        }
                                        else {
                                            fake_card.account_balance[acc_id] -= withdraw_cash;
                                            atmc.residual_cash -= withdraw_cash;
                                            break;
                                        }
                                    }

                                    break;
                                }
                                case 4:
                                {
                                    cout << "Exit" << endl;
                                    return 0;
                                }
                            }
                        }
                    }
                    else {
                        cout << "There are no linked Accounts, please use another card." << endl;
                        break;
                    }

                }
                else {
                    cout << "Check your card again" << endl;
                    break;

                }

            }

        }

    }

    return 0;
}