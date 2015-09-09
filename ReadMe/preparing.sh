#!/bin/sh
chgrp lock /var/lock/lockdev
chmod g+w /var/lock/lockdev
usermod -a -G lock bijan #change bijan to your username
cp "ZPreparing/50-embedded_devices.rules" /etc/udev/rules.d/
echo "Please reboot to changes take effect"
