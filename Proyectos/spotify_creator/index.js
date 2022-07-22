import request from 'request'
import axios from 'axios'

//Definicion de todos los parametros que vamos a usar
let client_id = "fee6275da3ab4dd3ba15fd84725347df"
let client_secret = "c5cf39fc26304dc9a4b33492aed3299d"
let scopes = "user-read-private user-read-email"
let baseURI = "https://api.spotify.com/v1"
let options = {
  url: "https://accounts.spotify.com/api/token",
  headers: {
    'Authorization': 'Basic ' + (new Buffer.from(client_id + ':' + client_secret).toString('base64'))
  },
  form: {
    grant_type: 'client_credentials'
  },
  json: true
}

let optionsFetch = {
  method: "POST",
  headers: {
    'Authorization': 'Basic ' + (new Buffer.from(client_id + ':' + client_secret).toString('base64'))
  },
  form: {
    grant_type: 'client_credentials'
  },
  json: true
}

//Petición del token de spotify (PENDIENTE)
function getToken(){
  request.post(options, (error, response, body) => {
    if (!error && response.statusCode === 200) {
      console.log(body.access_token)
    } 
  })
}

function getTokenFetch () {
  fetch("https://accounts.spotify.com/api/token", optionsFetch)
  .then(response => response.json())
  .then(data => console.log(data))
}

//Obtener información de un artista (modificar token cuando esté lista la funcion)
function getArtist(artist) {
  return fetch(baseURI + '/search?q=' + artist + '&type=artist', {
    headers: {
      'Accept': 'application/json',
      'Content-Type': 'application/json',
      'Authorization': 'Bearer ' + 'BQAN7PlUkMFX6azZl7zNVkp5lfor5yuSNBQ1RmIV6NGxLb-i8aKn2sYxQbVa61J6qvXKb0ks6II_pg9K9OeGy7Ysn7vGd5rtZ6_CDL0TQZzUj0XiXGY'
    },
    json: true
  })
  .then(response => response.json())
}

getToken()






