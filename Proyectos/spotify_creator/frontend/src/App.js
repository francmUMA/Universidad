import './App.css';

let client_id = "fee6275da3ab4dd3ba15fd84725347df"
let redirect_uri = 'http://localhost:3000/inicio'
let scopes = "user-read-private user-read-email playlist-read-private user-top-read playlist-modify-public playlist-modify-private"
let authorization_link = 'https://accounts.spotify.com/authorize?client_id=' + client_id + '&response_type=code&redirect_uri=' + redirect_uri + '&scope=' + scopes

function App() {
  return (
    <div className="App">
      <button onClick={authorization_link}> Log in spotify </button>
    </div>
  );
}

export default App;
