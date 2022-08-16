import { useState, useEffect } from "react";
import Navbar from "./Navbar.js";
import { getToken } from "../services/token.js"
import { Sidebar } from "./Sidebar"

const Inicio = () => {
  let code = window.location.search.split("=")[1];
  const [token, setToken] = useState(null);
  const [tracks, setTracks] = useState([]);

  const backHome = (link) => {
    window.location.href = link;
  };

  useEffect(() => {
    if (token == null) getToken(code).then(setToken);
  }, [code, token]);

  return (
    <div id="main">
      <Navbar />
      <Sidebar token={token} />
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

