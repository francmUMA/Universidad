from logging import error
import spotipy
import spotipy.util as util
from spotipy.oauth2 import SpotifyClientCredentials
from spotipy.oauth2 import SpotifyOAuth

#Hay que conseguir un client id para pioder realizar peticiones a la API
clientID = "fee6275da3ab4dd3ba15fd84725347df"
clientSecret = "c5cf39fc26304dc9a4b33492aed3299d"

#Crear el manager de gestion con los credenciales anteriormente conseguidos
manager = SpotifyClientCredentials(client_id=clientID, client_secret=clientSecret)
token = SpotifyOAuth(client_id=clientID, client_secret=clientSecret, redirect_uri='http://localhost:8888/callback')

#Asignamos el manager que vamos a usar
spotify_client = spotipy.Spotify(client_credentials_manager=manager)

#Lets play
def getUserURI(username):
    try:
        user = spotify_client.search(username, type='lists')
        print(user)
    except:
        print("No se ha podido obtener el id del usuario")

#Buscar playlists de un usuario
def get_playlists(username):
    try:
        playlists = spotify_client.user_playlists(username)
        for playlist in playlists['items']:
            print(playlist['name'])
    except:
        print("No se han podido obtener playlists")

getUserURI('jarito99')
#get_playlists(getUserURI('jarito99'))
