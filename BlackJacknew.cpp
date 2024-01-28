#include <iostream>
#include <ctime>

using namespace std;

void deal6decks(int deck[]) {
    for (int x = 0; x < 24; x++) {
        for (int i = 0; i < 14; i++) {
            deck[i+13*x] = (i+1);
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

void changeAmount(int& balance, int bet) {
    balance += bet;
}

void countCards(int card, int& count) {
    if (card == 2 || card == 3 || card == 4 || card == 5 || card == 6) {
        count = count + 1;
    } else if (card == 10 || card == 11 || card == 12 || card == 13 || card == 1) {
        count = count - 1;
    }
}

int nextCard(int deck[], int& currentCard, int& count) {
    currentCard++;
    int card = deck[currentCard];
    countCards(card, count);

    return deck[currentCard];
}

bool deal(int deck[], int& balance, int& bet, int& currentCard, int& count, bool print) {
            int dealer[10] = {0};
            int player[10] = {0};
            int player2[10] = {0};
            int dealerHand = 0;
            int playerHand = 0;
            int player2Hand = 0;
            bool doubleBet = false;
            bool split = false;
            int decksRemaining = 0;

            if (print) {
                cout << "Balance: " << balance << endl;
            }
            if (currentCard >= 250) {
                shuffle(deck);
                currentCard = 0;
                count = 0;
            }

            for (int i = 10; i < 10; i++) {
                dealer[i] = 0;
                player[i] = 0;
                player2[i] = 0;
            }

            dealerHand = 0;
            playerHand = 0;
            player2Hand = 0;

            decksRemaining = ((312 - currentCard) / 52);
            if (count >= 1) {
                if (decksRemaining > 4) {
                    bet = count / 2;
                }
                else {
                    bet = count;
                }
            }
            else if (count < 1) {
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




            //blackjack
            if (player[0] == 1 && player[1] == 10) {
                changeAmount(balance, (bet * 1.5));
                //cout << "Player has 21" << endl;
                return true;
            }

            if (player[0] == 10 && player[1] == 1) {
                changeAmount(balance, bet * 1.5);
                //cout << "Player has 21" << endl;
                return true;
            }





            //dealerdraws
            for (int i = 2; i < 17; i++) {
                dealer[i] = nextCard(deck, currentCard, count);
                dealerHand += dealer[i];
                if (dealerHand > 21) {
                    for (int j = 0; j < 10; j++) {
                        if (dealer[j] == 11) {
                            dealer[j] == 1;
                            dealerHand -= 10;
                            break;
                        }
                    }
                }
            }




            //insurance
            if ((dealer[0] == 11 || dealer1 == 1) && count > 5) {
                if (dealer[1] == 10) {
                    changeAmount(balance, bet * 1.5);
                }
                else {
                    changeAmount(balance, bet * -1.5);
                }
            }




            //playerdraws
            for (int i = 2; i < 17; i++) {
                player[i] = nextCard(deck, currentCard, count);
                playerHand += dealer[i];
                    if ((dealer[0] == 4 || dealer[0] == 5 || dealer[0] == 6) && (player[0] == player[1])) {
                                    split = true;
                                    if (print) {
                                        cout << "Split" << endl;
                                    }
                                    player2[0] = player[0];
                                    player2[1] = nextCard(deck, currentCard, count);
                                    for (int i = 2; i < 17; i++) {
                                        player2[i] = nextCard(deck, currentCard, count);
                                        player2Hand += dealer[i];
                                        if (dealer[0] != 11 && (player2Hand == 9) || player2Hand == 10) || player2Hand == 11)){
                                            player2[i + 1] = nextCard(deck, currentCard, count);
                                            doubleBet = true;
                                            if (print) {
                                                cout << "Double Bet" << endl;
                                            }
                                            i = 20;
                                        }
                                        if (player2Hand > 21) {
                                            for (int j = 0; j < 10; j++) {
                                                if (player2[j] == 11) {
                                                    player2[j] == 1;
                                                    player2Hand -= 10;
                                                    j = 20;
                                                }
                                            }
                                        }
                                    }
                    }
                    if (dealer[0] != 11 && (playerHand == 9) || playerHand == 10) || playerHand == 11)){
                        player[i + 1] = nextCard(deck, currentCard, count);
                        doubleBet = true;
                        if (print) {
                            cout << "Double Bet" << endl;
                        }
                        i = 20;
                    }
                    if (playerHand > 21) {
                        for (int j = 0; j < 10; j++) {
                            if (player[j] == 11) {
                                player[j] == 1;
                                playerHand -= 10;
                                j = 20;
                            }
                        }
                    }
            }



            
            if (print) {
                cout << "Dealer hand:";
                for (int i = 0; i < 10; i++) {
                    cout << ' ' + dealer[i];
                }
                cout << endl;
                cout << "Player hand:";
                for (int i = 0; i < 10; i++) {
                    cout << ' ' + player[i];
                }
                cout << endl;
                cout << "Player2 hand:";
                for (int i = 0; i < 10; i++) {
                    cout << ' ' + player2[i];
                }
                cout << endl;
            }




            //win or lose
            if (playerHand > 21 && dealerHand > 21) {
                doubleBet = false;
                return false;
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
                return false;
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
                    return true;
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
                        return true;
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
                        return false;
                    }
                    else if (playerHand == dealerHand) {
                        doubleBet = false;
                        if (print) {
                            cout << "Draw" << endl;
                        }
                        return false;
                    }
                }
                return false;
            }

            //win or lose second hand
            if (split) {
                if (player2Hand > 21 && dealerHand > 21) {
                    if (doubleBet == true) {
                        doubleBet = false;
                    }
                    split = false;
                    return false;
                }
                else if (player2Hand > 21) {
                    if (print) {
                        cout << "Dealer Wins second hand" << endl;
                    }
                    if (doubleBet == true) {
                        changeAmount(balance, -bet * 2);
                        doubleBet = false;
                    }
                    else {
                        changeAmount(balance, -bet);
                    }
                    split = false;
                    return false;
                }
                else {
                    if (dealerHand > 21) {
                        if (print) {
                            cout << "Player Wins  second hand" << endl;
                        }
                        if (doubleBet == true) {
                            changeAmount(balance, bet * 2);
                            doubleBet = false;
                        }
                        else {
                            changeAmount(balance, bet);
                        }
                        split = false;
                        return true;
                    }
                    else {
                        if (player2Hand > dealerHand) {
                            if (print) {
                                cout << "Player Wins second hand" << endl;
                            }
                            if (doubleBet == true) {
                                changeAmount(balance, bet * 2);
                                doubleBet = false;
                            }
                            else {
                                changeAmount(balance, bet);
                            }
                            split = false;
                            return true;
                        }
                        else if (player2Hand < dealerHand) {
                            if (print) {
                                cout << "Dealer Wins second hand" << endl;
                            }
                            if (doubleBet == true) {
                                changeAmount(balance, -bet * 2);
                                doubleBet = false;
                            }
                            else {
                                changeAmount(balance, -bet);
                            }
                            split = false;
                            return false;
                        }
                        else if (player2Hand == dealerHand) {
                            doubleBet = false;
                            if (print) {
                                cout << "Draw second hand" << endl;
                            }
                            split = false;
                            return false;
                        }
                    }
                    split = false;
                    return false;
                }
            }
    
}

int main()
{
    int balance = 500;
    int bet = 1;
    int deck[313] = {0};
    int currentCard = 0;
    int total = 0;
    int tables = 1;
    int count = 0;
    int decksRemaining = 6;
    srand(time(0));
    deal6decks(deck);
    shuffle(deck);
    
    for (int x = 0; x < tables; x++) {
        for (int i = 0; i < 300; i++) {
            if (decksRemaining <= 1 || balance <= 0) {
                break;
            }

            //deal(deck, balance, bet, currentCard, count, true);
            decksRemaining = ((312 - currentCard) / 52);
        }
        shuffle(deck);
        total += balance;
        balance = 500;
        bet = 1;
        count = 0;
        currentCard = 0;
    }

    cout << "Average = " << total / (tables) << endl;
        
}

