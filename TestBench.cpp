#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <vector>
#include <cstdlib>
using namespace std;

class card { //card class defining what the card is
private:
    string cardSuits;
    string cardValue;
    int cardNumVal;
public:
    card() {
        cardSuits = "N/A";
        cardValue = "0";
    }
    card(string suit, string value, int numval) {
        cardSuits = suit;
        cardValue = value;
        cardNumVal = numval;
    }
    string getSuit() {
        return cardSuits;
    }
    string getValue() {
        return cardValue;
    }
    int getNumValue() {
        return cardNumVal;
    }
    void returnCard() {
        cout << getValue() << " of " << getSuit() << endl;
    }
};

class deck { //deck class which manages the deck's function
private:
    card* deck[52];
    int currentIndexPos = -1;
    string cardValues[13] = { "Ace","2","3","4","5","6","7","8","9","10","Jack-(8)","Queen-(9)","King-(10)" }; //inefficient?
    int cardNumValues[13] = { 1,2,3,4,5,6,7,8,9,10,8,9,10 };
    string cardSuits[4] = { "Hearts","Diamonds","Clubs","Spades" };
public:
    void createDeck() {
        int indx = 0;
        for (int suit = 0; suit < (sizeof(cardSuits) / sizeof(string)); suit++) {
            for (int val = 0; val < (sizeof(cardValues) / sizeof(string)); val++) {
                deck[indx] = new card(cardSuits[suit], cardValues[val], cardNumValues[val]);
                indx++;
            }
        }
    }
    void randomizeDeck() {
        srand(time(0));
        unsigned seed = rand();
        int n = (sizeof(deck) / sizeof(deck[0]));
        shuffle(deck, deck + n, default_random_engine(seed));
    }
    card returnCard() {
        currentIndexPos++;
        return *deck[currentIndexPos];
    }
    void resetIndex() {
        currentIndexPos = -1;
    }
};

class gameLoop {
private:
    deck cardStack;
    vector<card> hand;
    int8_t playr_win_cnt = 0;
    int8_t dealr_win_cnt = 0;
    int8_t playr_hand_val = 0;
public:
    gameLoop() {
        bool end_cond = true;
        bool turn_cond = true;
        cardStack.createDeck();
        cardStack.randomizeDeck();
        while (end_cond) {
            hand.clear();
            hand.push_back(cardStack.returnCard());
            gameTurn(turn_cond);
        }
    }

    void versus(int playr_hand_val, int dealr_hand_value) {
        cout << "\nYou:" << static_cast<int>(playr_hand_val) << " vs Dealer:" << static_cast<int>(dealr_hand_value) << endl;
    }

    void drawCard() {
        hand.push_back(cardStack.returnCard());
    }

    void returnCard(int i) {
        cout << hand.at(i).getValue() << " of " << hand.at(i).getSuit() << endl;
    }

    void gameTurn(bool turn_cond) {
        drawCard(); cout << "\n";
        turn_cond = true;
        while (turn_cond) {
            if (totalHand(true) != -1) { //allow player to keep drawing cards unless they are over 21.
                int Y_N_Input;
                cout << "Draw Card?[1-(Y)/2-(N)]" << endl;
                cin >> Y_N_Input;
                if (!cin) { //stop non-numeric characters from being put into the game
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "NaN... Try Again." << endl;
                    cin >> Y_N_Input;
                }
                if (Y_N_Input == 1) { //if player chooses to draw another card
                    drawCard();
                }
                else { //if player decides to stop drawing cards, figure out who won.
                    compareHands(totalHand(false));
                    turn_cond = false;
                    break;
                }
            }
            else { //if the player goes over 21 at any point.
                cout << "OVER 21! Dealer Wins!" << endl;
                dealr_win_cnt++;
                turn_cond = false;
                break;
            }
        }
        int Y_N_Input2;
        cout << "Play again?[1-(Y)/2-(N)]" << endl;
        cin >> Y_N_Input2;
        if (Y_N_Input2 == 1) {
            return;
        }
        else {
            exit(0);
        }
    }


    int totalHand(bool return_value) { //outs the total value of all cards in the player's hand.
                                       //return value is used to determine if the result needs to be printed.
        playr_hand_val = 0;
        for (int i = 0; i < hand.size(); i++) {
            cout << '\n';
            if (return_value)
                returnCard(i);
            playr_hand_val += hand.at(i).getNumValue();
        }
        if (return_value)
            cout << "Hand Value: " << static_cast<int>(playr_hand_val) << endl;
        if (playr_hand_val > 21)
            return -1;
        return playr_hand_val;
    }

    void compareHands(int player_hand_val) { //Use this for the written CPT for iteration, selection, and sequencing
        vector<card> dealr_hand; //dealer's hand
        int8_t dealr_hand_value = 0;
        cout << "Dealer's Hand:" << endl;
        while (dealr_hand_value < 16) { //dealer's hand, drawing cards until it is at or above 16.
            card current = cardStack.returnCard();
            cout << "\n";
            current.returnCard();
            dealr_hand_value += current.getNumValue();
            dealr_hand.push_back(current);
        }
        bool dealr_over = dealr_hand_value < 22;
        if (player_hand_val <= dealr_hand_value && dealr_over) { //decide whether the player or the dealer won.
            versus(player_hand_val, dealr_hand_value);
            cout << "Dealer Wins!\n" << endl;
            dealr_win_cnt++;
        }
        else {
            if (!dealr_over) { //dealer goes over 21.
                versus(player_hand_val, dealr_hand_value);
                cout << "Dealer Over 21! Player Wins!\n" << endl;
                playr_win_cnt++;
            }
            else { //player has greater value
                versus(player_hand_val, dealr_hand_value);
                cout << "Player Wins!\n" << endl;
                playr_win_cnt++;
            }
        }
        cout << "Your Wins: " << static_cast<int>(playr_win_cnt) << " | Dealer Wins: " << static_cast<int>(dealr_win_cnt) << "\n\n"; //print out how many wins that either has
    }
};


int main() {
    gameLoop game;
    return 0;
}
