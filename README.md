# battleship
Socket based battleship

How To Launch:
===============================================================================
  Makefile:
  -----------------------------------------------------------
    <make client>
    <make server>
    <make clean>

  Launch Server:
  -----------------------------------------------------------
  ./bs_server

  Launch Client (two instances):
  -----------------------------------------------------------
  ./bs_client <IP_ADDRESS> <PORT_NUMBER>

    ARGV:
    ---------------------------------------------------------
    IP_ADDRESS  : Host Ip address or local loop back (127.0.0.1)
    PORT_NUMBER : 4700

Rules:
===============================================================================
- Place Ship
- Fire
- Sink enemy ship < 3 units >
- Win ( or lose if you're bad ;) )

!!! NOTE !!!
-------------------------------------------------------------
  The game is turn based. This means your actions are limited
  to the opposing player. (ie if you place your ship you will
    not be able to fire until the opposing user places their
    ship. This applies to firing your shots.)

How is player 1 and player 2 determined?
-------------------------------------------------------------
  Player 1 => first user connect to server  
  player 2 => second user to connect to server  

Key Bindings:
===============================================================================
1) Placing initial Ship Steps:
--------------------------------------------------------------

|===> *ref* -> Move Around
|     KEY_LEFT  : move left
|l    KEY_RIGHT : move right
|o    KEY_UP    : move up
|o    KEY_DOWN  : move down
|p
|    SPACE (1st press) : place initial position then use the
|b                        left and right arrow keys to rotate
|a                        ship.
|c    ----------------------------------------------------------
|k    KEY_LEFT  : rotate ship <counter clock wise>
|     KEY_RIGHT : rotate ship <clock wise>
|
|____ ESC_KEY   : step back to placing initial position
                (reverts back to step *ref* -> Move Around)
                note after user presses ESC_KEY he or she
                can then use the four arrow keys to move
                around to place initial piece again.

    SPACE(2nd press) : confirm ship placement after ship has
                        been rotated to desired possition

2) Firing On Enemy Steps:
--------------------------------------------------------------
    KEY_LEFT  : move left  
    KEY_RIGHT : move right  
    KEY_UP    : move up  
    KEY_DOWN  : move down  

    SPACE_BAR : Fire  

3) Endgame:
--------------------------------------------------------------
    KEY_Q : exit game (q key on keyboard)
