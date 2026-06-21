function LoadingSpinner() {
  return (
    <div className="space-y-3 py-6">
      {[1, 2, 3].map((i) => (
        <div
          key={i}
          className="h-16 rounded-xl bg-surface border border-surface overflow-hidden relative"
        >
          <div
            className="absolute inset-0 bg-gradient-to-r from-transparent via-gray-200 dark:via-gray-700 to-transparent animate-shimmer"
            style={{ backgroundSize: '200% 100%' }}
          />
        </div>
      ))}
    </div>
  )
}

export default LoadingSpinner
