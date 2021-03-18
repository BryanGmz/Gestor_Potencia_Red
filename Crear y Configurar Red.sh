#!/bin/bash

# 1 - nombre de red
# 2 - password
# 3 - nombre de tarjeta wifi

echo param_1 = Nombre de red
echo param_2 = Password
echo param_3 = Nombre de tarjeta wifi
echo Creando Archivo de Configuracion de Red...
touch /etc/hostapd/my-wlan.conf
echo Escribiendo Archivo de Configuracion de Red...
echo "
interfaz = $1
controlador = nl80211
wmm_enabled = 0
ssid = $2
canal = 6
puente = br0
 
# establece el modo de wifi, depende de los dispositivos que utilizará. Puede ser a, b, g, n. Establecer en g asegura la compatibilidad con versiones anteriores.
hw_mode = g
 
#macaddr_acl establece opciones para el filtrado de direcciones mac. 0 significa "aceptar a menos que esté en la lista de denegados"
macaddr_acl = 0
 
# establecer ignore_broadcast_ssid en 1 inhabilitará la transmisión de ssid
ignore_broadcast_ssid = 0
 
#Sets algoritmo de autenticación
# 1 - solo autenticación de sistema abierto
# 2: autenticación de sistema abierto y autenticación de clave compartida
auth_algs = 1
 
###### Establece la autenticación WPA y WPA2 #####
La opción #wpa establece qué implementación de wpa usar
# 1 - solo wpa
# 2 - solo wpa2
# 3 - ambos
wpa = 3
 
# establece la contraseña de wpa requerida por los clientes para autenticarse en la red
wpa_passphrase = $3
 
#sets gestión de claves de wpa
wpa_key_mgmt = WPA-PSK
 
#establece el cifrado utilizado por WPA
wpa_pairwise = TKIP
 
# establece el cifrado utilizado por WPA2
rsn_pairwise = CCMP" >> /etc/hostapd/my-wlan.conf
echo Fin de la Configuracion...
