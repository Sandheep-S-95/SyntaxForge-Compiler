// Completes rules and updates dependent states in the Earley Parser
void complete(std::vector<std::vector<State>> &chart, size_t i)
{
    // Track chart[i]’s size to know when new states are added
    size_t lastSize = 0;
    
    // Keep looping as long as new states are added to chart[i]
    while (lastSize != chart[i].size()) {
        // Update lastSize to current number of states
        lastSize = chart[i].size();
        
        // Loop through each state in chart[i] (list of parse possibilities at position i)
        for (size_t j = 0; j < chart[i].size(); j++) {
            // Get the current state (e.g., T -> a •, 0)
            auto state = chart[i][j];
            
            // Check if rule is done (dot at end, e.g., T -> a • means T is complete)
            if (state.dot == state.prod.rhs.size()) {
                // Look at states where this rule started (chart[state.start])
                // These might expect this rule’s LHS (e.g., E -> • T expects T)
                for (auto &prev : chart[state.start]) {
                    // Check if prev needs this rule’s LHS (e.g., T) and isn’t done
                    if (prev.dot < prev.prod.rhs.size() && prev.prod.rhs[prev.dot] == state.prod.lhs) {
                        // Advance prev’s dot (e.g., E -> • T becomes E -> T •)
                        State newState(prev.prod, prev.dot + 1, prev.start);
                        
                        // Add new state to chart[i] if not already there
                        if (std::find(chart[i].begin(), chart[i].end(), newState) == chart[i].end())
                            chart[i].push_back(newState);
                    }
                }
            }
        }
    }
}