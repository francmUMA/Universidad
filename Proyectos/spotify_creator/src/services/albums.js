import { SPOTIFY as sp, options } from "../.env";

export const getAlbumTracks = async (token, albumID) => {
    return fetch(sp.baseURI + "/albums/" + albumID + "/tracks?limit=50", options(token))
      .then((response) => response.json())
      .then((items) => items.items);
};