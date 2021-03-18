#!/bin/bash

# Parametros
# $1 = Nombre del puente
# $2 = Nombre de la tarjeta de red
# $3 = Nomnre de la tarjeta wifi
# $4 = Nombre de la Conexion Cableada 
echo Parametros
echo 1 -> Nombre del puente
echo 2 -> Nombre de la tarjeta de red
echo 3 -> Nomnre de la tarjeta wifi
echo 4 -> Nombre de la Conexion Cableada
sudo nmcli conn add type bridge con-name $1 ifname $1
sudo nmcli conn add type ethernet slave-type bridge con-name bridge-br0 ifname $2 master $1
sudo nmcli conn up $1
sudo nmcli conn down $4
sudo ifconfig $1 down
sudo brctl delbr $1
sudo ip addr flush dev $2
sudo iw dev $3 set 4addr on
sudo brctl addbr $1 $3 $2
sudo brctl addif $1 $3 $2
sudo ip link set dev $1 up
