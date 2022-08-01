let client_id = "fee6275da3ab4dd3ba15fd84725347df"
let client_secret = "c5cf39fc26304dc9a4b33492aed3299d"
let redirect_uri = 'http://localhost:3000/inicio'

//Obtiene el token de uso de las peticiones
async function getToken(code) {
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

export function Inicio() {
  let code = window.location.search.split('=')[1]
  const token = async () => {
    return await getToken(code)
  }

  return (
    <div>
      <h1> Inicio </h1>
      <h2> { token } </h2>
    </div>
  )
}

