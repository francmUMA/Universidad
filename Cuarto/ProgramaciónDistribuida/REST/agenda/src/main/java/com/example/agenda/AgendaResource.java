package com.example.agenda;

import jakarta.json.bind.Jsonb;
import jakarta.json.bind.JsonbBuilder;
import jakarta.ws.rs.*;
import jakarta.ws.rs.core.MediaType;
import jakarta.ws.rs.core.Response;

import java.util.LinkedList;
import java.util.List;
@Path("/data")
public class AgendaResource {
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
    public Response newRegister(Contacto c){
        c.setId(agenda.size());
        agenda.add(c);
        return Response.ok().build();
    }

    @PUT
    @Path("/{id}")
    @Consumes(MediaType.APPLICATION_JSON)
    @Produces("text/plain")
    public Response updateRegister(@PathParam("id") int id, Contacto c){
        if (id < agenda.size() && id >= 0){
            c.setId(id);
            agenda.remove(id);
            agenda.add(id, c);
            return Response.ok("Contacto actualizado correctamente").build();
        } else {
            return Response.ok("El identificador es incorrecto", "text/plain").build();
        }
    }
}