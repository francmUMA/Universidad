import "../styles/Navbar.css";

const Navbar = () => {
  return (
    <div id="navbar">
      <img
        alt=""
        className="spotify-logo"
        src={require("../images/Spotify_Logo_RGB_White.png")}
      />
      <button className="works-btn">How it works</button>
      <button className="about-btn">About</button>
    </div>
  );
};

export default Navbar;