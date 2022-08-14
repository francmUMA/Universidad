import { SPOTIFY as sp, options } from "../.env";

export const getUserID = async (token) => {
    return fetch(sp.baseURI + "/me", options(token))
        .then((response) => response.json())
        .then((json) => {
            return json.id;
        }).catch((error) => {
            console.log(error);
        }
        );
}