enable
configure terminal

router eigrp @AS
no auto-summary                 # Deshabilita el resumen automático
network @IP                     # network 192.168.2.1 0.0.0.0
passive-interface @INTERFACE    # No enviar paquetes EIGRP por la interfaz --- passive-interface fastethernet 0/0.100
exit