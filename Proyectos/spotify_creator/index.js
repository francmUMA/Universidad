import express from 'express'

//Definicion de todos los parametros que vamos a usar
let client_id = "fee6275da3ab4dd3ba15fd84725347df"
let client_secret = "c5cf39fc26304dc9a4b33492aed3299d"
let redirect_uri = 'http://localhost:8000/inicio'
let scopes = "user-read-private user-read-email"
let baseURI = "https://api.spotify.com/v1"
let options = {
  headers: {
    'Accept': 'application/json',
    'Content-Type': 'application/json',
    'Authorization': 'Bearer ' + await getTokenFetch()
  },
  json: true
}


//Obtiene el token de uso de las peticiones
async function getTokenFetch () {
  return fetch("https://accounts.spotify.com/api/token", {
    method: "POST",
    body: 'grant_type=client_credentials&client_id=' + client_id + '&client_secret=' + client_secret + '&redirect_uri=' + redirect_uri + '&scope=' + scopes,
    headers: {
      'Content-Type': 'application/x-www-form-urlencoded',
    }
  })
  .then(response => response.json())
  .then(data => { return data.access_token })
}

//Obtener información de un artista (modificar token cuando esté lista la funcion)
async function getArtistID(artist) {
  return fetch(baseURI + '/search?q=' + artist + '&type=artist', options)
  .then(response => response.json())
  .then(data => { return data.artists.items[0].id })
}

//Obtener canciones de un artista dado su ID
async function getArtistSongs(artistID) {
  return fetch(baseURI + '/artists/' + artistID + '/top-tracks?market=ES', options)
  .then(response => response.json())
  .then(data => { 
    let songs = []
    data.tracks.forEach(song => {
      songs.push({
        name: song.name,
        id: song.id,
        album: song.album.name,
        uri: song.uri
      })
    })
    return songs
  })
}

//Obtener informacion del usuario registrado
async function getUserInfo() {
  return fetch(baseURI + '/me', options)
  .then(response => response.json())
  .then(data => { return data })
}

//Aplicacion de express
const app = express()

app.get('/', (req, res) => {
  res.send('Hello World!')
})

app.get('/login', (req, res) => {
  res.redirect('https://accounts.spotify.com/authorize?client_id=' + client_id + '&response_type=code&redirect_uri=' + redirect_uri)
})

app.get('/inicio', async (req, res) => {
  res.send(await getUserInfo())
})

app.listen(8000, () => {
  console.log('Link: http://localhost:8000/')
})
















