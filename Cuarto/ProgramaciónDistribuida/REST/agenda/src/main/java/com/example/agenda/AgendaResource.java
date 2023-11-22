package com.example.agenda;

import jakarta.json.bind.Jsonb;
import jakarta.json.bind.JsonbBuilder;
import jakarta.ws.rs.*;
import jakarta.ws.rs.core.MediaType;
import jakarta.ws.rs.core.Response;
import netscape.javascript.JSObject;
import java.awt.*;
import java.util.LinkedList;
import java.util.List;
@Path("/data")
public class AgendaResource {

    public static class Contacto{
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

        public String getNombre() {
            return nombre;
        }

        public String getApellidos() {
            return apellidos;
        }

        public int getNumber() {
            return number;
        }

        public int getId() {
            return id;
        }
    }
    private static final List<Contacto> agenda = new LinkedList<>();

    @GET
    @Produces("application/json")
    public Response getitemsJSON() {
        Jsonb json = JsonbBuilder.create();
        return Response.ok(json.toJson(agenda), MediaType.APPLICATION_JSON).build();
    }

    @GET
    @Path("/count")
    @Produces("text/plain")
    public Response getCount(){
        return Response.ok(agenda.size(), "text/plain").build();
    }

    @GET
    @Path("/{id}")
    @Produces("application/json")
    public Response getElem(@PathParam("id") int id){
        Jsonb json = JsonbBuilder.create();
        return Response.ok(json.toJson(agenda.get(id)), "text/plain").build();
    }

    @POST
    @Consumes("application/json")
    public void newRegister(String json){
        Jsonb jsonb = JsonbBuilder.create();
        String name = jsonb.fromJson(json, String.class);
        agenda.add(new Contacto(name, "Cano", 1, 1));
    }
}