let options = (token) => {
    return {
      headers: {
        Accept: "application/json",
        "Content-Type": "application/json",
        Authorization: "Bearer " + token
      }
    };
  };

export const getAlbumTracks = async (token, albumID) => {
    return fetch(process.env.BASE_URI + "/albums/" + albumID + "/tracks?limit=50", options(token))
      .then((response) => response.json())
      .then((items) => items.items);
  };