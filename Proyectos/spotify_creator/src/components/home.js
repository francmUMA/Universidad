import "../styles/home.css";

let client_id = "fee6275da3ab4dd3ba15fd84725347df";
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
      <h1 className="name"> WEBSITE NAME </h1>
      <span className="description"> description website </span>
      <br />
      <h1> Inicia sesión con tu cuenta de Spotify </h1>
      <button onClick={login} className="spotify-btn">
        Login with spotify
      </button>
    </div>
  );
};

export default Home;