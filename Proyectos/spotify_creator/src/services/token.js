import { SPOTIFY as sp } from '../.env';
import { Buffer } from 'buffer';

export const getToken = async (code) => {
    return fetch("https://accounts.spotify.com/api/token", {
      method: "POST",
      body:
        "grant_type=authorization_code&code=" +
        code +
        "&redirect_uri=" +
        sp.redirect_uri,
      headers: {
        "Content-Type": "application/x-www-form-urlencoded",
        Authorization:
          "Basic " +
          new Buffer.from(sp.client_id + ":" + sp.client_secret).toString("base64")
      }
    })
      .then((response) => response.json())
      .then((data) => {
        return data.access_token;
      });
  };