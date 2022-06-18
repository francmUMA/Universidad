package es.uma.rysd.app;

import javax.net.ssl.HttpsURLConnection;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLEncoder;
import java.util.ArrayList;

import com.google.gson.Gson;

import es.uma.rysd.entities.*;

public class SWClient {
	// TODO: Complete el nombre de la aplicaci�n
    private final String app_name = "Practica Bloque III";
    private final int year = 2022;
    
    private final String url_api = "https://swapi.dev/api/";

    // M�todos auxiliares facilitados
    
    // Obtiene la URL del recurso id del tipo resource
	public String generateEndpoint(String resource, Integer id){
		return url_api + resource + "/" + id + "/";
	}
	
	// Dada una URL de un recurso obtiene su ID
	public Integer getIDFromURL(String url){
		String[] parts = url.split("/");
		return Integer.parseInt(parts[parts.length-1]);
	}
	
	// Consulta un recurso y devuelve cu�ntos elementos tiene
	public int getNumberOfResources(String resource){    	
		// TODO: Trate de forma adecuada las posibles excepciones que pueden producirse
		try {
			// TODO: Cree la URL correspondiente: https://swapi.dev/api/{recurso}/ reemplazando el recurso por el par�metro
			URL url = new URL(url_api + resource + "/");

			// TODO: Cree la conexi�n a partir de la URL
			HttpsURLConnection connection = (HttpsURLConnection) url.openConnection();

			// TODO: A�ada las cabeceras User-Agent y Accept (vea el enunciado)
			connection.setRequestProperty("Accept", "application/json");
			connection.setRequestProperty("User-Agent", app_name + year);

			// TODO: Indique que es una petici�n GET
			connection.setRequestMethod("GET");
			
			// TODO: Compruebe que el c�digo recibido en la respuesta es correcto
			if (connection.getResponseCode() != 200){
				System.err.println("Error: " + connection.getResponseCode());
				return -1;
			} else {
				// TODO: Deserialice la respuesta a ResourceCountResponse
				Gson parser = new Gson();
				InputStream in = connection.getInputStream(); // TODO: Obtenga el InputStream de la conexi�n
				ResourceCountResponse c = parser.fromJson(new InputStreamReader(in), ResourceCountResponse.class);

				// TODO: Devuelva el n�mero de elementos
				return c.count;
			}
		} catch (IOException e) {
			e.printStackTrace();
			return -1;
		}
        
	}
	
	public Person getPerson(String urlname) {
    	Person p = null;
    	// Por si acaso viene como http la pasamos a https
    	urlname = urlname.replaceAll("http:", "https:");

    	// TODO: Trate de forma adecuada las posibles excepciones que pueden producirse
		try {
			// TODO: Cree la URL correspondiente
			URL url = new URL(urlname);

			// TODO: Cree la conexi�n a partir de la URL
			HttpsURLConnection connection = (HttpsURLConnection) url.openConnection();

			// TODO: A�ada las cabeceras User-Agent y Accept (vea el enunciado)
			connection.setRequestProperty("Accept", "application/json");
			connection.setRequestProperty("User-Agent", app_name + year);

			// TODO: Indique que es una petici�n GET
			connection.setRequestMethod("GET");
			
			// TODO: Compruebe que el c�digo recibido en la respuesta es correcto
			if (connection.getResponseCode() != 200){
				System.err.println("Error: " + connection.getResponseCode());
			}
			// TODO: Deserialice la respuesta a Person
			Gson parser = new Gson();
			InputStream in = connection.getInputStream(); // TODO: Obtenga el InputStream de la conexi�n
			p = parser.fromJson(new InputStreamReader(in), Person.class);

			// TODO: Para las preguntas 2 y 3 (no necesita completar esto para la pregunta 1)
			// TODO: A partir de la URL en el campo homreworld obtenga los datos del planeta y almac�nelo en atributo homeplanet
			Planet homPlanet = getPlanet(p.homeworld);
			p.homeplanet = homPlanet;
		} catch (Exception e) {
			e.printStackTrace();
		}
    	return p;
	}

	public Planet getPlanet(String urlname) {
    	Planet p = null;
    	// Por si acaso viene como http la pasamos a https
    	urlname = urlname.replaceAll("http:", "https:");
		// TODO: Trate de forma adecuada las posibles excepciones que pueden producirse
		try {
			// TODO: Cree la URL correspondiente
			URL url = new URL(urlname);

			// TODO: Cree la conexi�n a partir de la URL
			HttpsURLConnection connection = (HttpsURLConnection) url.openConnection();

			// TODO: A�ada las cabeceras User-Agent y Accept (vea el enunciado)
			connection.setRequestProperty("Accept", "application/json");
			connection.setRequestProperty("User-Agent", app_name + year);

			// TODO: Indique que es una petici�n GET
			connection.setRequestMethod("GET");
			
			// TODO: Compruebe que el c�digo recibido en la respuesta es correcto
			if (connection.getResponseCode() != 200){
				System.err.println("Error: " + connection.getResponseCode());
			}
    	
    		// TODO: Deserialice la respuesta a Planet
			Gson parser = new Gson();
			InputStream in = connection.getInputStream(); // TODO: Obtenga el InputStream de la conexi�n
			p = parser.fromJson(new InputStreamReader(in), Planet.class);

		} catch (Exception e) {
			e.printStackTrace();
		}
        return p;
	}

	public Film getFilm(String urlname){
		Film f = null;
		// Por si acaso viene como http la pasamos a https
		urlname = urlname.replaceAll("http:", "https:");
		try {
			// TODO: Cree la URL correspondiente
			URL url = new URL(urlname);

			// TODO: Cree la conexi�n a partir de la URL
			HttpsURLConnection connection = (HttpsURLConnection) url.openConnection();

			// TODO: A�ada las cabeceras User-Agent y Accept (vea el enunciado)
			connection.setRequestProperty("Accept", "application/json");
			connection.setRequestProperty("User-Agent", app_name + year);

			// TODO: Indique que es una petici�n GET
			connection.setRequestMethod("GET");
			
			// TODO: Compruebe que el c�digo recibido en la respuesta es correcto
			if (connection.getResponseCode() != 200){
				System.err.println("Error: " + connection.getResponseCode());
			}

			Gson parser = new Gson();
			InputStream in = connection.getInputStream(); // TODO: Obtenga el InputStream de la conexi�n
			f = parser.fromJson(new InputStreamReader(in), Film.class);

		} catch (Exception e){
			e.printStackTrace();
		}
		return f;

	}

	public Person search(String name){
    	Person p = null;
    	try {
			// TODO: Cree la URL correspondiente
			URL url = new URL(url_api + "people/?search=" + name + "/");

			// TODO: Cree la conexi�n a partir de la URL
			HttpsURLConnection connection = (HttpsURLConnection) url.openConnection();

			// TODO: A�ada las cabeceras User-Agent y Accept (vea el enunciado)
			connection.setRequestProperty("Accept", "application/json");
			connection.setRequestProperty("User-Agent", app_name + year);

			// TODO: Indique que es una petici�n GET
			connection.setRequestMethod("GET");
			
			// TODO: Compruebe que el c�digo recibido en la respuesta es correcto
			if (connection.getResponseCode() != 200){
				System.err.println("Error: " + connection.getResponseCode());
			}

			// TODO: Deserialice la respuesta a SearchResponse -> Use la primera posici�n del array como resultado
			Gson parser = new Gson();
			InputStream in = connection.getInputStream(); // TODO: Obtenga el InputStream de la conexi�n
			SearchResponse s = parser.fromJson(new InputStreamReader(in), SearchResponse.class);
			p = s.results[0];
			p.homeplanet = getPlanet(url.toString());
			Planet pl = new Planet();
			pl = getPlanet(p.homeworld);
			p.homeplanet = pl;
					
		} catch (Exception e) {
			e.printStackTrace();
		}
        return p;
    }

}
