#include "tools.hpp"

// Global constants for deck of cards
const int points[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
const char* suits[] = {"Unknown", "Spades", "Hearts", "Diamonds", "Clubs"};
const char ranks[] = {"-A23456789TJQK"};

// Enum type for suits
enum SuitT {
    UNKNOWN,
    SPADES,
    HEARTS,
    DIAMONDS,
    CLUBS
};

//------------------------------------------------------------------------------
class CardT {
    private:
    // Data members of the card class
        SuitT suit;
        char cardRank;
        int point;

    public:
        CardT(SuitT, int, char);

    // Empty constructor for creating array
    CardT( ){}

    // Normal card constructor
    CardT( SuitT s, char r ){
        suit = s;
        cardRank = r;

        // Compare card rank to point value
        for (int k=0; k<13; ++k){
            if (cardRank == ranks[k]) point = points[k];
        }
    }

    // Print function -------------------------------------
    void print(ostream& out){
        int k;
        switch(suit){
            case SPADES: k=1; break;
            case HEARTS: k=2; break;
            case DIAMONDS: k=3; break;
            case CLUBS: k=4; break;
            default: fatal("Cannot convert suit to int");
        }
        string suitName = suits[k];

        cout << cardRank << " of " << suitName << ": " << point << endl;
        out << cardRank << " of " << suitName << ": " << point << endl;
    }
};

//------------------------------------------------------------------------------
int main()
{
    int numCards = 0;    // Keep track of number of cards
    SuitT st;            // Suit of the card
    CardT cardArray[52]; // Store the cards in an array of card objects

    banner();

    ofstream deck( "deck.txt" );
        if (!deck) fatal ("Could not open deck.txt for deck output.");

    // Create a deck of cards with a nested for loop
    // 1-4 for suits, 1-13 for ranks
    for(int k=1; k<5; ++k){
        for (int m=1; m<14; ++m){
            switch(k){
                case 1: st = SPADES; break;
                case 2: st = HEARTS; break;
                case 3: st = DIAMONDS; break;
                case 4: st = CLUBS; break;
                default: fatal("Suit not recognized.");
            }

            // Create card and store it
            cardArray[numCards] = CardT( st, ranks[m] );
            ++numCards;
        }
    }

    // Walk through entire array and print the deck
    for(int k=0; k<52; ++k){
        cardArray[k].print(deck);
    }

    deck.close();
    bye();
    return 0;
}
