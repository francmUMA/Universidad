import { BrowserRouter, Routes, Route } from "react-router-dom";
import { Inicio } from "./components/inicio.js";

let client_id = "fee6275da3ab4dd3ba15fd84725347df"
let redirect_uri = 'http://localhost:3000/inicio'
let scopes = "user-read-private user-read-email playlist-read-private user-top-read playlist-modify-public playlist-modify-private"
let authorization_link = 'https://accounts.spotify.com/authorize?client_id=' + client_id + '&response_type=code&redirect_uri=' + redirect_uri + '&scope=' + scopes

function Home() {
  const loginSpotify = () => {
    window.location.href = authorization_link
  }
  return (
    <div>
      <h1>Home</h1>
      <button onClick={ loginSpotify }>Loguee con Spotify</button>
    </div>
  )
}

function App() {
  return (
    <BrowserRouter>
      <Routes>
        <Route path="/" element={<Home />} />
        <Route path="/inicio" element={<Inicio />} />
      </Routes>
    </BrowserRouter>
  )
}

export default App;
