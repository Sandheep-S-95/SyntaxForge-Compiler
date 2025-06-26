// Predicts possible grammar rules for a non-terminal
void predict(std::vector<State> &chart, size_t i, const std::string &nonTerminal)
{
    // Iterate through all grammar productions
    for (const auto &prod : grammar) {
        // Check if the production’s left-hand side matches the non-terminal
        if (prod.lhs == nonTerminal) {
            // Create a new state for the production, starting at position i
            State newState(prod, 0, i);
            
            // Add the state to chart[i] if it’s not already there
            if (std::find(chart.begin(), chart.end(), newState) == chart.end())
                chart.push_back(newState);
        }
    }
}