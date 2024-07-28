

#include <iostream>
#include <string>

using namespace std;

class ATMController {
private:
	int num = 0;

public:
	string serial_number = "";
	bool cash_bin_working = true;
	int residual_cash = 0; // dollers
	bool card_reader_working = true; // for test card reader device 


	void set_atm(int _cash, string _sn, bool cash_bin, bool card_reader);

};
