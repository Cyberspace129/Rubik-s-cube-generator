#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

// Function to refill the modifier bucket
void refillModifierBucket(vector<string>& modifierBucket) {
    modifierBucket = {"", "2", "'", "", "2", "'", "", "2", "'", "", "2"};
}

// Function to get a new move while ensuring it doesn't repeat improperly
string getNewMove(vector<string>& moves, vector<string>& lastMoves) {
    string newMove;
    do {
        newMove = moves[rand() % moves.size()];
    } while (!lastMoves.empty() && newMove == lastMoves.back()); // Prevent consecutive identical moves

    return newMove;
}

// Function to get a move modifier
string getModifier(vector<string>& modifierBucket) {
    if (modifierBucket.empty()) {
        refillModifierBucket(modifierBucket);
    }
    string modifier = modifierBucket.front();
    modifierBucket.erase(modifierBucket.begin());
    return modifier;
}

// Function to check if the scramble is valid
bool analysisLook(const vector<string>& scramble) {
    for (size_t i = 2; i < scramble.size(); ++i) {
        string baseMove = scramble[i].substr(0, 1);
        string prevBase1 = scramble[i - 1].substr(0, 1);
        string prevBase2 = scramble[i - 2].substr(0, 1);

        if (baseMove == prevBase1 || baseMove == prevBase2) {
            return false;
        }
    }
    return true;
}

// Function to generate a valid scramble
void generateScramble(vector<string>& scramble, vector<string>& moves, vector<string>& modifierBucket) {
    vector<string> lastMoves;
    bool validScramble = false;

    while (!validScramble) {
        scramble.clear();
        lastMoves.clear();

        for (int i = 0; i < 13; ++i) {
            string newMove = getNewMove(moves, lastMoves);
            string modifier = getModifier(modifierBucket);

            scramble.push_back(newMove + modifier);
            lastMoves.push_back(newMove);

            if (lastMoves.size() > 3) {
                lastMoves.erase(lastMoves.begin());
            }
        }

        validScramble = analysisLook(scramble);
    }
}

// Main function
int main() {
    srand(time(0));

    vector<string> moves = {"U", "D", "L", "R", "F", "B"};
    vector<string> modifierBucket;
    refillModifierBucket(modifierBucket);
    vector<string> scramble;

    generateScramble(scramble, moves, modifierBucket);

    cout << "Generated Scramble: ";
    for (const auto& move : scramble) {
        cout << move << " ";
    }
    cout << endl;

    return 0;
}
