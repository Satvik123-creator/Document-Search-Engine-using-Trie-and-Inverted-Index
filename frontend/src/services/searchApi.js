import axios from 'axios'

const client = axios.create({
  baseURL: '/api',
})

export function search(query) {
  return client.get('/search', { params: { q: query } })
}

export function autocomplete(prefix) {
  return client.get('/autocomplete', { params: { prefix } })
}

export function getStats() {
  return client.get('/stats')
}
