#!/bin/sh
USERNAME=bijan #change bijan to your username
GROUP_NAME=uucp #change to lock if you are runnting arch
chgrp $GROUP_NAME /var/lock/lockdev
chmod g+w /var/lock/lockdev
<<<<<<< HEAD
usermod -a -G $GROUP_NAME $USERNAME
usermod -a -G users $USERNAME
=======
usermod -a -G uucp esi #change bijan to your username
>>>>>>> d3ce5cb851ae57c009feb6c140eb89471307b1ff
cp "ZPreparing/50-embedded_devices.rules" /etc/udev/rules.d/
cp ZPreparing/gtkterm.desktop /usr/share/applications/
chmod +x /usr/share/applications/gtkterm.desktop
echo "Please reboot to changes take effect"
#add Qt color scheme
cp 'ZPreparing/Cobalt.xml' '~/.config/QtProject/qtcreator/styles'
chmod 777 '~/.config/QtProject/qtcreator/styles/Cobalt.xml'
