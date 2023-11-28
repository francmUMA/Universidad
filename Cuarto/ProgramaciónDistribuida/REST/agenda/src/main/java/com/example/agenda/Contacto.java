package com.example.agenda;

public class Contacto{
    private String nombre;
    private String apellidos;
    private int number;
    private int id;

    public Contacto(){}

    public Contacto(String nombre, String apellidos, int number){
        this.nombre = nombre;
        this.apellidos = apellidos;
        this.number = number;
        id = 1;
    }

    public void setId(int id) {
        this.id = id;
    }

    public void setNombre(String nombre) {
        this.nombre = nombre;
    }

    public void setApellidos(String apellidos) {
        this.apellidos = apellidos;
    }

    public void setNumber(int number) {
        this.number = number;
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
