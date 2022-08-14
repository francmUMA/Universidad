export const SPOTIFY = {
    client_id: "fee6275da3ab4dd3ba15fd84725347df",
    client_secret: "c5cf39fc26304dc9a4b33492aed3299d",
    redirect_uri: "http://localhost:3000/inicio",
    baseURI: "https://api.spotify.com/v1",
    scopes: "user-read-private user-read-email playlist-read-private user-top-read playlist-modify-public playlist-modify-private"
}

export const authorization_link = "https://accounts.spotify.com/authorize?client_id=" + SPOTIFY.client_id +
"&response_type=code&redirect_uri=" + SPOTIFY.redirect_uri +
"&scope=" + SPOTIFY.scopes;

export const options = (token) => {
    return {
        headers: {
            Accept: "application/json",
            "Content-Type": "application/json",
            Authorization: "Bearer " + token
        }
    }
}