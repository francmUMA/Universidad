import { getAlbumTracks } from "./albums";
import { getUserID } from "./user";
import { SPOTIFY as sp, options } from "../.env";

export const createPlaylist = async (token) => {
    let useToken = token;
    let userID = await getUserID(token);
  
    //Creación de la playlist
    let playlistID = await fetch(sp.baseURI + "/users/" + userID + "/playlists", {
      method: "POST",
      body: JSON.stringify({
        name: "The HARDEST playlist",
        description: "Playlist creada por javascript",
        public: false
      }),
      headers: {
        Accept: "application/json",
        "Content-Type": "application/json",
        Authorization: "Bearer " + token
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
        options(token)
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
      await fetch(sp.baseURI + "/playlists/" + playlistID + "/tracks?uris=" + test, {
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

export const getPlaylists = async (token) => {
    let allData = [];
    let offset = 0;
    let res = await fetch(
      sp.baseURI + "/me/playlists?limit=50&offset=" + offset,
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
        sp.baseURI + "/me/playlists?limit=50&offset=" + offset,
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