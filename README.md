# Crocotta

Game in which there is a Hunter (controlled by user) that is trying to kill the Crocotta monster with an arrow. It is on a 5x5 grid that has 3 randomly placed pits. The hunter can move North, South, East, or West, or fire an arrow in one of those directions (be careful, the hunter only has 2 arrows, and if you miss the Crocotta randomly runs somewhere else).

For BasicMain, it is just the game as would be played by the user.

For ProbMap, this is still played by the user, but it displays a rating on the chance of a pit or the monster being in each of the 25 possible locations on the map.

AIMain is a game that is completely played by an "AI" except for choosing a direction for moving, it gives a recommendation on where to move, but in the end this is up to User. This is because there are still some bugs involving infinite loops that the AI can get stuck into. The general strategy of AI is at every turn check if the Monster is guranteed to be next to it at a certain location, if it is then fire in that direction. If not, then it tries to get to the bottom left of the map (0,0) and from there sweep across map searching for Crocatta. The AI uses same probability map as in ProbMap to make decisions.
