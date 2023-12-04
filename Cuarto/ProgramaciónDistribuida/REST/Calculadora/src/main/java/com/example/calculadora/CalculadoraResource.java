package com.example.calculadora;

import jakarta.ws.rs.*;
import jakarta.ws.rs.core.MediaType;
import jakarta.ws.rs.core.Response;

@Path("/")
public class CalculadoraResource {

    @GET
    @Path("/suma")
    //@Consumes(MediaType.APPLICATION_JSON)
    @Produces(MediaType.APPLICATION_JSON)
    public Response sumaJSON() {
        Data res = new Data(10,12);
        res.setOperacion("suma");
        res.setResultado(22);
        return Response.ok(res, MediaType.APPLICATION_JSON).build();
    }

    @GET
    @Path("/suma/{operando1}/{operando2}")
    @Produces(MediaType.APPLICATION_XML)
    public Response sumaXML(@PathParam("operando1") int operando1, @PathParam("operando2") int operando2) {
        Data res = new Data(operando1, operando2);
        res.setOperacion("suma");
        res.setResultado(operando1+operando2);

        return Response.ok(res, MediaType.APPLICATION_XML).build();
    }

    @POST
    @Path("/resta")
    @Consumes(MediaType.APPLICATION_JSON)
    @Produces(MediaType.APPLICATION_JSON)
    public Response restaJSON(Data d) {
        d.setOperacion("resta");
        d.setResultado(d.getOperando_1() - d.getOperando_2());
        return Response.ok(d, MediaType.APPLICATION_JSON).build();
    }

    @GET
    @Path("/resta/{operando1}/{operando2}")
    @Produces(MediaType.APPLICATION_XML)
    public Response restaXML(@PathParam("operando1") int operando1, @PathParam("operando2") int operando2) {
        Data res = new Data(operando1, operando2);
        res.setOperacion("resta");
        res.setResultado(operando1-operando2);
        return Response.ok(res, MediaType.APPLICATION_XML).build();
    }
}