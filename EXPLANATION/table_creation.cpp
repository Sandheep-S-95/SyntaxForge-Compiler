// Implements the Earley parsing algorithm to validate input and build a chart
std::vector<std::vector<State>> parse(const std::vector<Token> &tokens)
{
    // Create a chart with one entry per token plus one for the start (EOF)
    std::vector<std::vector<State>> chart(tokens.size() + 1);
    
    // Initialize chart[0] with the start rule: Program -> StatementList
    // State format: {Production, dot_position, start_position}
    chart[0].push_back({{"Program", {"StatementList"}}, 0, 0}); // Start state

    // Loop through each chart position (0 to tokens.size())
    for (size_t i = 0; i <= tokens.size(); i++) {
        // Track chart size to detect when no new states are added
        size_t lastSize = 0;
        
        // Keep processing until no new states are added to chart[i]
        while (lastSize != chart[i].size()) {
            // Update lastSize to current chart size
            lastSize = chart[i].size();
            
            // Iterate over all states in chart[i]
            for (size_t j = 0; j < chart[i].size(); j++) {
                // Get the current state (e.g., Program -> • StatementList)
                auto s = chart[i][j];
                
                // Check if the state expects more symbols (dot not at end)
                if (s.dot < s.prod.rhs.size()) {
                    // Get the next expected symbol (e.g., StatementList)
                    std::string next = s.prod.rhs[s.dot];
                    
                    // If next is a non-terminal (e.g., StatementList), predict rules
                    if (isNonTerminal(next))
                        predict(chart[i], i, next); // Predict phase
                    
                    // If next is a terminal and we have tokens, scan the token
                    else if (i < tokens.size())
                        scan(chart, i, tokens[i]); // Scan phase
                }
                // If dot is at the end, the rule is complete
                else
                    complete(chart, i); // Complete phase
            }
        }
    }

    // Define the accept state: Program -> StatementList • (fully parsed)
    State accept({{"Program", {"StatementList"}}, 1, 0});
    
    // Check if accept state is in the final chart position
    if (std::find(chart[tokens.size()].begin(), chart[tokens.size()].end(), accept) == chart[tokens.size()].end()) {
        // If not found, find the furthest chart position with states
        size_t max_i = 0;
        for (size_t i = 0; i <= tokens.size(); ++i)
            if (!chart[i].empty())
                max_i = i;
        
        // Get the problematic token (or EOF if at end)
        std::string error_token = (max_i < tokens.size()) ? tokens[max_i].value : "EOF";
        
        // Get the token’s type (e.g., KEYWORD, IDENTIFIER)
        std::string error_type = (max_i < tokens.size()) ? tokenTypeToString(tokens[max_i].type) : "EOF_TOKEN";
        
        // Throw an error with details about where parsing failed
        throw std::runtime_error("Syntax error at token " + std::to_string(max_i) +
                                 ", near '" + error_token + "' (type: " + error_type + ")");
    }
    
    // Return the completed chart for AST construction
    return chart;
}