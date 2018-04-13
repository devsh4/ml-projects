**PART 2**

**************************************************
To run the model :- Use command -> ./TopMain -u 'number of rounds'  (e.g. can be 1 - 99)

To test manually :- Go to 'Play' State and uncomment the code in the 'Initial' transition
**************************************************

Steps while developing the model iteratively-

	STEP 1 -
	- Created dealer, player (provides service) and top capsule.
	- Created a play protocol [messages - deal(), ack()] 
	- Built a simple model where dealer deals cards to 2 players and stops game.
	- Tested the flow
	
	STEP 2 - 
 	- Implemented a random number generator 'operation' in dealer capsule to generate random cards for dealing
 	- Added tick protocol for self communication
 	- Added logic of interpreting cards and their suit. 
 	- Tested the flow
 	
	 STEP 3 - 
 	- Added "used" cards logic to make sure cards do not repeat
 	- Added composite state to enact a for loop to generate deck
 	- Added another player capsule (p=5)
 		
	 STEP 4 -
  	- Added open flop logic
  	- Fixed bugs wrt used cards check    
    
  	STEP 5 -
  	- Added a mechanism to store player cards in 1d arrays
  	- Completed flop logic
  	- Added a new comp state for playing (i.e. for checking hands of each player)
  	
  	STEP 6 -
  	- Changed entire logic checking etc back to int as it is better for comparison [only for display it would be char]
  	- Made the logic for all hands up till straight
  	- Sorted out the logic of DecideWinner State, to determine which player won the round
  	- Added code to handle two digit input
  	
  	STEP 7 - 
    - Tested and fixed entire dealing cards logic to avoid duplicates, finally!  
  	- Hands checking for all kinds of possible hands (i.e. up to royal flush)
  	- Created functions for straight, sorting, finding a specific card in hand, higher straight etc. for re-usability
  	- Handled Two digit cmd args!
  	
  	STEP 8 - 
  	- Added a manual input function to test for certain rare hands
  	- Converted 'iftie?', 'hand rank', 'tie evaluation' logic -> model driven
  	- Added code to display every player's best hand i.e. 5/7 (and sorted according to ascending order)
  	- Made 'number of players' dynamic for the entire model (replaced ALL statci references)
  	
  	STEP 8 -
  	- Handle Ties?
  		- High Card case done
  		- Pair case done
  		- Double Pair done
  		- Trips done
  		- Straight done
  		- Flush done
  		- Full house done
  		- Four of a kind done
  		- Straight flush - done
  	(What about kicker cases in pair, double pair, trips? - DONE)
  		
  	STEP 9 -
  	- Re-factored to make it more model driven and cleaned code at places
  	- Added more operations to reduce code duplication.

 
      