class Solution {
public:
    // Memoization table to store results of subproblems
    // Key: string (represented by curr + idx + above), Value: bool (is it possible?)
    unordered_map<string, bool> dp;

    bool solve(string curr, unordered_map<string, vector<char>>& mp, int idx, string above) {
        // Base Case: We reached the top of the pyramid (only 1 block remains)
        if (curr.length() == 1) return true;

        // --- EXPLANATION OF YOUR KEY LOGIC ---
        // We create a unique key because the result depends on 3 changing states:
        // 1. 'curr': The current row we are building ON TOP OF.
        // 2. 'idx': The position we are currently looking at in 'curr'.
        // 3. 'above': The partial row we have built so far for the next level.
        // If we encounter this exact combination again, we return the stored result to save time.
        string key = curr + "_" + to_string(idx) + "_" + above;
        
        if (dp.count(key)) return dp[key];

        // Transition Case: The 'above' row is fully built.
        // We now move up a level. 'above' becomes the new 'curr', and we restart 'idx' at 0.
        if (idx == curr.length() - 1) {
            return dp[key] = solve(above, mp, 0, ""); 
        }

        // Identify the base pair (left and right blocks) from the current row
        string pair = curr.substr(idx, 2);

        // If this pair has no allowed parent blocks in our map, this path is dead.
        if (mp.find(pair) == mp.end()) return dp[key] = false;

        // Try every possible allowed character for the block above this pair
        for (auto& ch : mp[pair]) {
            above.push_back(ch); // Place the block
            
            // Recursive Step: Try to build the NEXT block in the 'above' row (idx + 1)
            if (solve(curr, mp, idx + 1, above)) return true;
            
            above.pop_back(); // Backtrack: Remove the block and try the next option
        }
        
        // If no options work for this state, mark it as false
        return dp[key] = false;
    }

    bool pyramidTransition(string bottom, vector<string>& allowed) {
        unordered_map<string, vector<char>> mp;
        
        // Preprocess 'allowed' into a map for O(1) lookups
        // Example: "ABC" -> Key: "AB", Value: ['C']
        for (auto& pattern : allowed) {
            mp[pattern.substr(0, 2)].push_back(pattern[2]);
        }
        
        return solve(bottom, mp, 0, "");
    }
};
