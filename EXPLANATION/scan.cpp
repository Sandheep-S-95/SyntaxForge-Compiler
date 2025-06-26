// Matches the current token against expected terminals
void scan(std::vector<std::vector<State>> &chart, size_t i, const Token &token)
{
    // Iterate through all states in chart[i]
    for (const auto &state : chart[i]) {
        // Check if the state expects another symbol
        if (state.dot < state.prod.rhs.size()) {
            // Get the next expected symbol (e.g., "int", ";")
            std::string next = state.prod.rhs[state.dot];
            
            // Convert token type to string (e.g., KEYWORD, IDENTIFIER)
            std::string tokenTypeStr = tokenTypeToString(token.type);
            
            // Check if next matches the token’s type or value
            if (next == tokenTypeStr || next == token.value) {
                // Create a new state, advancing the dot
                State newState(state.prod, state.dot + 1, state.start);
                
                // Add the new state to chart[i+1] if not already present
                if (std::find(chart[i + 1].begin(), chart[i + 1].end(), newState) == chart[i + 1].end())
                    chart[i + 1].push_back(newState);
            }
        }
    }
}