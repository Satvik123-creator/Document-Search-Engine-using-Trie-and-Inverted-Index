function Suggestions({ suggestions, onSelect }) {
  if (!suggestions || suggestions.length === 0) return null

  return (
    <ul className="absolute top-full left-0 right-0 z-10 mt-1 bg-surface border border-surface rounded-xl shadow-lg overflow-hidden">
      {suggestions.map((s, i) => (
        <li
          key={i}
          onClick={() => onSelect(s)}
          onKeyDown={(e) => e.key === 'Enter' && onSelect(s)}
          tabIndex={0}
          className="flex items-center gap-3 px-5 py-2.5 text-sm cursor-pointer hover:bg-gray-100 dark:hover:bg-gray-800 transition-colors"
        >
          <span className="text-secondary text-xs">🔍</span>
          {s}
        </li>
      ))}
    </ul>
  )
}

export default Suggestions
