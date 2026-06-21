function AnalyticsDashboard({ stats, searchCount, avgResponseTime }) {
  const metrics = [
    {
      label: 'Documents Indexed',
      value: stats?.totalDocuments ?? '—',
      icon: '📄',
      color: 'bg-blue-50 dark:bg-blue-900/20 text-blue-600 dark:text-blue-400',
    },
    {
      label: 'Unique Words',
      value: stats?.uniqueWords ?? '—',
      icon: '📖',
      color: 'bg-green-50 dark:bg-green-900/20 text-green-600 dark:text-green-400',
    },
    {
      label: 'Avg Doc Length',
      value: stats?.averageDocumentLength?.toFixed(1) ?? '—',
      icon: '📏',
      color: 'bg-purple-50 dark:bg-purple-900/20 text-purple-600 dark:text-purple-400',
    },
    {
      label: 'Index Size (pairs)',
      value: stats?.indexSize ?? '—',
      icon: '🗂️',
      color: 'bg-orange-50 dark:bg-orange-900/20 text-orange-600 dark:text-orange-400',
    },
    {
      label: 'Searches Performed',
      value: searchCount,
      icon: '🔍',
      color: 'bg-pink-50 dark:bg-pink-900/20 text-pink-600 dark:text-pink-400',
    },
    {
      label: 'Avg Response Time',
      value: avgResponseTime ? `${avgResponseTime.toFixed(0)} ms` : '—',
      icon: '⚡',
      color: 'bg-cyan-50 dark:bg-cyan-900/20 text-cyan-600 dark:text-cyan-400',
    },
  ]

  return (
    <div className="mt-8">
      <h2 className="text-lg font-semibold mb-4">Analytics Dashboard</h2>
      <div className="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 gap-4">
        {metrics.map((m) => (
          <div
            key={m.label}
            className="bg-surface border border-surface rounded-xl p-4 shadow-sm hover:shadow-md transition-shadow"
          >
            <div className="flex items-center gap-3">
              <span className={`w-10 h-10 rounded-lg flex items-center justify-center text-lg ${m.color}`}>
                {m.icon}
              </span>
              <div>
                <p className="text-xs text-secondary uppercase tracking-wider">{m.label}</p>
                <p className="text-2xl font-bold mt-0.5">{m.value}</p>
              </div>
            </div>
          </div>
        ))}
      </div>

      {stats && (
        <div className="mt-6 bg-surface border border-surface rounded-xl p-5 shadow-sm">
          <h3 className="text-sm font-semibold text-secondary uppercase tracking-wider mb-4">
            Indexing Performance
          </h3>
          <div className="space-y-3">
            <Bar label="Indexing Time" value={stats.indexingTimeMs ?? 0} suffix="ms" max={Math.max(stats.indexingTimeMs ?? 0, 1)} />
            <Bar label="Search Time (last)" value={stats.searchTimeMs ?? 0} suffix="ms" max={Math.max(stats.searchTimeMs ?? 0, 1)} />
            <Bar label="Autocomplete Time (last)" value={stats.autocompleteTimeMs ?? 0} suffix="ms" max={Math.max(stats.autocompleteTimeMs ?? 0, 1)} />
          </div>
        </div>
      )}
    </div>
  )
}

function Bar({ label, value, suffix, max }) {
  const pct = max > 0 ? (value / max) * 100 : 0
  return (
    <div>
      <div className="flex justify-between text-sm mb-1">
        <span className="text-secondary">{label}</span>
        <span className="font-medium">{value.toFixed(1)} {suffix}</span>
      </div>
      <div className="h-2 bg-gray-200 dark:bg-gray-700 rounded-full overflow-hidden">
        <div
          className="h-full bg-gradient-to-r from-brand-500 to-cyan-500 rounded-full transition-all duration-500"
          style={{ width: `${pct}%` }}
        />
      </div>
    </div>
  )
}

export default AnalyticsDashboard
