#include <iostream>
#include <ctime>

using namespace std;

void deal6decks(int deck[]) {
    for (int x = 0; x < 24; x++) {
        for (int i = 0; i < 14; i++) {
            deck[i + 13 * x] = (i + 1);
        }
    }

    for (int i = 0; i < 312; i++) {
        if (deck[i] == 13) {
            deck[i] = 10;
        }
        if (deck[i] == 12) {
            deck[i] = 10;
        }
        if (deck[i] == 11) {
            deck[i] = 10;
        }
        if (deck[i] == 1) {
            deck[i] = 11;
        }

    }
}

void shuffle(int deck[]) {
    for (int i = 0; i < 10000; i++) {
        int rand1 = rand() % 312;
        int rand2 = rand() % 312;
        int temp = deck[rand2];
        deck[rand2] = deck[rand1];
        deck[rand1] = temp;
    }
}

void changeAmount(double& balance, double bet) {
    balance += bet;
}

void countCards(int card, int& count) {
    if (card == 2 || card == 3 || card == 4 || card == 5 || card == 6) {
        count = count + 1;
    }
    else if (card == 10 || card == 11 || card == 12 || card == 13 || card == 1) {
        count = count - 1;
    }
}

int nextCard(int deck[], int& currentCard, int& count) {
    currentCard++;
    if (currentCard >= 300) {
        shuffle(deck);
        currentCard = 0;
    }

    int card = deck[currentCard];
    countCards(card, count);

    return deck[currentCard];
}

bool deal(int deck[], double& balance, double& bet, int& currentCard, int& count, bool print) {
    int dealer[20] = { 0 };
    int player[20] = { 0 };
    int player2[20] = { 0 };
    int dealerHand = 0;
    int playerHand = 0;
    int player2Hand = 0;
    int trueCount = 0;
    bool doubleBet = false;
    bool doubleBet2 = false;
    bool split = false;
    int decksRemaining = 0;

    if (print) {
        cout << "Balance: " << balance << endl;
    }
    if (currentCard >= 310) {
        shuffle(deck);
        currentCard = 0;
        count = 0;
    }

    for (int i = 0; i < 10; i++) {
        dealer[i] = 0;
        player[i] = 0;
        player2[i] = 0;
    }

    dealerHand = 0;
    playerHand = 0;
    player2Hand = 0;

    decksRemaining = ((312 - currentCard) / 52);
    trueCount =  (count / decksRemaining);

    if (trueCount > 1) {
        bet = trueCount;
    } else{
        bet = 1;
    }


    if (print) {
        cout << "bet " << bet << endl;
        cout << "count " << count << endl;
    }



    dealer[0] = nextCard(deck, currentCard, count);
    player[0] = nextCard(deck, currentCard, count);
    dealer[1] = nextCard(deck, currentCard, count);
    player[1] = nextCard(deck, currentCard, count);

    playerHand = player[0] + player[1];
    dealerHand = dealer[0] + dealer[1];


    //blackjack
    if (player[0] == 1 && player[1] == 10) {
        changeAmount(balance, (bet * 1.5));
        if (print) {
            cout << "Player has 21" << endl;
        }
        return true;
    }

    if (player[0] == 10 && player[1] == 1) {
        changeAmount(balance, bet * 1.5);
        if (print) {
            cout << "Player has 21" << endl;
        }
        return true;
    }

    if (dealer[0] == 1 && dealer[1] == 10) {
        changeAmount(balance, (bet * -1));
        if (print) {
            cout << "Dealer has 21" << endl;
        }
        return false;
    }

    if (dealer[0] == 10 && dealer[1] == 1) {
        changeAmount(balance, bet * -1);
        if (print) {
            cout << "Dealer has 21" << endl;
        }
        return false;
    }
    



    int index = 1;
    split = false;
    //playerdraws
    while (playerHand < 17 && doubleBet == false && index < 20) {
            if (index > 1) {
                player[index] = nextCard(deck, currentCard, count);
                playerHand += player[index];
            }
            if (playerHand > 21) {
                for (int j = 0; j < 10; j++) {
                    if (player[j] == 11) {
                        player[j] = 1;
                        playerHand -= 10;
                    }
                }
            }
            index++;
    }

    if (doubleBet == true) {
        player[index] = nextCard(deck, currentCard, count);
        if (print) {
            cout << "Double Bet" << endl;
        }
        index = 0;
        while (playerHand > 21) {
            player[index] = 1;
            playerHand -= 10;
        }
    }



    if (split == true) {
        if (print) {
            cout << "Split" << endl;
        }
        player2[0] = player[0];
        player2[1] = nextCard(deck, currentCard, count);
        while (player2Hand < 17 && doubleBet == false) {
            int k = 2;
            player2[k] = nextCard(deck, currentCard, count);
            player2Hand += player2[k];
            if ((dealer[0] == 4 || dealer[0] == 5 || dealer[0] == 6) && (playerHand >= 12) && (playerHand <= 16)) {
                k = 20;
            } if (((dealer[0] == 10) && (player2Hand == 16)) || ((dealer[0] == 2) && (player2Hand == 13)) || ((dealer[0] == 2) || (dealer[0] == 3) && (player2Hand == 12)) && trueCount >= 3) {
                k = 20;
            }
            else if (player2Hand > 21) {
                for (int j = 0; j < 10; j++) {
                    if (player2[j] == 11) {
                        player2[j] = 1;
                        player2Hand -= 10;
                    }
                }
            }
            else if ((dealer[0] == 3 || dealer[0] == 4 || dealer[0] == 5 || dealer[0] == 6) && (player2Hand == 9) && trueCount >= 3) {
                doubleBet2 = true;
            }
            else if ((dealer[0] != 10 && dealer[0] != 11 && dealer[0] != 1) && (player2Hand == 10 || player2Hand == 11) && trueCount >= 1) {
                doubleBet2 = true;
            }
            else if ((dealer[0] == 10) && (player2Hand == 11) && trueCount >= 1) {
                doubleBet2 = true;
            }
            else if ((dealer[0] == 5 || dealer[0] == 6) && (player2[0] == 11 || player2[1] == 11) && (player2Hand == 13 || player2Hand == 14 || player2Hand == 15 || player2Hand == 16 || player2Hand == 17 || player2Hand == 18) && trueCount >= 3) {
                doubleBet2 = true;
            }
            else if ((dealer[0] == 4) && (player2[0] == 11 || player2[1] == 11) && (player2Hand == 15 || player2Hand == 16 || player2Hand == 17 || player2Hand == 18) && trueCount >= 3) {
                doubleBet2 = true;
            }
            else if ((dealer[0] == 3) && (player2[0] == 11 || player2[1] == 11) && (player2Hand == 17) && trueCount >= 3) {
                doubleBet2 = true;
            }
            else if ((dealer[0] != 7) && (player2Hand == 9) && trueCount >= 3) {
                doubleBet2 = true;
            }
            k++;
        }
    }


    if (doubleBet2 == true) {
        player2[index] = nextCard(deck, currentCard, count);
        if (print) {
            cout << "Double Bet" << endl;
        }
        index = 0;
        while (player2Hand > 21) {
            player2[index] = 1;
            player2Hand -= 10;
        }
    }


    //dealerdraws
    while (dealerHand < 17) {
        int i = 2;
        dealer[i] = nextCard(deck, currentCard, count);
        dealerHand += dealer[i];
        if (dealerHand > 21) {
            for (int j = 0; j < 10; j++) {
                if (dealer[j] == 11) {
                    dealer[j] = 1;
                    dealerHand -= 10;
                }
            }
        }
        i++;
    }




    //insurance
    if ((dealer[0] == 11 || dealer[0] == 1) && trueCount >= 3) {
        if (dealer[1] == 10) {
            changeAmount(balance, bet * 0.5);
        }
        else {
            changeAmount(balance, bet * -0.5);
        }
    }



    if (print) {
        cout << "Dealer hand:";
        for (int i = 0; i < 10; i++) {
            cout << ' ' << dealer[i];
        }
        cout << endl;
        cout << "Player hand:";
        for (int i = 0; i < 10; i++) {
            cout << ' ' << player[i];
        }
        cout << endl;
        cout << "Player2 hand:";
        for (int i = 0; i < 10; i++) {
            cout << ' ' << player2[i];
        }
        cout << endl;
    }


    //win or lose
    if (playerHand > 21 && dealerHand > 21) {
        doubleBet = false;
    }
    else if (playerHand > 21) {
        if (print) {
            cout << "Dealer Wins" << endl;
        }
        if (doubleBet == true) {
            changeAmount(balance, -bet * 2);
            doubleBet = false;
        }
        else {
            changeAmount(balance, -bet);
        }
    }
    else {
        if (dealerHand > 21) {
            if (print) {
                cout << "Player Wins" << endl;
            }
            if (doubleBet == true) {
                changeAmount(balance, bet * 2);
                doubleBet = false;
            }
            else {
                changeAmount(balance, bet);
            }
        }
        else {
            if (playerHand > dealerHand) {
                if (print) {
                    cout << "Player Wins" << endl;
                }
                if (doubleBet == true) {
                    changeAmount(balance, bet * 2);
                    doubleBet = false;
                }
                else {
                    changeAmount(balance, bet);
                }
            }
            else if (playerHand < dealerHand) {
                if (print) {
                    cout << "Dealer Wins" << endl;
                }
                if (doubleBet == true) {
                    changeAmount(balance, -bet * 2);
                    doubleBet = false;
                }
                else {
                    changeAmount(balance, -bet);
                }
            }
            else if (playerHand == dealerHand) {
                doubleBet = false;
                if (print) {
                    cout << "Draw" << endl;
                }
            }
        }
    }



    //win or lose second hand
    if (split) {
        if (player2Hand > 21 && dealerHand > 21) {
            split = false;
        }
        else if (player2Hand > 21) {
            if (print) {
                cout << "Dealer Wins second hand" << endl;
            }
            if (doubleBet2 == true) {
                changeAmount(balance, -bet * 2);
                doubleBet2 = false;
            }
            else {
                changeAmount(balance, -bet);
            }
            split = false;
        }
        else {
            if (dealerHand > 21) {
                if (print) {
                    cout << "Player Wins  second hand" << endl;
                }
                if (doubleBet2 == true) {
                    changeAmount(balance, bet * 2);
                    doubleBet2 = false;
                }
                else {
                    changeAmount(balance, bet);
                }
                split = false;
            }
            else {
                if (player2Hand > dealerHand) {
                    if (print) {
                        cout << "Player Wins second hand" << endl;
                    }
                    if (doubleBet2 == true) {
                        changeAmount(balance, bet * 2);
                        doubleBet2 = false;
                    }
                    else {
                        changeAmount(balance, bet);
                    }
                    split = false;
                }
                else if (player2Hand < dealerHand) {
                    if (print) {
                        cout << "Dealer Wins second hand" << endl;
                    }
                    if (doubleBet2 == true) {
                        changeAmount(balance, -bet * 2);
                        doubleBet2 = false;
                    }
                    else {
                        changeAmount(balance, -bet);
                    }
                    split = false;
                }
                else if (player2Hand == dealerHand) {
                    doubleBet = false;
                    if (print) {
                        cout << "Draw second hand" << endl;
                    }
                    split = false;
                }
            }
            split = false; 
        }
    }
    return false;
}

int main()
{
    double balance = 500;
    double bet = 1;
    int deck[313] = { 0 };
    int currentCard = 0;
    double total = 0;
    int tables = 1000;
    int count = 0;
    int decksRemaining = 6;
    int wins = 0;
    srand(time(0));
    deal6decks(deck);
    shuffle(deck);



    for (int x = 0; x < tables; x++) {
        for (int i = 0; i < 100; i++) {
            if (decksRemaining <= 1 || balance <= 0 || currentCard >= 250) {
                break;
            }

            deal(deck, balance, bet, currentCard, count, false);
            decksRemaining = ((312 - currentCard) / 52);
        }
        if (balance > 500) {
            wins++;
        }
        //cout << "Balance = " << balance << endl;
        shuffle(deck);
        total += balance;
        balance = 500;
        bet = 1;
        count = 0;
        currentCard = 0;
        decksRemaining = 6;
    }

    cout << "Wins = " << wins << endl;
    cout << "Average = " << total / (tables) << endl;

}

