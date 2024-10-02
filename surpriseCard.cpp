#include "surpriseCard.hpp"
using namespace ariel;

surpriseCard::surpriseCard()
{
    // Initialize the vector with different surprise cards
    cards = {
            "Advance to Go (Collect $200)",
            "Bank pays you dividend of $50",
            "Go back 3 spaces",
            "Go directly to Jail – do not pass Go, do not collect $200",
            "Make general repairs on all your property – For each house pay $25, for each hotel pay $100",
            "Pay poor tax of $15",
            "Take a trip to Reading Railroad – If you pass Go collect $200",
            "Take a walk on the Boardwalk – Advance token to Boardwalk",
            "You have been elected Chairman of the Board – Pay each player $50",
            "Your building loan matures – Collect $150",
            "Get out of Jail Free – This card may be kept until needed or traded",
            "Advance to Illinois Ave. – If you pass Go, collect $200",
            "Advance to St. Charles Place – If you pass Go, collect $200",
            "You are assessed for street repairs – $40 per house, $115 per hotel",
            "Advance to nearest Utility – If unowned you may buy it from the Bank. If owned, throw dice and pay owner a total ten times the amount thrown",
            "Advance to nearest Railroad. If unowned, you may buy it from the Bank. If owned, pay owner twice the rental to which they are otherwise entitled"
    };
    // Seed random number generator
    srand(static_cast<unsigned>(time(0)));
}

std::string surpriseCard::getCard() const
{
    int index = rand() % cards.size();  // Get a random index
    return cards[index];  // Return the card at the random index
}

// Method to add a new card dynamically from user input
void surpriseCard::addCard()
{
    std::string cardContent;
    std::cout << "Enter the content of the new surprise card: ";
    std::getline(std::cin, cardContent); // Get card content from the user
    cards.push_back(cardContent);  // Add card to the vector
    std::cout << "New card added successfully!" << std::endl;
}
// Function to process the selected card and apply its effects on the player
void surpriseCard::processCard(Player* player,std::vector<Player*>& allplayers, sf::RenderWindow &window)
{
    std::string card = getCard();  // Get a random card
    std::cout << player->getName() << " drew the card: " << card << std::endl;

    if (card == "Advance to Go (Collect $200)")
    {
        player->setCurrentSquare(40-player->currentIndex, window); // Pass the window if needed
        player->money += 200;
        std::cout << player->getName() << " advances to Go and collects $200.\n";
    }
    else if (card == "Bank pays you dividend of $50")
    {
        player->money += 50;
        std::cout << player->getName() << " receives $50 from the bank.\n";
    }
    else if (card == "Go back 3 spaces")
    {
        player->setCurrentSquare(37, window);
        std::cout << player->getName() << " goes back 3 spaces.\n";
    }
    else if (card == "Go directly to Jail – do not pass Go, do not collect $200")
    {
        if(10 < player->currentIndex)
        {
            player->money -= 200;
        }
        player->setCurrentSquare(40-(player->currentIndex-10), window);  // Jail position
        player->turnsInJail = 3;
        std::cout << player->getName() << " goes to jail.\n";
    }
    else if (card == "Make general repairs on all your property – For each house pay $25, for each hotel pay $100")
    {
        int houses = player->ownedProperties.size(); // Assuming this counts houses
        int hotels = 0; // Replace with actual hotel counting logic
        int repairCost = houses * 25 + hotels * 100;
        player->money -= repairCost;
        std::cout << player->getName() << " pays $" << repairCost << " for repairs.\n";
    }
    else if (card == "Pay poor tax of $15")
    {
        player->money -= 15;
        std::cout << player->getName() << " pays poor tax of $15.\n";
    }
    else if (card == "Take a trip to Reading Railroad – If you pass Go collect $200") {
        player->setCurrentSquare(40-(player->currentIndex-5), window);
        std::cout << player->getName() << " takes a trip to Reading Railroad.\n";
    }
    else if (card == "Take a walk on the Boardwalk – Advance token to Boardwalk") {
        player->setCurrentSquare(40-(player->currentIndex-39), window);
        std::cout << player->getName() << " advances to Boardwalk.\n";
    }
    else if (card == "You have been elected Chairman of the Board – Pay each player $50")
    {
        // Assuming there is a way to get all players
        for (Player* otherPlayer : allplayers)
        {
             if (&otherPlayer != &player)
             {
                 player->money -= 50;
                 otherPlayer->money += 50;
                 std::cout << player->getName() << " pays $50 to " << otherPlayer->getName() << ".\n";
             }
        }
    }
    else if (card == "Your building loan matures – Collect $150")
    {
        player->money += 150;
        std::cout << player->getName() << " collects $150 from the matured loan.\n";
    }
    else if (card == "Get out of Jail Free – This card may be kept until needed or traded")
    {
        player->getOutFromJail = true;
        std::cout << player->getName() << " gets a Get Out of Jail Free card.\n";
    }
    else if (card == "Advance to Illinois Ave. – If you pass Go, collect $200")
    {
        player->setCurrentSquare(40-(player->currentIndex-24),window);
    }
    else if (card == "Advance to St. Charles Place – If you pass Go, collect $200")
    {
        player->setCurrentSquare(40-(player->currentIndex-11), window);
    }
    else if (card == "You are assessed for street repairs – $40 per house, $115 per hotel")
    {
        int hotels = 0;
        int houses = 0;
        for(int i = 0; i < player->ownedProperties.size(); i++)
        {
            if(player->ownedProperties[i].numberOfHouses == 5)
            {
                hotels++;
            }
            else
            {
                houses += player->ownedProperties[i].numberOfHouses;
            }
        }
        int assessmentCost = houses * 40 + hotels * 115;
        player->money -= assessmentCost;
        std::cout << player->getName() << " pays $" << assessmentCost << " for street repairs.\n";
    }
    else if (card == "Advance to nearest Utility – If unowned you may buy it from the Bank. If owned, throw dice and pay owner a total ten times the amount thrown")
    {

        if(abs(12-player->currentIndex)< abs(28-player->currentIndex))
        {
            player->setCurrentSquare(40-(player->currentIndex-12),window);
        }
        else
        {
            player->setCurrentSquare(40-(player->currentIndex-28),window);
        }
        std::cout << player->getName() << " go to nearest Utility\n";
    }
    else if (card == "Advance to nearest Railroad. If unowned, you may buy it from the Bank. If owned, pay owner twice the rental to which they are otherwise entitled")
    {
        int dis1 = abs(5-player->currentIndex);
        int dis2 = abs(15-player->currentIndex);
        int dis3 = abs(25-player->currentIndex);
        int dis4 = abs(35-player->currentIndex);
        if(dis1 <= dis2 && dis1 <= dis3 && dis1 <= dis4)
        {
            player->setCurrentSquare(40-(player->currentIndex-5),window);
        }
        else if(dis2 <= dis1 && dis2 <= dis3 && dis2 <= dis4)
        {
            player->setCurrentSquare(40-(player->currentIndex-15),window);
        }
        else if(dis3 <= dis1 && dis3 <= dis2 && dis3 <= dis4)
        {
            player->setCurrentSquare(40-(player->currentIndex-25),window);
        }
        else
        {
            player->setCurrentSquare(40-(player->currentIndex-35),window);
        }
        std::cout << player->getName() << " go to nearest Train\n";
    }
}