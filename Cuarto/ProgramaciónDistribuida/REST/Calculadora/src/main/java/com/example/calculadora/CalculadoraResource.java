package com.example.calculadora;

import jakarta.ws.rs.Consumes;
import jakarta.ws.rs.GET;
import jakarta.ws.rs.Path;
import jakarta.ws.rs.Produces;
import jakarta.ws.rs.core.MediaType;
import jakarta.ws.rs.core.Response;

@Path("/")
public class CalculadoraResource {
    public static class Data{
        private String operacion;
        private int operando_1;
        private int operando_2;
        private int resultado;
        public Data(){}

        public Data(int operando_1, int operando_2){
            this.operacion = "";
            this.operando_1 = operando_1;
            this.operando_2 = operando_2;
            this.resultado = 0;
        }

        public String getOperacion() {
            return operacion;
        }

        public int getOperando_1() {
            return operando_1;
        }

        public int getOperando_2() {
            return operando_2;
        }

        public int getResultado() {
            return resultado;
        }

        public void setOperacion(String operacion) {
            this.operacion = operacion;
        }

        public void setOperando1(int operando_1) {
            this.operando_1 = operando_1;
        }

        public void setOperando2(int operando_2) {
            this.operando_2 = operando_2;
        }

        public void setResultado(int resultado) {
            this.resultado = resultado;
        }
    }
    @GET
    @Path("/suma")
    @Consumes(MediaType.APPLICATION_JSON)
    @Produces(MediaType.APPLICATION_JSON)
    public Response suma(Data d) {
        Data res = new Data(10, 12);
        res.setOperacion("suma");
        res.setResultado(10 + 12);
        return Response.ok(res).build();
    }
}