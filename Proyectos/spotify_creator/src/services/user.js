let options = (token) => {
    return {
      headers: {
        Accept: "application/json",
        "Content-Type": "application/json",
        Authorization: "Bearer " + token
      }
    };
  };

export const getUserID = async (token) => {
    return fetch(process.env.BASE_URI + "/me", options(token))
        .then((response) => response.json())
        .then((json) => {
            return json.id;
        }).catch((error) => {
            console.log(error);
        }
        );
}