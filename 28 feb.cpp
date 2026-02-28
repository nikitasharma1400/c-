#include <iostream>
#include <vector>
#include <string>
#include <random>

using namespace std;

int main() {
    vector<string> advice = {
        "if at first you don't succeed, that stuff is not for you",
        "Having a bad day? No worries! Wear sunglasses. Now you’re having a bad evening",
        "Its very expensive to eat 3 times a day. Wake up later, miss breakfast, and save money",
    };

    random_device rd;
    mt19937 gen(rd());
    
    cout << "need advice? press enter. (type 'q' to quit)" << endl;
    
    string input;
    while (getline(cin, input) && input != "q") {
        uniform_int_distribution<> dis(0, advice.size() - 1);
        cout << "> " << advice[dis(gen)] << "\n\n";
    }
    
    return 0;
}