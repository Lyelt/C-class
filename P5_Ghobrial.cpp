#include "tools.hpp"
#include "card.cpp"
#define OUTFILE "deck.txt"

//------------------------------------------------------------------------------

class DeckT {
    private:
        CardT cardArray[52];
        int numOfCards;
        ostream& deckOut;

    public:
        DeckT(CardT, int, ostream&);

//------------------------------------------------------------------------------
        DeckT(CardT cardArray[], int numOfCards, ostream& outS): deckOut(outS){
        // Create a deck of cards with a nested for loop
        // 1-4 for suits, 1-13 for ranks
            SuitT st;
            numOfCards = 0;
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
                cardArray[numOfCards] = CardT( st, ranks[m] );
                ++numOfCards;
                }
            }
        }

//------------------------------------------------------------------------------
        void shuffle() {
            cout << "Shuffling Deck." << endl;
            for ( int n = numOfCards; n>0; --n){
                int r = rand() % n; // Random number between 1 and n

            // Perform a swap with card at subscript r, and last card
                CardT cardSwap = cardArray[r];
                cardArray[r] = cardArray[n];
                cardArray[n] = cardSwap;
            }
            cout << "Deck Shuffled." << endl;
        }

//------------------------------------------------------------------------------
        void serialize(ostream& deckOut) {
            for (int k=0; k<52; ++k){
                CardT c = cardArray[k];
                c.serialize(deckOut);
            }
        }

//------------------------------------------------------------------------------
        void print(ostream& out) {
            // Loop through cards in array. Print each to screen
            // Using CardT::operator <<
            cout << "Printing deck" << endl;
            for(int k=0; k<52; ++k){
                CardT c = cardArray[k];
                c.print(out);
            }
        }
};

//------------------------------------------------------------------------------
int main()
{
    int numCards = 0;    // Keep track of number of cards
    //SuitT st;            // Suit of the card
    CardT cardArray[52]; // Store the cards in an array of card objects

    banner();

    ofstream deckFile( OUTFILE );
        if (!deckFile) fatal ("Could not open %s for deck output.", OUTFILE);

    DeckT deck(cardArray, numCards, deckFile);
    cout << "Deck created." << endl;

    srand((unsigned) time(NULL));

    deck.shuffle();
    deck.print(cout);
    deck.serialize(deckFile);

    deckFile.close();
    bye();
    return 0;
}
