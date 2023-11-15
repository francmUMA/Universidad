package com.example.agenda;

import jakarta.ws.rs.GET;
import jakarta.ws.rs.Path;
import jakarta.ws.rs.Produces;
import jakarta.ws.rs.core.MediaType;
import jakarta.ws.rs.core.Response;

import java.awt.*;
import java.util.LinkedList;
import java.util.List;
@Path("/data")
public class AgendaResource {

    private static class Contacto{
        private String nombre;
        private String apellidos;
        private int number;
        private int id;
        public Contacto(String nombre, String apellidos, int number, int id){
            this.nombre = nombre;
            this.apellidos = apellidos;
            this.number = number;
            this.id = id;
        }
    }
    private final static List<Integer> agenda = new LinkedList<>();

    @GET
    @Produces("application/json")
    public Response getitemsJSON() {
        agenda.add(1);
        return Response.ok(new Contacto("Jose","Lopez",675262, 2), "application/json").build();
    }
}