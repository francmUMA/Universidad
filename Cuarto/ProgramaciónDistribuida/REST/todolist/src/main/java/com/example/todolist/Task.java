package com.example.todolist;

public class Task {
    private int id;
    private String description;
    private String fechaHoraAgregado;
    private Status status;
    private String fechaHoraCompletado;
    private boolean eliminado;

    public Task(){}

    public int getId() {
        return id;
    }

    public String getFechaHoraAgregado() {
        return fechaHoraAgregado;
    }

    public String getFechaHoraCompletado() {
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

    public void setFechaHoraAgregado(String fechaHoraAgregado) {
        this.fechaHoraAgregado = fechaHoraAgregado;
    }

    public void setFechaHoraCompletado(String fechaHoraCompletado) {
        this.fechaHoraCompletado = fechaHoraCompletado;
    }

    public void setStatus(Status status) {
        this.status = status;
    }
}
