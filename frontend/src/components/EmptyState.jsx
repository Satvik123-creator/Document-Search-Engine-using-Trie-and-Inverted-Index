function EmptyState({ hasQuery, hasSearched }) {
  if (hasSearched) {
    return (
      <div className="flex flex-col items-center justify-center py-16 text-center">
        <svg className="w-32 h-32 text-secondary mb-6" fill="none" viewBox="0 0 128 128">
          <circle cx="64" cy="64" r="48" stroke="currentColor" strokeWidth="3" />
          <circle cx="64" cy="64" r="20" stroke="currentColor" strokeWidth="3" strokeDasharray="8 4" />
          <line x1="64" y1="44" x2="64" y2="28" stroke="currentColor" strokeWidth="3" strokeLinecap="round" />
          <line x1="64" y1="84" x2="64" y2="100" stroke="currentColor" strokeWidth="3" strokeLinecap="round" />
          <line x1="44" y1="64" x2="28" y2="64" stroke="currentColor" strokeWidth="3" strokeLinecap="round" />
          <line x1="84" y1="64" x2="100" y2="64" stroke="currentColor" strokeWidth="3" strokeLinecap="round" />
        </svg>
        <p className="text-lg font-medium text-secondary">No results found</p>
        <p className="text-sm text-secondary mt-1">Try a different search term.</p>
      </div>
    )
  }

  return (
    <div className="flex flex-col items-center justify-center py-16 text-center">
      <svg className="w-32 h-32 text-secondary mb-6" fill="none" viewBox="0 0 128 128">
        <rect x="20" y="40" width="88" height="56" rx="8" stroke="currentColor" strokeWidth="3" />
        <line x1="36" y1="60" x2="92" y2="60" stroke="currentColor" strokeWidth="2" strokeLinecap="round" />
        <line x1="36" y1="72" x2="76" y2="72" stroke="currentColor" strokeWidth="2" strokeLinecap="round" />
        <line x1="36" y1="84" x2="60" y2="84" stroke="currentColor" strokeWidth="2" strokeLinecap="round" />
        <circle cx="64" cy="20" r="10" stroke="currentColor" strokeWidth="3" />
        <line x1="64" y1="30" x2="64" y2="40" stroke="currentColor" strokeWidth="3" strokeLinecap="round" />
      </svg>
      <p className="text-lg font-medium text-secondary">Search your documents</p>
      <p className="text-sm text-secondary mt-1">Type a query above to get started.</p>
    </div>
  )
}

export default EmptyState
