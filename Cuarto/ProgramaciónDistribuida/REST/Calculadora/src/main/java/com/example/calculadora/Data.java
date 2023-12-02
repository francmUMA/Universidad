package com.example.calculadora;

public class Data {
    private String operacion;
    private int operando_1;
    private int operando_2;
    private int resultado;

    public Data() {
    }

    public Data(int operando_1, int operando_2) {
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

    public void setOperando_1(int operando_1) {
        this.operando_1 = operando_1;
    }

    public void setOperando_2(int operando_2) {
        this.operando_2 = operando_2;
    }

    public void setResultado(int resultado) {
        this.resultado = resultado;
    }
}
