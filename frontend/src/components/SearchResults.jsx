import LoadingSpinner from './LoadingSpinner'
import EmptyState from './EmptyState'

function SearchResults({ results, loading, error, hasSearched }) {
  if (loading) return <LoadingSpinner />

  if (error) {
    return (
      <div className="text-center py-12">
        <span className="text-3xl">⚠️</span>
        <p className="text-red-500 font-medium mt-2">{error}</p>
      </div>
    )
  }

  if (!results || results.length === 0) {
    return <EmptyState hasQuery={false} hasSearched={hasSearched} />
  }

  return (
    <div className="space-y-2.5 mt-2">
      {results.map((r, i) => (
        <div
          key={i}
          className="bg-surface border border-surface rounded-xl p-4 hover:shadow-md transition-shadow animate-fadeIn"
          style={{ animationDelay: `${i * 40}ms`, animationFillMode: 'backwards' }}
        >
          <div className="flex items-center justify-between mb-2">
            <span className="font-medium text-sm">Document #{r.docId}</span>
            <span className="text-xs font-mono text-secondary bg-gray-100 dark:bg-gray-800 px-2 py-0.5 rounded-full">
              {r.score.toFixed(4)}
            </span>
          </div>
          <div className="h-1.5 bg-gray-200 dark:bg-gray-700 rounded-full overflow-hidden">
            <div
              className="h-full bg-gradient-to-r from-brand-500 to-cyan-400 rounded-full transition-all duration-500"
              style={{ width: `${Math.min(r.score * 100, 100)}%` }}
            />
          </div>
        </div>
      ))}
    </div>
  )
}

export default SearchResults
