import { useState, useEffect, useRef, useCallback } from 'react'

function SearchBar({ query, onChange, onSubmit, onSuggest, responseTime }) {
  const [local, setLocal] = useState(query)
  const timerRef = useRef(null)

  useEffect(() => { setLocal(query) }, [query])

  const debouncedSuggest = useCallback((value) => {
    if (timerRef.current) clearTimeout(timerRef.current)
    timerRef.current = setTimeout(() => onSuggest(value), 200)
  }, [onSuggest])

  const handleChange = (e) => {
    const value = e.target.value
    setLocal(value)
    onChange(value)
    debouncedSuggest(value)
  }

  const handleSubmit = (e) => {
    e.preventDefault()
    if (timerRef.current) clearTimeout(timerRef.current)
    onSubmit(local)
  }

  return (
    <form onSubmit={handleSubmit}>
      <div className="flex items-center gap-2 bg-surface border border-surface rounded-2xl px-5 py-1 shadow-sm focus-within:border-brand-500 focus-within:shadow-md transition-all">
        <span className="text-lg text-secondary">🔍</span>
        <input
          className="flex-1 border-none outline-none bg-transparent text-base py-3 placeholder-secondary"
          type="text"
          placeholder="Search documents…"
          value={local}
          onChange={handleChange}
          autoFocus
        />
        {responseTime != null && (
          <span className="text-xs text-secondary font-mono whitespace-nowrap">
            {responseTime} ms
          </span>
        )}
        <button
          type="submit"
          className="bg-brand-500 hover:bg-brand-600 text-white rounded-xl px-5 py-2 text-sm font-medium transition-colors"
        >
          Search
        </button>
      </div>
    </form>
  )
}

export default SearchBar
