package com.example.todolist;

import jakarta.ws.rs.*;
import jakarta.ws.rs.core.MediaType;
import jakarta.ws.rs.core.Response;

import java.time.LocalDateTime;
import java.util.LinkedList;
import java.util.List;

@Path("/todolist")
public class TodolistResource {
    private static final List<Task> taskList = new LinkedList<>();
    @POST
    @Path("/add")
    @Consumes(MediaType.APPLICATION_JSON)
    public Response addTask(Task t) {
        t.setId(taskList.size());
        t.setFechaHoraAgregado(LocalDateTime.now().toString());
        t.setFechaHoraCompletado("");
        t.setStatus(Status.INCOMPLETA);
        t.setEliminado(false);
        taskList.add(t);
        return Response.ok().build();
    }

    @PUT
    @Path("/complete/{id}")
    @Produces("text/plain")
    public Response updateTask(@PathParam("id") int id){
        if (id >= taskList.size()) return Response.ok("El id que has indicado no existe").build();
        if (taskList.get(id).getStatus() == Status.COMPLETADA) return Response.ok("La tarea ya estaba completada").build();
        taskList.get(id).setStatus(Status.COMPLETADA);
        taskList.get(id).setFechaHoraCompletado(LocalDateTime.now().toString());
        return Response.ok().build();
    }

    @PUT
    @Path("/delete/{id}")
    @Produces("text/plain")
    public Response removeTask(@PathParam("id") int id){
        if (id >= taskList.size()) return Response.ok("El id que has indicado no existe").build();
        if (taskList.get(id).getEliminado()) return Response.ok("La tarea ya estaba terminada").build();
        taskList.get(id).setEliminado(true);
        return Response.ok().build();
    }

    @GET
    @Path("/all")
    @Produces(MediaType.APPLICATION_JSON)
    public Response getAllTasks(){
        return Response.ok(taskList, MediaType.APPLICATION_JSON).build();
    }


    @GET
    @Path("/{id}")
    @Produces({MediaType.APPLICATION_JSON, "text/plain"})
    public Response getTask(@PathParam("id") int id){
        if (id >= taskList.size()) return Response.ok("El id que has indicado no existe").build();
        return Response.ok(taskList.get(id), MediaType.APPLICATION_JSON).build();
    }
}