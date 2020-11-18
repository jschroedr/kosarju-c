# kosarju-c
Implementation of Kosaraju's algorithm for computing strong connected components (SCCs) in linear time using the "two-pass" method

## test cases
Please note, test cases were sourced from the following community-based repository:
https://github.com/beaunus/stanford-algs

## checking for memory leaks with valgrind
(a note for ci builds)
```
valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all {file}
```
i.e. 
```
valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./dist/Debug/GNU-Linux/kosarju-c
```

