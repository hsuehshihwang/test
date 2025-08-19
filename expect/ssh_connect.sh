#!/usr/bin/expect -f
spawn ssh pi@192.168.2.86
after 500
expect -re ".*password:.*"
send -- "raspberry\r"
after 500
send -- "ssh -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null root@192.168.40.1\r"
expect -re ".*password:.*"
send -- "12345\r"
after 500
interact
