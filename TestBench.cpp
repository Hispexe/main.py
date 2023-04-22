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

class deck { //deck class which manages the deck's (list) function
private:
    card* cardDeck[52]; // creates an empty array of card objects
    int currentIndexPos;
    string cardValues[13] = { "Ace","2","3","4","5","6","7","8","9","10","Jack","Queen","King" }; //inefficient?
    int cardNumValues[13] = { 1,2,3,4,5,6,7,8,9,10,8,9,10 };
    string cardSuits[4] = { "Hearts","Diamonds","Clubs","Spades" };
public:
    deck() {
        currentIndexPos = -1;
    }

    void createDeck() { //places card objects in all of the 52 indexes of cardDeck
        int indx = 0;
        for (int suit = 0; suit < (sizeof(cardSuits) / sizeof(string)); suit++) {
            for (int val = 0; val < (sizeof(cardValues) / sizeof(string)); val++) {
                cardDeck[indx] = new card(cardSuits[suit], cardValues[val], cardNumValues[val]);
                indx++;
            }
        }
    }

    void randomizeDeck() {
        srand(time(0));
        unsigned seed = rand();
        int n = (sizeof(cardDeck) / sizeof(cardDeck[0]));
        shuffle(cardDeck, cardDeck + n, default_random_engine(seed));
    }

    card returnCard() {
        if (currentIndexPos = 51) { //if at the last card...
            currentIndexPos = -1; //reset the index.
            randomizeDeck(); //rerandomize the deck.
        }
        currentIndexPos++;
        return *cardDeck[currentIndexPos]; //return the card object at a specified 
                                           //index of the deck (list)
    }
};

class gameLoop {
private:
    deck cardStack;
    vector<card> hand;
    int8_t playr_win_cnt = 0;
    int8_t dealr_win_cnt = 0;
public:
    gameLoop() {
        bool end_cond = true;
        bool turn_cond = true;
        cardStack.createDeck();
        cardStack.randomizeDeck();
        while (end_cond) {
            hand.clear();
            if (!gameTurn(turn_cond)) {
                end_cond = false;
            }
        }
    }

    void versus(int playr_hand_val, int dealr_hand_value) {
        cout << "\nYou:" << static_cast<int>(playr_hand_val) << " vs Dealer:" << static_cast<int>(dealr_hand_value) << endl;
    }

    void drawCard() {
        hand.push_back(cardStack.returnCard());
    }

    void returnCardInHand(int i) {
        cout << "\n" << hand.at(i).getValue() << " of " << hand.at(i).getSuit();
    }

    bool gameTurn(bool turn_cond) {
        drawCard(); drawCard();
        turn_cond = true;
        while (turn_cond) {
            cout << "\n============" << endl;
            cout << " Your Hand:" << endl;
            cout << "============";
            if (totalHand(true) < 22) { //allow player to keep drawing cards unless they are over 21.
                int Y_N_Input;
                cout << "Draw Card?[1 <- (Yes)/2 <- (No)]" << endl;
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
                    compareHands(totalHand(false)); //call to algo 
                    turn_cond = false;
                    break;
                }
            }
            else { //if the player goes over 21 at any point.
                cout << "Uh Oh!\n\n"; //lol
                compareHands(totalHand(false));
                turn_cond = false;
                break;
            }
        }
        int Y_N_Input2;
        cout << "Play again?[1 <- (Yes)/2 <- (No)]" << endl;
        cin >> Y_N_Input2;
        if (Y_N_Input2 == 1) {
            return true;
        }
        return false;
    }

    int totalHand(bool return_value) { //outs the total value of all cards in the player's hand.
        //return value is used to determine if the result needs to be printed.
        int8_t hand_value = 0;
        for (int i = 0; i < hand.size(); i++) {
            if (return_value) {
                cout << '\n';
                returnCardInHand(i);
            }
            hand_value += hand.at(i).getNumValue();
        }
        if (return_value)
            cout << "\n\nHand Value : " << static_cast<int>(hand_value) << endl;
        //if (hand_value > 21)
            //return -1;
        return hand_value;
    }

    //Use this for the written CPT for iteration, selection, and sequencing
    void compareHands(int player_hand_val) {
        vector<card> dealr_hand; //dealer's hand
        int8_t dealr_hand_value = 0;
        cout << "\n================" << endl;
        cout << " Dealer's Hand:" << endl;
        cout << "================";
        while (dealr_hand_value < 16) { //dealer's hand, drawing cards until it is at or above 16. (iteration)
            card current = cardStack.returnCard();
            cout << "\n";
            current.returnCard();
            dealr_hand_value += current.getNumValue();
            dealr_hand.push_back(current);
        }
        bool dealr_over = dealr_hand_value < 22;
        if (player_hand_val > 21) {
            versus(player_hand_val, dealr_hand_value);
            cout << "\nPLAYER OVER 21! Dealer Wins!" << endl;
            dealr_win_cnt++;
        }
        else {
            if (player_hand_val <= dealr_hand_value && dealr_over) { //decide whether the player or the dealer won. (selection)
                versus(player_hand_val, dealr_hand_value);
                cout << "Dealer Wins!\n" << endl;
                dealr_win_cnt++;
            }
            else {
                if (!dealr_over) { //dealer goes over 21. (sequencing)
                    versus(player_hand_val, dealr_hand_value);
                    cout << "DEALER OVER 21! Player Wins!\n" << endl;
                    playr_win_cnt++;
                }
                else { //player has greater value
                    versus(player_hand_val, dealr_hand_value);
                    cout << "Player Wins!\n" << endl;
                    playr_win_cnt++;
                }
            }
        }
        cout << "Your Wins: " << static_cast<int>(playr_win_cnt) << " | Dealer Wins: " << static_cast<int>(dealr_win_cnt) << "\n\n"; 
        //print out how many wins that the player and dealer has
    }
};

int main() {
    gameLoop game;
    return 0;
}