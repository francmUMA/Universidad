//Definicion de todos los parametros que vamos a usar
let client_id = "fee6275da3ab4dd3ba15fd84725347df"
let client_secret = "c5cf39fc26304dc9a4b33492aed3299d"
let redirect_uri = 'http://localhost:8000/inicio'
let code = ""
let scopes = "user-read-private user-read-email playlist-read-private user-top-read playlist-modify-public playlist-modify-private"
let baseURI = "https://api.spotify.com/v1"
let options = (token) => {
  return {
    headers: {
      'Accept': 'application/json',
      'Content-Type': 'application/json',
      'Authorization': 'Bearer ' + token
    }
  }
}

//Obtiene el token de uso de las peticiones
async function getToken() {
  return fetch("https://accounts.spotify.com/api/token", {
    method: "POST",
    body: 'grant_type=authorization_code&code=' + code + '&redirect_uri=' + redirect_uri,
    headers: {
      'Content-Type': 'application/x-www-form-urlencoded',
      'Authorization': 'Basic ' + (new Buffer.from(client_id + ':' + client_secret).toString('base64'))
    }
  })
  .then(response => response.json())
  .then(data => { return data.access_token })
}

//Obtener información de un artista (modificar token cuando esté lista la funcion)
async function getArtistID(artist) {
  return fetch(baseURI + '/search?q=' + artist + '&type=artist', options(await getToken()))
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
async function getUserInfo(token) {
  return fetch(baseURI + '/me', options(token))
  .then(response => response.json())
  .then(data => { return data })
}

//Obtener las playlist de un usuario dado su ID
async function getUserPlaylists(token) {
  return fetch(baseURI + '/me/playlists', options(token))
  .then(response => response.json())
  .then(data => { return data })
}

//Obtener el wrapped de canciones del usuario logueado
async function getUserMostListenedSongs(token) {
  return fetch(baseURI + '/me/top/tracks?limit=50', options(token))
  .then(response => response.json())
  .then(data => { return data })
}

//Crear una playlist
async function createPlaylist(token, name, id) {
  return fetch(baseURI + '/users/' + id + '/playlists', {
    method: "POST",
    body: JSON.stringify({
      name: name,
      description: "Playlist creada por javascript",
      public: false
    }),
    headers: {
      'Accept': 'application/json',
      'Content-Type': 'application/json',
      'Authorization': 'Bearer ' + token
    }
  })
  .then(response => {
    if (response.status >= 200 && response.status < 300) {
      console.log("Playlist creada")
    } else {
      console.log("Error al crear playlist")
    }
  })
}



















