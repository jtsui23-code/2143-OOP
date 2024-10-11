# Class Design For Knucklebones

## Dice Class
  - Data: Sides, Current Value
    
  - Actions: roll(), getValue()
    
  - Relationships: Will be used by the Player.

## Player Class
  - Data: Name, Score, diceSet, playerStats
    
  - Actions: rollDice(), getScore()
    
  - Relationships: Each player will get a dice and participate in the game. Use Composition for Dice Class.

## Game Class
  - Data: Players, Rules, currentRound
    
  - -Actions: startGame(), endGame(), updateScore()
    
  - Relationships: Controls Players and their actions. Uses composiiton for Players.

## Knucklebones
  - Data: board(), knuckleboneSpecificRules()
    
  - Actions: getWinner(), getLoser(), startRound(), endRound(), calculateLeaderboard(), drawBoard(), animateDice(), countStreak(), getStreak(), getLeaderboard()
    
  - Relationships: Inherits from Game Class.
