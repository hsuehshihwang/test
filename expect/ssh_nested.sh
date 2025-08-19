#!/usr/bin/expect -f
set sshsvr1host "192.168.2.86"
set sshsvr1user "pi"
# set sshsvr1user "root"
set sshsvr1pwd "raspberry"
set sshsvr1pwddelay "500"
set sshsvr2host "192.168.40.1"
set sshsvr2hostdelay "1000"
set sshsvr2user "root"
set sshsvr2pwd "12345"
set sshsvr2pwddelay "500"
set delay -1
# spawn $env(SHELL)
spawn ssh -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null -t ${sshsvr1user}@$sshsvr1host
after 500
expect {
    -re ".*password:.*" {
        send -- "${sshsvr1pwd}\r"
        after $sshsvr1pwddelay
        send -- "echo \"Enter ssh server 1 - (1)\"\r"
        send -- "ssh -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null -t ${sshsvr2user}@$sshsvr2host\r"
        after $sshsvr2hostdelay
        expect {
            -re ".*password:.*" {
                send -- "${sshsvr2pwd}\r"
                after $sshsvr2pwddelay
                send -- "echo \"Enter ssh server 2 - (1)\"\r"
                interact
            }
            -re ".*#.*" {
                send -- "echo \"Enter ssh server 2 - (2)\"\r"
                interact
            }
        }
    }    
    -re ".*#.*" {
        send -- "echo \"Enter ssh server 1 - (2)\"\r"
        send -- "ssh -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null -t ${sshsvr2user}@$sshsvr2host\r"
        after $sshsvr2hostdelay
        expect {
            -re ".*password:.*" {
                send -- "${sshsvr2pwd}\r"
                after $sshsvr2pwddelay
                send -- "echo \"Enter ssh server 2 - (1)\"\r"
                interact
            }
            -re ".*#.*" {
                send -- "echo \"Enter ssh server 2 - (2)\"\r"
                interact
            }
        }
    }    
}        
         
         
