import { BrowserRouter, Routes, Route } from "react-router-dom";
import Inicio from "./inicio.js";
import Home from "./home.js";

export default function App() {
  return (
    <BrowserRouter>
      <Routes>
        <Route path="/" element={<Home />} />
        <Route path="/inicio" element={<Inicio />} />
      </Routes>
    </BrowserRouter>
  );
}
