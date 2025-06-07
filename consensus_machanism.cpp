#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

struct Miner {
    int id;
    int power;
};

struct Staker {
    int id;
    int stake;
};

struct Delegate {
    int id;
    int votes;
};

int main() {
    srand(time(0));

    // Create 3 miners with random power (1 to 100) for PoW
    vector<Miner> miners;
    for (int i = 1; i <= 3; i++) {
        Miner m;
        m.id = i;
        m.power = rand() % 100 + 1;
        miners.push_back(m);
    }

    // Create 3 stakers with random stake (1 to 100) for PoS
    vector<Staker> stakers;
    for (int i = 1; i <= 3; i++) {
        Staker s;
        s.id = i;
        s.stake = rand() % 100 + 1;
        stakers.push_back(s);
    }

    // Create 3 delegates with votes initialized to 0 for DPoS
    vector<Delegate> delegates;
    for (int i = 1; i <= 3; i++) {
        Delegate d;
        d.id = i;
        d.votes = 0;
        delegates.push_back(d);
    }

    // Simulate 3 voters, each voting for a random delegate
    for (int i = 0; i < 3; i++) {
        int choice = rand() % 3; // 0 to 2
        delegates[choice].votes++;
    }

    // PoW: Select miner with highest power
    Miner selected_miner = miners[0];
    for (const auto& m : miners) {
        if (m.power > selected_miner.power) {
            selected_miner = m;
        }
    }
    cout << "PoW:" << endl;
    cout << "Miners:" << endl;
    for (const auto& m : miners) {
        cout << "Miner " << m.id << ": power " << m.power << endl;
    }
    cout << "Selected: Miner " << selected_miner.id << " with power " << selected_miner.power << endl;
    cout << "Explanation: The miner with the highest computational power is selected." << endl;
    cout << endl;

    // PoS: Select staker with highest stake
    Staker selected_staker = stakers[0];
    for (const auto& s : stakers) {
        if (s.stake > selected_staker.stake) {
            selected_staker = s;
        }
    }
    cout << "PoS:" << endl;
    cout << "Stakers:" << endl;
    for (const auto& s : stakers) {
        cout << "Staker " << s.id << ": stake " << s.stake << endl;
    }
    cout << "Selected: Staker " << selected_staker.id << " with stake " << selected_staker.stake << endl;
    cout << "Explanation: The staker with the highest stake is selected." << endl;
    cout << endl;

    // DPoS: Select delegate randomly based on votes
    int total_votes = 0;
    for (const auto& d : delegates) {
        total_votes += d.votes;
    }
    Delegate selected_delegate = delegates[0]; // Default in case total_votes is 0
    if (total_votes > 0) {
        int r = rand() % total_votes;
        int accumulated = 0;
        for (const auto& d : delegates) {
            accumulated += d.votes;
            if (accumulated > r) {
                selected_delegate = d;
                break;
            }
        }
    }
    cout << "DPoS:" << endl;
    cout << "Delegates:" << endl;
    for (const auto& d : delegates) {
        cout << "Delegate " << d.id << ": votes " << d.votes << endl;
    }
    cout << "Selected: Delegate " << selected_delegate.id << " with " << selected_delegate.votes << " votes" << endl;
    cout << "Explanation: A delegate is selected randomly, with the probability proportional to the number of votes they have." << endl;

    return 0;
}