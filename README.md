# Springer_Tour
Python script to fill a chessboard with a Knight's tour

## Info
- Uses Interactive Python (hence the '#%%')
- Bruteforce search for one possible solution
- extremely inefficient (will crash very likely)

## Problems
- returns just the first solution it finds
- returns nothing if there is no solution (easy fix would be to wrap another function around fill_board())

## to do
- implement better algorithms 
  - https://en.wikipedia.org/wiki/Knight%27s_tour#Finding_tours_with_computers
  - (two sided search) https://www.youtube.com/watch?v=wL3uWO-KLUE
  - ...