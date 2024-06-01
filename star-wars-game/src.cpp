#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <ctime>
using namespace std;

class Universe;
class Planet;
class Starship;
class Player;
// CLASS DECLARATIONS
class Planet
{
private:
    int planetID;
    int x_coordinate;
    int y_coordinate;
    int z_coordinate;
    Player *owner;
    int health;
    int level;

public:
    Planet();
    Planet(int id, int x, int y, int z, Player *owner_t);
    int getX();
    int getY();
    int getZ();
    void setCoords(int x, int y, int z);
    int getPlanetID();
    Player *getOwner();
    int getHealth();
    int getLevel();
    void setPlanetID(int i);
    void setOwner(Player *o);
    void setHealth(int h);
    void setLevel(int l);
    void recovery();
    int defend();
    friend void saveGame(const Universe &universe, const Player players[], int numPlayers);
};
class Starship
{
private:
    int spaceid;
    int level;
    int health;
    string type;

public:
    int (Starship::*attackValue)();
    Starship();
    Starship(int id, int shipLevel, const string &ship_type);
    int getSpaceID();
    int getLevel();
    int getHealth();
    void setSpaceID(int s);
    void setLevel(int l);
    void setHealth(int h);
    int damage();
    int tank();
    void recover();
    friend void saveGame(const Universe &universe, const Player players[], int numPlayers);
};
class Player
{
public:
    typedef Planet *OwnedPlanets;
    typedef Starship starships[2];
    Player();
    Player(int id, Universe *uni);
    int getPlayerID();
    int getSize();
    int getTotalXP();
    int getXP();
    void setPlayerID(int id);
    void setSize(int s);
    void setTotalXP(int txp);
    void setXP(int xp);
    void addPlanet(Planet *planet);
    void removePlanet(Planet *planet);
    void upgradePlanet(int planetID);
    void upgradeShip(int spaceid);
    void fight(Planet *planet);
    void explore(int x, int y, int z);
    void starshipLoadout();
    void planetLoadout();
    friend void saveGame(const Universe &universe, const Player players[], int numPlayers);

private:
    int playerid;
    int size;
    Universe *universe_p;
    int xp;
    int total_xp;
    OwnedPlanets *owned_planets;
    starships starship;
};
class Universe
{
private:
    int x_size;
    int y_size;
    int z_size;
    Planet ****universe;

public:
    Universe();
    Universe(int xs, int ys, int zs);
    int getX();
    int getY();
    int getZ();
    Planet *getPlanet(int x, int y, int z);
    void setPlanet(Planet *planet);
    friend void saveGame(const Universe &universe, const Player players[], int numPlayers);
};
// UNIVERSE METHOD FUNCTIONS
Universe::Universe()
{
    x_size = 0;
    y_size = 0;
    z_size = 0;
    universe = NULL;
}
Universe::Universe(int xs, int ys, int zs)
{
    x_size = xs;
    y_size = ys;
    z_size = zs;
    universe = new Planet ***[xs];
    for (int x = 0; x < xs; ++x)
    {
        universe[x] = new Planet **[ys];
        for (int y = 0; y < ys; ++y)
        {
            universe[x][y] = new Planet *[zs];
            for (int z = 0; z < zs; ++z)
            {
                universe[x][y][z] = NULL;
            }
        }
    }
}
Planet *Universe::getPlanet(int x, int y, int z)
{
    if (universe[x][y][z] == NULL)
    {
        return NULL;
    }
    return universe[x][y][z];
}
void Universe::setPlanet(Planet *planet)
{
    int x, y, z;
    srand(time(0));
    do
    {
        x = rand() % x_size;
        y = rand() % y_size;
        z = rand() % z_size;
    } while (universe[x][y][z] != NULL);
    if (universe[x][y][z] == NULL)
    {
        universe[x][y][z] = planet;
        planet->setCoords(x, y, z);
    }
}
int Universe::getX()
{
    return x_size;
}
int Universe::getY()
{
    return y_size;
}
int Universe::getZ()
{
    return z_size;
}
// PLANET METHOD FUNCTIONS
Planet::Planet()
{
    planetID = 0;
    x_coordinate = 0;
    y_coordinate = 0;
    z_coordinate = 0;
    owner = NULL;
    level = (rand() % 5) + 1;
    health = level * 50;
}
Planet::Planet(int id, int x, int y, int z, Player *owner_t)
{
    planetID = id;
    x_coordinate = x;
    y_coordinate = y;
    z_coordinate = z;
    owner = owner_t;
    level = (rand() % 5) + 1;
    health = level * 50;
}
int Planet::getX()
{
    return x_coordinate;
}
int Planet::getY()
{
    return y_coordinate;
}
int Planet::getZ()
{
    return z_coordinate;
}
void Planet::setCoords(int x, int y, int z)
{
    x_coordinate = x;
    y_coordinate = y;
    z_coordinate = z;
}
int Planet::getPlanetID()
{
    return planetID;
}
Player *Planet::getOwner()
{
    return owner;
}
int Planet::getHealth()
{
    return health;
}
int Planet::getLevel()
{
    return level;
}
void Planet::setPlanetID(int i)
{
    planetID = i;
}
void Planet::setOwner(Player *o)
{
    owner = o;
}
void Planet::setHealth(int h)
{
    health = h;
}
void Planet::setLevel(int l)
{
    level = l;
}
void Planet::recovery()
{
    health = level * 50;
}
int Planet::defend()
{
    return level * 30;
}
// STARSHIP METHOD FUNCTIONS
Starship::Starship()
{
    spaceid = 0;
    level = 0;
    health = level * 25;
    type = "";
}
Starship::Starship(int id, int ship_level, const string &ship_type)
{
    spaceid = id;
    level = ship_level;
    type = ship_type;
    if (ship_type == "Tank")
    {
        health = 75 * ship_level;
        attackValue = &Starship::tank;
    }
    else if (ship_type == "Damage")
    {
        health = 25 * ship_level;
        attackValue = &Starship::damage;
    }
}
int Starship::getSpaceID()
{
    return spaceid;
}
int Starship::getLevel()
{
    return level;
}
int Starship::getHealth()
{
    return health;
}
void Starship::setSpaceID(int s)
{
    spaceid = s;
}
void Starship::setLevel(int l)
{
    level = l;
}
void Starship::setHealth(int h)
{
    health = h;
}
int Starship::damage()
{
    return 75 * level;
}
int Starship::tank()
{
    return 25 * level;
}
void Starship::recover()
{
    if (type == "Tank")
    {
        health = 75 * level;
    }
    else if (type == "Damage")
    {
        health = 25 * level;
    }
}
// PLAYER METHOD FUNCTIONS
Player::Player()
{
    playerid = 0;
    size = 0;
    xp = 0;
    total_xp = 0;
    universe_p = NULL;
    owned_planets = NULL;
}
Player::Player(int id, Universe *uni)
{
    playerid = id;
    universe_p = uni;
    size = 0;
    xp = 0;
    total_xp = 0;
    owned_planets = NULL;
    starship[0] = Starship(0, 1, "Tank");
    starship[1] = Starship(1, 1, "Damage");
}
int Player::getPlayerID()
{
    return playerid;
}
int Player::getSize()
{
    return size;
}
int Player::getTotalXP()
{
    return total_xp;
}
int Player::getXP()
{
    return xp;
}
void Player::setPlayerID(int id)
{
    playerid = id;
}
void Player::setSize(int s)
{
    size = s;
}
void Player::setTotalXP(int txp)
{
    total_xp = txp;
}
void Player::setXP(int xp)
{
    this->xp = xp;
}
void Player::addPlanet(Planet *planet)
{
    if (owned_planets == NULL)
    {
        owned_planets = new OwnedPlanets[1];
        owned_planets[0] = planet;
        size = 1;
    }
    else
    {
        OwnedPlanets *temp = new OwnedPlanets[size + 1];
        for (int i = 0; i < size; i++)
        {
            temp[i] = this->owned_planets[i];
        }
        temp[size] = planet;
        delete[] owned_planets;
        size++;
        owned_planets = new OwnedPlanets[size];
        for (int i = 0; i < size; i++)
        {
            owned_planets[i] = temp[i];
        }
        planet->setOwner(this);
        delete[] temp;
    }
    xp += planet->getLevel();
    cout << "Planet successfully added to your loadout" << endl;
}
void Player::removePlanet(Planet *planet)
{
    for (int i = 0; i < size; i++)
    {
        if (owned_planets[i] == planet)
        {
            for (int j = i; j < size - 1; j++)
            {
                owned_planets[j] = owned_planets[j + 1];
            }
            size--;
            cout << "Planet successfully removed from opponent" << endl;
            OwnedPlanets *temp = new Planet *[size];
            for (int k = 0; k < size; k++)
            {
                temp[k] = owned_planets[k];
            }
            delete[] owned_planets;
            owned_planets = new Planet *[size];
            for (int k = 0; k < size; k++)
            {
                owned_planets[k] = temp[k];
            }
            temp = NULL;
            return;
        }
    }
}
void Player::upgradePlanet(int planetID)
{
    bool flag = false;
    for (int i = 0; i < size; i++)
    {
        if (owned_planets[i]->getPlanetID() == planetID)
        {
            flag = true;
            int upgrade_cost = (0.5 * xp);
            if (upgrade_cost <= total_xp && xp != 0)
            {
                owned_planets[i]->setLevel(owned_planets[i]->getLevel() + 1);
                total_xp -= upgrade_cost;
                owned_planets[i]->recovery();
                cout << "Your planet has been upgraded!" << endl;
                return;
            }
            else
            {
                cout << "You don't have enough XP to upgrade your planet." << endl;
            }
        }
    }
    if (flag == false)
    {
        cout << "No such Planet ID exists!" << endl;
        return;
    }
}
void Player::upgradeShip(int spaceid)
{
    bool flag = false;
    for (int i = 0; i < 2; i++)
    {
        if (spaceid == starship[i].getSpaceID())
        {
            flag = true;
            int upgrade_cost = 2 * xp;
            if (upgrade_cost > total_xp || xp == 0 || total_xp == 0)
            {
                cout << "You don't have enough XP to upgrade your starship." << endl;
                return;
            }
            else
            {
                total_xp -= upgrade_cost;
                starship[spaceid].setLevel(starship[spaceid].getLevel() + 1);
                cout << "Your starship (SpaceID " << spaceid << ") has been upgraded to level " << starship[spaceid].getLevel() << "." << endl;
            }
        }
    }
    if (flag == false)
    {
        cout << "No such Starship ID exists!" << endl;
        return;
    }
}
void Player::fight(Planet *planet)
{
    bool flag = true;
    int choice;
    int n;
    while (flag)
    {
        cout << "Which ship would you like to choose? (1) Tank (2) Damage" << endl;
        cin >> choice;
        if (choice == 1 || choice == 2)
        {
            flag = false;
        }
        else
        {
            cout << "Invalid choice. Choose either (1) Tank (2) Damage." << endl;
            flag = true;
        }
    }
    if (choice == 1)
    {
        n = 0;
    }
    else if (choice == 2)
    {
        n = 1;
    }
    int player_health = starship[n].getHealth();
    int planet_health = planet->getHealth();
    int damage = (starship[n].*starship[n].attackValue)();
    cout << "Initial Planet health: " << planet_health << endl;
    cout << "Initial Starship health: " << player_health << endl;
    while (player_health > 0 || planet_health > 0)
    {
        int player_attack = damage;
        planet_health = planet_health - player_attack;
        if(planet_health<=0)
        {
            planet_health=0;
        }
        cout << "Planet Health is " << planet_health << " after taking " << player_attack << " attack damage!" << endl;

        if (planet_health <= 0)
        {
            planet->getOwner()->removePlanet(planet);
            planet->setOwner(this);
            planet->recovery();
            this->addPlanet(planet);
            cout << "You have conquered the planet!" << endl;
            xp = 1 * planet->getLevel();
            total_xp += xp;
            return;
        }
        else if (planet_health >= 0)
        {
            int planet_defense = planet->defend();
            player_health = player_health - planet_defense;
            if(player_health<=0)
            {
                player_health=0;
            }
            cout << "Player Health is " << player_health << " after taking " << planet_defense << " defense damage!" << endl;
            if (player_health <= 0)
            {
                starship[n].recover();
                starship[n].setLevel(starship[n].getLevel() - 1);
                int x = 2 * planet->getLevel();
                planet->getOwner()->setXP(x);
                int current = planet->getOwner()->getTotalXP();
                planet->getOwner()->setTotalXP(current+x);
                cout << "Player " << planet->getOwner()->getPlayerID() << " defended their planet and received " << planet->getOwner()->getXP() << " XP!\n";
                total_xp -= 2;
                cout << "Starship Destroyed!" << endl;
                return;
            }
        }
    }
}
void Player::explore(int x, int y, int z)
{
    if (x < 0 || y < 0 || z < 0 || x >= universe_p->getX() || y >= universe_p->getY() || z >= universe_p->getZ())
    {
        cout << "Coordinates are out of bound. Turn lost!" << endl;
        return;
    }
    Planet *px = universe_p->getPlanet(x, y, z);
    if (universe_p->getPlanet(x, y, z) == NULL)
    {
        cout << "You explored an empty space. Your turn is over." << endl;
        return;
    }
    if (px->getOwner() == this)
    {
        cout << "You've already discovered this planet." << endl;
        return;
    }
    if (px->getOwner() != NULL && px->getOwner() != this)
    {
        cout << "This planet is owned by another player. Do you want to (1) attack or (2) skip turn?" << endl;
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            fight(px);
        }
        return;
    }
    if (px->getX() == x && px->getY() == y && px->getZ() == z)
    {
        cout << "You've discovered an unclaimed planet. Do you want to (1) conquer it or (2) skip turn?" << endl;
        int choice;
        cin >> choice;

        if (choice == 1)
        {
            px->setOwner(this);
            addPlanet(px);
            int planet_level = px->getLevel();

            xp = planet_level;
            total_xp += xp;
            cout << "You've conquered the planet and gained " << xp << " experience!" << endl;

            cout << "Do you want to (1) upgrade planets or (2) upgrade the starship? (3) view loadout (4) skip turn" << endl;
            cin >> choice;
            if (choice == 1)
            {
                int upgrade_cost = 0.5 * xp;
                if (upgrade_cost <= total_xp)
                {
                    upgradePlanet(px->getPlanetID());
                }
                else
                {
                    cout << "You don't have enough XP to upgrade planets." << endl;
                }
            }
            else if (choice == 2)
            {
                int upgrade_cost = 2 * xp;
                if (upgrade_cost <= total_xp)
                {
                    int spaceID;
                    cout << "Enter the Space ID of the starship to upgrade: ";
                    cin >> spaceID;
                    upgradeShip(spaceID);
                }
                else
                {
                    cout << "You don't have enough XP to upgrade your starship." << endl;
                }
            }
            else if (choice == 3)
            {
                starshipLoadout();
                planetLoadout();
                return;
            }
            else if (choice == 4)
            {
                cout << "Turn skipped!" << endl;
                return;
            }
        }
    }
    else
    {
        cout << "You explored an empty space. Your turn is over." << endl;
        return;
    }
}
void Player::starshipLoadout()
{
    cout << "============================" << endl;
    cout << "Your Starships" << endl;
    cout << "============================" << endl;
    for (int i = 0; i < 2; i++)
    {
        cout << "Starship " << starship[i].getSpaceID() << ": Health-" << starship[i].getHealth() << ": Level-" << starship[i].getLevel() << endl;
    }
    cout << endl;
}
void Player::planetLoadout()
{
    cout << "============================" << endl;
    cout << "Your Planets" << endl;
    cout << "============================" << endl;
    if (this->getSize() == 0)
    {
        cout << "You have no planets" << endl;
        cout << endl;
    }
    else
    {
        for (int i = 0; i < this->getSize(); i++)
        {
            cout << "Planet " << owned_planets[i]->getPlanetID() << ": Health-" << owned_planets[i]->getHealth() << ": Level-" << owned_planets[i]->getLevel() << endl;
            cout << "Planet " << owned_planets[i]->getPlanetID() << " Coordinates: "
                 << "X(" << owned_planets[i]->getX() << ") Y(" << owned_planets[i]->getY() << ") Z(" << owned_planets[i]->getZ() << ")" << endl;
            cout << endl;
        }
        cout << endl;
    }
}
// INT MAIN
int main()
{
    int universe_sX = 3;
    int universe_sY = 3;
    int universe_sZ = 3;
    int num_players = 2;
    Universe universe_m(universe_sX, universe_sY, universe_sZ);

    // Planet Initializations
    Planet planetx[15];
    for (int i = 0; i < 15; i++)
    {
        planetx[i] = Planet();
        planetx[i].setPlanetID(i);
    }

    for (int i = 0; i < 15; i++)
    {
        universe_m.setPlanet(&planetx[i]);
    }

    // Player Initializations
    Player players[num_players];
    players[0] = Player(1, &universe_m);
    players[1] = Player(2, &universe_m);
    int current_player = 0;

    // Main Game Loop
    int moves = 0;
    cout << "!SATAAR WARS!" << endl;
    cout << "Instructions: You are playing in a 3x3x3 universe with 2 players. The game will last for 50 moves before deciding "<<endl;;
    cout << "the winner based on total xp. Turns are used up while exploring!" << endl;
    while (moves < 50)
    {
        cout << "============================" << endl;
        cout << "Game State : Move " << moves + 1 << endl;
        cout << "Turn: Player " << players[current_player].getPlayerID() << endl;
        cout << "Player XP: " << players[current_player].getTotalXP() << endl;
        cout << "============Menu============" << endl;
        cout << "1. Explore" << endl;
        cout << "2. Upgrade Planet" << endl;
        cout << "3. Upgrade Starship" << endl;
        cout << "4. Print current loadout" << endl;
        cout << "============================" << endl;

        bool check = true;
        int choice;
        cout << "Enter your choice: ";
        while (check)
        {
            cin >> choice;
            if (choice == 1 || choice == 2 || choice == 3 || choice == 4)
            {
                check = false;
            }
            else
            {
                cout << "Invalid Input! Try again." << endl;
            }
        }
        switch (choice)
        {
        case 1:
            int x, y, z;
            cout << "Enter coordinates to explore (x y z): ";
            cin >> x >> y >> z;
            players[current_player].explore(x, y, z);
            break;
        case 2:
            int planetID;
            cout << "Enter the Planet ID to upgrade: ";
            cin >> planetID;
            players[current_player].upgradePlanet(planetID);
            break;
        case 3:
            int spaceID;
            cout << "Enter the Space ID of the starship to upgrade: ";
            cin >> spaceID;
            players[current_player].upgradeShip(spaceID);
            break;
        case 4:
            players[current_player].planetLoadout();
            players[current_player].starshipLoadout();
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
            break;
        }
        if(!(choice == 2 || choice == 3 || choice == 4))
        {
            current_player = (current_player + 1) % num_players;
            moves++;
        }
        
    }
    if (players[0].getTotalXP() > players[1].getTotalXP())
    {
        cout << "Player 1 won the game with more experience!" << endl;
    }
    else if (players[0].getTotalXP() < players[1].getTotalXP())
    {
        cout << "Player 2 won the game with more experience!" << endl;
    }
    else if (players[0].getTotalXP() == players[1].getTotalXP())
    {
        cout << "It is a draw!" << endl;
    }
    return 0;
}