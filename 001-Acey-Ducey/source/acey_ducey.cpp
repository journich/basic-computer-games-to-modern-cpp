// *****************************************************************
// Modern C++ Port of original Basic game AceyDucey
// with original bugs/features included.
//
// https://www.atariarchives.org/basicgames/showpage.php?page=2
//
// Various language ports for this game available here.
// https://github.com/coding-horror/basic-computer-games/tree/main
//
// Play the original Basic game in a browser here
// https://coding-horror.github.io/basic-computer-games/01_Acey_Ducey/javascript/aceyducey.html
//
// Tim Buchalka - October 14th, 2023.
// *****************************************************************

#include "acey_ducey.hpp"

#include <iomanip>
#include <iostream>

AceyDucey::AceyDucey() {}

void AceyDucey::displayHeader() const {
  std::cout << std::setw(31) << "ACEY DUCEY CARD GAME\n"
            << "CREATIVE COMPUTING  MORRISTOWN, NEW JERSEY\n\n\n"
            << "ACEY-DUCEY IS PLAYED IN THE FOLLOWING MANNER\n"
            << "THE DEALER (COMPUTER) DEALS TWO CARDS FACE UP\n"
            << "YOU HAVE AN OPTION TO BET OR NOT BET DEPENDING\n"
            << "ON WHETHER OR NOT YOU FEEL THE CARD WILL HAVE\n"
            << "A VALUE BETWEEN THE FIRST TWO.\n"
            << "IF YOU DO NOT WANT TO BET, INPUT: 0\n";
}

// Main game loop
void AceyDucey::play() {
  while (true) {
    switch (gameStatus) {
      case Status::starting:
        displayHeader();
        gameStatus = Status::drawDisplayAndBet;
        break;

      case Status::drawDisplayAndBet: {
        drawCards();
        displayBalance();
        displayCards();
        m_bet = placeBet();
        if (m_bet <= 0) {
          std::cout << "\nCHICKEN!!\n\n";
          gameStatus = Status::drawDisplayAndBet;
        } else {
          gameStatus = Status::determineResult;
        }
        break;
      }

      case Status::determineResult:
        if (finishGame()) {
          gameStatus = Status::gameOver;
        } else {
          gameStatus = Status::drawDisplayAndBet;
        }
        break;

      case Status::gameOver:
        if (playAgain()) {
          m_funds = initialFunds;
          gameStatus = Status::drawDisplayAndBet;
        } else {
          std::cout << "O.K., HOPE YOU HAD FUN!\n";
          exit(EXIT_SUCCESS);
        }
        break;
    }
  }
}

// Draw the first two cards for the player.
void AceyDucey::drawCards() {
  do {
    saveCard(firstCard, drawCard());
    saveCard(secondCard, drawCard());
    // As the game is based on the player deciding to bet on
    // the next card being between the range of the 1st and 2nd cards
    // we need to make sure that the first card is less than the 2nd one in
    // terms of value
  } while (m_cards.at(firstCard) >= m_cards.at(secondCard));
}

// Save the players card into the array
void AceyDucey::saveCard(int card, int drawn) { m_cards.at(card) = drawn; }

// Draws a random card.
int AceyDucey::drawCard() const {
  static std::random_device rd;
  static std::default_random_engine engine{rd()};
  // cards in a deck 2-10 then 11 = Jack, 12 = Queen, 13 = King, 14 = Ace
  static std::uniform_int_distribution randomCard{2, cardsInGame};

  return randomCard(engine);
}

void AceyDucey::displayBalance() const {
  std::cout << "YOU NOW HAVE " << m_funds << " DOLLARS\n";
}

void AceyDucey::displayCards() const {
  std::cout << "\nHERE ARE YOUR NEXT TWO CARDS:\n";
  displayCard(m_cards.at(firstCard));
  displayCard(m_cards.at(secondCard));
}

void AceyDucey::displayCard(int cardFaceValue) const {
  std::cout << getCardFaceName(cardFaceValue) << "\n";
}

int AceyDucey::placeBet() const {
  int betPlaced{0};
  bool validInput{false};
  do {
    std::cout << "\n\nWHAT IS YOUR BET?\n";
    std::cin >> betPlaced;
    if (!std::cin.fail()) {
      validInput = true;
    } else {
      // Not a number entered.
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  } while (!validInput);
  return betPlaced;
}
// playout the game
bool AceyDucey::finishGame() {
  bool gameOver{false};
  saveCard(thirdCard, drawCard());
  std::cout << "\n\n\nHERE IS THE CARD WE DREW:\n";
  displayCard(m_cards.at(thirdCard));

  // Is the 3rd drawn card "between" the 1st and 2nd cards ?
  if (m_cards.at(thirdCard) > m_cards.at(firstCard) &&
      m_cards.at(thirdCard) < m_cards.at(secondCard)) {
    // it is so player won
    m_funds += m_bet;
    std::cout << "YOU WIN!!\n";
    // not game over because player has funds
  } else {
    m_funds -= m_bet;
    if (m_funds > 0) {
      std::cout << "SORRY, YOU LOSE\n";
    } else {
      // bankrupt
      std::cout << "\n\nSORRY, FRIEND, BUT YOU BLEW YOUR WAD.\n\n";
      gameOver = true;
    }
  }
  return gameOver;
}

bool AceyDucey::playAgain() const {
  std::cout << "TRY AGAIN (YES OR NO)\n";
  std::string anotherGame{};
  std::cin >> anotherGame;
  if ("YES" == anotherGame) {
    return true;
  }
  return false;
}

// Retrieves the card face name for a given card value
std::string AceyDucey::getCardFaceName(int cardValue) const {
  // We are using cards 2-14 in the game, so deduct 2
  // for accessing the array which, of course, starts from zero.
  return m_faceNames.at(cardValue - 2);
}

int main() {
  AceyDucey game{};
  game.play();
}
