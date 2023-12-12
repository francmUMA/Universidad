#!/bin/bash

# Preparación de certificado
mkdir -p /etc/docker/certs.d/dockreg.ho.ac.uma.es
touch /etc/docker/certs.d/dockreg.ho.ac.uma.es/ca.crt
echo "-----BEGIN CERTIFICATE-----
MIIFRjCCAy6gAwIBAgIJAJQtulcK821/MA0GCSqGSIb3DQEBCwUAMGMxCzAJBgNV
BAYTAkVTMQ8wDQYDVQQIDAZNYWxhZ2ExDzANBgNVBAcMBk1hbGFnYTEMMAoGA1UE
CgwDVU1BMQswCQYDVQQLDAJBQzEXMBUGA1UEAwwORG9ja2VyX1Rlc3QgQ0EwHhcN
MjAwNTAzMTUzNDI3WhcNMzAwNTAxMTUzNDI3WjAfMR0wGwYDVQQDDBRkb2NrcmVn
LmhvLmFjLnVtYS5lczCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBALU9
d2YI2pAomFIFVUMJZrPXmR7elilhOC6pyHXuEhFTHxKgMl+i/iJTbVqvGpG/SJ5y
o9K5dSO7cskKwP5+WHbygoJnBivrDqkdBrYaOtlTgMw1yNB+b2qjwd8clEpsJOtk
HB/VZC2BZYSlCbgR62OQGUnkDLKC6R4TlOLs5Rl0hteOJuRrv99um5yVd0H0azVT
9BZdqmB9czRly1/trNL3pd9UoIMwEVATdRAcE/j2FdYj5LAuv4Jc5/xPiQ8pMCfj
myhTFgk4ZdsAh6fJlcoxZQg8Q4eDqwSQhDUKUx146yM1PYNRIV0oTv3ChlK/Tzse
mNrpMKN1Ju6pUHmS6ZJ+6BKQagctqUZjFCCepiOs2411pKU7MisFer5EmEjAQ2Ck
SSnPyGUhqmPqW9NrWhXgw88sNqAE1G2Sn1biJ++zDjb9jZ6k7SfHGqc09inDK+5c
VPj4x+UETuterLKP0KbmSuC1Nou56r7ibfnVRq59pkXVTL/1b4XCNDwsD04QM3In
m3sP65RX3VxVNWDk8e1fJiDgSBz2rG9eYqydOBKn2xzjMxxHpJ2UWGwJ7EW78sgg
KTbZjCKH0DcK8E9qaqbVtDZfW2vKfd2eOJqqT8FjN4nDdCJzCMXkFtIKgjtYSrUE
N0S0Ed2492JxQgTqS0T4Qd6r2oX89j0/ocM498pNAgMBAAGjQTA/MCgGA1UdEQQh
MB+CFGRvY2tyZWcuaG8uYWMudW1hLmVzggdkb2NrcmVnMBMGA1UdJQQMMAoGCCsG
AQUFBwMBMA0GCSqGSIb3DQEBCwUAA4ICAQBjs0xQ488HG56X5/BxQQ8T0yDjI8QO
BO+JzjQvhdiU+PF7UkFRBpbs3upsJylGDjCR2kMR/HxO/emcWVDnZQhdgmqZIjth
x2OT99+/F+9MxTaRueMWgi+1cM86/APCEAHm/KL004M/EzgTgX3XQQIHf5yG+ZzA
FnTSDpPg+WdyMd3lY5DsSjyOw/ZUM7f7iLwHAhSkY1gIFmhXAi/DHspqQwo+SQKx
HqnYUwX7bYvCcSzNs5jOpdOo5h2nqaqdvQ++n7LzbJmQm9t+ZntMAcNto7BzoXoQ
l7SBKnwZAcnAPE/ZudLxPRjjci2O8jYx4/bYUzpRKL0PPio6gaw+BrW/8IjsFsVw
7P2yuac7vcLMSqSSEqELjxp4w4wh7C/9/mH9RuDUOmNLiAuzTD+QxnAsalGq/81K
5pe3fhkUhUgTZMZIZ8w41LizlRcMoyrPGE9VLixT+347xcVvzhIVjnD7YpbgN0dM
17uacjd3bP9sFtFlwpLSv2bZRKD1IlWuTl2GWL07+Ghnxwv9CUjdlEdDIqBjOYNe
5rIOXaCaYvLsxFGAgY3jM4S0wxOHNf+kaDNPlJbVC48NWrCjCXxh35my/kdrsbp1
wTjJ4DJZHkLyNYoo59wGJ9BptdyLXO/ob3D6B/AoXZNi4hudxL2ZLY5IK7eQat1g
qDaaAII59cwKNw==
-----END CERTIFICATE-----
-----BEGIN CERTIFICATE-----
MIIFmTCCA4GgAwIBAgIJAKm09hXW3Q1fMA0GCSqGSIb3DQEBCwUAMGMxCzAJBgNV
BAYTAkVTMQ8wDQYDVQQIDAZNYWxhZ2ExDzANBgNVBAcMBk1hbGFnYTEMMAoGA1UE
CgwDVU1BMQswCQYDVQQLDAJBQzEXMBUGA1UEAwwORG9ja2VyX1Rlc3QgQ0EwHhcN
MTkwMjE2MTIzMjAxWhcNMjkwMjEzMTIzMjAxWjBjMQswCQYDVQQGEwJFUzEPMA0G
A1UECAwGTWFsYWdhMQ8wDQYDVQQHDAZNYWxhZ2ExDDAKBgNVBAoMA1VNQTELMAkG
A1UECwwCQUMxFzAVBgNVBAMMDkRvY2tlcl9UZXN0IENBMIICIjANBgkqhkiG9w0B
AQEFAAOCAg8AMIICCgKCAgEAxfbYRSieAjOggjABJxbqxrYsC0xIGVPc25ab+V3L
o1OR6/Aos48p14adRCcUMq3fbqNdORYNlIgPi0tFD32qJ4g8DWbXt+/txK2LoNrG
dHLN7kl7MgzWjHr4a1BKbGiQTNHkz3VBotDQ7syTrkgL6QAPKj/nQivxTsdGJMSr
W9XxmUlj+O8EjTS40SxPy7i5dgQJf6342UZ3s+QOTT3J/X6GuQSnuqeY8UkAQ6kC
a3jmEzViO7t4xRaUpVLCekrwW5B8DntoO1hLnBEC+KwlcHgCHo+DErsDHBNGDvfm
TDBnbi4vjyHTz/txX2ZCr6HSWlolwQcCm70Kd3oIjf4SmYlIxJgJvTm10KRbW4sK
dQgpzGBo0WF8k/70X9sqn/NCEFh3oQPS3GwQGsgi1brtBpVT2SFtCwyg5J69cf8a
eJLX2Yk9wnBtTCPuXioOjOq1jO721ols1WRfouP1hYKxU+vbCC1viAaI1GVbBbpV
nxA/BBrTBPNEZRGhIhj07jsBmHywgdsDatJrK8GuwJqIivNURVa+pUvsNiydsoHe
62icrkLDjCIDoBt4RPuIS894cajDzwodXmAkNm8YGI4vNhJWizDlK8r94H7yYUIn
VSPi81l2PTZGMKMAwjE9JypWRWvhia9Vo6S6EUt9jTiF1XDajIWIIFIKmMBLCaCh
S2MCAwEAAaNQME4wHQYDVR0OBBYEFO/qoawjJVougNr6umcqMriyA9LUMB8GA1Ud
IwQYMBaAFO/qoawjJVougNr6umcqMriyA9LUMAwGA1UdEwQFMAMBAf8wDQYJKoZI
hvcNAQELBQADggIBABthpLmGZnjbYA3Jommc3VA+nBRgu9OsbXTQl2paxTgKZhKR
9kqbjhiUG8SW3JBPYu+yJeY0r8Y32p5N6ymwg4AnueQ2sTv3IktqdNHwdp+yoefb
OO1mgUeqwUphRIY07+bXOe7li9t3CErPCdNqzd7/4SRW3vS/vDRmoCsFydZPBqEB
2ydfFsZDl3PznqC+sV4bE17CkGKUe7a6iK6bS2Ka7+4xgdfrQJqcp73mKnDRSqOI
0wP2FLZ5kCbKKaiFbuZO1B43QXSPdfxkdoTK/JfqMwauK2s/WG8wxmvLp89Zd01g
0ojCe4yQd2/euXJtg7HcZpE9PhwIqxmNSWsIwxQPrbIt/up7+EE3K6dHb/t9fEvt
QlO6kq3yEMb2V3kqiEjuJKAiz6ukzX+3IWl4QKzjWD374pDXN0xRypVd35SJ/TTZ
ByyTODNKbxtcVRICsD99bS3hslMe5uwFq+b85tJx7p1FT5+gb89Shk83Z+o2xj4s
0LCXH3+MMhcg2/kcPyBG8rin8+pAGmSWEOk4owXHmbeJFmKRc77MAQzkOmwhbHtB
0+U7t36Kz273smZEhRtrdwJNMbm66v8ZAQfjA28UDh6Tf564H4/LcFONmcHHEz5E
eYPGU0IJsvcSH1re09XgF1hcQk70X5U6TyqozPYWUfEBCGm/pzqlWxjpNUQ9
-----END CERTIFICATE-----" > /etc/docker/certs.d/dockreg.ho.ac.uma.es/ca.crt

# Añadir registro de docker
touch /etc/docker/daemon.json
echo '{
  "registry-mirrors" : ["https://dockreg.ho.ac.uma.es"],
  "bip" : "10.253.0.1/25"
}' > /etc/docker/daemon.json

# Reiniciar docker
service docker restart
service nfsclient start
rc-update add nfsclient
rc-update add docker

# Preparar NFS
mkdir /wp-data
mount 10.0.16.42:/shared/wordpress /wp-data

# Correr container de wordpress
WORDPRESS_DB_HOST=10.0.16.50
WORDPRESS_DB_USER=wordpress
WORDPRESS_DB_PASSWORD='Vc0910$$'
WORDPRESS_DB_NAME=wordpress

docker run --name wordpress --rm -d -p 8080:80 -e WORDPRESS_DB_HOST=$WORDPRESS_DB_HOST -e WORDPRESS_DB_USER=$WORDPRESS_DB_USER -e WORDPRESS_DB_PASSWORD=$WORDPRESS_DB_PASSWORD -e WORDPRESS_DB_NAME=$WORDPRESS_DB_NAME -v /wp-data:/var/www/html/wp-content wordpress:5.8.3-php7.4-apache

####### CONFIGURACIÓN DE CLUSTER CON SWARM #######
# Iniciar swarm en el master
docker swarm init --default-addr-pool 10.254.0.0/16 --default-addr-pool-mask-length 28 --advertise-addr 10.0.16.45

# Borrar red de overlay y crear otra con más direcciones
docker network rm ingress
docker network create --driver overlay --ingress --subnet=10.251.0.0/16 --gateway=10.251.0.1 ingress

# Unirse al swarm como worker
docker swarm join --token SWMTKN-1-15jp451sfyye8hxyt7x10b0m2i513xeecbrbbh1i6hr47g33ys-4xpk129hfes2bq0dg4rezllc2 10.0.16.45:2377 --advertise-addr 10.0.16.46

# Transformar en reachable el nodo worker
docker node promote dock-16-46

# IMPORTANTE #
# La consecuencia inmediata es que con solo dos managers, no hay tolerancia a fallos del manager del
# cluster ya que no se puede elegir a un superviviente con un solo voto. Con 3 managers necesitamos 2
# supervivientes (solo se puede averiar 1) para hacer una elección. Con 4 y 5 managers necesitamos 3
# supervivientes, lo que supone que puedan averiarse 1 y 2 nodos respectivamente.
# Lo que está determinando el número de managers es la tolerancia a fallos de nodos manager en el
# cluster. Debido al algoritmo nos encontramos que tener 3 o 4 managers permite una tolerancia a fallos
# de 1 nodo en ambos casos, mientras que tener 5 o 6 managers tolera el fallo de hasta 2 nodos en
# ambos casos.
# Como puede verse, es más rentable tener 3, 5 o 7 nodos desde el punto de vista de la tolerancia a
# fallos que 4, 6 u 8. En https://docs.docker.com/engine/swarm/admin_guide/ puedes ampliar esto y
# ver una tabla que muestra la relación entre el número de nodos y la tolerancia a fallos.

# Para eliminar un node del swarm
# Se rebaja a worker
# docker node demote dock-16-46
# Se elimina
# docker swarm leave

# Se puede rehacer el swarm con otro nodo
# docker swarm init --default-addr-pool 10.254.0.0/16 --default-addr-pool-mask-length 28 --advertise-addr 10.0.16.45 --force-new-cluster

####### DEFINIR STACK DE APLICACIÓN #######
# En docker-compose.yml se define el stack de la aplicación