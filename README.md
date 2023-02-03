## Welcome to the Risk Game project for Advanced Program Design with C++ at Concordia University! 😎

In this project, we will be building a simple version of the "Risk" computer game, based on the Warzone version of the game. The game is played on a connected graph map representing a world map, where each node is a territory and each edge represents adjacency between territories. Two or more players can play by placing armies on territories they own, from which they can attack adjacent territories to conquer them. The objective of the game is to conquer all territories on the map.

### Map 📜
The game map is divided into subgraphs that represent continents. Each continent is given a control value (a "bonus" in Warzone terminology) that determines the number of armies per turn that is given to a player that controls all of it. During game play, every territory belongs to one and only one player and contains zero or more armies that belong to the player owning the territory. In our implementation, the game can be played on any connected graph that is defined by the user before play, saved as a text file representation, and loaded by the game during play.

### Game 🎲
The game consists of 5 different phases, in which specific actions are happening. In each phase, there are possible transitions to other phases, which are all triggered by specific conditions. The bulk of the action in the game are happening in the main game phase, which consists of the reinforcement phase, the orders issuing phase, and the orders execution phase, that execute in a closed cycle until the entire map is controlled by a single player, at which point the game ends. Every iteration of the main game phase is called a turn. In every turn, a round-robin mode of execution is used to go through every player in each of the sub-phases of the main game phase.

### Startup Phase 👌
The game starts by the startup phase, where the number of players is determined, then all the territories are randomly and somehow evenly assigned to the players. Once the startup phase is done, the game goes to the main play phase that consists of the reinforcement phase, the orders issuing phase, and the orders execution phase.

### Reinforcement Phase 😈
At the beginning of every turn, every player is given a number of armies that are placed in their reinforcement pool. The number of armies given depends on the number of territories they own (# of territories owned divided by 3, rounded down). If the player owns all the territories of an entire continent, the player is given a number of armies corresponding to the continent's control bonus value. In any case, the minimal number of reinforcement armies for any player is 3. Once the reinforcement phase is done.

### Orders Issuing Phase ✅
Each player, in round-robin turn order, gives one of their orders, or signify that they don't have any more orders to issue this turn. Once all the players have signified that they don't have any more orders for this turn, the game switches to the orders execution phase (see below). Note that the orders only have an effect on the game when they are executed. Issuing an order is simply to signify the intention to execute an order.

The possible orders are:

Deploy: dispatch armies from a player's reinforcement pool to their own territories.  
Attack: an attacking territory (owned by the player issuing the order) attacks an adjacent defending territory (owned by another player).  
Defend: armies from a source territory (owned by the player issuing the order) are transferred to an adjacent destination territory (also owned by the player).  
Play a card: bomb another player's territory (halve the armies on target territory), blockade one of their own territories (double the armies in target territory and make it neutral), negotiate a truce for 1 turn with another player, get 5 armies added to the player's reinforcement pool, airlift armies between 2 territories (can be non-adjacent) owned by the player playing the card.  

Orders Execution Phase  
All the orders are executed in the order they were issued, using a first-in, first-out execution order  

For more information, please visit:
https://users.encs.concordia.ca/~paquet/wiki/images/0/02/Project.COMP345.2022.2.pdf


This project was implemented in 3 distinct assigments as described bellow:
https://users.encs.concordia.ca/~paquet/wiki/images/4/45/Assignment1.COMP345.2022.2.pdf
https://users.encs.concordia.ca/~paquet/wiki/images/8/82/Assignment2.COMP345.2022.2.pdf
https://users.encs.concordia.ca/~paquet/wiki/images/8/8e/Assignment3.COMP345.2022.2.pdf

Thank you and happy coding!
