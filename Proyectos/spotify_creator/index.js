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
  headers: {
    'Accept': 'application/json',
    'Content-Type': 'application/json',
    'Authorization': 'Basic ' + (new Buffer.from(client_id + ':' + client_secret).toString('base64'))
  },
  method: "POST",
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

async function getTokenFetch () {
  return fetch("https://accounts.spotify.com/api/token", optionsFetch)
  .then(response => response.json())
  .then(data => { return data.access_token })
}

//Obtener información de un artista (modificar token cuando esté lista la funcion)
async function getArtistID(artist) {
  return fetch(baseURI + '/search?q=' + artist + '&type=artist', {
    headers: {
      'Accept': 'application/json',
      'Content-Type': 'application/json',
      'Authorization': 'Bearer ' + 'BQDK4VR-X8lVl5nrgHm842R3DyVZFcCBOrcuJx54oVpYnRcNaYN4suIqdusIQNh6uhyzwm-xiG0SeMW6AXXJsC01uO0PCGK6w5snoAwTE0XoBDjVhFQ'
    },
    json: true
  })
  .then(response => response.json())
  .then(data => { return data.artists.items[0].id })
}
console.table(await getArtistID("Sub-Zero-Project"))












