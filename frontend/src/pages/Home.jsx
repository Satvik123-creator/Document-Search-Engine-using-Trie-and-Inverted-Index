import { useState, useEffect, useCallback } from 'react'
import DarkModeToggle from '../components/DarkModeToggle'
import SearchBar from '../components/SearchBar'
import Suggestions from '../components/Suggestions'
import SearchResults from '../components/SearchResults'
import SearchHistory from '../components/SearchHistory'
import StatsCard from '../components/StatsCard'
import AnalyticsDashboard from '../components/AnalyticsDashboard'
import { search, autocomplete, getStats } from '../services/searchApi'

const HISTORY_KEY = 'search_history'

function loadHistory() {
  try {
    return JSON.parse(localStorage.getItem(HISTORY_KEY)) || []
  } catch { return [] }
}

function saveHistory(h) {
  localStorage.setItem(HISTORY_KEY, JSON.stringify(h))
}

function Home() {
  const [dark, setDark] = useState(() => localStorage.getItem('dark') === 'true')
  const [query, setQuery] = useState('')
  const [results, setResults] = useState([])
  const [suggestions, setSuggestions] = useState([])
  const [stats, setStats] = useState(null)
  const [loading, setLoading] = useState(false)
  const [error, setError] = useState(null)
  const [hasSearched, setHasSearched] = useState(false)
  const [responseTime, setResponseTime] = useState(null)
  const [searchCount, setSearchCount] = useState(0)
  const [avgResponseTime, setAvgResponseTime] = useState(0)
  const [history, setHistory] = useState(loadHistory)
  const [showAnalytics, setShowAnalytics] = useState(false)

  useEffect(() => {
    document.documentElement.classList.toggle('dark', dark)
    localStorage.setItem('dark', dark)
  }, [dark])

  useEffect(() => {
    getStats()
      .then(res => setStats(res.data))
      .catch(() => {})
  }, [])

  const addToHistory = useCallback((q, time, count) => {
    setHistory(prev => {
      const next = [{ query: q, responseTime: time, resultCount: count, ts: Date.now() }, ...prev].slice(0, 20)
      saveHistory(next)
      return next
    })
  }, [])

  const handleSearch = useCallback(async (q) => {
    if (!q.trim()) return
    setLoading(true)
    setError(null)
    setSuggestions([])
    setHasSearched(true)
    const start = performance.now()
    try {
      const res = await search(q)
      const elapsed = Math.round(performance.now() - start)
      setResponseTime(elapsed)
      const resultsData = res.data.results || []
      setResults(resultsData)
      setSearchCount(c => c + 1)
      setAvgResponseTime(prev => prev ? (prev + elapsed) / 2 : elapsed)
      addToHistory(q, elapsed, resultsData.length)
    } catch {
      setError('Search failed. Is the backend running?')
      setResults([])
    } finally {
      setLoading(false)
    }
  }, [addToHistory])

  const handleSuggest = useCallback(async (prefix) => {
    if (!prefix.trim()) { setSuggestions([]); return }
    try {
      const res = await autocomplete(prefix)
      setSuggestions(res.data.suggestions || [])
    } catch { setSuggestions([]) }
  }, [])

  const handleSelectSuggestion = useCallback((suggestion) => {
    setQuery(suggestion)
    handleSearch(suggestion)
  }, [handleSearch])

  const handleClearHistory = useCallback(() => {
    setHistory([])
    saveHistory([])
  }, [])

  return (
    <div className="min-h-screen flex flex-col" style={{ backgroundColor: 'var(--bg)', color: 'var(--text)' }}>
      <DarkModeToggle dark={dark} onToggle={() => setDark(d => !d)} />

      <header className="text-center pt-12 pb-4 px-4">
        <h1 className="text-4xl font-semibold tracking-tight" style={{ color: 'var(--accent)' }}>
          Search Engine
        </h1>
        <p className="text-sm mt-1" style={{ color: 'var(--text-secondary)' }}>
          Full-text document search with TF-IDF ranking
        </p>
      </header>

      <main className="w-full max-w-2xl mx-auto px-4 pb-12 flex-1">
        <div className="relative mb-2">
          <SearchBar
            query={query}
            onChange={setQuery}
            onSubmit={handleSearch}
            onSuggest={handleSuggest}
            responseTime={responseTime}
          />
          <Suggestions
            suggestions={suggestions}
            onSelect={handleSelectSuggestion}
          />
        </div>

        <button
          onClick={() => setShowAnalytics(v => !v)}
          className="text-xs font-medium mb-4 px-3 py-1.5 rounded-lg border border-surface hover:shadow-sm transition-all"
          style={{ color: 'var(--text-secondary)', borderColor: 'var(--border)' }}
        >
          {showAnalytics ? 'Hide' : 'Show'} Analytics Dashboard
        </button>

        {showAnalytics && (
          <AnalyticsDashboard
            stats={stats}
            searchCount={searchCount}
            avgResponseTime={avgResponseTime}
          />
        )}

        <SearchHistory
          history={history}
          onSelect={handleSelectSuggestion}
          onClear={handleClearHistory}
        />

        <SearchResults results={results} loading={loading} error={error} hasSearched={hasSearched} />

        {stats && <StatsCard stats={stats} />}
      </main>
    </div>
  )
}

export default Home
