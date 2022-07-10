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

//Petición del token de spotify (PENDIENTE)
const token = () => {
  let token = ""
  request.post(options, (error, response, body) => {
    if (!error && response.statusCode === 200) {
      token = body.access_token
      console.log(token)
    } 
  })
  return token
}

//Obtener información de un artista (modificar token cuando esté lista la funcion)
const artistInfo = async (artist) =>{
  let res = ""
  await fetch(baseURI + '/search?q=' + artist + '&type=artist', {
    headers: {
      'Accept': 'application/json',
      'Content-Type': 'application/json',
      'Authorization': 'Bearer ' + 'BQBg0Ej76DE7Iko5BuggNrzCgDuYXUginAIlh-dHIN4V4AExrdKLjXpKx5jR0i9p_FVSy-YckRORtKrd7FcUSng1IV6ONeerez55zMPGUMTbvc_MZAQ'
    },
    json: true
  })
  .then(response => response.json())
  .then(data => {
    res = data.artists.items[0].id
  })
  return res
}




