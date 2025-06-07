#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <sstream>
#include <ctime>

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
        hexStream << hex << hashValue;
        return hexStream.str();
    }

    void setData(const string& newData) {
        data = newData;
        hash = calculateHash();
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

bool isChainValid(const vector<Block>& blockchain) {
    for (size_t i = 1; i < blockchain.size(); ++i) {
        if (blockchain[i].previousHash != blockchain[i-1].hash) {
            return false;
        }
    }
    return true;
}

int main() {
    vector<Block> blockchain;

    // Create genesis block
    Block genesis(0, "Genesis Block", "0");
    blockchain.push_back(genesis);

    // Create Block 1
    Block block1(1, "Block 1 Data", blockchain.back().hash);
    blockchain.push_back(block1);

    // Create Block 2
    Block block2(2, "Block 2 Data", blockchain.back().hash);
    blockchain.push_back(block2);

    // Display blockchain before modification
    cout << "Blockchain before modification:" << endl;
    for (const auto& block : blockchain) {
        block.printBlock();
    }
    cout << "Is chain valid? " << (isChainValid(blockchain) ? "Yes" : "No") << endl;

    // Modify Block 1's data
    blockchain[1].setData("Modified Block 1 Data");

    // Display blockchain after modification
    cout << "\nBlockchain after modifying Block 1:" << endl;
    for (const auto& block : blockchain) {
        block.printBlock();
    }
    cout << "Is chain valid? " << (isChainValid(blockchain) ? "Yes" : "No") << endl;

    return 0;
}