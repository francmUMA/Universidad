import { useState, useEffect } from "react";
import Navbar from "./Navbar.js";
import { getToken } from "../services/token.js"
import { createPlaylist, getPlaylists } from "../services/playlist.js"

const Inicio = () => {
  let code = window.location.search.split("=")[1];
  const [token, setToken] = useState(null);
  const [playlists, setPlaylists] = useState([]);
  const [tracks, setTracks] = useState([]);

  const backHome = (link) => {
    window.location.href = link;
  };

  useEffect(() => {
    if (token == null) getToken(code).then(setToken);
  }, [code, token]);

  useEffect(() => {
    if (token != null) {
      Promise.resolve(getPlaylists(token)).then(setPlaylists);
    }
  }, [token]);

  useEffect(() => {
    if (token != null) {
      Promise.resolve(createPlaylist(token)).then(setTracks);
    }
  }, [token]);

  const ListPlaylist = () => {
    console.log(playlists);
    return (
      <ul>
        {playlists.map((playlist) => {
          console.log(playlist.images[0]);
          return (
            <>
              <img
                className="img-playlist"
                alt=""
                src={playlist.images[0].url}
              />
              <li>{playlist.name}</li>
            </>
          );
        })}
      </ul>
    );
  };

  const Creator = () => {
    console.log(tracks);
  };

  return (
    <div id="main">
      <Navbar />
      <Creator />
      <button
        onClick={() => {
          return backHome("/");
        }}
      >
        Volver al menú principal
      </button>
    </div>
  );
};

export default Inicio;

