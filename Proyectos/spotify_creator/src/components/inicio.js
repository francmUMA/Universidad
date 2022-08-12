import { useState, useEffect } from "react";
import Navbar from "./Navbar.js";

let client_id = "fee6275da3ab4dd3ba15fd84725347df";
let redirect_uri = "https://6rbnh9.csb.app/inicio";
let client_secret = "c5cf39fc26304dc9a4b33492aed3299d";
let baseURI = "https://api.spotify.com/v1";
let options = (token) => {
  return {
    headers: {
      Accept: "application/json",
      "Content-Type": "application/json",
      Authorization: "Bearer " + token
    }
  };
};

const getToken = async (code) => {
  return fetch("https://accounts.spotify.com/api/token", {
    method: "POST",
    body:
      "grant_type=authorization_code&code=" +
      code +
      "&redirect_uri=" +
      redirect_uri,
    headers: {
      "Content-Type": "application/x-www-form-urlencoded",
      Authorization:
        "Basic " +
        new Buffer.from(client_id + ":" + client_secret).toString("base64")
    }
  })
    .then((response) => response.json())
    .then((data) => {
      return data.access_token;
    });
};

const getUserID = async (token) => {
  return fetch(baseURI + "/me", options(token))
    .then((response) => response.json())
    .then((data) => {
      return data.id;
    });
};

const createPlaylist = async (token) => {
  let useToken = token;
  let userID = await getUserID(useToken);

  //Creación de la playlist
  let playlistID = await fetch(baseURI + "/users/" + userID + "/playlists", {
    method: "POST",
    body: JSON.stringify({
      name: "The HARDEST playlist",
      description: "Playlist creada por javascript",
      public: false
    }),
    headers: {
      Accept: "application/json",
      "Content-Type": "application/json",
      Authorization: "Bearer " + useToken
    }
  })
    .then((response) => {
      if (response.status >= 200 && response.status < 300) {
        console.log("Playlist creada");
      } else {
        console.log("Error al crear playlist");
      }
      return response.json();
    })
    .then((data) => data.id);

  //Añadir canciones a la playlist
  let artistIDs = "4AGDRCSqrobTOwmsvPuSrC"; //Fraw
  let trackList = [];
  while (trackList.length < 2000) {
    let tracksFullInfo = await fetch(
      "https://api.spotify.com/v1/recommendations?limit=50&market=ES&seed_artists=" +
        artistIDs +
        "&seed_genres=hardstyle&seed_tracks=14Zge11a2WwpKq0GX31ked",
      options(useToken)
    )
      .then((response) => response.json())
      .then((json) => json.tracks);
    if (tracksFullInfo !== undefined) {
      tracksFullInfo.map(async (recommendation) => {
        let albumTracks = await getAlbumTracks(
          useToken,
          recommendation.album.id
        );
        if (albumTracks !== undefined) {
          albumTracks.forEach(async (track) => {
            //Comprobar si la cancion no esta en la playlist
            if (!trackList.includes(track.uri)) {
              trackList.push(track.uri);
            }
          });
        }
      });
    }
  }
  console.log(trackList.length);
  let inicio = 0;
  let fin = 0;
  while (inicio < trackList.length) {
    let test = [];
    if (trackList.length - fin < 100) {
      fin += trackList.length - fin;
    } else {
      fin += 100;
    }
    for (let i = inicio; i < fin; i++) {
      test.push(trackList[i]);
    }
    await fetch(baseURI + "/playlists/" + playlistID + "/tracks?uris=" + test, {
      method: "POST",
      headers: {
        Accept: "application/json",
        "Content-Type": "application/json",
        Authorization: "Bearer " + useToken
      }
    }).then((response) => {
      if (response.status >= 200 && response.status < 300) {
        console.log("añadido correctamente");
      }
    });
    inicio = fin;
  }

  return trackList;
};

const getAlbumTracks = async (token, id) => {
  return fetch(baseURI + "/albums/" + id + "/tracks?limit=50", options(token))
    .then((response) => response.json())
    .then((items) => items.items);
};

const getPlaylists = async (token) => {
  let allData = [];
  let offset = 0;
  let res = await fetch(
    baseURI + "/me/playlists?limit=50&offset=" + offset,
    options(token)
  )
    .then((response) => response.json())
    .then((json) => {
      return json;
    });
  res.items.forEach((element) => {
    allData.push(element);
  });
  while (res.total > allData.length) {
    offset += 50;
    res = await fetch(
      baseURI + "/me/playlists?limit=50&offset=" + offset,
      options(token)
    )
      .then((response) => response.json())
      .then((json) => {
        return json;
      });
    res.items.forEach((element) => {
      allData.push(element);
    });
  }
  return allData;
};

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

