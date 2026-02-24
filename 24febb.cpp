#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    double usd_amount;
    double exchange_rate = 82.50; // example rate for usd to inr

    cout << "--- simple currency converter ---" << endl;
    cout << "enter amount in usd: ";
    cin >> usd_amount;

    double inr_result = usd_amount * exchange_rate;

    // fixed and setprecision(2) keeps it to 2 decimal places
    cout << fixed << setprecision(2);
    cout << "$" << usd_amount << " is approx ₹" << inr_result << endl;

    return 0;
}