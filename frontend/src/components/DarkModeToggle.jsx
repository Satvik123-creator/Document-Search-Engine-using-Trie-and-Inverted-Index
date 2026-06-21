function DarkModeToggle({ dark, onToggle }) {
  return (
    <button
      onClick={onToggle}
      className="fixed top-4 right-4 z-50 w-10 h-10 rounded-full bg-surface border border-surface shadow-md flex items-center justify-center text-lg hover:scale-110 transition-transform"
      aria-label="Toggle dark mode"
    >
      {dark ? '☀️' : '🌙'}
    </button>
  )
}

export default DarkModeToggle
