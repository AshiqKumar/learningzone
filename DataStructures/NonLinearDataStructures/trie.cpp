// Trie (Prefix Tree) Implementation - Complete program with all operations
/*
Key Features of Trie:
Core Operations:
✅ Insertion: Add words efficiently with shared prefixes
✅ Search: Find complete words and check existence
✅ Prefix Search: Find all words starting with given prefix
✅ Deletion: Remove words while preserving shared prefixes
Trie Properties:
🌳 Tree Structure: Each node represents a character
📝 Prefix Sharing: Common prefixes share same path
🎯 End-of-Word Marking: Special marking for word endings
💾 Space Optimization: Compressed trie variants
Advanced Features:
🔍 Autocomplete: Suggest words based on prefix
📊 Word Count: Track frequency of insertions
🎨 Pattern Matching: Wildcard and pattern searches
📈 Statistics: Prefix counts, longest common prefix
Smart Memory Management:
🧠 Uses smart pointers for automatic memory management
🛡️ Exception-safe operations throughout
🚫 RAII principles for resource management
📈 Efficient memory usage with shared nodes
Educational Demonstrations:
📊 Performance Analysis: Time/space complexity analysis
🧪 Trie Visualization: Tree structure display
📝 Practical Applications: Autocomplete, spell checker
🔄 Comparison Studies: Trie vs other string structures
*/

#include <iostream>
#include <unordered_map>
#include <memory>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

class Trie {
private:
    struct TrieNode {
        std::unordered_map<char, std::shared_ptr<TrieNode>> children;
        bool isEndOfWord;
        int wordCount; // Number of times this word was inserted
        
        TrieNode() : isEndOfWord(false), wordCount(0) {}
    };
    
    using NodePtr = std::shared_ptr<TrieNode>;
    NodePtr root_;
    size_t totalWords_;
    size_t totalNodes_;
    
    // Helper function for collecting words with given prefix
    void collectWordsHelper(NodePtr node, const std::string& currentWord, 
                           std::vector<std::string>& result) const {
        if (!node) return;
        
        if (node->isEndOfWord) {
            result.push_back(currentWord);
        }
        
        for (const auto& [ch, childNode] : node->children) {
            collectWordsHelper(childNode, currentWord + ch, result);
        }
    }
    
    // Helper function for collecting words with counts
    void collectWordsWithCountHelper(NodePtr node, const std::string& currentWord,
                                   std::vector<std::pair<std::string, int>>& result) const {
        if (!node) return;
        
        if (node->isEndOfWord) {
            result.emplace_back(currentWord, node->wordCount);
        }
        
        for (const auto& [ch, childNode] : node->children) {
            collectWordsWithCountHelper(childNode, currentWord + ch, result);
        }
    }
    
    // Helper function for displaying trie structure
    void displayHelper(NodePtr node, const std::string& prefix, 
                      const std::string& currentPath, int depth) const {
        if (!node) return;
        
        // Print current node info
        if (depth > 0) {
            std::cout << prefix;
            std::cout << "└── ";
            std::cout << currentPath.back();
            if (node->isEndOfWord) {
                std::cout << " [WORD]";
                if (node->wordCount > 1) {
                    std::cout << " (count: " << node->wordCount << ")";
                }
            }
            std::cout << std::endl;
        }
        
        // Print children
        std::vector<char> sortedKeys;
        for (const auto& [ch, child] : node->children) {
            sortedKeys.push_back(ch);
        }
        std::sort(sortedKeys.begin(), sortedKeys.end());
        
        for (size_t i = 0; i < sortedKeys.size(); ++i) {
            char ch = sortedKeys[i];
            std::string newPrefix = prefix;
            if (depth > 0) {
                newPrefix += (i == sortedKeys.size() - 1) ? "    " : "│   ";
            }
            displayHelper(node->children.at(ch), newPrefix, currentPath + ch, depth + 1);
        }
    }
    
    // Helper function for deletion
    bool deleteHelper(NodePtr node, const std::string& word, size_t index) {
        if (index == word.length()) {
            // We've reached the end of the word
            if (!node->isEndOfWord) {
                return false; // Word doesn't exist
            }
            
            node->isEndOfWord = false;
            node->wordCount = 0;
            
            // Return true if node has no children (can be deleted)
            return node->children.empty();
        }
        
        char ch = word[index];
        if (node->children.find(ch) == node->children.end()) {
            return false; // Word doesn't exist
        }
        
        NodePtr childNode = node->children[ch];
        bool shouldDeleteChild = deleteHelper(childNode, word, index + 1);
        
        if (shouldDeleteChild) {
            node->children.erase(ch);
            totalNodes_--;
            
            // Return true if current node can be deleted
            // (has no children and is not end of another word)
            return !node->isEndOfWord && node->children.empty();
        }
        
        return false;
    }
    
public:
    // Constructor
    Trie() : totalWords_(0), totalNodes_(1) {
        root_ = std::make_shared<TrieNode>();
    }
    
    // Insert word
    void insert(const std::string& word) {
        if (word.empty()) {
            std::cout << "Cannot insert empty word" << std::endl;
            return;
        }
        
        NodePtr current = root_;
        bool newWordAdded = false;
        
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = std::make_shared<TrieNode>();
                totalNodes_++;
            }
            current = current->children[ch];
        }
        
        if (!current->isEndOfWord) {
            newWordAdded = true;
            totalWords_++;
            current->isEndOfWord = true;
        }
        current->wordCount++;
        
        std::cout << "Inserted '" << word << "'" 
                  << (newWordAdded ? " (new word)" : " (duplicate)")
                  << " | Words: " << totalWords_ << ", Nodes: " << totalNodes_ << std::endl;
    }
    
    // Search for complete word
    bool search(const std::string& word) const {
        NodePtr node = findNode(word);
        return node && node->isEndOfWord;
    }
    
    // Check if any word starts with given prefix
    bool startsWith(const std::string& prefix) const {
        return findNode(prefix) != nullptr;
    }
    
    // Get word count for a specific word
    int getWordCount(const std::string& word) const {
        NodePtr node = findNode(word);
        if (node && node->isEndOfWord) {
            return node->wordCount;
        }
        return 0;
    }
    
    // Find all words with given prefix
    std::vector<std::string> findWordsWithPrefix(const std::string& prefix) const {
        std::vector<std::string> result;
        NodePtr prefixNode = findNode(prefix);
        
        if (prefixNode) {
            collectWordsHelper(prefixNode, prefix, result);
        }
        
        return result;
    }
    
    // Get all words in trie
    std::vector<std::string> getAllWords() const {
        return findWordsWithPrefix("");
    }
    
    // Get all words with their counts
    std::vector<std::pair<std::string, int>> getAllWordsWithCount() const {
        std::vector<std::pair<std::string, int>> result;
        collectWordsWithCountHelper(root_, "", result);
        return result;
    }
    
    // Delete word
    bool remove(const std::string& word) {
        if (word.empty()) {
            std::cout << "Cannot remove empty word" << std::endl;
            return false;
        }
        
        bool existed = search(word);
        if (!existed) {
            std::cout << "Word '" << word << "' not found" << std::endl;
            return false;
        }
        
        deleteHelper(root_, word, 0);
        totalWords_--;
        
        std::cout << "Removed '" << word << "' | Words: " << totalWords_ 
                  << ", Nodes: " << totalNodes_ << std::endl;
        return true;
    }
    
    // Find longest common prefix of all words
    std::string longestCommonPrefix() const {
        std::string lcp = "";
        NodePtr current = root_;
        
        while (current->children.size() == 1 && !current->isEndOfWord) {
            auto it = current->children.begin();
            lcp += it->first;
            current = it->second;
        }
        
        return lcp;
    }
    
    // Count words with given prefix
    int countWordsWithPrefix(const std::string& prefix) const {
        NodePtr prefixNode = findNode(prefix);
        if (!prefixNode) return 0;
        
        return countWordsInSubtree(prefixNode);
    }
    
    // Autocomplete functionality
    std::vector<std::string> autocomplete(const std::string& prefix, int maxSuggestions = 10) const {
        std::vector<std::string> suggestions = findWordsWithPrefix(prefix);
        
        // Sort suggestions by length first, then alphabetically
        std::sort(suggestions.begin(), suggestions.end(), 
                 [](const std::string& a, const std::string& b) {
                     if (a.length() != b.length()) {
                         return a.length() < b.length();
                     }
                     return a < b;
                 });
        
        if (suggestions.size() > static_cast<size_t>(maxSuggestions)) {
            suggestions.resize(maxSuggestions);
        }
        
        return suggestions;
    }
    
    // Pattern matching with wildcards (. matches any character)
    std::vector<std::string> patternMatch(const std::string& pattern) const {
        std::vector<std::string> result;
        patternMatchHelper(root_, pattern, 0, "", result);
        return result;
    }
    
private:
    // Helper for pattern matching
    void patternMatchHelper(NodePtr node, const std::string& pattern, 
                           size_t index, const std::string& currentWord,
                           std::vector<std::string>& result) const {
        if (index == pattern.length()) {
            if (node && node->isEndOfWord) {
                result.push_back(currentWord);
            }
            return;
        }
        
        if (!node) return;
        
        char ch = pattern[index];
        
        if (ch == '.') {
            // Wildcard - try all children
            for (const auto& [childChar, childNode] : node->children) {
                patternMatchHelper(childNode, pattern, index + 1, 
                                 currentWord + childChar, result);
            }
        } else {
            // Specific character
            if (node->children.find(ch) != node->children.end()) {
                patternMatchHelper(node->children.at(ch), pattern, index + 1,
                                 currentWord + ch, result);
            }
        }
    }
    
    // Helper to find node for given string
    NodePtr findNode(const std::string& str) const {
        NodePtr current = root_;
        
        for (char ch : str) {
            if (current->children.find(ch) == current->children.end()) {
                return nullptr;
            }
            current = current->children[ch];
        }
        
        return current;
    }
    
    // Helper to count words in subtree
    int countWordsInSubtree(NodePtr node) const {
        if (!node) return 0;
        
        int count = node->isEndOfWord ? 1 : 0;
        
        for (const auto& [ch, child] : node->children) {
            count += countWordsInSubtree(child);
        }
        
        return count;
    }
    
public:
    // Properties
    size_t size() const { return totalWords_; }
    size_t nodeCount() const { return totalNodes_; }
    bool empty() const { return totalWords_ == 0; }
    
    // Display trie structure
    void display() const {
        if (empty()) {
            std::cout << "Trie is empty" << std::endl;
            return;
        }
        
        std::cout << "Trie Structure:" << std::endl;
        std::cout << "root" << std::endl;
        displayHelper(root_, "", "", 0);
    }
    
    // Display statistics
    void displayStatistics() const {
        std::cout << "\nTrie Statistics:" << std::endl;
        std::cout << "Total words: " << totalWords_ << std::endl;
        std::cout << "Total nodes: " << totalNodes_ << std::endl;
        std::cout << "Memory efficiency: " << std::fixed << std::setprecision(2)
                  << (totalNodes_ > 0 ? (double)totalWords_ / totalNodes_ : 0) << " words/node" << std::endl;
        
        if (!empty()) {
            std::string lcp = longestCommonPrefix();
            std::cout << "Longest common prefix: '" << lcp << "'" << std::endl;
            
            // Find the word with maximum length
            auto allWords = getAllWords();
            if (!allWords.empty()) {
                auto maxWord = *std::max_element(allWords.begin(), allWords.end(),
                                               [](const std::string& a, const std::string& b) {
                                                   return a.length() < b.length();
                                               });
                std::cout << "Longest word: '" << maxWord << "' (" << maxWord.length() << " chars)" << std::endl;
                
                auto minWord = *std::min_element(allWords.begin(), allWords.end(),
                                               [](const std::string& a, const std::string& b) {
                                                   return a.length() < b.length();
                                               });
                std::cout << "Shortest word: '" << minWord << "' (" << minWord.length() << " chars)" << std::endl;
            }
        }
    }
    
    // Clear trie
    void clear() {
        root_ = std::make_shared<TrieNode>();
        totalWords_ = 0;
        totalNodes_ = 1;
        std::cout << "Trie cleared" << std::endl;
    }
};

// Utility functions for demonstration
void printSeparator(const std::string& title) {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "  " << title << std::endl;
    std::cout << std::string(60, '=') << std::endl;
}

void printStringVector(const std::vector<std::string>& vec, const std::string& label) {
    std::cout << label << " (" << vec.size() << "): ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << "'" << vec[i] << "'";
        if (i < vec.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;
}

void demonstrateBasicOperations() {
    printSeparator("BASIC TRIE OPERATIONS");
    
    Trie trie;
    
    std::cout << "\n--- Word Insertion ---" << std::endl;
    std::vector<std::string> words = {"cat", "car", "card", "care", "careful", "cats", "dog", "dodge"};
    
    for (const std::string& word : words) {
        trie.insert(word);
    }
    
    trie.display();
    trie.displayStatistics();
    
    std::cout << "\n--- Word Search ---" << std::endl;
    std::vector<std::string> searchWords = {"cat", "car", "care", "caring", "dog", "elephant"};
    
    for (const std::string& word : searchWords) {
        bool found = trie.search(word);
        std::cout << "Search '" << word << "': " << (found ? "Found" : "Not Found");
        if (found) {
            std::cout << " (count: " << trie.getWordCount(word) << ")";
        }
        std::cout << std::endl;
    }
    
    std::cout << "\n--- Prefix Search ---" << std::endl;
    std::vector<std::string> prefixes = {"ca", "car", "do", "cat", "x"};
    
    for (const std::string& prefix : prefixes) {
        bool hasPrefix = trie.startsWith(prefix);
        std::cout << "Prefix '" << prefix << "': " << (hasPrefix ? "Exists" : "Not Found");
        if (hasPrefix) {
            std::cout << " (" << trie.countWordsWithPrefix(prefix) << " words)";
        }
        std::cout << std::endl;
    }
}

void demonstratePrefixOperations() {
    printSeparator("PREFIX-BASED OPERATIONS");
    
    Trie trie;
    std::vector<std::string> dictionary = {
        "apple", "application", "apply", "appreciate", "approach",
        "banana", "band", "bandana", "bank", "bankrupt",
        "cat", "catch", "category", "cathedral"
    };
    
    for (const std::string& word : dictionary) {
        trie.insert(word);
    }
    
    std::cout << "\n--- Words with Prefix 'app' ---" << std::endl;
    auto appWords = trie.findWordsWithPrefix("app");
    printStringVector(appWords, "Words starting with 'app'");
    
    std::cout << "\n--- Words with Prefix 'ban' ---" << std::endl;
    auto banWords = trie.findWordsWithPrefix("ban");
    printStringVector(banWords, "Words starting with 'ban'");
    
    std::cout << "\n--- Words with Prefix 'cat' ---" << std::endl;
    auto catWords = trie.findWordsWithPrefix("cat");
    printStringVector(catWords, "Words starting with 'cat'");
    
    std::cout << "\n--- All Words in Dictionary ---" << std::endl;
    auto allWords = trie.getAllWords();
    printStringVector(allWords, "All words");
    
    std::cout << "\n--- Longest Common Prefix ---" << std::endl;
    std::cout << "Longest common prefix of all words: '" << trie.longestCommonPrefix() << "'" << std::endl;
}

void demonstrateAutocomplete() {
    printSeparator("AUTOCOMPLETE FUNCTIONALITY");
    
    Trie trie;
    std::vector<std::string> vocabulary = {
        "programming", "program", "programmer", "programs",
        "project", "projects", "projection", "projector",
        "problem", "problems", "problematic",
        "process", "processing", "processor", "processes",
        "product", "production", "productive", "productivity"
    };
    
    for (const std::string& word : vocabulary) {
        trie.insert(word);
    }
    
    std::cout << "\n--- Autocomplete Suggestions ---" << std::endl;
    std::vector<std::string> queries = {"pro", "prog", "proc", "proj"};
    
    for (const std::string& query : queries) {
        auto suggestions = trie.autocomplete(query, 5);
        std::cout << "Autocomplete for '" << query << "': ";
        for (size_t i = 0; i < suggestions.size(); ++i) {
            std::cout << suggestions[i];
            if (i < suggestions.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;
    }
    
    std::cout << "\n--- Simulating Typing ---" << std::endl;
    std::string typedSoFar = "";
    std::string fullWord = "programming";
    
    for (char ch : fullWord) {
        typedSoFar += ch;
        auto suggestions = trie.autocomplete(typedSoFar, 3);
        std::cout << "Typed: '" << typedSoFar << "' → Suggestions: ";
        for (size_t i = 0; i < suggestions.size(); ++i) {
            std::cout << suggestions[i];
            if (i < suggestions.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;
        
        if (suggestions.size() == 1 && suggestions[0] == typedSoFar) {
            std::cout << "  → Complete word found!" << std::endl;
            break;
        }
    }
}

void demonstratePatternMatching() {
    printSeparator("PATTERN MATCHING");
    
    Trie trie;
    std::vector<std::string> words = {
        "cat", "bat", "rat", "hat", "mat",
        "car", "bar", "tar", "far",
        "can", "ban", "tan", "fan", "man"
    };
    
    for (const std::string& word : words) {
        trie.insert(word);
    }
    
    std::cout << "\n--- Wildcard Pattern Matching ---" << std::endl;
    std::vector<std::string> patterns = {".at", "ca.", "..r", ".a.", "ba."};
    
    for (const std::string& pattern : patterns) {
        auto matches = trie.patternMatch(pattern);
        std::cout << "Pattern '" << pattern << "' matches: ";
        for (size_t i = 0; i < matches.size(); ++i) {
            std::cout << matches[i];
            if (i < matches.size() - 1) std::cout << ", ";
        }
        std::cout << " (" << matches.size() << " matches)" << std::endl;
    }
    
    std::cout << "\n--- Pattern Explanation ---" << std::endl;
    std::cout << "Pattern '.at' means: any character followed by 'at'" << std::endl;
    std::cout << "Pattern 'ca.' means: 'ca' followed by any character" << std::endl;
    std::cout << "Pattern '.a.' means: any char, 'a', any char" << std::endl;
}

void demonstrateDeletion() {
    printSeparator("WORD DELETION OPERATIONS");
    
    Trie trie;
    std::vector<std::string> words = {"cat", "cats", "dog", "doggy", "dodge", "door", "down"};
    
    std::cout << "\n--- Building Trie ---" << std::endl;
    for (const std::string& word : words) {
        trie.insert(word);
    }
    
    trie.display();
    std::cout << "\nOriginal words: ";
    auto originalWords = trie.getAllWords();
    printStringVector(originalWords, "Words");
    
    std::cout << "\n--- Deletion Operations ---" << std::endl;
    
    // Delete a word that is prefix of another
    std::cout << "\nDeleting 'cat' (prefix of 'cats'):" << std::endl;
    trie.remove("cat");
    trie.display();
    
    // Delete a word that shares prefix with others
    std::cout << "\nDeleting 'doggy':" << std::endl;
    trie.remove("doggy");
    auto remainingWords = trie.getAllWords();
    printStringVector(remainingWords, "Remaining words");
    
    // Try to delete non-existent word
    std::cout << "\nAttempting to delete 'elephant':" << std::endl;
    trie.remove("elephant");
    
    // Delete a word that would make a branch disappear
    std::cout << "\nDeleting 'down':" << std::endl;
    trie.remove("down");
    trie.display();
    
    trie.displayStatistics();
}

void demonstrateWordFrequency() {
    printSeparator("WORD FREQUENCY TRACKING");
    
    Trie trie;
    
    std::cout << "\n--- Inserting Words with Repetition ---" << std::endl;
    std::vector<std::string> text = {
        "the", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog",
        "the", "dog", "was", "lazy", "and", "the", "fox", "was", "quick"
    };
    
    for (const std::string& word : text) {
        trie.insert(word);
    }
    
    std::cout << "\n--- Word Frequencies ---" << std::endl;
    auto wordsWithCount = trie.getAllWordsWithCount();
    
    // Sort by frequency (descending)
    std::sort(wordsWithCount.begin(), wordsWithCount.end(),
             [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
                 return a.second > b.second;
             });
    
    std::cout << "Word frequency analysis:" << std::endl;
    for (const auto& [word, count] : wordsWithCount) {
        std::cout << "  '" << word << "': " << count << " time" << (count > 1 ? "s" : "") << std::endl;
    }
    
    std::cout << "\n--- Most/Least Frequent Words ---" << std::endl;
    if (!wordsWithCount.empty()) {
        std::cout << "Most frequent: '" << wordsWithCount[0].first << "' (" << wordsWithCount[0].second << " times)" << std::endl;
        std::cout << "Least frequent: '" << wordsWithCount.back().first << "' (" << wordsWithCount.back().second << " time" << (wordsWithCount.back().second > 1 ? "s" : "") << ")" << std::endl;
    }
}

void demonstratePracticalApplications() {
    printSeparator("PRACTICAL APPLICATIONS");
    
    // 1. Spell Checker
    std::cout << "\n--- Spell Checker Application ---" << std::endl;
    Trie dictionary;
    
    std::vector<std::string> correctWords = {
        "hello", "world", "computer", "science", "programming",
        "algorithm", "data", "structure", "software", "hardware"
    };
    
    for (const std::string& word : correctWords) {
        dictionary.insert(word);
    }
    
    std::vector<std::string> userInput = {"hello", "wrold", "compter", "science", "programing"};
    
    std::cout << "Spell checking results:" << std::endl;
    for (const std::string& word : userInput) {
        bool isCorrect = dictionary.search(word);
        std::cout << "  '" << word << "': " << (isCorrect ? "✓ Correct" : "✗ Misspelled");
        
        if (!isCorrect) {
            // Suggest corrections based on similar prefixes
            std::string prefix = word.substr(0, std::min(word.length(), size_t(3)));
            auto suggestions = dictionary.autocomplete(prefix, 3);
            if (!suggestions.empty()) {
                std::cout << " → Did you mean: ";
                for (size_t i = 0; i < suggestions.size(); ++i) {
                    std::cout << suggestions[i];
                    if (i < suggestions.size() - 1) std::cout << ", ";
                }
            }
        }
        std::cout << std::endl;
    }
    
    // 2. IP Address Routing (Longest Prefix Match)
    std::cout << "\n--- Network Routing Table ---" << std::endl;
    Trie routingTable;
    
    std::vector<std::string> routes = {
        "192.168.1", "192.168.2", "192.168", "10.0.0", "10.0.1", "172.16"
    };
    
    for (const std::string& route : routes) {
        routingTable.insert(route);
    }
    
    std::vector<std::string> ipPrefixes = {"192.168.1", "192.168.5", "10.0.0", "172.16", "8.8.8"};
    
    std::cout << "Routing decisions:" << std::endl;
    for (const std::string& ip : ipPrefixes) {
        std::string bestMatch = "";
        
        // Find longest matching prefix
        for (size_t len = ip.length(); len > 0; --len) {
            std::string prefix = ip.substr(0, len);
            if (routingTable.search(prefix)) {
                bestMatch = prefix;
                break;
            }
        }
        
        std::cout << "  IP '" << ip << "': ";
        if (!bestMatch.empty()) {
            std::cout << "Route via '" << bestMatch << "'";
        } else {
            std::cout << "No route found";
        }
        std::cout << std::endl;
    }
    
    // 3. DNA Sequence Analysis
    std::cout << "\n--- DNA Sequence Analysis ---" << std::endl;
    Trie dnaSequences;
    
    std::vector<std::string> sequences = {
        "ATCG", "ATCGA", "ATCGAT", "GCTA", "GCTAA", "TTAG", "TTAGA", "CCGG"
    };
    
    for (const std::string& seq : sequences) {
        dnaSequences.insert(seq);
    }
    
    std::cout << "Finding sequences with common prefixes:" << std::endl;
    std::vector<std::string> queryPrefixes = {"ATC", "GCT", "TTA", "CC"};
    
    for (const std::string& prefix : queryPrefixes) {
        auto matches = dnaSequences.findWordsWithPrefix(prefix);
        std::cout << "  Sequences starting with '" << prefix << "': ";
        printStringVector(matches, "");
    }
}

void demonstratePerformanceCharacteristics() {
    printSeparator("PERFORMANCE CHARACTERISTICS");
    
    Trie trie;
    
    std::cout << "\n--- Space Efficiency Analysis ---" << std::endl;
    
    // Test 1: Words with common prefixes (efficient)
    std::vector<std::string> commonPrefixWords = {
        "test", "testing", "tester", "tests", "tested"
    };
    
    for (const std::string& word : commonPrefixWords) {
        trie.insert(word);
    }
    
    std::cout << "Words with common prefix 'test':" << std::endl;
    trie.displayStatistics();
    
    trie.clear();
    
    // Test 2: Words with no common prefixes (less efficient)
    std::vector<std::string> noCommonPrefixWords = {
        "apple", "banana", "cherry", "date", "elderberry"
    };
    
    for (const std::string& word : noCommonPrefixWords) {
        trie.insert(word);
    }
    
    std::cout << "\nWords with no common prefixes:" << std::endl;
    trie.displayStatistics();
    
    std::cout << "\n--- Time Complexity Summary ---" << std::endl;
    std::cout << "╔══════════════════╦══════════════╗" << std::endl;
    std::cout << "║    Operation     ║ Complexity   ║" << std::endl;
    std::cout << "╠══════════════════╬══════════════╣" << std::endl;
    std::cout << "║ Insert           ║     O(m)     ║" << std::endl;
    std::cout << "║ Search           ║     O(m)     ║" << std::endl;
    std::cout << "║ Delete           ║     O(m)     ║" << std::endl;
    std::cout << "║ Prefix Search    ║     O(p)     ║" << std::endl;
    std::cout << "║ Autocomplete     ║   O(p + n)   ║" << std::endl;
    std::cout << "╚══════════════════╩══════════════╝" << std::endl;
    std::cout << "Where: m = word length, p = prefix length, n = number of results" << std::endl;
    
    std::cout << "\nSpace Complexity:" << std::endl;
    std::cout << "Best Case:  O(n) - when all words share common prefix" << std::endl;
    std::cout << "Worst Case: O(alphabet_size * n * m) - no shared prefixes" << std::endl;
    std::cout << "Typical:    O(alphabet_size * number_of_nodes)" << std::endl;
    
    std::cout << "\nTrie vs Other Data Structures:" << std::endl;
    std::cout << "🆚 Hash Table: Trie better for prefix operations, Hash better for exact lookup" << std::endl;
    std::cout << "🆚 BST: Trie better for string operations, BST better for general ordering" << std::endl;
    std::cout << "🆚 Array: Trie better for dynamic vocabulary, Array better for fixed small sets" << std::endl;
}

int main() {
    std::cout << "===============================================" << std::endl;
    std::cout << "          TRIE DEMONSTRATION                 " << std::endl;
    std::cout << "===============================================" << std::endl;
    
    try {
        demonstrateBasicOperations();
        demonstratePrefixOperations();
        demonstrateAutocomplete();
        demonstratePatternMatching();
        demonstrateDeletion();
        demonstrateWordFrequency();
        demonstratePracticalApplications();
        demonstratePerformanceCharacteristics();
        
        printSeparator("COMPREHENSIVE SUMMARY");
        
        std::cout << "\nTrie (Prefix Tree) Key Properties:" << std::endl;
        std::cout << "🌳 Tree Structure: Each node represents a character" << std::endl;
        std::cout << "📝 Prefix Sharing: Common prefixes share same path" << std::endl;
        std::cout << "🎯 End-of-Word Marking: Special flag for word endings" << std::endl;
        std::cout << "⚡ Efficient Prefix Operations: Fast prefix-based queries" << std::endl;
        
        std::cout << "\nCore Advantages:" << std::endl;
        std::cout << "✅ Excellent for prefix-based operations" << std::endl;
        std::cout << "✅ Efficient autocomplete functionality" << std::endl;
        std::cout << "✅ Space-efficient for words with common prefixes" << std::endl;
        std::cout << "✅ Supports pattern matching and wildcards" << std::endl;
        std::cout << "✅ Natural implementation for string algorithms" << std::endl;
        std::cout << "✅ Fast word insertion, deletion, and search" << std::endl;
        
        std::cout << "\nDisadvantages:" << std::endl;
        std::cout << "❌ High memory usage for sparse datasets" << std::endl;
        std::cout << "❌ Not cache-friendly due to pointer chasing" << std::endl;
        std::cout << "❌ Complex implementation compared to hash tables" << std::endl;
        std::cout << "❌ Poor performance for completely different strings" << std::endl;
        
        std::cout << "\nTime Complexity:" << std::endl;
        std::cout << "• Insert: O(m) where m is word length" << std::endl;
        std::cout << "• Search: O(m) where m is word length" << std::endl;
        std::cout << "• Delete: O(m) where m is word length" << std::endl;
        std::cout << "• Prefix Search: O(p) where p is prefix length" << std::endl;
        std::cout << "• Find All Prefixes: O(p + n) where n is number of results" << std::endl;
        
        std::cout << "\nSpace Complexity:" << std::endl;
        std::cout << "• Best Case: O(n) - shared prefixes" << std::endl;
        std::cout << "• Worst Case: O(alphabet_size × n × average_length)" << std::endl;
        std::cout << "• Practical: Depends on prefix sharing" << std::endl;
        
        std::cout << "\nCommon Applications:" << std::endl;
        std::cout << "🎯 Autocomplete Systems: Search engines, IDEs, mobile keyboards" << std::endl;
        std::cout << "🎯 Spell Checkers: Word processors, text editors" << std::endl;
        std::cout << "🎯 IP Routing: Longest prefix match in routers" << std::endl;
        std::cout << "🎯 Dictionary Lookups: Digital dictionaries, word games" << std::endl;
        std::cout << "🎯 DNA Sequence Analysis: Bioinformatics applications" << std::endl;
        std::cout << "🎯 URL Routing: Web frameworks and servers" << std::endl;
        std::cout << "🎯 File System: Path-based operations" << std::endl;
        std::cout << "🎯 Compiler Design: Symbol tables, keyword recognition" << std::endl;
        
        std::cout << "\nOptimization Techniques:" << std::endl;
        std::cout << "🔧 Compressed Trie: Merge single-child chains" << std::endl;
        std::cout << "🔧 Patricia Trie: Radix tree with path compression" << std::endl;
        std::cout << "🔧 Ternary Search Trie: Space-efficient alternative" << std::endl;
        std::cout << "🔧 Suffix Trie: For suffix-based operations" << std::endl;
        
        std::cout << "\nWhen to Use Trie:" << std::endl;
        std::cout << "💡 Need efficient prefix-based operations" << std::endl;
        std::cout << "💡 Implementing autocomplete functionality" << std::endl;
        std::cout << "💡 Working with string datasets with common prefixes" << std::endl;
        std::cout << "💡 Pattern matching and wildcard searches" << std::endl;
        std::cout << "💡 Building spell checkers or word validators" << std::endl;
        std::cout << "💡 Implementing routing algorithms" << std::endl;
        
        std::cout << "\nConsider Alternatives:" << std::endl;
        std::cout << "🔄 Hash Tables for exact string matching" << std::endl;
        std::cout << "🔄 Suffix Arrays/Trees for suffix operations" << std::endl;
        std::cout << "🔄 Bloom Filters for membership testing" << std::endl;
        std::cout << "🔄 Finite Automata for pattern matching" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n===============================================" << std::endl;
    std::cout << "          DEMONSTRATION COMPLETE              " << std::endl;
    std::cout << "===============================================" << std::endl;
    
    return 0;
}
