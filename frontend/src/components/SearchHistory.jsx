function SearchHistory({ history, onSelect, onClear }) {
  if (!history || history.length === 0) return null

  return (
    <div className="mt-6 bg-surface border border-surface rounded-xl p-4 shadow-sm">
      <div className="flex items-center justify-between mb-3">
        <h3 className="text-sm font-semibold text-secondary uppercase tracking-wider">
          Recent Searches
        </h3>
        <button
          onClick={onClear}
          className="text-xs text-brand-500 hover:text-brand-600 dark:text-brand-500 transition-colors"
        >
          Clear
        </button>
      </div>
      <div className="flex flex-wrap gap-2">
        {history.map((item, i) => (
          <button
            key={i}
            onClick={() => onSelect(item.query)}
            className="px-3 py-1.5 text-sm rounded-full bg-gray-100 dark:bg-gray-800 text-gray-700 dark:text-gray-300 hover:bg-brand-50 dark:hover:bg-brand-900/30 hover:text-brand-600 dark:hover:text-brand-400 transition-colors"
          >
            {item.query}
            <span className="ml-2 text-xs text-secondary">
              {item.responseTime}ms
            </span>
          </button>
        ))}
      </div>
    </div>
  )
}

export default SearchHistory
