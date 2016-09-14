#!/bin/sh
USERNAME=`whoami` #change bijan to your username

# for newer systems answer yes
# if you have any error about lock user group change all "lock" to uucp
echo -n "Are you using arch linux [y/n]: "
read answer
if [ $answer == 'y' ]; then
	GROUP_NAME=lock 
else
	GROUP_NAME=uucp
fi

sudo chgrp $GROUP_NAME /var/lock/lockdev
sudo chmod g+w /var/lock/lockdev
sudo usermod -a -G $GROUP_NAME $USERNAME
sudo usermod -a -G users $USERNAME
sudo cp "Resources/50-embedded_devices.rules" /etc/udev/rules.d/
#sudo cp Resources/gtkterm.desktop /usr/share/applications/
#sudo chmod +x /usr/share/applications/gtkterm.desktop

#add Qt color scheme
mkdir ~/.config/QtProject/qtcreator/styles
cp 'Resources/Cobalt.xml' ~/.config/QtProject/qtcreator/styles
chmod 777 ~/.config/QtProject/qtcreator/styles/Cobalt.xml
echo "Please reboot to changes take effect"
