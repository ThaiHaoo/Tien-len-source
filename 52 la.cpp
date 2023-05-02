#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int NUM_CARDS = 52;
const int NUM_RANKS = 13;
const int NUM_SUITS = 4;
const int NUM_PLAYERS = 4;

enum Rank {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};
enum Suit {CLUBS, DIAMONDS, HEARTS, SPADES};

struct Card
{
    Rank rank;
    Suit suit;
};

void ShuffleDeck(Card deck[]);
void PrintDeck(Card deck[]);
void DealCards(Card deck[], Card hands[][NUM_CARDS/NUM_PLAYERS]);
void PrintHand(Card hand[]);
int GetCardValue(Card card);
int GetHandValue(Card hand[]);
void PlayGame(Card deck[], Card hands[][NUM_CARDS/NUM_PLAYERS]);

int main()
{
    Card deck[NUM_CARDS];
    Card hands[NUM_PLAYERS][NUM_CARDS/NUM_PLAYERS];

    srand(time(0));

    ShuffleDeck(deck);
    PrintDeck(deck);

    DealCards(deck, hands);
    for (int i = 0; i < NUM_PLAYERS; i++)
    {
        cout << "Player " << i+1 << "'s hand:" << endl;
        PrintHand(hands[i]);
        cout << endl;
    }

    PlayGame(deck, hands);

    return 0;
}

void ShuffleDeck(Card deck[])
{
    for (int i = 0; i < NUM_CARDS; i++)
    {
        deck[i].rank = static_cast<Rank>(i % NUM_RANKS);
        deck[i].suit = static_cast<Suit>(i / NUM_RANKS);
    }

    for (int i = 0; i < NUM_CARDS; i++)
    {
        int j = rand() % NUM_CARDS;
        Card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

void PrintDeck(Card deck[])
{
    for (int i = 0; i < NUM_CARDS; i++)
    {
        cout << deck[i].rank << " of " << deck[i].suit << endl;
    }
    cout << endl;
}

void DealCards(Card deck[], Card hands[][NUM_CARDS/NUM_PLAYERS])
{
    for (int i = 0; i < NUM_CARDS/NUM_PLAYERS; i++)
    {
        for (int j = 0; j < NUM_PLAYERS; j++)
        {
            hands[j][i] = deck[NUM_CARDS/NUM_PLAYERS*j + i];
        }
    }
}

void PrintHand(Card hand[])
{
    for (int i = 0; i < NUM_CARDS/NUM_PLAYERS; i++)
    {
        cout << hand[i].rank << " of " << hand[i].suit << endl;
    }
}

int GetCardValue(Card card)
{
    switch (card.rank)
    {
        case ACE:
            return 14;
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
            return 10;
        case JACK:
            return 11;
        case QUEEN:
            return 12;
        case KING:
            return 13;
        default:
            return 0;
    }
}

int GetHandValue(Card hand[])
{
    int value = 0;
    int num_aces = 0;

    for (int i = 0; i < NUM_CARDS/NUM_PLAYERS; i++)
    {
        value += GetCardValue(hand[i]);
        if (hand[i].rank == ACE)
        {
            num_aces++;
        }
    }

    while (num_aces > 0 && value > 21)
    {
        value -= 10;
        num_aces--;
    }

    return value;
}

void PlayGame(Card deck[], Card hands[][NUM_CARDS/NUM_PLAYERS])
{
    int scores[NUM_PLAYERS] = {0};
    int highest_score = 0;
    int winner = -1;

    for (int i = 0; i < NUM_PLAYERS; i++)
    {
        scores[i] = GetHandValue(hands[i]);
        cout << "Player " << i+1 << "'s score: " << scores[i] << endl;

        if (scores[i] > highest_score && scores[i] <= 21)
        {
            highest_score = scores[i];
            winner = i;
        }
    }

    if (winner == -1)
    {
        cout << "No winner - all players bust!" << endl;
    }
    else
    {
        cout << "Player " << winner+1 << " wins with a score of " << highest_score << "!" << endl;
    }
}

