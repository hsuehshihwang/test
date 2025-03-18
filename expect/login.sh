#!/bin/bash
echo "please enter your name: "
read -s user
[ "$user" != "ralph" ] && echo "Wrong user!!" && exit 0; 
echo "please enter your password: "
read -s pwd
[ "$pwd" != "12345" ] && echo "Wrong pwd!!" && exit 0; 
echo "login sucessfully!!"

