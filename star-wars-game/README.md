# Sataar Wars

## Introduction
Welcome to Sataar Wars, a 3D space turn-based game where players conquer planets and fight for dominance. The goal is to gain experience and levels by exploring and battling for planets. The player with the most levels at the end wins.

## Objective
I've created a turn-based game where each player inputs coordinates to explore. Depending on the coordinates, players can either skip their turn, discover a new planet, or attack an opponent's planet.

## How to Play

### Setup
The game takes place in a 3x3x3 universe with two players. Each player controls starships and can discover or conquer planets.

### Turns
Players take turns to input coordinates to explore. Each turn, they have different options: 

- **Explore:** Input the coordinates (x, y, z) to explore.
- **Upgrade Planet:** Upgrade a planet by its ID.
- **Upgrade Starship:** Upgrade a starship by its space ID.
- **View Loadout:** Check the current status of starships and planets.

### Gameplay
When a player explores a coordinate, they may discover an empty space, an unclaimed planet, or an opponent's planet.

- If an unclaimed planet is discovered, the player can choose to conquer it.
- If an opponent's planet is discovered, the player can choose to attack or skip the turn.
- Battles occur between the player's starship and the planet's defenses until one loses all health.
- Players earn experience points (XP) by exploring, conquering, and defending planets.

The game lasts for 50 moves. The player with the highest total XP at the end of the game wins.

## Code Explanation

### Universe Class
Represents the 3D space where the game takes place.

#### Attributes:
- `Universe`: 3D array of Planet objects.
- `x_size`, `y_size`, `z_size`: Dimensions of the array.

#### Methods:
- `constructors`: Initialize the universe.
- `getPlanet()`: Returns the planet at given coordinates or `NULL` if empty.
- `setPlanet()`: Places a planet in a random, unoccupied space.

### Planet Class
Represents a planet that can be discovered or conquered.

#### Attributes:
- `planetID`: Unique identifier.
- `x_coordinate`, `y_coordinate`, `z_coordinate`
- `owner`: Pointer to the owning player.
- `health`, `level`: Health and level of the planet.

#### Methods:
- `constructors`: Initialize planets.
- `recovery()`: Restores health after a battle.
- `defend()`: Returns the planet's attack value.

### Starship Class
Represents a starship used by players to explore and attack.

#### Attributes:
- `spaceid`: Unique identifier.
- `level`, `health`, `type`: Attributes defining the starship.
- `attackValue`: Function pointer to determine attack value.

#### Methods:
- `constructors and setters/getters`
- `damage()`, `tank()`: Determine attack values based on type.
- `recover()`: Resets health based on level.

### Player Class
Represents a player in the game.

#### Attributes:
- `playerid`: Unique identifier.
- `owned_planets`: List of owned planets.
- `universe`: Pointer to the main universe.
- `starship`: List of starships.
- `xp`, `total_xp`: Experience points.

#### Methods:
- `constructors and setters/getters`
- `addPlanet()`, `removePlanet()`: Manage owned planets.
- `upgradePlanet()`, `upgradeShip()`: Upgrade planets and starships.
- `fight()`: Battle for a planet.
- `explore()`: Explore a coordinate in the 3D space.
