function StatsCard({ stats }) {
  const items = [
    { label: 'Documents', value: stats.totalDocuments },
    { label: 'Unique Words', value: stats.uniqueWords },
    { label: 'Avg Doc Length', value: stats.averageDocumentLength?.toFixed(1) },
    { label: 'Index Size', value: stats.indexSize },
    { label: 'Indexing', value: `${stats.indexingTimeMs?.toFixed(1)} ms` },
    { label: 'Query Time', value: `${stats.searchTimeMs?.toFixed(1)} ms` },
  ]

  return (
    <div className="mt-6 bg-surface border border-surface rounded-xl p-5 shadow-sm">
      <h3 className="text-sm font-semibold text-secondary uppercase tracking-wider mb-4">
        Index Statistics
      </h3>
      <div className="grid grid-cols-2 sm:grid-cols-3 md:grid-cols-6 gap-4">
        {items.map((item) => (
          <div key={item.label} className="text-center">
            <p className="text-2xl font-bold text-brand-500">{item.value}</p>
            <p className="text-xs text-secondary mt-0.5">{item.label}</p>
          </div>
        ))}
      </div>
    </div>
  )
}

export default StatsCard
