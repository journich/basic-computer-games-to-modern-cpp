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

#pragma once
#include <array>
#include <random>

enum Status : short { starting, drawDisplayAndBet, determineResult, gameOver };

class AceyDucey {
 public:
  AceyDucey();
  void play();

 private:
  static constexpr size_t firstCard{0};
  static constexpr size_t secondCard{1};
  static constexpr size_t thirdCard{2};
  static constexpr size_t numberCardsInGame{3};
  static constexpr int cardsInGame{14};
  static constexpr size_t initialFunds{100};

  std::array<int, numberCardsInGame> m_cards{};

  const std::array<std::string, cardsInGame> m_faceNames{
      "TWO",  "THREE", "FOUR", "FIVE",  "SIX",  "SEVEN", "EIGHT",
      "NINE", "TEN",   "JACK", "QUEEN", "KING", "ACE"};

  int m_funds{initialFunds};
  int m_bet{0};
  Status gameStatus{Status::starting};

  void displayHeader() const;
  void drawCards();
  void displayBalance() const;
  int placeBet() const;
  bool finishGame();
  bool playAgain() const;
  void displayCards() const;

  std::string getCardFaceName(int cardValue) const;
  int drawCard() const;
  void displayCard(int cardFaceValue) const;
  void saveCard(int card, int drawn);
  int getDrawnCard(int card);
};
