package com.example.todolist;

import java.util.Date;

public class Task {
    private int id;
    private String description;
    private Date fechaHoraAgregado;
    private Status status;
    private Date fechaHoraCompletado;
    private boolean eliminado;

    public Task(){}

    public Task(String description){
        this.description = description;
        this.id = -1;
        fechaHoraAgregado.getTime();
        fechaHoraCompletado = null;
        this.status = Status.INCOMPLETA;
        this.eliminado = false;
    }

    public int getId() {
        return id;
    }

    public Date getFechaHoraAgregado() {
        return fechaHoraAgregado;
    }

    public Date getFechaHoraCompletado() {
        return fechaHoraCompletado;
    }

    public Status getStatus() {
        return status;
    }

    public String getDescription() {
        return description;
    }

    public boolean getEliminado(){
        return eliminado;
    }

    public void setId(int id) {
        this.id = id;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public void setEliminado(boolean eliminado) {
        this.eliminado = eliminado;
    }

    public void setFechaHoraAgregado(Date fechaHoraAgregado) {
        this.fechaHoraAgregado = fechaHoraAgregado;
    }

    public void setFechaHoraCompletado(Date fechaHoraCompletado) {
        this.fechaHoraCompletado = fechaHoraCompletado;
    }

    public void setStatus(Status status) {
        this.status = status;
    }
}
