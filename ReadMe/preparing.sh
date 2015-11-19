#!/bin/sh
USERNAME=ahmad #change bijan to your username
GROUP_NAME=uucp #change to lock if you are runnting arch
chgrp $GROUP_NAME /var/lock/lockdev
chmod g+w /var/lock/lockdev
usermod -a -G $GROUP_NAME $USERNAME
usermod -a -G users $USERNAME
cp "ZPreparing/50-embedded_devices.rules" /etc/udev/rules.d/
cp ZPreparing/gtkterm.desktop /usr/share/applications/
chmod +x /usr/share/applications/gtkterm.desktop
#add Qt color scheme
mkdir ~/.config/QtProject/qtcreator/styles
cp 'ZPreparing/Cobalt.xml' ~/.config/QtProject/qtcreator/styles
chmod 777 ~/.config/QtProject/qtcreator/styles/Cobalt.xml
echo "Please reboot to changes take effect"
