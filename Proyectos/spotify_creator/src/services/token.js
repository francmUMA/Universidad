export const getToken = async (code) => {
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