#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <math.h>
#include <time.h>

class player;

class card
{
protected:
    std::string name;
    std::string type;
    bool isTapped;

public:
    card() : name(""), type("") {}
    card(std::string n, std::string t) : name(n), type(t), isTapped(false)
    {
    }

    std::string getCardName()
    {
        return this->name;
    }

    virtual int play(player *p) = 0;
};

class effect
{
protected:
    std::string description;

public:
    effect() : description("") {}
    effect(std::string d) : description(d)
    {
    }

    virtual void affect(card *cards)
    {
    }
};

class player
{
protected:
    std::string name;
    int hitPoint;
    std::string totalMana;
    std::vector<std::shared_ptr<card>> library;
    std::vector<std::shared_ptr<card>> hand;
    std::vector<std::shared_ptr<card>> inPlay;
    std::vector<std::shared_ptr<card>> discards;

public:
    player(std::string n, int hP, std::string tM, std::vector<std::shared_ptr<card>> l) : name(n), hitPoint(hP), totalMana(tM), library(l)
    {
        for (int i = 0; i < 5; i++)
        {
            int r = std::rand() % library.size();
            hand.emplace_back(library[r]);
            library.erase(library.begin() + r);
        }
    }

    std::string getTotalMana()
    {
        return this->totalMana;
    }

    int getHP()
    {
        return this->hitPoint;
    }

    void setMana(std::string mana)
    {
        this->totalMana = mana;
    }

    void addMana(char m)
    {
        this->totalMana += m;
    }

    int drawCard()
    {
        if (library.size() == 0)
        {
            std::cout << "You do not have any cards in your library." << std::endl;
            return 2;
        }
        else if (hand.size() >= 7)
        {
            std::cout << "You have 7 cards in your hand. You cannot draw more card!" << std::endl;
            return 1;
        }
        else
        {
            int r = std::rand() % library.size();
            hand.emplace_back(library[r]);
            library.erase(library.begin() + r);
            return 0;
        }
    }

    std::vector<std::shared_ptr<card>> getCardsInHand()
    {
        return hand;
    }

    std::vector<std::shared_ptr<card>> getCardsInPlay()
    {
        return inPlay;
    }
};

bool compareAndPayMana(player *p, std::string cardMana)
{
    std::string newPlayerMana = p->getTotalMana();

    for (int i = 0; i < cardMana.size(); i++)
    {
        int index = newPlayerMana.find(cardMana[i]);
        if (index != std::string::npos)
        {
            newPlayerMana.erase(index, 1);
        }
        else
        {
            if (cardMana[i] == 'X')
            {
                newPlayerMana = newPlayerMana.substr(0, newPlayerMana.size() - 1);
            }
            else
            {
                return false;
            }
        }
    }

    p->setMana(newPlayerMana);

    return true;
}

class creatureCard : public card
{
protected:
    int attackPower;
    int hitPoint;
    std::string color;
    std::string manaCost;
    bool hasFirstStrike;
    bool hasTrample;

public:
    creatureCard() : card(), attackPower(0), hitPoint(0), color(""), manaCost(""), hasFirstStrike(false), hasTrample(false) {}
    creatureCard(std::string n, std::string t, int aP, int hP, std::string c, std::string mC, bool hFS, bool hT) : card(n, t), attackPower(aP), hitPoint(hP), color(c), manaCost(mC), hasFirstStrike(hFS), hasTrample(hT)
    {
    }

    int play(player *p)
    {
        bool isPlayable = compareAndPayMana(p, this->manaCost);
        if (!isPlayable)
        {
            std::cout << "There is not enough mana to play this card!" << std::endl;
            return 0;
        }
        else
        {
            std::cout << "Card has been played!" << std::endl;
            return 1;
        }
    }
};

class sorceryCard : public card
{
protected:
    effect cardEffect;
    std::string color;
    std::string manaCost;

public:
    sorceryCard(std::string n, std::string t, effect e, std::string c, std::string mC) : card(n, t), cardEffect(e), color(c), manaCost(mC)
    {
    }

    int play(player *p)
    {
        bool isPlayable = compareAndPayMana(p, this->manaCost);
        if (!isPlayable)
        {
            std::cout << "There is not enough mana to play this card!" << std::endl;
            return 0;
        }
        else
        {
            std::cout << "Card has been played!" << std::endl;
            return 1;
        }
    }
};

class enchantmentCard : public card
{
protected:
    effect cardEffect;
    std::string color;
    std::string manaCost;

public:
    enchantmentCard(std::string n, std::string t, effect e, std::string c, std::string mC) : card(n, t), cardEffect(e), color(c), manaCost(mC)
    {
    }

    int play(player *p)
    {
        bool isPlayable = compareAndPayMana(p, this->manaCost);
        if (!isPlayable)
        {
            std::cout << "There is not enough mana to play this card!" << std::endl;
            return 0;
        }
        else
        {
            std::cout << "Card has been played!" << std::endl;
            return 1;
        }
    }
};

class landCard : public card
{
protected:
    char mana;

public:
    landCard(std::string n, std::string t, char m) : card(n, t), mana(m)
    {
    }

    int play(player *p)
    {
        p->addMana(this->mana);
        return 1;
    }
};

class destroyEnchantmentEffect : public effect
{
public:
    destroyEnchantmentEffect(std::string d) : effect(d) {}

    void affect(card *cards)
    {
    }
};

class damageTargetCreatureOrPlayerEffect : public effect
{
public:
    damageTargetCreatureOrPlayerEffect(std::string d) : effect(d) {}

    void affect(card *cards)
    {
    }
};

class destoryLandEffect : public effect
{
public:
    destoryLandEffect(std::string d) : effect(d) {}

    void affect(card *cards)
    {
    }
};

class damageAllCreaturesEffect : public effect
{
public:
    damageAllCreaturesEffect(std::string d) : effect(d) {}

    void affect(card *cards)
    {
    }
};

class destroyCreatureEffect : public effect
{
public:
    destroyCreatureEffect(std::string d) : effect(d) {}

    void affect(card *cards)
    {
    }
};

class gainTrampleEffect : public effect
{
public:
    gainTrampleEffect(std::string d) : effect(d) {}

    void affect(card *cards)
    {
    }
};

class allWhiteCreaturesPositiveGainEffect : public effect
{
public:
    allWhiteCreaturesPositiveGainEffect(std::string d) : effect(d) {}

    void affect(card *cards)
    {
    }
};

class allBlackCreaturesNegativeGainEffect : public effect
{
public:
    allBlackCreaturesNegativeGainEffect(std::string d) : effect(d) {}

    void affect(card *cards)
    {
    }
};

class allBlackCreaturesPositiveGainEffect : public effect
{
public:
    allBlackCreaturesPositiveGainEffect(std::string d) : effect(d) {}

    void affect(card *cards)
    {
    }
};

class allGreenCreaturesLoseTrampleEffect : public effect
{
public:
    allGreenCreaturesLoseTrampleEffect(std::string d) : effect(d) {}

    void affect(card *cards)
    {
    }
};

class loseFirstStrikeEffect : public effect
{
public:
    loseFirstStrikeEffect(std::string d) : effect(d) {}

    void affect(card *cards)
    {
    }
};

class returnCardFromDiscardEffect : public effect
{
public:
    returnCardFromDiscardEffect(std::string d) : effect(d) {}

    void affect(card *cards)
    {
    }
};

int main()
{
    std::srand(std::time(0));

    // effects
    destroyEnchantmentEffect destroyEnchantmentE("Destroy 1 Target Enchantment");
    damageTargetCreatureOrPlayerEffect damageTargetCreatureOrPlayerE("Deal 2 dmg to target creature or player");
    destoryLandEffect destoryLandE("Destroy 1 Target Land");
    damageAllCreaturesEffect damageAllCreaturesE("Deal 1 dmg to all creatures");
    destroyCreatureEffect destroyCreatureE("Destroy 1 Target Creature");
    returnCardFromDiscardEffect returnCardFromDiscardE("Return 1 character card from discard to hand");

    gainTrampleEffect gainTrampleE("1 Target creature gains Trample");
    allWhiteCreaturesPositiveGainEffect allWhiteCreaturesPositiveGainE("All white creatures gain +1/+1");
    allBlackCreaturesNegativeGainEffect allBlackCreaturesNegativeGainE("All black creatures gain -1/-1");
    allBlackCreaturesPositiveGainEffect allBlackCreaturesPositiveGainE("All black creatures gain +2/+0");
    allGreenCreaturesLoseTrampleEffect allGreenCreaturesLoseTrampleE("All green creatures lose Trample");
    loseFirstStrikeEffect loseFirstStrikeE("1 Target creature loses First Strike");

    // land cards
    std::shared_ptr<card> forest = std::make_shared<landCard>("Forest", "land", 'G');
    std::shared_ptr<card> island = std::make_shared<landCard>("Island", "land", 'L');
    std::shared_ptr<card> mountain = std::make_shared<landCard>("Mountain", "land", 'R');
    std::shared_ptr<card> plains = std::make_shared<landCard>("Plains", "land", 'W');
    std::shared_ptr<card> swamp = std::make_shared<landCard>("Swamp", "land", 'B');

    // creature cards
    std::shared_ptr<card> soldier = std::make_shared<creatureCard>("Soldier", "creature", 1, 1, "white", "W", false, false);
    std::shared_ptr<card> armoredPegasus = std::make_shared<creatureCard>("Armored Pegasus", "creature", 1, 2, "white", "WX", false, false);
    std::shared_ptr<card> whiteKnight = std::make_shared<creatureCard>("White Knight", "creature", 2, 2, "white", "WW", true, false);
    std::shared_ptr<card> angryBear = std::make_shared<creatureCard>("Angry Bear", "creature", 3, 2, "green", "GXX", false, true);
    std::shared_ptr<card> guard = std::make_shared<creatureCard>("Guard", "creature", 2, 5, "white", "WWXX", false, false);
    std::shared_ptr<card> werewolf = std::make_shared<creatureCard>("Werewolf", "creature", 4, 6, "green", "GWXX", false, true);
    std::shared_ptr<card> skeleton = std::make_shared<creatureCard>("Skeleton", "creature", 1, 1, "black", "B", false, false);
    std::shared_ptr<card> ghost = std::make_shared<creatureCard>("Ghost", "creature", 2, 1, "black", "BX", false, false);
    std::shared_ptr<card> blackKnight = std::make_shared<creatureCard>("Black Knight", "creature", 2, 2, "black", "BB", true, false);
    std::shared_ptr<card> orcManiac = std::make_shared<creatureCard>("Orc Maniac", "creature", 4, 1, "red", "RXX", false, false);
    std::shared_ptr<card> hobgoblin = std::make_shared<creatureCard>("Hobgoblin", "creature", 3, 3, "red", "RBX", false, false);
    std::shared_ptr<card> vampire = std::make_shared<creatureCard>("Vampire", "creature", 6, 3, "black", "BXXX", false, false);

    // sorcery cards
    std::shared_ptr<card> disenchant = std::make_shared<sorceryCard>("Disenchant", "sorcery", destroyEnchantmentE, "white", "WX");
    std::shared_ptr<card> lightningBolt = std::make_shared<sorceryCard>("Lightning Bolt", "sorcery", damageTargetCreatureOrPlayerE, "green", "GX");
    std::shared_ptr<card> flood = std::make_shared<sorceryCard>("Flood", "sorcery", destoryLandE, "green", "GWX");
    std::shared_ptr<card> reanimate = std::make_shared<sorceryCard>("Reanimate", "sorcery", returnCardFromDiscardE, "black", "B");
    std::shared_ptr<card> plague = std::make_shared<sorceryCard>("Plague", "sorcery", damageAllCreaturesE, "black", "BXX");
    std::shared_ptr<card> terror = std::make_shared<sorceryCard>("Terror", "sorcery", destroyCreatureE, "black", "BX");

    // enchantment cards
    std::shared_ptr<card> rage = std::make_shared<enchantmentCard>("Rage", "enchantment", gainTrampleE, "green", "G");
    std::shared_ptr<card> holyWar = std::make_shared<enchantmentCard>("Holy War", "enchantment", allWhiteCreaturesPositiveGainE, "white", "WX");
    std::shared_ptr<card> holyLight = std::make_shared<enchantmentCard>("Holy Light", "enchantment", allBlackCreaturesNegativeGainE, "white", "WX");
    std::shared_ptr<card> unholyWar = std::make_shared<enchantmentCard>("Unholy War", "enchantment", allBlackCreaturesPositiveGainE, "black", "BX");
    std::shared_ptr<card> restrain = std::make_shared<enchantmentCard>("Restrain", "enchantment", allGreenCreaturesLoseTrampleE, "red", "RXX");
    std::shared_ptr<card> slow = std::make_shared<enchantmentCard>("Slow", "enchantment", loseFirstStrikeE, "black", "B");

    std::vector<std::shared_ptr<card>> player1Library{
        plains, plains, plains, plains, plains, forest, forest, forest, island,
        soldier, soldier, soldier, armoredPegasus, armoredPegasus, whiteKnight, whiteKnight, angryBear, guard, werewolf,
        disenchant, lightningBolt, flood, flood,
        rage, holyWar, holyLight};

    std::vector<std::shared_ptr<card>> player2Library{
        swamp, swamp, swamp, swamp, swamp, mountain, mountain, mountain, island,
        skeleton, skeleton, skeleton, ghost, ghost, blackKnight, blackKnight, orcManiac, hobgoblin, vampire,
        reanimate, plague, terror, terror,
        unholyWar, restrain, slow};

    player player1("player1", 15, "", player1Library);
    player player2("player2", 15, "", player2Library);

    while (player1.getHP() > 0 && player2.getHP() > 0)
    {
        int status = player1.drawCard();
        if (status == 2)
        {
            std::cout << "Game is over!" << std::endl;
            break;
        }

        std::vector<std::shared_ptr<card>> player1cardsInPlay = player1.getCardsInPlay();
        std::vector<std::shared_ptr<card>> player2cardsInPlay = player2.getCardsInPlay();
        std::cout << "Your cards in-play" << std::endl;
        for (int i = 1; i <= player1cardsInPlay.size(); i++)
        {
            std::cout << player1cardsInPlay[i - 1]->getCardName() << ", ";
        }
        std::cout << std::endl;

        std::cout << "Opponent's cards in-play" << std::endl;
        for (int i = 1; i <= player2cardsInPlay.size(); i++)
        {
            std::cout << player2cardsInPlay[i - 1]->getCardName() << ", ";
        }
        std::cout << std::endl;

        std::cout << "Your HP: " << player1.getHP() << std::endl;
        std::cout << "Opponent's HP: " << player1.getHP() << std::endl;

        std::vector<std::shared_ptr<card>> cardsInHand = player1.getCardsInHand();
        std::cout << "Your cards in-hand" << std::endl;
        for (int i = 1; i <= cardsInHand.size(); i++)
        {
            std::cout << i << "- " << cardsInHand[i - 1]->getCardName() << ", ";
        }
        std::cout << std::endl;

        int result = 0;
        while (status == 0)
        {
            std::cout << "Please choose a card number to play: " << std::endl;
            int cardNumber;
            std::cin >> cardNumber;

            result = cardsInHand[cardNumber - 1]->play(&player1);
        }
    }

    return 0;
}