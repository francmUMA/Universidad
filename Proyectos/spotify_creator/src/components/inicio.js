import { useState, useEffect } from "react";

let client_id = "fee6275da3ab4dd3ba15fd84725347df";
let redirect_uri = "https://localhost:3000/inicio";
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

const getUserInfo = async (token) => {
  return fetch(baseURI + "/me", options(token))
    .then((response) => response.json())
    .then((data) => {
      return data;
    });
}

const Inicio = () => {
  let code = window.location.search.split("=")[1];
  const [token, setToken] = useState(null);
  const [user, setUser] = useState("");
  const backHome = () => {
    window.location.href = "/";
  };

  useEffect(() => {
    getToken(code).then(setToken);
  }, [code]);

  useEffect(() => {
    if (token != null) {
      getUserInfo(token).then((info) => {
        console.log(info);
        setUser(info);
      });
    }
  }, [token]);

  return (
    <div>
      <h1> Estas en la pagina de inicio </h1>
      <button onClick={backHome}>Vuelta al Home</button>
      <h2> El usuario es: {user.display_name} </h2>
      <h2> El email es: {user.email} </h2>
      <h2> El id es: {user.id} </h2>
    </div>
  );
};

export default Inicio;

