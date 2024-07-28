
#include <iostream>
#include "atmcontroller.h"

using namespace std;


void ATMController::set_atm(int _cash, string _sn, bool cash_bin, bool card_reader) {
	ATMController::residual_cash = _cash;
	ATMController::cash_bin_working = cash_bin;
	ATMController::serial_number = _sn;
	ATMController::card_reader_working = card_reader;

}
