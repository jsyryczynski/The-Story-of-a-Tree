WARNING:
The code provided by hackerrank to parse inputs is incorrect. The data provided in test cases is correct though, so you can write your own parser.
Or just fix the bug by replacing the lines in provided code with:


        int g = stoi(first_multiple_input[0]);
        int k = stoi(first_multiple_input[1]);
        vector<vector<int>> guesses(g);

        for (int i = 0; i < g; i++) {
            guesses[i].resize(2);
            
          
The solution to this problem is combined from the following steps:
1. Craete adjacency list from provided edges
2. DFS traversal from arbitrary chosen node (here first node). During this traversal mark parents of all visited nodes
3. Go through the list of guesses and compare it with parents lists from previous point. Mark points in partial mark list.
3a. If the guess is correct, that means that it will be correct for all possible roots higher up in the tree. And incorrect for all possible roots starting from current child. This will be marked in partial mark list by increasing value stored for first node. And decreasing value stored for current child.
3b. If the guess is incorrect that means that it will become correct for all roots that start in tree below (including) current child (that was incorrectly guessed to be a parent). Mark this by increasing count for child.
4. DFS traversal where count of each node is sum of count of parent and the current node.
5. Compare value stored for each node with number of guesses required for win.
6. Reduce resulting fraction
