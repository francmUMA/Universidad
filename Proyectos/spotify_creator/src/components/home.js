import "../styles/home.css";
import Navbar from "./Navbar.js";
import { client_id } from "../env.js";

let redirect_uri = "https://6rbnh9.csb.app/inicio";
let scopes =
  "user-read-private user-read-email playlist-read-private user-top-read playlist-modify-public playlist-modify-private";
let authorization_link =
  "https://accounts.spotify.com/authorize?client_id=" +
  client_id +
  "&response_type=code&redirect_uri=" +
  redirect_uri +
  "&scope=" +
  scopes;

const Home = () => {
  const login = () => {
    window.location.href = authorization_link;
  };

  return (
    <div id="main">
      <Navbar />
      <div id="login-body">
        <h1 className="description">
          Make personalized playlists with your favourite artists, songs or
          discover new music with playlists based on your musical tastes.
        </h1>
        <button onClick={login} className="spotify-btn">
          {client_id}
        </button>
      </div>
    </div>
  );
};

export default Home;