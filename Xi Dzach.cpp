#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

// Enumerate the ranks of cards
enum Rank
{
    ACE = 1,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING
};

// Enumerate the suits of cards
enum Suit
{
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
};

// Define a card structure
struct Card
{
    Rank rank;
    Suit suit;
};

// Print the value of a card
void PrintCardValue(Card card)
{
    switch (card.rank)
    {
        case ACE:
            cout << "At";
            break;
        case TWO:
            cout << "2";
            break;
        case THREE:
            cout << "3";
            break;
        case FOUR:
            cout << "4";
            break;
        case FIVE:
            cout << "5";
            break;
        case SIX:
            cout << "6";
            break;
        case SEVEN:
            cout << "7";
            break;
        case EIGHT:
            cout << "8";
            break;
        case NINE:
            cout << "9";
            break;
        case TEN:
            cout << "10";
            break;
        case JACK:
            cout << "Boi";
            break;
        case QUEEN:
            cout << "Dam";
            break;
        case KING:
            cout << "Gia";
            break;
    }
}

// Print the suit of a card
void PrintCardSuit(Card card)
{
    switch (card.suit)
    {
        case CLUBS:
            cout << "Bich";
            break;
        case DIAMONDS:
            cout << "Chuon";
            break;
        case HEARTS:
            cout << "Ro";
            break;
        case SPADES:
            cout << "Co";
            break;
    }
}

// Print a card
void PrintCard(Card card)
{
    PrintCardValue(card);
    cout << " ";
    PrintCardSuit(card);
}

// Get the value of a card
int GetCardValue(Card card)
{
    switch (card.rank)
    {
        case ACE:
            return 11;
        case TWO:
            return 2;
        case THREE:
            return 3;
        case FOUR:
            return 4;
        case FIVE:
            return 5;
        case SIX:
            return 6;
        case SEVEN:
            return 7;
        case EIGHT:
            return 8;
        case NINE:
            return 9;
        case TEN:
        case JACK:
        case QUEEN:
        case KING:
            return 10;
    }
}

// Get the value of a hand
int GetHandValue(vector<Card>& hand)
{
    int value = 0;
    int num_aces = 0;

    for (int i = 0; i < hand.size(); i++)
    {
        value += GetCardValue(hand[i]);
        if (hand[i].rank == ACE)
        {
            num_aces++;
        }
    }

    while (value > 21 && num_aces > 0)
    {
        value -= 10;
        num_aces--;
    }

    return value;
}

// Check if a hand has a blackjack
bool HasBlackjack(vector<Card>& hand)
{
    return (hand.size() == 2 && GetHandValue(hand) == 21);
}

// Print a hand of cards
void PrintHand(vector<Card>& hand)
{
    for (int i = 0; i < hand.size(); i++)
    {
        PrintCard(hand[i]);
        cout << ", ";
    }
    cout << endl;
}

// Shuffle a deck of cards
void ShuffleDeck(vector<Card>& deck)
{
    random_shuffle(deck.begin(), deck.end());
}

// Deal a card to a hand
void DealCard(vector<Card>& hand, vector<Card>& deck)
{
    hand.push_back(deck.back());
    deck.pop_back();
}

// Play a round of blackjack
void PlayBlackjack()
{
    vector<Card> deck;

    // Create the deck of cards
    for (int i = ACE; i <= KING; i++)
    {
        for (int j = CLUBS; j <= SPADES; j++)
        {
            Card card = { (Rank)i, (Suit)j };
            deck.push_back(card);
        }
    }

    // Shuffle the deck
    ShuffleDeck(deck);

    // Create the player and dealer hands
    vector<Card> player_hand;
    vector<Card> dealer_hand;

    // Deal the cards
    DealCard(player_hand, deck);
    DealCard(dealer_hand, deck);
    DealCard(player_hand, deck);
    DealCard(dealer_hand, deck);

    // Print the hands
    cout << "Bai nguoi choi: ";
    PrintHand(player_hand);
    cout << "Bai nha cai: ";
    cout << "<la bai an>, ";
    PrintCard(dealer_hand[1]);
    cout << endl;

    // Check for blackjack
    if (HasBlackjack(player_hand))
    {
        cout << "Player has a blackjack! Player wins!" << endl;
        return;
    }
    if (HasBlackjack(dealer_hand))
    {
        cout << "Dealer has a blackjack! Dealer wins!" << endl;
        return;
    }

    // Player's turn
    while (GetHandValue(player_hand) < 21)
    {
        char choice;
        cout << "Rut (r) hay dan (d)? ";
        cin >> choice;
        if (choice == 'r')
        {
            DealCard(player_hand, deck);
            cout << "Bai nguoi choi: ";
            PrintHand(player_hand);
        }
        else if (choice == 'd')
        {
            break;
        }
    }

    // Player busts
    if (GetHandValue(player_hand) > 21)
    {
        cout << "Nguoi choi Quac! Cai thang!" << endl;
        return;
    }

    // Dealer's turn
    cout << "Bai nha cai: ";
    PrintHand(dealer_hand);
    while (GetHandValue(dealer_hand) < 17)
    {
        DealCard(dealer_hand, deck);
        cout << "Bai nha cai: ";
        PrintHand(dealer_hand);
    }

    // Dealer busts
    if (GetHandValue(dealer_hand) > 21)
    {
        cout << "Cai Quac! Nguoi choi thang!" << endl;
        return;
    }

    // Compare hands
    if (GetHandValue(player_hand) > GetHandValue(dealer_hand))
    {
        cout << "Nguoi choi thang!" << endl;
    }
    else if (GetHandValue(player_hand) < GetHandValue(dealer_hand))
    {
        cout << "Cai thang!" << endl;
    }
    else
    {
        cout << "Push (tie)!" << endl;
    }
}

int main()
{
    char choice;
    do
    {
        PlayBlackjack();
        cout << "Play again? (y/n) ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    return 0;
}


