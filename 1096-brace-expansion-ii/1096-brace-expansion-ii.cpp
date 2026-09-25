#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<string> braceExpansionII(string expression) {
        int i = 0;
        set<string> resultSet = parse(expression, i);
        return vector<string>(resultSet.begin(), resultSet.end());
    }

private:
    set<string> parse(const string& expr, int& i) {
        // Keeps track of the total union set at the current nesting level
        set<string> totalUnion;
        
        // Keeps track of sets being concatenated at the current level
        // e.g., A{b,c}D -> Cartesian product of A, {b,c}, D
        vector<set<string>> currentConcat = { {""} };

        while (i < expr.length() && expr[i] != '}') {
            if (expr[i] == '{') {
                i++; // Skip '{'
                set<string> subResult = parse(expr, i);
                i++; // Skip '}'
                
                // Concatenate subResult with the last set in currentConcat
                currentConcat.back() = multiply(currentConcat.back(), subResult);
            } 
            else if (expr[i] == ',') {
                // Comma ends current concatenation term; fold it into totalUnion
                set<string> term = combineConcat(currentConcat);
                totalUnion.insert(term.begin(), term.end());
                
                // Reset currentConcat for the next term after the comma
                currentConcat = { {""} };
                i++; // Skip ','
            } 
            else {
                // Single letter x
                set<string> letterSet = { string(1, expr[i]) };
                currentConcat.back() = multiply(currentConcat.back(), letterSet);
                i++;
            }
        }

        // Fold remaining concatenation term into totalUnion
        set<string> term = combineConcat(currentConcat);
        totalUnion.insert(term.begin(), term.end());

        return totalUnion;
    }

    // Helper to compute Cartesian product of two sets of strings
    set<string> multiply(const set<string>& A, const set<string>& B) {
        set<string> result;
        for (const string& a : A) {
            for (const string& b : B) {
                result.insert(a + b);
            }
        }
        return result;
    }

    // Helper to combine all sets in currentConcat into one via Cartesian product
    set<string> combineConcat(const vector<set<string>>& concatList) {
        set<string> result = { "" };
        for (const auto& s : concatList) {
            result = multiply(result, s);
        }
        return result;
    }
};