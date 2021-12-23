#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <time.h>


class Effect {
public:
};



class Card {
protected:
    std::string cardName;
    std::string cardManaCost;
    std::string cardColor;
    std::string cardType;
    std::string abilityName;
    int cardMana;
    bool isTapped;
    int baseHp;
    int attackPower;
    bool playCheck;


public:

    Card() : cardName("none"), cardManaCost("0"), cardColor("none"), cardMana(0), cardType("none"), baseHp(0), attackPower(0), abilityName("") {
        playCheck = false;
        isTapped = false;
    }

    Card(std::string cN, std::string cMC, std::string cC, int cM, std::string cT, int hp, int ap, std::string aN) :
        cardName(cN), cardManaCost(cMC), cardColor(cC), cardMana(cM), cardType(cT), baseHp(hp), attackPower(ap), abilityName(aN) {

    }

    //    Card(std::string cN, std::string cMC, std::string cC) : cardName(cN), cardManaCost(cMC), cardColor(cC){
    //
    //    }




    void setCheck(bool z)
    {
        playCheck = z;
    }

    bool getCheck()
    {
        return playCheck;
    }


    virtual std::string getAbilityName()
    {
        return abilityName;
    }

    virtual std::string getManaCost()
    {
        return cardManaCost;
    }

    virtual std::string getCardType()
    {
        return cardType;
    }

    virtual void setTap(bool t)
    {
        isTapped = t;
    }

    virtual bool getTap()
    {
        return isTapped;
    }

    virtual std::string getCardColor()
    {
        return cardColor;
    }

    virtual std::string getCardName()
    {
        return cardName;
    }
    std::string getCard() {
        if (stoi(cardManaCost) > 0) {
            int loop = stoi(cardManaCost);
            cardManaCost = cardManaCost.erase(0, 1);
            for (loop; loop > 0; loop--) {
                std::string value;
                std::cout << "Please enter which color to use for colorless mana (Please enter uppercase. Like :'B-L-W-G-R')";
                std::cin >> value;
                value = value.at(0);
                cardManaCost.insert(0, value);
            }
            return cardManaCost;
        }

        else {
            cardManaCost = cardManaCost.erase(0, 1);

            return cardManaCost;

        }
    }

    virtual void printInfo()
    {
        std::cout << "-" << cardName << "-";
    }

    virtual void untapAllCards()
    {
        isTapped = false;
    }

    virtual void tapAllCards()
    {
        isTapped = true;
    }

    virtual int getCardAp() {
        return attackPower;
    }

    virtual void decreaseCardBaseHp(int n)
    {
        baseHp = baseHp - n;
    }

    virtual int getCardHp() {
        return baseHp;
    }

    virtual void decraseAttackPow(int n)
    {
        attackPower -= n;
    }

    virtual void decreaseHealth(int n)
    {
        baseHp += n;
    }

    virtual void increaseHealth(int n)
    {
        baseHp += n;
    }

    virtual void increaseAttackPow(int n)
    {
        attackPower += n;
    }


};

class landCard : public Card {
protected:
    std::string givenMana;
    bool isDead;
public:

    landCard() : isDead(false), givenMana("0"), Card() {
    }

    landCard(std::string cN, std::string cMC, std::string cC, int cM, std::string cT, int hp, int ap, std::string aN)
        :Card(cN, cMC, cC, cM, cT, hp, ap, aN) {

        isDead = false;

    }


    // Mana'ları string ile aldığımız için if / else ile kontrol edip oyuncuya öyle mana vericez ??
    std::string ManaType()
    {
        if (cardName == "Forest")
        {
            return "G";
        }
        else if (cardName == "Island")
        {
            // Blue kullanan kart yok ??
            return "L";
        }
        else if (cardName == "Mountain")
        {
            return "R";
        }
        else if (cardName == "Plains")
        {
            return "W";
        }
        else if (cardName == "Swamp")
        {
            return "B";
        }

    }

    void destroyedCard()
    {
        isDead = true;
    }

};


class creatureCard : public Card {
protected:
    bool hasAbility;
    bool isDead;
public:


    creatureCard() : hasAbility(false), Card() {
        isDead = false;
    }


    creatureCard(std::string cN, std::string cMC, std::string cC, bool hasAb, int cM, std::string cT, int hp, int ap, std::string aN)
        : Card(cN, cMC, cC, cM, cT, hp, ap, aN), hasAbility(hasAb) {

        isDead = false;

        if (baseHp <= 0)
        {
            isDead = true;
        }

    }




    // Fonksiyonlar ile hp ve attack powerı ayarlamak gerekebilir ilerde


    void destroyedCard()
    {
        isDead = true;
        baseHp = 0;
    }

    void increaseAttackPow(int n)
    {
        attackPower += n;
    }

    void increaseHealth(int n)
    {
        baseHp += n;
    }

    void decreaseHealth(int n)
    {
        baseHp += n;
    }



    void decraseAttackPow(int n)
    {
        attackPower -= n;
    }

    void hasAbilitySetTrue()
    {
        hasAbility = true;
    }

    void hasAbilitySetFalse()
    {
        hasAbility = false;
    }

    void abilityNameSet(std::string newAbilityName)
    {
        abilityName = newAbilityName;
    }

    bool gethasAbility()
    {
        return hasAbility;
    }

    int getCardHp() {
        return baseHp;
    }

    void decreaseCardBaseHp(int n)
    {
        baseHp = baseHp - n;
    }

    int getCardAp() {
        return attackPower;
    }

    std::string getAbilityName()
    {
        return abilityName;
    }
};

class enchantmentCard : public Card {
protected:
    // effectin pointer olması gerekebilir
    Effect effect;
public:

    // Alttaki constructor yanlış olabilir kontrol etmek gerekli.
    enchantmentCard() : Card(), effect() {

    }


    enchantmentCard(std::string cN, std::string cMC, std::string cC, Effect effect, int cM, std::string cT, int hp, int ap, std::string aN) :
        Card(cN, cMC, cC, cM, cT, hp, ap, aN), effect(effect) {

    }


};

class sorceryCard : public Card {
protected:
    // effectin pointer olması gerekebilir
    Effect effect;
public:

    // Alttaki constructor yanlış olabilir kontrol etmek gerekli.
    sorceryCard() : Card(), effect() {

    }


    sorceryCard(std::string cN, std::string cMC, std::string cC, Effect effect, int cM, std::string cT, int hp, int ap, std::string aN) :
        Card(cN, cMC, cC, cM, cT, hp, ap, aN), effect(effect) {

    }

};


class Player {
protected:
    int playerBaseHp;
    int playerGreenMana;
    int playerBlueMana;
    int playerRedMana;
    int playerWhiteMana;
    int playerBlackMana;
    bool isAlive;
    std::vector<creatureCard> playerCreatureCards;
    std::vector<creatureCard> ::iterator creaturePtr;
    std::vector<landCard> playerLandCards;
    std::vector<landCard> ::iterator landPtr;
    std::vector<enchantmentCard> playerEnchanmentCards;
    std::vector<enchantmentCard> ::iterator enchanmentPtr;
    std::vector<sorceryCard> playerSorceryCards;
public:

    std::vector<Card> hand;
    std::vector<Card> inPlay;
    std::vector<Card> library;
    std::vector<Card> discard;
    std::vector<Card> playerDeck;

    Player() :
        playerBaseHp(15), playerGreenMana(0), playerBlueMana(0), playerRedMana(0), playerWhiteMana(0), playerBlackMana(0) {
        isAlive = true;
    }


    void addCardToHand(std::shared_ptr<Card> card)
    {
        hand.push_back(*card);
    }

    void addCardToInplay(std::shared_ptr<Card> card)
    {
        inPlay.push_back(*card);
    }

    void addCardToLibrary(std::shared_ptr<Card> card)
    {
        library.push_back(*card);
    }

    void addCardToDiscard(std::shared_ptr<Card> card)
    {
        discard.push_back(*card);
    }



    int returnPlayerHp()
    {
        return playerBaseHp;
    }

    void setIsAliveFalse()
    {
        isAlive = false;
    }

    bool getIsAlive()
    {
        return isAlive;
    }

    void setIsAlive()
    {
        isAlive = false;
    }




    void destroyTargetCreatureCard(std::shared_ptr<creatureCard> targetCreatureCard)
    {
        for (creaturePtr = playerCreatureCards.begin(); creaturePtr != playerCreatureCards.end(); creaturePtr++)
        {
            if (creaturePtr->getCardName() == targetCreatureCard->getCardName())
            {
                // Çalışmayabilir - Tüm playerCreatureCard vektörü silinebilir
                playerCreatureCards.erase(creaturePtr);

                creaturePtr->destroyedCard();
            }
        }
    }

    void destroyTargetLandCard(std::shared_ptr<landCard> targetLandCard)
    {
        for (landPtr = playerLandCards.begin(); landPtr != playerLandCards.end(); landPtr++)
        {
            if (landPtr->getCardName() == targetLandCard->getCardName())
            {
                // Çalışmayabilir - Tüm playerCreatureCard vektörü silinebilir
                playerLandCards.erase(landPtr);

                landPtr->destroyedCard();
            }
        }
    }

    void destroyTargetEnchanmentCard(std::shared_ptr<enchantmentCard> targetEnchanmentCard)
    {
        for (enchanmentPtr = playerEnchanmentCards.begin(); enchanmentPtr != playerEnchanmentCards.end(); enchanmentPtr++)
        {
            if (enchanmentPtr->getCardName() == targetEnchanmentCard->getCardName())
            {
                // Çalışmayabilir - Tüm playerCreatureCard vektörü silinebilir
                playerEnchanmentCards.erase(enchanmentPtr);


            }
        }
    }


    // Kısayol ??

    void greenCreatureCardBuff()
    {
        for (creaturePtr = playerCreatureCards.begin(); creaturePtr != playerCreatureCards.end(); creaturePtr++)
        {
            if (creaturePtr->getCardColor() == "Green")
            {
                creaturePtr->increaseHealth(1);
                creaturePtr->increaseAttackPow(1);
            }
        }
    }

    void blueCreatureCardBuff()
    {
        for (creaturePtr = playerCreatureCards.begin(); creaturePtr != playerCreatureCards.end(); creaturePtr++)
        {
            if (creaturePtr->getCardColor() == "Blue")
            {
                creaturePtr->increaseHealth(1);
                creaturePtr->increaseAttackPow(1);
            }
        }
    }

    void redCreatureCardBuff()
    {
        for (creaturePtr = playerCreatureCards.begin(); creaturePtr != playerCreatureCards.end(); creaturePtr++)
        {
            if (creaturePtr->getCardColor() == "Red")
            {
                creaturePtr->increaseHealth(1);
                creaturePtr->increaseAttackPow(1);
            }
        }
    }

    void whiteCreatureCardBuff()
    {
        for (creaturePtr = playerCreatureCards.begin(); creaturePtr != playerCreatureCards.end(); creaturePtr++)
        {
            if (creaturePtr->getCardColor() == "White")
            {
                creaturePtr->increaseHealth(1);
                creaturePtr->increaseAttackPow(1);
            }
        }
    }

    void blackCreatureCardBuff()
    {
        for (creaturePtr = playerCreatureCards.begin(); creaturePtr != playerCreatureCards.end(); creaturePtr++)
        {
            if (creaturePtr->getCardColor() == "Black")
            {
                creaturePtr->increaseHealth(1);
                creaturePtr->increaseAttackPow(1);
            }
        }
    }

    void greenCreatureCardNerf()
    {
        for (creaturePtr = playerCreatureCards.begin(); creaturePtr != playerCreatureCards.end(); creaturePtr++)
        {
            if (creaturePtr->getCardColor() == "Green")
            {
                creaturePtr->decreaseHealth(1);
                creaturePtr->decraseAttackPow(1);
            }
        }
    }

    void blueCreatureCardNerf()
    {
        for (creaturePtr = playerCreatureCards.begin(); creaturePtr != playerCreatureCards.end(); creaturePtr++)
        {
            if (creaturePtr->getCardColor() == "Blue")
            {
                creaturePtr->decreaseHealth(1);
                creaturePtr->decraseAttackPow(1);
            }
        }
    }

    void redCreatureCardNerf()
    {
        for (creaturePtr = playerCreatureCards.begin(); creaturePtr != playerCreatureCards.end(); creaturePtr++)
        {
            if (creaturePtr->getCardColor() == "Red")
            {
                creaturePtr->decreaseHealth(1);
                creaturePtr->decraseAttackPow(1);
            }
        }
    }

    void whiteCreatureCardNerf()
    {
        for (creaturePtr = playerCreatureCards.begin(); creaturePtr != playerCreatureCards.end(); creaturePtr++)
        {
            if (creaturePtr->getCardColor() == "White")
            {
                creaturePtr->decreaseHealth(1);
                creaturePtr->decraseAttackPow(1);
            }
        }
    }

    void blackCreatureCardNerf()
    {
        for (creaturePtr = playerCreatureCards.begin(); creaturePtr != playerCreatureCards.end(); creaturePtr++)
        {
            if (creaturePtr->getCardColor() == "Black")
            {
                creaturePtr->decreaseHealth(1);
                creaturePtr->decraseAttackPow(1);
            }
        }
    }

    void dealXDamagePlayerOrCreatureCard()
    {
        // Nasıl Olucak
    }

    void moveCreatureCardDiscardToHand()
    {
        if (hand.size() < 7)
        {
            hand.push_back(discard.back());
            discard.pop_back();
        }
    }

    void moveInPlayToDiscard(std::shared_ptr<Player> targetPlayer)
    {

        std::vector<Card> ::iterator vPtr = inPlay.begin();
        std::cout << "Fonksiyon ici " << std::endl;
        std::cout << inPlay.size() << std::endl;
        for (int i = 0; i < inPlay.size(); i++)
        {
            std::shared_ptr<Card> c = std::make_shared<Card>(targetPlayer->inPlay[i]);
            std::cout << "For ici " << std::endl;
            if (c->getCardName() == inPlay[i].getCardName())
            {
                discard.push_back(inPlay[i]);
                inPlay.erase(vPtr + i);
            }

        }
    }


    void targetCreatureGetsFirstStrike(std::shared_ptr<creatureCard> targetCreatureCard)
    {
        for (creaturePtr = playerCreatureCards.begin(); creaturePtr != playerCreatureCards.end(); creaturePtr++)
        {
            if (creaturePtr->getCardName() == targetCreatureCard->getCardName())
            {
                targetCreatureCard->hasAbilitySetTrue();
                targetCreatureCard->abilityNameSet("First Strike");
            }
        }
    }

    void targetCreatureLosesFirstStrike(std::shared_ptr<creatureCard> targetCreatureCard)
    {
        for (creaturePtr = playerCreatureCards.begin(); creaturePtr != playerCreatureCards.end(); creaturePtr++)
        {
            if (creaturePtr->getCardName() == targetCreatureCard->getCardName())
            {
                targetCreatureCard->hasAbilitySetFalse();
                targetCreatureCard->abilityNameSet("none");
            }
        }
    }

    void targetCreatureGetsTrample(std::shared_ptr<creatureCard> targetCreatureCard)
    {
        for (creaturePtr = playerCreatureCards.begin(); creaturePtr != playerCreatureCards.end(); creaturePtr++)
        {
            if (creaturePtr->getCardName() == targetCreatureCard->getCardName())
            {
                targetCreatureCard->hasAbilitySetTrue();
                targetCreatureCard->abilityNameSet("Trample");
            }
        }
    }

    void targetCreatureLosesTrample(std::shared_ptr<creatureCard> targetCreatureCard)
    {
        for (creaturePtr = playerCreatureCards.begin(); creaturePtr != playerCreatureCards.end(); creaturePtr++)
        {
            if (creaturePtr->getCardName() == targetCreatureCard->getCardName())
            {
                targetCreatureCard->hasAbilitySetFalse();
                targetCreatureCard->abilityNameSet("none");
            }
        }
    }

    // player.AddMana(1, island.manatype());
    void AddMana(std::string manatype)
    {
        if (manatype == "G")
        {
            playerGreenMana += 1;
        }
        else if (manatype == "L")
        {
            playerBlueMana += 1;
        }
        else if (manatype == "R")
        {
            playerRedMana += 1;
        }
        else if (manatype == "W")
        {
            playerWhiteMana += 1;
        }
        else if (manatype == "B")
        {
            playerBlackMana += 1;
        }
    }


    int getGreenMana()
    {
        return playerGreenMana;
    }

    void setGreenMana(int n)
    {
        playerGreenMana += n;
    }

    int getBlueMana()
    {
        return playerBlueMana;
    }

    void setBlueMana(int n)
    {
        playerBlueMana += n;
    }

    int getRedMana()
    {
        return playerRedMana;
    }

    void setRedMana(int n)
    {
        playerRedMana += n;
    }

    int getWhiteMana()
    {
        return playerWhiteMana;
    }

    void setWhiteMana(int n)
    {
        playerWhiteMana += n;
    }

    int getBlackMana()
    {
        return playerBlackMana;
    }

    void setBlackMana(int n)
    {
        playerBlackMana += n;
    }

    int getPlayerHp()
    {
        return playerBaseHp;
    }

    void setPlayerHp(int n)
    {
        playerBaseHp = playerBaseHp - n;
    }


    std::vector<creatureCard> getCreatureCards()
    {
        return playerCreatureCards;
    }

    //Print Piles---- Start
    void printLibrary()
    {
        for (int i = 0; i < library.size(); i++)
        {
            std::cout << "Card Number: " << i + 1 << "  ";
            (library[i]).printInfo();
            std::cout << " ,";

        }
    }

    void printHand()
    {
        for (int i = 0; i < hand.size(); i++)
        {
            std::cout << "Card Number: " << i + 1 << "  ";
            (hand[i]).printInfo();
            std::cout << " " << std::endl;
        }
    }

    void printDiscard()
    {
        for (int i = 0; i < discard.size(); i++)
        {
            std::cout << "Card Number: " << i + 1 << "  ";
            (discard[i]).printInfo();
            std::cout << " ,";
        }
    }

    void printInPlay()
    {
        for (int i = 0; i < inPlay.size(); i++)
        {
            std::cout << "Card Number: " << i + 1 << "  ";
            (inPlay[i]).printInfo();
            std::cout << " ,";

        }
    }
    //Print Piles ---- Ends

    void untappAllCardsInPlay()
    {
        //Oyuncu Defend yaptıktan sonra tüm kartları untapp yapmamız lazım
        for (int i = 0; i < inPlay.size(); ++i)
        {
            inPlay[i].untapAllCards();
        }
    }

    void addHandCard(int cardNumber)
    {
        std::vector<Card> ::iterator vPtr = library.begin();
        hand.push_back(library[cardNumber]);
        library.erase(vPtr + cardNumber);
    }

};

void drawRandomCardsAtBegin(std::shared_ptr<Player> targetPlayer)
{
    srand(time(0));
    for (int i = 0; i < 5; i++)
    {
        if (targetPlayer->hand.size() < 7)
        {
            int x = rand() % targetPlayer->library.size();
            targetPlayer->addHandCard(x);
        }
    }
}

void drawRandomCardOneTimes(std::shared_ptr<Player> targetPlayer)
{
    srand(time(0));
    if (targetPlayer->hand.size() < 7) {
        int x = rand() % targetPlayer->library.size();
        targetPlayer->addHandCard(x);
    }
}



//Player olmadan olmayacak gibi ??
class DestroyCreatureCard : public Effect {
public:
    void destroyCreatureCard(std::shared_ptr<Player> player, std::shared_ptr<creatureCard>* targetCreatureCard)
    {
        player->destroyTargetCreatureCard(*targetCreatureCard);

        //std::shared_ptr<std::vector<Tank>>tankArray = std::make_shared<std::vector<Tank>>;
    }
};

class DestroyLandCard : public Effect {
public:

    void destroyLandCard(std::shared_ptr<Player> player, std::shared_ptr<landCard>* targetLandCard)
    {
        player->destroyTargetLandCard(*targetLandCard);
    }
};

class DestroyEnchanmentCard : public Effect {

    void destroyEnchanmentCard(std::shared_ptr<Player> player, std::shared_ptr<enchantmentCard>* targetEnchanmentCard)
    {
        player->destroyTargetEnchanmentCard(*targetEnchanmentCard);
    }
};

class BuffAColorCard : public Effect {
public:
    //target color'u Card.cardColor şeklinde alıcak galiba ??
    void BuffColor(std::string targetColor, std::shared_ptr<Player> targetPlayer)
    {
        if (targetColor == "Green")
        {
            targetPlayer->greenCreatureCardBuff();
        }
        else if (targetColor == "Blue")
        {
            targetPlayer->blueCreatureCardBuff();
        }
        else if (targetColor == "Red")
        {
            targetPlayer->redCreatureCardBuff();
        }
        else if (targetColor == "White")
        {
            targetPlayer->whiteCreatureCardBuff();
        }
        else if (targetColor == "Black")
        {
            targetPlayer->blackCreatureCardBuff();
        }
    }
};

class NerfAColorCard : public Effect {

    void NerfColor(std::string targetColor, std::shared_ptr<Player> targetPlayer)
    {
        if (targetColor == "Green")
        {
            targetPlayer->greenCreatureCardNerf();
        }
        else if (targetColor == "Blue")
        {
            targetPlayer->blueCreatureCardNerf();
        }
        else if (targetColor == "Red")
        {
            targetPlayer->redCreatureCardNerf();
        }
        else if (targetColor == "White")
        {
            targetPlayer->whiteCreatureCardNerf();
        }
        else if (targetColor == "Black")
        {
            targetPlayer->blackCreatureCardNerf();
        }
    }
};

class DealXDamage : public Effect {
    // Oyuncuya ya da belirli bir karta belirtilen hasarı verir
};

class MoveCard : public Effect {
public:
    void moveCardFromDiscardToHand(std::shared_ptr<Player> targetPlayer)
    {
        targetPlayer->moveCreatureCardDiscardToHand();
    }
};

class CreatureCardGetsFirstStrike : public Effect {
public:

    void creatureCardGetsFirstStrike(std::shared_ptr<Player> targetPlayer, std::shared_ptr<creatureCard> targetCreatureCard)
    {
        targetPlayer->targetCreatureGetsFirstStrike(targetCreatureCard);
        //First Strike effektini buraya yazıcaz
    }
};

class CreatureCardLosesFirstStrike : public Effect {
public:

    void creatureCardLosesFirstStrike(std::shared_ptr<Player> targetPlayer, std::shared_ptr<creatureCard> targetCreatureCard)
    {
        targetPlayer->targetCreatureLosesFirstStrike(targetCreatureCard);
    }
};

class CreatureCardGetsTrample : public Effect {
public:

    void creatureCardGetsTrample(std::shared_ptr<Player> targetPlayer, std::shared_ptr<creatureCard> targetCreatureCard)
    {
        targetPlayer->targetCreatureGetsTrample(targetCreatureCard);
        //Trample effectini buraya yazıcaz
    }
};

class CreatureCardLosesTrample : public Effect {
public:

    void creatureCardLosesTrample(std::shared_ptr<Player> targetPlayer, std::shared_ptr<creatureCard> targetCreatureCard)
    {
        targetPlayer->targetCreatureLosesTrample(targetCreatureCard);
    }
};


bool CardColorCost(std::shared_ptr<Card> targetCard, std::shared_ptr<Player> targetPlayer)
{
    bool isPlayable = false;

    //tek sıkıntı eğer GWR kısmında Green mana yoksa , G ve R de 1 e eşitse card oynanmamasına rağmen playable gözükücek
    std::string fcard = targetCard->getCard();
    int loop = fcard.length();
    int check;
    int i = 0;
    //GWR
    for (i; i < loop; i++) {
        if (fcard.at(i) == 'W')
        {
            if (targetPlayer->getWhiteMana() - 1 >= 0)
            {
                targetPlayer->setWhiteMana(-1);
                isPlayable = true;
            }
            else
            {
                std::cout << "Not enough mana" << std::endl;
                return isPlayable = false;
                break;
            }
        }

        else if (fcard.at(i) == 'R')
        {
            if (targetPlayer->getRedMana() - 1 >= 0)
            {
                targetPlayer->setRedMana(-1);
                isPlayable = true;

            }
            else
            {
                std::cout << "Not enough mana" << std::endl;
                return isPlayable = false;
                break;
            }
        }
        else if (fcard.at(i) == 'L')
        {
            if (targetPlayer->getBlueMana() - 1 >= 0)
            {
                targetPlayer->setBlueMana(-1);
                isPlayable = true;
            }
            else
            {
                std::cout << "Not enough mana" << std::endl;
                return isPlayable = false;
                break;
            }
        }
        else if (fcard.at(i) == 'G')
        {
            if (targetPlayer->getGreenMana() - 1 >= 0)
            {
                targetPlayer->setGreenMana(-1);
                isPlayable = true;
            }
            else
            {
                std::cout << "Not enough mana" << std::endl;
                return isPlayable = false;
                break;
            }
        }

        else if (fcard.at(i) == 'B')
        {
            if (targetPlayer->getBlackMana() - 1 >= 0)
            {
                targetPlayer->setBlackMana(-1);
                isPlayable = true;
            }
            else
            {
                std::cout << "Not enough mana" << std::endl;
                return isPlayable = false;
                break;
            }
        }
    }
    if (isPlayable == false)
    {
        for (check = 0; check < i; check++)
        {
            // B = 5 w = 0 - b = 4 w= nem B = 5
            if (fcard.at(check) == 'W')
            {
                targetPlayer->setWhiteMana(1);
            }
            else if (fcard.at(check) == 'R')
            {
                targetPlayer->setRedMana(1);
            }
            else if (fcard.at(check) == 'B')
            {
                targetPlayer->setBlackMana(1);
            }
            else if (fcard.at(check) == 'G')
            {
                targetPlayer->setGreenMana(1);
            }
            else if (fcard.at(check) == 'L')
            {
                targetPlayer->setBlueMana(1);
            }
        }
    }
    else
    {
        return true;
    }
}

void handToInPlay(std::shared_ptr<Player> targetPlayer)
{
    //ManaCheck & Land card only one times &
    int input = 0;
    std::cout << "Please enter a number which is you want to play: " << std::endl;
    std::cin >> input;
    for (int i = 1; i <= targetPlayer->hand.size(); i++)
    {
        std::vector<Card> ::iterator vPtr = targetPlayer->hand.begin();
        if (input == i)
        {
            std::string checkType = targetPlayer->hand[i - 1].getCardType();
            if (checkType == "landCard")
            {
                std::string manaCostCheck = targetPlayer->hand[i - 1].getManaCost();
                targetPlayer->AddMana(manaCostCheck);
                targetPlayer->hand.erase(vPtr + (i - 1));
            }
            else {

                std::shared_ptr<Card> c = std::make_shared<Card>(targetPlayer->hand[i - 1]);
                bool x = CardColorCost(c, targetPlayer);
                if (x == true)
                {
                    targetPlayer->addCardToInplay(c);
                    targetPlayer->hand.erase(vPtr + (i - 1));
                }

            }
        }
    }
}

void playerDecks(std::shared_ptr<Player> targetPlayer1, std::shared_ptr<Player>  targetPlayer2)
{
    // Effectler
    DestroyCreatureCard destroyCreatureCard;
    DestroyLandCard destroyLandCard;
    DestroyEnchanmentCard destroyEnchanmentCard;
    BuffAColorCard buffAColorCard;
    NerfAColorCard nerfAColorCard;
    DealXDamage dealXDamage;
    MoveCard moveCard;
    CreatureCardGetsFirstStrike creatureCardGetsFirstStrike;
    CreatureCardLosesFirstStrike creatureCardLosesFirstStrike;
    CreatureCardGetsTrample creatureCardGetsTrample;
    CreatureCardLosesTrample creatureCardLosesTrample;

    //targetplayer->getWhiteMana() - targetCard->getMana() >= 0
    //LandCard (0 lar silinecek)
    std::shared_ptr<Card>Forest1 = std::make_shared<landCard>("Forest", "G", "Green", 0, "landCard", 0, 0, "NULL");
    std::shared_ptr<Card>Forest2 = std::make_shared<landCard>("Forest", "G", "Green", 0, "landCard", 0, 0, "NULL");
    std::shared_ptr<Card>Forest3 = std::make_shared<landCard>("Forest", "G", "Green", 0, "landCard", 0, 0, "NULL");
    std::shared_ptr<Card>Island1 = std::make_shared<landCard>("Island", "L", "Blue", 0, "landCard", 0, 0, "NULL");
    std::shared_ptr<Card>Island2 = std::make_shared<landCard>("Island", "L", "Blue", 0, "landCard", 0, 0, "NULL");
    std::shared_ptr<Card>Mountain1 = std::make_shared<landCard>("Mountain", "R", "Red", 0, "landCard", 0, 0, "NULL");
    std::shared_ptr<Card>Mountain2 = std::make_shared<landCard>("Mountain", "R", "Red", 0, "landCard", 0, 0, "NULL");
    std::shared_ptr<Card>Mountain3 = std::make_shared<landCard>("Mountain", "R", "Red", 0, "landCard", 0, 0, "NULL");
    std::shared_ptr<Card>Plains1 = std::make_shared<landCard>("Plains", "W", "White", 0, "landCard", 0, 0, "NULL");
    std::shared_ptr<Card>Plains2 = std::make_shared<landCard>("Plains", "W", "White", 0, "landCard", 0, 0, "NULL");
    std::shared_ptr<Card>Plains3 = std::make_shared<landCard>("Plains", "W", "White", 0, "landCard", 0, 0, "NULL");
    std::shared_ptr<Card>Plains4 = std::make_shared<landCard>("Plains", "W", "White", 0, "landCard", 0, 0, "NULL");
    std::shared_ptr<Card>Plains5 = std::make_shared<landCard>("Plains", "W", "White", 0, "landCard", 0, 0, "NULL");
    std::shared_ptr<Card>Swamp1 = std::make_shared<landCard>("Swamp", "B", "Black", 0, "landCard", 0, 0, "NULL");
    std::shared_ptr<Card>Swamp2 = std::make_shared<landCard>("Swamp", "B", "Black", 0, "landCard", 0, 0, "NULL");
    std::shared_ptr<Card>Swamp3 = std::make_shared<landCard>("Swamp", "B", "Black", 0, "landCard", 0, 0, "NULL");
    std::shared_ptr<Card>Swamp4 = std::make_shared<landCard>("Swamp", "B", "Black", 0, "landCard", 0, 0, "NULL");
    std::shared_ptr<Card>Swamp5 = std::make_shared<landCard>("Swamp", "B", "Black", 0, "landCard", 0, 0, "NULL");
    //CreaturCards
    std::shared_ptr<Card>Soldier1 = std::make_shared<creatureCard>("Soldier", "0W", "White", false, 1, "creatureCard", 1, 1, "NULL");
    std::shared_ptr<Card>Soldier2 = std::make_shared<creatureCard>("Soldier", "0W", "White", false, 1, "creatureCard", 1, 1, "NULL");
    std::shared_ptr<Card>Soldier3 = std::make_shared<creatureCard>("Soldier", "0W", "White", false, 1, "creatureCard", 1, 1, "NULL");
    std::shared_ptr<Card>ArmoredPegasus1 = std::make_shared<creatureCard>("Armored Pegasus", "1W", "White", false, 2, "creatureCard", 1, 2, "NULL");
    std::shared_ptr<Card>ArmoredPegasus2 = std::make_shared<creatureCard>("Armored Pegasus", "1W", "White", false, 2, "creatureCard", 1, 2, "NULL");
    std::shared_ptr<Card>WhiteKnight1 = std::make_shared<creatureCard>("White Knight", "0WW", "White", true, 2, "creatureCard", 2, 2, "First Strike");
    std::shared_ptr<Card>WhiteKnight2 = std::make_shared<creatureCard>("White Knight", "0WW", "White", true, 2, "creatureCard", 2, 2, "First Strike");
    std::shared_ptr<Card>AngryBear = std::make_shared<creatureCard>("Angry Bear", "2G", "Green", true, 3, "creatureCard", 3, 2, "Trample");
    std::shared_ptr<Card>Guard = std::make_shared<creatureCard>("Guard", "2WW", "White", false, 4, "creatureCard", 2, 5, "NULL");
    std::shared_ptr<Card>Werewolf = std::make_shared<creatureCard>("Werewolf", "2GW", "Green", true, 4, "creatureCard", 4, 6, "Trample");
    std::shared_ptr<Card>Skeleton1 = std::make_shared<creatureCard>("Skeleton", "0B", "Black", false, 1, "creatureCard", 1, 1, "NULL");
    std::shared_ptr<Card>Skeleton2 = std::make_shared<creatureCard>("Skeleton", "0B", "Black", false, 1, "creatureCard", 1, 1, "NULL");
    std::shared_ptr<Card>Skeleton3 = std::make_shared<creatureCard>("Skeleton", "0B", "Black", false, 1, "creatureCard", 1, 1, "NULL");
    std::shared_ptr<Card>Ghost1 = std::make_shared<creatureCard>("Ghost", "1B", "Black", false, 2, "creatureCard", 2, 1, "NULL");
    std::shared_ptr<Card>Ghost2 = std::make_shared<creatureCard>("Ghost", "1B", "Black", false, 2, "creatureCard", 2, 1, "NULL");
    std::shared_ptr<Card>BlackKnight1 = std::make_shared<creatureCard>("Black Knight", "0BB", "Black", true, 2, "creatureCard", 2, 2, "First Strike");
    std::shared_ptr<Card>BlackKnight2 = std::make_shared<creatureCard>("Black Knight", "0BB", "Black", true, 2, "creatureCard", 2, 2, "First Strike");
    std::shared_ptr<Card>OrcManiac = std::make_shared<creatureCard>("Orc Maniac", "2R", "Red", false, 3, "creatureCard", 4, 1, "NULL");
    std::shared_ptr<Card>Hobgoblin = std::make_shared<creatureCard>("Hobgoblin", "1RB", "Red", false, 3, "creatureCard", 3, 3, "NULL");
    std::shared_ptr<Card>Vampire = std::make_shared<creatureCard>("Vampire", "3B", "Black", false, 4, "creatureCard", 6, 3, "NULL");

    //EnchanmentCards
    std::shared_ptr<Card> Rage = std::make_shared<enchantmentCard>("Rage", "0G", "Green", creatureCardGetsTrample, 1, "enchantmentCard", 0, 0, "NULL");
    std::shared_ptr<Card> HolyWar = std::make_shared<enchantmentCard>("Holy War", "1W", "White", buffAColorCard, 2, "enchantmentCard", 0, 0, "NULL");
    std::shared_ptr<Card> HolyLight = std::make_shared<enchantmentCard>("Holy Light", "1W", "White", nerfAColorCard, 2, "enchantmentCard", 0, 0, "NULL");
    std::shared_ptr<Card> UnholyWar = std::make_shared<enchantmentCard>("Unholy War", "1B", "Black", buffAColorCard, 2, "enchantmentCard", 0, 0, "NULL");
    std::shared_ptr<Card> Restrain = std::make_shared<enchantmentCard>("Restrain", "2R", "Red", creatureCardLosesTrample, 3, "enchantmentCard", 0, 0, "NULL"); // All Green creatures diyor bizde Ã¶yle bir fonksiyon yok !!
    std::shared_ptr<Card> Slow = std::make_shared<enchantmentCard>("Slow", "0B", "Black", creatureCardLosesFirstStrike, 1, "enchantmentCard", 0, 0, "NULL");

    //SorceryCards
    std::shared_ptr<Card> Disenchant = std::make_shared<sorceryCard>("Disenchant", "1W", "White", destroyEnchanmentCard, 2, "sorceryCard", 0, 0, "NULL");
    std::shared_ptr<Card> LightningBolt = std::make_shared<sorceryCard>("Lightning Bolt", "1G", "Green", dealXDamage, 2, "sorceryCard", 0, 0, "NULL");
    std::shared_ptr<Card> Flood1 = std::make_shared<sorceryCard>("Flood", "1GW", "Green", destroyLandCard, 3, "sorceryCard", 0, 0, "NULL");
    std::shared_ptr<Card> Flood2 = std::make_shared<sorceryCard>("Flood", "1GW", "Green", destroyLandCard, 3, "sorceryCard", 0, 0, "NULL");
    std::shared_ptr<Card> Reanimate = std::make_shared<sorceryCard>("Reanimate", "0B", "Black", moveCard, 1, "sorceryCard", 0, 0, "NULL");
    std::shared_ptr<Card> Plague = std::make_shared<sorceryCard>("Plague", "2B", "Black", dealXDamage, 3, "sorceryCard", 0, 0, "NULL"); // deal 1 dmg to all creatures
    std::shared_ptr<Card> Terror1 = std::make_shared<sorceryCard>("Terror", "1B", "Black", destroyCreatureCard, 2, "sorceryCard", 0, 0, "NULL");
    std::shared_ptr<Card> Terror2 = std::make_shared<sorceryCard>("Terror", "1B", "Black", destroyCreatureCard, 2, "sorceryCard", 0, 0, "NULL");

    //Land Cards
    targetPlayer1->addCardToLibrary(Forest1);
    targetPlayer1->addCardToLibrary(Forest2);
    targetPlayer1->addCardToLibrary(Forest3);
    targetPlayer1->addCardToLibrary(Island1);
    targetPlayer2->addCardToLibrary(Island2);
    targetPlayer2->addCardToLibrary(Mountain1);
    targetPlayer2->addCardToLibrary(Mountain2);
    targetPlayer2->addCardToLibrary(Mountain3);
    targetPlayer1->addCardToLibrary(Plains1);
    targetPlayer1->addCardToLibrary(Plains2);
    targetPlayer1->addCardToLibrary(Plains3);
    targetPlayer1->addCardToLibrary(Plains4);
    targetPlayer1->addCardToLibrary(Plains5);
    targetPlayer2->addCardToLibrary(Swamp1);
    targetPlayer2->addCardToLibrary(Swamp2);
    targetPlayer2->addCardToLibrary(Swamp3);
    targetPlayer2->addCardToLibrary(Swamp4);
    targetPlayer2->addCardToLibrary(Swamp5);
    //    //Creature Cards
    targetPlayer1->addCardToLibrary(Soldier1);
    targetPlayer1->addCardToLibrary(Soldier2);
    targetPlayer1->addCardToLibrary(Soldier3);
    targetPlayer1->addCardToLibrary(ArmoredPegasus1);
    targetPlayer1->addCardToLibrary(ArmoredPegasus2);
    targetPlayer1->addCardToLibrary(WhiteKnight1);
    targetPlayer1->addCardToLibrary(WhiteKnight2);
    targetPlayer1->addCardToLibrary(AngryBear);
    targetPlayer1->addCardToLibrary(Guard);
    targetPlayer1->addCardToLibrary(Werewolf);
    targetPlayer2->addCardToLibrary(Skeleton1);
    targetPlayer2->addCardToLibrary(Skeleton2);
    targetPlayer2->addCardToLibrary(Skeleton3);
    targetPlayer2->addCardToLibrary(Ghost1);
    targetPlayer2->addCardToLibrary(Ghost2);
    targetPlayer2->addCardToLibrary(BlackKnight1);
    targetPlayer2->addCardToLibrary(BlackKnight2);
    targetPlayer2->addCardToLibrary(OrcManiac);
    targetPlayer2->addCardToLibrary(Hobgoblin);
    targetPlayer2->addCardToLibrary(Vampire);
    //    Sorcery Cards
    targetPlayer1->addCardToLibrary(Disenchant);
    targetPlayer1->addCardToLibrary(LightningBolt);
    targetPlayer1->addCardToLibrary(Flood1);
    targetPlayer1->addCardToLibrary(Flood2);
    targetPlayer2->addCardToLibrary(Reanimate);
    targetPlayer2->addCardToLibrary(Plague);
    targetPlayer2->addCardToLibrary(Terror1);
    targetPlayer2->addCardToLibrary(Terror2);
    //    Enchanment Cards
    targetPlayer1->addCardToLibrary(Rage);
    targetPlayer1->addCardToLibrary(HolyWar);
    targetPlayer1->addCardToLibrary(HolyLight);
    targetPlayer2->addCardToLibrary(UnholyWar);
    targetPlayer2->addCardToLibrary(Restrain);
    targetPlayer2->addCardToLibrary(Slow);

    //std::cout<<targetPlayer1->library.size()<< std::endl;
}

void combat(std::shared_ptr<Card> attackCard, std::shared_ptr<Card> defendingCard, std::shared_ptr<Player> attackerPlayer, std::shared_ptr<Player> defenderPlayer)
{
    std::shared_ptr<Card> c1 = std::make_shared<Card>();
    std::shared_ptr<Card> c2 = std::make_shared<Card>();

    c1 = attackCard;
    c2 = defendingCard;
    // Kartlar arasındaki combat
    //A
    if (attackCard->getAbilityName() == "Trample")
    {
        int extraDamage = 0;
        std::cout << attackCard->getCardName() << " is using Trample effect." << std::endl;
        defendingCard->decreaseCardBaseHp(attackCard->getCardAp());
        if (defendingCard->getCardHp() <= 0)
        {
            std::cout << defendingCard->getCardName() << " is dead!" << std::endl;
            defenderPlayer->moveInPlayToDiscard(defenderPlayer);
            //defendingCard->destroyedCard();
            //Kart Silicez
            defenderPlayer->addCardToDiscard(defendingCard);
        }

        extraDamage = attackCard->getCardAp() - defendingCard->getCardHp();
        defenderPlayer->setPlayerHp(extraDamage);
    }

    //B
    else if (attackCard->getAbilityName() == "First Strike")
    {
        //i
        if (defendingCard->getAbilityName() == "First Strike")
        {
            std::cout << attackCard->getCardName() << " is attacking to " << defendingCard->getCardName() << std::endl;
            defendingCard->decreaseCardBaseHp(attackCard->getCardAp());
            attackCard->decreaseCardBaseHp(defendingCard->getCardAp());
            if (defendingCard->getCardHp() <= 0)
            {
                std::cout << defendingCard->getCardName() << " is dead!" << std::endl;
                //defendingCard->destroyedCard();
            }
            else if (attackCard->getCardHp() <= 0)
            {
                std::cout << attackCard->getCardName() << " is dead!" << std::endl;
                //attackCard->destroyedCard();
            }
            // Tur bitince canı tekrardan aldığı kadar artmalı
            else
            {
                defendingCard->decreaseCardBaseHp(-attackCard->getCardAp());
                attackCard->decreaseCardBaseHp(-defendingCard->getCardAp());
            }
        }
        //ii
        else if (defendingCard->getAbilityName() != "First Strike")
        {
            std::cout << attackCard->getCardName() << " is attacking to " << defendingCard->getCardName() << std::endl;
            defendingCard->decreaseCardBaseHp(attackCard->getCardAp());
            if (defendingCard->getCardHp() <= 0)
            {
                std::cout << defendingCard->getCardName() << " is dead!" << std::endl;
                //defendingCard->destroyedCard();
            }
            // Tur bitince canı tekrardan aldığı kadar artmalı
            else
            {
                defendingCard->decreaseCardBaseHp(-attackCard->getCardAp());
            }
        }
    }
    //C
    else if (attackCard->getAbilityName() == "NULL")
    {
        //i
        if (defendingCard->getAbilityName() == "First Strike")
        {
            attackCard->decreaseCardBaseHp(defendingCard->getCardAp());
            if (attackCard->getCardHp() <= 0)
            {
                std::cout << std::endl;
                std::cout << attackCard->getCardName() << " is dead!" << std::endl;
                //attackCard->destroyedCard();
            }
            else
            {
                defendingCard->decreaseCardBaseHp(attackCard->getCardAp());
            }
        }

        //ii
        if (defendingCard->getAbilityName() == "NULL")
        {
            std::cout << attackCard->getCardName() << " is attacking to " << defendingCard->getCardName() << std::endl;
            defendingCard->decreaseCardBaseHp(attackCard->getCardAp());
            attackCard->decreaseCardBaseHp(defendingCard->getCardAp());
            if (defendingCard->getCardHp() <= 0)
            {
                std::cout << defendingCard->getCardName() << " is dead!" << std::endl;
                //defendingCard->destroyedCard();
            }
            else if (attackCard->getCardHp() <= 0)
            {
                std::cout << attackCard->getCardName() << " is dead!" << std::endl;
                //attackCard->destroyedCard();
            }
            else
            {
                defendingCard->decreaseCardBaseHp(-attackCard->getCardAp());
                attackCard->decreaseCardBaseHp(-defendingCard->getCardAp());
            }
        }
    }
}

void combatForCardAndPlayer(std::shared_ptr<Card> attackerCard, std::shared_ptr<Player> attackerPlayer, std::shared_ptr<Player> defenderPlayer)
{
    //Kart-Player combat
    defenderPlayer->setPlayerHp(attackerCard->getCardAp());
    std::cout << "Player HP : " << defenderPlayer->getPlayerHp() << std::endl;
    if (defenderPlayer->getPlayerHp() <= 0)
    {
        defenderPlayer->setIsAliveFalse();
    }
}



std::shared_ptr<Card> drawCardForCombat(std::shared_ptr<Player> targetPlayer, std::shared_ptr<Card> control)
{
    std::cout << "Please enter a number which is you want to attack " << std::endl;
    int input = 0;
    std::cin >> input;
    if (targetPlayer->inPlay.size() > 0) {

        for (int i = 0; i <= targetPlayer->inPlay.size(); i++)
        {
            if (input == (i + 1))
            {
                std::string checkType = targetPlayer->inPlay[i].getCardType();
                std::shared_ptr<Card> c1 = std::make_shared<Card>();
                if (checkType == "creatureCard")
                {
                    std::vector<Card> ::iterator vPtr = targetPlayer->inPlay.begin();
                    std::shared_ptr<Card> c = std::make_shared<Card>(targetPlayer->inPlay[i]);
                    control->setCheck(true);
                    control->setTap(true);
                    return  c;
                }
                else
                {
                    control->setTap(false);
                    control->setCheck(false);
                }
            }
            else
            {
                control->setTap(false);
                control->setCheck(false);
            }
        }

    }
    else
    {
        control->setTap(false);
        control->setCheck(false);
    }
}

void begin(std::shared_ptr<Player> player1, std::shared_ptr<Player> player2)
{

    playerDecks(player1, player2);
    drawRandomCardsAtBegin(player1);
    drawRandomCardsAtBegin(player2);
    std::cout << "Player 1's turn : " << std::endl;
    std::cout << "Player 1' hand cards" << std::endl;
    player1->printHand();
    handToInPlay(player1);
    std::cout << "Player 1's In play cards" << std::endl;
    player1->printInPlay();

    std::cout << "Player 2's turn : " << std::endl;
    std::cout << "Player 2' hand cards" << std::endl;
    player2->printHand();
    handToInPlay(player2);
    std::cout << "Player 2's In play cards" << std::endl;
    player2->printInPlay();
}


void gameLoop(std::shared_ptr<Player> targetPlayer1, std::shared_ptr<Player> targetPlayer2)
{
    drawRandomCardOneTimes(targetPlayer1);
    std::cout << "Player 1's turn : " << std::endl;
    std::cout << "Player 1' hand cards" << std::endl;
    targetPlayer1->printHand();
    handToInPlay(targetPlayer1);
    std::cout << "Player 1's In play cards" << std::endl;
    targetPlayer1->printInPlay();
    for (int i = 0; i < targetPlayer1->inPlay.size(); i++)
    {
        int z;
        std::cout << "Do you want to attack ? (1/0)" << std::endl;
        std::cin >> z;
        if (z == 1)
        {
            std::shared_ptr<Card> controlCard = std::make_shared<Card>();
            std::shared_ptr<Card> tempCard1 = drawCardForCombat(targetPlayer1, controlCard);
            std::shared_ptr<Card> tempCard2 = drawCardForCombat(targetPlayer2, controlCard);

            if (controlCard->getCheck() == true)
            {
                combat(tempCard1, tempCard2, targetPlayer1, targetPlayer2);
            }
            else
            {
                combatForCardAndPlayer(tempCard1, targetPlayer1, targetPlayer2);
            }
        }
    }
    drawRandomCardOneTimes(targetPlayer2);
    std::cout << "Player 2's turn : " << std::endl;
    std::cout << "Player 2' hand cards" << std::endl;
    targetPlayer2->printHand();
    handToInPlay(targetPlayer2);
    std::cout << "Player 2's In play cards" << std::endl;
    targetPlayer2->printInPlay();
    for (int i = 0; i < targetPlayer2->inPlay.size(); i++)
    {
        int z;
        std::cout << "Do you want to attack ? (1/0)" << std::endl;
        std::cin >> z;
        if (z == 1)
        {
            std::shared_ptr<Card> controlCard = std::make_shared<Card>();
            std::shared_ptr<Card> tempCard1 = drawCardForCombat(targetPlayer2, controlCard);
            std::shared_ptr<Card> tempCard2 = drawCardForCombat(targetPlayer1, controlCard);

            if (controlCard->getCheck() == true)
            {
                combat(tempCard1, tempCard2, targetPlayer2, targetPlayer1);
            }
            else
            {
                combatForCardAndPlayer(tempCard2, targetPlayer2, targetPlayer1);
            }
        }
    }
}


int main()
{
    std::shared_ptr<Player> player1 = std::make_shared<Player>();
    std::shared_ptr<Player> player2 = std::make_shared<Player>();
    begin(player1, player2);
    while (player1->getIsAlive() && player2->getIsAlive() || (player1->library.size() == 0 && player2->library.size() == 0))
    {
        gameLoop(player1, player2);
    }
    if (player1->getIsAlive() == false)
    {
        std::cout << "Player 2 won!" << std::endl;
    }
    else
    {
        std::cout << "Player 1 won!" << std::endl;
    }

    return 0;
}