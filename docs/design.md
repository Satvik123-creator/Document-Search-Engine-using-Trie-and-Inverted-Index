# Search Engine Design

## Architecture

- Backend: C++ with custom Inverted Index, Trie, and Ranker
- Frontend: React (Vite)
- API: RESTful endpoints for search and suggestions

## Components

### Backend
- **InvertedIndex**: Maps terms to document IDs
- **Trie**: Prefix tree for autocomplete suggestions
- **Ranker**: TF-IDF scoring of search results
- **DocumentParser**: Reads and tokenizes documents
- **Tokenizer**: Splits text into tokens

### Frontend
- **SearchBar**: Input field for queries
- **SearchResults**: Displays ranked results
- **Suggestions**: Autocomplete dropdown
- **TrieVisualizer**: Visual representation of the trie
- **StatsCard**: Shows index statistics
