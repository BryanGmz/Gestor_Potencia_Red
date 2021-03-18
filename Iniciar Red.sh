#!/bin/bash

echo Iniciando Red...
echo Configurando...
sudo service NetworkManager stop
sudo nohup hostapd /etc/hostapd/my-wlan.conf &
echo ---------------------Red Inciada------------------------

