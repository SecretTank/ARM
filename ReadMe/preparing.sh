#!/bin/sh
USERNAME=bijan #change bijan to your username
GROUP_NAME=uucp #change to lock if you are runnting arch
chgrp $GROUP_NAME /var/lock/lockdev
chmod g+w /var/lock/lockdev
usermod -a -G $GROUP_NAME $USERNAME
usermod -a -G users $USERNAME
cp "ZPreparing/50-embedded_devices.rules" /etc/udev/rules.d/
cp ZPreparing/gtkterm.desktop /usr/share/applications/
chmod +x /usr/share/applications/gtkterm.desktop
echo "Please reboot to changes take effect"
