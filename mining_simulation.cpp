#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <sstream>
#include <ctime>
#include <chrono>
#include <iomanip>

using namespace std;

class Block {
public:
    int index;
    string timestamp;
    string data;
    string previousHash;
    string hash;
    int nonce;

    Block(int idx, const string& dat, const string& prevHash)
        : index(idx), data(dat), previousHash(prevHash), nonce(0) {
        timestamp = getCurrentTime();
        hash = calculateHash();
    }

    string calculateHash() const {
        stringstream ss;
        ss << index << timestamp << data << previousHash << nonce;
        string input = ss.str();
        size_t hashValue = std::hash<std::string>()(input);
        stringstream hexStream;
        hexStream << std::hex << std::setfill('0') << std::setw(16) << hashValue;
        return hexStream.str();
    }

    void mineBlock(int difficulty) {
        auto start = chrono::high_resolution_clock::now();
        string target(difficulty, '0');
        int attempts = 0;
        while (true) {
            hash = calculateHash();
            attempts++;
            if (hash.substr(0, difficulty) == target) {
                break;
            }
            nonce++;
        }
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        cout << "Block " << index << " mined after " << attempts << " attempts." << endl;
        cout << "Time taken: " << elapsed.count() << " seconds." << endl;
    }

    void printBlock() const {
        cout << "Block #" << index << endl;
        cout << "Timestamp: " << timestamp << endl;
        cout << "Data: " << data << endl;
        cout << "Previous Hash: " << previousHash << endl;
        cout << "Hash: " << hash << endl;
        cout << "Nonce: " << nonce << endl;
        cout << "------------------------" << endl;
    }

private:
    string getCurrentTime() {
        time_t now = time(nullptr);
        char buf[100];
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
        return string(buf);
    }
};

int main() {
    vector<Block> blockchain;
    int difficulty = 4;  // Hash must start with "0000"

    // Create and mine the genesis block
    Block genesis(0, "Genesis Block", "0");
    genesis.mineBlock(difficulty);
    blockchain.push_back(genesis);

    // Create and mine Block 1
    Block block1(1, "Block 1 Data", blockchain.back().hash);
    block1.mineBlock(difficulty);
    blockchain.push_back(block1);

    // Create and mine Block 2
    Block block2(2, "Block 2 Data", blockchain.back().hash);
    block2.mineBlock(difficulty);
    blockchain.push_back(block2);

    // Display the blockchain
    cout << "\nBlockchain:" << endl;
    for (const auto& block : blockchain) {
        block.printBlock();
    }

    return 0;
}